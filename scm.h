#include "StatementData.h"

typedef void (*SCMAction)(bool);
class SCM : public StatementData{// SET CONTROLLER MODE
public:
  static SCMAction action;

  SCM(){
    paramCount = 1;
  }
  bool mode;
  void resolveStatement(String t){
    mode = t.toInt() == 1;
    action(mode);
  }
  String buildStatement(){
    if(mode)
      return "SCM,1";
    return "SCM,0";
  }
private:
  static noAction(bool){
    Serial.println("Action Must Be Attached to SCM");
  }
};
static SCMAction SCM::action = SCM::noAction;
