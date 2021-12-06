#include "StatementData.h"

typedef void (*C2BAction)(String);
class C2B : public StatementData{// COMMAND DISTANCE AND ANGLE
public:
  static C2BAction action;

  C2B(){
    paramCount = 2;
  }
  String cmd;  
  void resolveStatement(String t){
    action(t);
  }
  String buildStatement(){
    return "C2B,"+cmd;
  }
private:
  static noAction(String){
    Serial.println("Action Must Be Attached to C2B");
  }
};
static C2BAction C2B::action = C2B::noAction;
