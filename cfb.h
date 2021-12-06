#include "StatementData.h"
typedef void (*CFBAction)();
class CFB : public StatementData{ // COMMAND FORCE BREAK
public:
  static CFBAction action;
  
  CFB(){paramCount = 0;}

  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "CFB";
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to CFB");
  }
};
static CFBAction CFB::action = CFB::noAction;
