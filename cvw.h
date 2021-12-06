#include "StatementData.h"
typedef void (*CVWAction)(double,double);
class CVW : public StatementData{ // COMMAND VELOCITY AND ANGULAR VELOCITY
public:
  CVW(){paramCount = 2;}
  static CVWAction action;
  double velocity;
  double angular_velocity;  
  void resolveStatement(String t){
    byte separator = t.indexOf(',');
    velocity = t.substring(0,separator).toDouble();
    t = t.substring(separator+1);
    angular_velocity = t.toDouble();
    action(velocity,angular_velocity);
  }
  String buildStatement(){
    return "CVW,"+String(velocity)+","+String(angular_velocity);
  }
private:
  static noAction(double x,double y){
    Serial.println("Action Must Be Attached to CFB");
  }
};
static CVWAction CVW::action = CVW::noAction;
