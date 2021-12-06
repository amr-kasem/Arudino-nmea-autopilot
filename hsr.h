#include "StatementData.h"

typedef void (*HSRAction)();
class HSR : public StatementData{// COMMAND DISTANCE AND ANGLE
public:
  static HSRAction action;

  HSR(){
    paramCount = 1;
  }
  String cmd;  
  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "HSR,"+cmd;
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to HSR");
  }
};
static HSRAction HSR::action = HSR::noAction;
