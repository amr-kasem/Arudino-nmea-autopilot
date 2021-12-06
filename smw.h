#include "StatementData.h"

typedef void (*SMWAction)(double);
class SMW : public StatementData{// SET MAXIMUM ROBOT ANGULAR VELOCITY
public:
  static SMWAction action;

  SMW(){
    paramCount = 1;
  }
  double max_ang_vel;  
  void resolveStatement(String t){
    max_ang_vel = t.toDouble();
    action(max_ang_vel);
  }
  String buildStatement(){
    return "SMW,"+String(max_ang_vel);
  }
private:
  static noAction(double){
    Serial.println("Action Must Be Attached to SMW");
  }
};
static SMWAction SMW::action = SMW::noAction;
