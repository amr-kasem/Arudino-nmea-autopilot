#include <PID_v1.h>
#include <EEPROM.h>

class AUTOPILOT{
public :

  //Configuration Variables
  byte FLAGS = 0b00000011; // 0 -> is_position_control; 1 -> is_closed_loop_control
  float max_angular_velocity = 30;
  float max_velocity = 1;
  float start_converge_time = 5;
  // 0 -> distance , 1 -> yaw , 2 -> velocity, 3 -> angular velocity
  double controller_gains[4][3] = {{0,0,0},{0.5,0,0},{0.5,0,0},{0.5,0,0}};
  //////////////////////////////////////////

  //runtime variables
  float estimated_time_for_distance = start_converge_time;
  float estimated_time_for_yaw = start_converge_time;
  double current_distance;
  double current_yaw;
  double current_velocity;
  double current_angular_velocity;

  double distance_setpoint;
  double yaw_setpoint;
  double velocity_setpoint;
  double angular_velocity_setpoint = 0;
  
  double distance_output;
  double yaw_output;
  double velocity_output;
  double angular_velocity_output;

  HardwareSerial* LogPort;
  ///////////////////////////////
  
  AUTOPILOT(){
    RETRIEVE();
    distance_controller = new PID(&current_distance,&distance_output, &distance_setpoint,controller_gains[0][0], controller_gains[0][1],controller_gains[0][2], DIRECT);
    yaw_controller = new PID(&current_yaw,&yaw_output, &yaw_setpoint_fake,controller_gains[1][0], controller_gains[1][1],controller_gains[1][2], DIRECT);
    velocity_controller = new PID(&current_velocity,&velocity_output, &velocity_setpoint,controller_gains[2][0], controller_gains[2][1],controller_gains[2][2], DIRECT);
    angular_velocity_controller = new PID(&current_angular_velocity,&angular_velocity_output, &angular_velocity_setpoint,controller_gains[3][0], controller_gains[3][1],controller_gains[3][2], DIRECT);
    distance_controller->SetMode(AUTOMATIC);
    yaw_controller->SetMode(AUTOMATIC);
    velocity_controller->SetMode(AUTOMATIC);
    angular_velocity_controller->SetMode(AUTOMATIC);
    distance_controller->SetOutputLimits(-255,255);
    yaw_controller->SetOutputLimits(-255,255);
    velocity_controller->SetOutputLimits(-2,2);
    angular_velocity_controller->SetOutputLimits(-30,30);
  }
  ~AUTOPILOT(){
    delete distance_controller;
    delete yaw_controller;
    delete velocity_controller;
    delete angular_velocity_controller;
  }
  STORE(){
    EEPROM.put(100, controller_gains);
    EEPROM.put(196, FLAGS);
    EEPROM.put(197, max_angular_velocity);
    EEPROM.put(201, max_velocity);
    EEPROM.put(205, start_converge_time);

  }
  RETRIEVE(){
    EEPROM.get(100, controller_gains);
    EEPROM.get(196, FLAGS);
    EEPROM.get(197, max_angular_velocity);
    EEPROM.get(201, max_velocity);
    EEPROM.get(205, start_converge_time);
  }


  //commands area
  void cmd_vel(double v, double w){
    velocity_setpoint = v;
    angular_velocity_setpoint = w;
  }
  void cmd_epsi(double d,double h){
    distance_setpoint = d;
    yaw_setpoint = h;
    estimated_time_for_distance = fabs((distance_setpoint-current_distance)/max_velocity);
    estimated_time_for_yaw = fabs((yaw_setpoint-current_yaw)/max_angular_velocity);
    if(estimated_time_for_yaw == 0) estimated_time_for_yaw = 0.2;
    if(estimated_time_for_distance == 0) estimated_time_for_distance = 0.2;
  }
  void cmd_CFB(){
    velocity_setpoint = 0;
    angular_velocity_setpoint = 0;
  }
  void cmd_SCG(byte controllerID,double p,double i,double d){
      controller_gains[controllerID][0] = p;
      controller_gains[controllerID][1] = i;
      controller_gains[controllerID][2] = d;
      distance_controller->SetTunings(controller_gains[0][0], controller_gains[0][1],controller_gains[0][2]);
      yaw_controller->SetTunings(controller_gains[1][0], controller_gains[1][1],controller_gains[1][2]);
      velocity_controller->SetTunings(controller_gains[2][0], controller_gains[2][1],controller_gains[2][2]);
      angular_velocity_controller->SetTunings(controller_gains[3][0], controller_gains[3][1],controller_gains[3][2]);
      print();
      delay(5000);
  }
  void cmd_SCM(bool Mode){
    bitWrite(FLAGS,0,Mode);
  }
  void cmd_SMV(double m_v){
    max_velocity = m_v;
  }
  void cmd_SMW(double m_w){
    max_angular_velocity = m_w;
  }    
   
  void print(){
    Serial.print("**Controller Mode : ");
    if(bitRead(FLAGS,0))      Serial.println("position control mode");
    else                      Serial.println("Velocity control mode"); 
    Serial.println("**Controller Gains");
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 3; j++){
        Serial.print(controller_gains[i][j]);
        Serial.print(",");
      }
      Serial.println();
    }
    Serial.println("**Controller Constants");
    Serial.println("Maximum Velocity: " + String(max_velocity));
    Serial.println("Maximum Angular Velocity: " + String(max_angular_velocity));
    Serial.println("Startup Converge Time: " + String(start_converge_time));
  } 

  
  void Compute(){
    distance_controller->Compute();
    yaw_controller->Compute();
    if(bitRead(FLAGS,0)){// is_position_control
      if(distance_setpoint == 1){
        angular_velocity_setpoint = (yaw_output)/estimated_time_for_yaw;
        velocity_setpoint = 1.5;
      }
      else if(distance_setpoint == -1){
        angular_velocity_setpoint = (yaw_output)/estimated_time_for_yaw;
        velocity_setpoint = -1.5;
      }
      else{
        
        angular_velocity_setpoint = 0;
        velocity_setpoint = 0;
      }
//      Serial.println(/);
      //velocity_setpoint = (distance_output)/estimated_time_for_distance;
      velocity_controller->Compute();
      angular_velocity_controller->Compute();
    }else{
      velocity_controller->Compute();
      angular_velocity_output = angular_velocity_setpoint;
    }
    
    unsigned long c = millis();
    if( c - Timer > 100){
      if(estimated_time_for_distance > 0.1)
        estimated_time_for_distance -= 0.01;
      if(estimated_time_for_yaw > 0.1)
        estimated_time_for_yaw -= 0.01;
      Timer = c;
    }
//    Serial2.print(current_yaw);
//    Serial2.print(',');
//    Serial2.println(yaw_setpoint);
  } 
  void setCurrentYaw(double yaw){
    current_yaw  = yaw -  yaw_setpoint;
    if (current_yaw > 180)
          current_yaw -= 360;
    if (current_yaw < -180)
          current_yaw += 360;
          
  }
private:
  PID* distance_controller;
  PID* yaw_controller;
  PID* velocity_controller;
  PID* angular_velocity_controller;
  unsigned long Timer;
  double yaw_setpoint_fake = 0;
};
