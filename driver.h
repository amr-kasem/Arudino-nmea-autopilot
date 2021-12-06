#include <Filters.h>
class Driver{
public:
  HardwareSerial * ComPort;
  Driver(){
      for(int i = 0; i < 2; i++){
        velFilters[i].setAsFilter( LOWPASS_BUTTERWORTH, 80);
        velStatistics[i].setWindowSecs( 20.0 / 80);
      }
  }
  float vl;
  float vr;
  float vl_fb;
  float vr_fb;
  void Compute(){
    vl *= 9.549297;  // rad/s -> rpm
    vr *= 9.549297;
    //vl = 100;
    //vr = 50;
    unsigned long t = millis()-Timer;
    int x = (int)(vl/0.305);
    int y = (int)(vr/0.305);
    if (t > 1){
      Serial2.print("!M "+String((vl+vr)/2)+" "+String((vl-vr)/2)+"\r");
  //    Serial2.flush();
      Serial2.print("?BS\r");
      Serial2.flush();
      
      if(Serial2.available()){
        String S = Serial2.readString();
  
        vl_fb_t = S.substring(S.indexOf('=')+1,S.indexOf(':')).toInt()*0.305;// rpm
        vr_fb_t = S.substring(S.indexOf(':')+1).toInt()*0.305;               // rpm
        vl_fb_t /= 9.549297; // rad/s
        vr_fb_t /= 9.549297; // rad/s
  
        //Serial.println(S);
        
        //Serial.print(String(vl_fb_t)+" , "+ String(vr_fb_t)+ " , " );
        velFilters[0].input( vl_fb_t );
        velStatistics[0].input( velFilters[0].output() );
        velFilters[1].input( vr_fb_t );
        velStatistics[1].input( velFilters[1].output() );
        vl_fb = velStatistics[0].mean();      
        vr_fb = velStatistics[1].mean();
        //Serial.println(String(vl_fb)+" , "+ String(vr_fb));
        Timer = millis();
      }

    }
  }
  void ESC(){
    Serial2.print("!EX\r");
    Serial2.flush();
    delay(3000);
  }
  void RES(){
    delay(1000);
    Serial2.print("!MG\r");
    Serial2.flush();
  }
  void CMD(String t){
    Serial2.print(t+'\r');
    Serial2.flush();
//    while(!Serial2.available()){
//    }
//    String x = Serial2.readString();
//    x = "$APC2D," + x.trim() +"*FF\r\n";
//    Serial.print(x);
  }

private:
    FilterTwoPole velFilters[2];                                       // create a two pole Lowpass filter
    RunningStatistics velStatistics[2];
    float vl_fb_t;
    float vr_fb_t;
    unsigned long Timer = 0;
};
