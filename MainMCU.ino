#include "NMEA.h"
#include "IMU.h"
#include "Autopilot.h"
#include "RobotModel.h"
#include "odometery.h"
#include "driver.h"
#include "walltracker.h"
#include "base.h"
int blind_time = 100;
String inputSentence = "";
HardwareSerial* StationPort;
HardwareSerial* LogPort;
NMEA nmea_h;
WallTracker* tracker;
IMU imu = IMU();
AUTOPILOT AP;
ROBOT R;
ODOMETERY odom;
Driver D;
BASE B;
bool hit_read = false;
bool WTMMode = false;
bool joyMode = false;
bool responsiveBaseMode = false;
int hit_count = 0;
int max_hit_count = 6;
void setup() {
  pinMode(5, OUTPUT);
  pinMode(2, INPUT_PULLUP);
//  mpu./Init();
  nmea_h.debug_on = true;
  nmea_h.verboseDebug = false;
  

  //Serial Debugger
  Serial.begin(115200);
  Serial.setTimeout(3);
  Serial3.begin(115200);
  Serial3.setTimeout(3);
  Serial2.begin(115200);
  Serial2.setTimeout(3);
  Serial1.begin(115200);
  Serial1.setTimeout(3);
  AP.RETRIEVE();
  odom.Init();
  Serial.println("Restarting");
  delay(1000);
  tracker = new WallTracker();
  // initializing firing actions
  CVW::action = [](double v, double w){if(!joyMode) AP.cmd_vel(v,w);};
  CDA::action = [](double d, double h){if(!joyMode) AP.cmd_epsi(d,imu.AHRS[2]-h);};
  CFB::action = [](){AP.cmd_CFB();D.ESC();};
  RFB::action = [](){D.RES();};
  C2D::action = [](String t){D.CMD(t);};
  C2B::action = [](String t){B.CMD(t);};
  MSC::action = [](){AP.STORE();R.STORE();tracker->STORE();};
  MRC::action = [](){AP.RETRIEVE();R.RETRIEVE();tracker->RETRIEVE();};
  MPC::action = [](){AP.print();R.print();};
  SCG::action = [](byte c, double p, double i, double d){AP.cmd_SCG(c,p,i,d);};
  SCM::action = [](bool Mode){AP.cmd_SCM(Mode);};
  WTM::action = [](bool Mode){WTMMode = Mode;};
  SMV::action = [](double max_v){AP.cmd_SMV(max_v);};
  SMW::action = [](double max_w){AP.cmd_SMW(max_w);};
  SOD::action = [](double offset){tracker->distance_setpoint = offset;};
  SBA::action = [](int angle,String TI){if(!joyMode ^ TI == "JS"){B.SBA(angle);}}; //$JSSBA,600*FF
  JCM::action = [](bool joy){
                              joyMode = joy;
                              if(joyMode)D.CMD("^CPRI 1 1_^CPRI 2 0");
                              else   D.CMD("^CPRI 1 0_^CPRI 2 1");
                            }; ///////////////////////////////////////
  HSF::action = hit; //$JSSBA,600*FF
  HSR::action = [](){hit_count = 0;B.SBA(150);};
  HSM::action = [](int a){max_hit_count = a;};
  SBM::action = [](bool b){responsiveBaseMode = b;};
  hit_count = 0;
  attachInterrupt(digitalPinToInterrupt(2), hit, CHANGE);
}

void loop() {
  imu.Compute();
  AP.setCurrentYaw(imu.AHRS[2]); // yaw relative to wall tracked
  CommandingThread();
  AP.Compute();
  R.v = AP.velocity_output;
  R.w = AP.angular_velocity_output;
  R.Compute();
    OneSecondStatus();
  D.vl = R.vl;
  D.vr = R.vr;
  D.Compute();
  R.vl_fb = D.vl_fb;
  R.vr_fb = D.vr_fb;
  odom.velocity = R.v_fb_filtered;
  AP.current_velocity = R.v_fb_filtered;
  AP.current_angular_velocity = R.w_fb;// mpu.rateGyro[2]; //  deg/s  //
  odom.angular_velocity = R.w_fb;
  odom.Compute();
  AP.current_distance = odom.X;
  if(WTMMode)
    //AP.yaw_setpoint = tracker->yaw_setpoint;
    AP.cmd_epsi(AP.distance_setpoint,tracker->yaw_setpoint);
  else
    AP.cmd_epsi(AP.distance_setpoint,AP.yaw_setpoint);
//  else()/
  B.Compute();
  hit_calculate();
  Serial.flush();
  Serial1.flush();

  
  
  
  
  Serial2.flush();
  Serial3.flush();
}
void CommandingThread(){
  // Serial Communication
  if(Serial.available()){
    nmea_h.sentence = Serial.readString();
    if(nmea_h.validate()){
      Statement *command = nmea_h.parseStatement();
      //Serial.print("$APACK,0*FF\r\n");

      delete command;
    }
  }
  if(Serial1.available()){
    nmea_h.sentence = Serial1.readString();
    if(nmea_h.validate()){
      Statement *command = nmea_h.parseStatement();
      //Serial.print("$APACK,0*FF\r\n");

      delete command;
      
    }
    //Serial.println(nmea_h.sentence);
  }
  Serial3.println("?EO [3]");
  if(Serial3.available()){
    Serial.println(Serial3.readString());
//    if(nmea_h.validate()){q
//      Statement *command = nmea_h.parseStatement();
//      //Serial.print("$APACK,0*FF\r\n");
//
//      delete command;
//      
//    }
    //Serial.println(nmea_h.sentence);
  }
  
}
void ControlOutputThread(double a, double b){
  //
  
}
void OneSecondStatus(){
  static unsigned long Timer;
  if(millis() - Timer > 100)
  {
//      tracker->/Compute();

    //Serial2.println("Working");
//    Serial.println(String(tracker->current_distance)+","+String(tracker->current_yaw * 10));/
    Serial.print(String(AP.yaw_setpoint)+","+String(AP.yaw_output)+",");
    Serial.print(String(AP.angular_velocity_setpoint)+","+String(AP.angular_velocity_output)+",");
    Serial.print(String(R.vl)+","+String(R.vr)+",");
    Serial.println(String(AP.distance_setpoint)+","+String(AP.current_distance));
  
//    Serial.print("$APUSF,"+String(tracker->current_distance)+","+String(tracker->dis tance_setpoint)+",");
//    Serial.print(String(AP.yaw_setpoint*10)+","+String(AP.current_yaw*10)+"*FF\r\n");
//    Serial.flush();
//    Serial.print("$APHSC,");
//    Serial.print(hit_count);
//    Serial.print("*FF\r\n");
//    Serial.flush();
  
//    if(joyMode)/
    //Serial2.print("?C\r");
    //Serial2.flush();
    //Serial.print(String(tracker->current_distance)+","+String(tracker->distance_setpoint)+",");
    //Serial.println(String(AP.yaw_setpoint*10)+","+String(AP.current_yaw*10));
    Timer = millis(); 
  }
}
void hit_calculate(){
  static unsigned long Timer_;
  if(millis() - Timer_ > blind_time)
  {
    hit_read = false;
    Timer_ = millis(); 
  }
    
}

void hit()
{
  if(!hit_read){
    if(responsiveBaseMode && !joyMode)
    {
      if(hit_count >= max_hit_count);
        B.SBA(785);
    }
    hit_count++;    
  }else{
    //Serial.println("Hit ignored");
  }
  hit_read = true;
}
