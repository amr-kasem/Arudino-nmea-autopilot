#include "StatementData.h"
typedef void (*ACKAction)();
class ACK : public StatementData{ // MAINTENANCE RETRIVE CONFIGURATION
public:
  static ACKAction action;
  
  ACK(){paramCount = 0;}

  void resolveStatement(String t){
    action();
  }
  String buildStatement(){
    return "ACK,0";
  }
private:
  static noAction(){
    Serial.println("Action Must Be Attached to ACK");
  }
};
static ACKAction ACK::action = ACK::noAction;
