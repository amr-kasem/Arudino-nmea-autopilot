#include "StatementData.h"
typedef void (*MSCAction)();
class MSC : public StatementData{ // MAINTENANCE STORE CONFIGURATION
public:
  static MSCAction action;
  
  MSC(){paramCount = 0;}

  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "MSC";
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to MSC");
  }
};
static MSCAction MSC::action = MSC::noAction;
