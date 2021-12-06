#include <EEPROM.h>
#include <Filters.h>
class ROBOT{
public:

  /// Configuration Variables
  float base_width = 0.655;
  float base_length = 0.77;
  float tire_radius = 0.12;


  /// Runtime Variables
  float w;
  float v;
  float vl;
  float vr;
  float vl_fb;
  float vr_fb;
  float w_fb;
  float r_fb;
  float v_fb_filtered;
  ROBOT(){
    RETRIEVE();  
    velFilter.setAsFilter( LOWPASS_BUTTERWORTH, 10);
    velStatistics.setWindowSecs( 20.0 / 10);
  }
  void STORE(){
    EEPROM.put(300, base_width);
    EEPROM.put(304, base_length);
    EEPROM.put(308, tire_radius);
  }
  void RETRIEVE(){
    EEPROM.get(300, base_width);
    EEPROM.get(304, base_length);
    EEPROM.get(308, tire_radius);
  }
  
  void Compute(){
    w *= PI/ 180; // rad/s
    vr_fb *= tire_radius; // m/s
    vl_fb *= tire_radius; // m/s
    //Serial.println(String(vl_fb)+" , "+String(vr_fb));
    w_fb = (vr_fb - vl_fb) / base_width;
    if(vr_fb != vl_fb){
      r_fb = 0.5*(vr_fb+vl_fb) / (vr_fb-vl_fb);
      v_fb = w_fb*r_fb;
    }
    else{
      v_fb = vr_fb;
    }
    w_fb /= PI / 180;
    if(w != 0){
      vl = w*((v/w)-base_width);// m/s
      vr = w*((v/w)+base_width);// m/s
    }else{
      vl = v;
      vr = v;
    }
        
    vl /= tire_radius; //rad/s
    vr /= tire_radius; //rad/s
    velFilter.input( v_fb );
    velStatistics.input( velFilter.output() );
    v_fb_filtered = velStatistics.mean();    
    
  }
  void print(){
    Serial.println("**ROBOT MODEL");
    Serial.println("Base Width : " + String(base_width));
    Serial.println("Base Length: " + String(base_length));
    Serial.println("Tire Raduis: " + String(tire_radius));
  }
private:
    FilterTwoPole velFilter;                                       // create a two pole Lowpass filter
    RunningStatistics velStatistics;
    float v_fb;

};
