#include "StatementData.h"
typedef void (*MRCAction)();
class MRC : public StatementData{ // MAINTENANCE RETRIVE CONFIGURATION
public:
  static MRCAction action;
  
  MRC(){paramCount = 0;}

  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "MRC";
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to MRC");
  }
};
static MRCAction MRC::action = MRC::noAction;
