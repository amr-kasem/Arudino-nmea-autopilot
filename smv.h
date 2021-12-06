#include "StatementData.h"

typedef void (*SMVAction)(double);
class SMV : public StatementData{// SET MAXIMUM ROBOT ANGULAR VELOCITY
public:
  static SMVAction action;

  SMV(){
    paramCount = 1;
  }
  double max_vel;  
  void resolveStatement(String t){
    max_vel = t.toDouble();
    action(max_vel);
  }
  String buildStatement(){
    return "SMV,"+String(max_vel);
  }
private:
  static noAction(double){
    Serial.println("Action Must Be Attached to SMV");
  }
};
static SMVAction SMV::action = SMV::noAction;
