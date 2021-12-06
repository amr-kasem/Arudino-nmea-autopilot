#include "StatementData.h"

typedef void (*HSFAction)();
class HSF : public StatementData{// COMMAND DISTANCE AND ANGLE
public:
  static HSFAction action;

  HSF(){
    paramCount = 0;
  }
  String cmd;  
  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "HSF,"+cmd;
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to HSF");
  }
};
static HSFAction HSF::action = HSF::noAction;
