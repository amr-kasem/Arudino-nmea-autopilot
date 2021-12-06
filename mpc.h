#include "StatementData.h"
typedef void (*MPCAction)();
class MPC : public StatementData{ // MAINTENANCE SAVE CONFIGURATION
public:
  static MPCAction action;
  
  MPC(){paramCount = 0;}

  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "MPC";
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to MPC");
  }
};
static MPCAction MPC::action = MPC::noAction;
