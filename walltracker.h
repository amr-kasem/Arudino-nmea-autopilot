#include <math.h>
#include <EEPROM.h>


class WallTracker{
public:
  float current_distance;
  float current_yaw;
  float distance_setpoint = 1500;
  float yaw_setpoint;
  float front,rear;
  WallTracker(){
    RETRIEVE();
  }  
  void STORE(){
    EEPROM.put(401, distance_setpoint);
  }
  void RETRIEVE(){
    EEPROM.get(401, distance_setpoint);
  }
  
  void Compute(){
//   if(Serial1.available()){
//     x = Serial1.readString();
//     front = x.substring(0,x.indexOf(',')).toFloat();
//     rear = x.substring(x.indexOf(',')+1).toFloat();
//   }
    if(front != 0 && front < 400)
      df = front;
    else
      yaw_setpoint = 0;
    
    if(rear != 0 && rear < 400)
      dr = rear;
    else
      yaw_setpoint = 0;
    current_yaw = atan2(dr-df,925);
    current_distance = ((df+dr)/2)*cos(current_yaw);
    current_yaw *= 180/PI;
    yaw_setpoint = atan2(current_distance-distance_setpoint,max_converge_distance)*180/PI;
  }
private:
  float df;
  float dr;
  float max_converge_distance = 4000;
  String x;
};
