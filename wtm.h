#include "StatementData.h"

typedef void (*WTMAction)(bool);
class WTM : public StatementData{// SET CONTROLLER MODE
public:
  static WTMAction action;

  WTM(){
    paramCount = 1;
  }
  bool mode;
  void resolveStatement(String t){
    mode = t.toInt() == 1;
    action(mode);
  }
  String buildStatement(){
    if(mode)
      return "WTM,1";
    return "WTM,0";
  }
private:
  static noAction(bool){
    Serial.println("Action Must Be Attached to WTM");
  }
};
static WTMAction WTM::action = WTM::noAction;
