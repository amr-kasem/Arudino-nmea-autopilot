#include "StatementData.h"

typedef void (*JCMAction)(bool);
class JCM : public StatementData{// COMMAND DISTANCE AND ANGLE
public:
  static JCMAction action;

  JCM(){
    paramCount = 1;
  }
  String cmd;  
  void resolveStatement(String t){
    if(t == "0")
      action(false);
    else if(t == "1")
      action(true);
  }
  String buildStatement(){
    return "JCM,"+cmd;
  }
private:
  static noAction(bool){
    Serial.println("Action Must Be Attached to JCM");
  }
};
static JCMAction JCM::action = JCM::noAction;
