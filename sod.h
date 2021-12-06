#include "StatementData.h"

typedef void (*SODAction)(double);
class SOD : public StatementData{// SET MAXIMUM ROBOT ANGULAR VELOCITY
public:
  static SODAction action;

  SOD(){
    paramCount = 1;
  }
  double offsetDistance;  
  void resolveStatement(String t){
    offsetDistance = t.toDouble();
    action(offsetDistance);
  }
  String buildStatement(){
    return "SOD,"+String(offsetDistance);
  }
private:
  static noAction(double){
    Serial.println("Action Must Be Attached to SOD");
  }
};
static SODAction SOD::action = SOD::noAction;
