#include "StatementData.h"

typedef void (*SBMAction)(bool);
class SBM : public StatementData{// SET CONTROLLER MODE
public:
  static SBMAction action;

  SBM(){
    paramCount = 1;
  }
  bool mode;
  void resolveStatement(String t){
    mode = t.toInt() == 1;
    action(mode);
  }
  String buildStatement(){
    if(mode)
      return "SBM,1";
    return "SBM,0";
  }
private:
  static noAction(bool){
    Serial.println("Action Must Be Attached to SBM");
  }
};
static SBMAction SBM::action = SBM::noAction;
