#include "StatementData.h"

typedef void (*HSMAction)(int);
class HSM : public StatementData{// SET CONTROLLER MODE
public:
  static HSMAction action;

  HSM(){
    paramCount = 1;
  }
  int mode;
  void resolveStatement(String t){
    mode = t.toInt();
    action(mode);
  }
  String buildStatement(){
      return "HSM,"+String(mode);
  }
private:
  static noAction(int){
    Serial.println("Action Must Be Attached to HSM");
  }
};
static HSMAction HSM::action = HSM::noAction;
