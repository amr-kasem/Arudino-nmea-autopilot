#include "StatementData.h"
typedef void (*RFBAction)();
class RFB : public StatementData{ // COMMAND FORCE BREAK
public:
  static RFBAction action;
  
  RFB(){paramCount = 0;}

  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "RFB";
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to RFB");
  }
};
static RFBAction RFB::action = RFB::noAction;
