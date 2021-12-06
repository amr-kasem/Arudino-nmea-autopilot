#include "StatementData.h"

typedef void (*SBAAction)(int,String);
class SBA : public StatementData{// SET MAXIMUM ROBOT ANGULAR VELOCITY
public:
  static SBAAction action;

  SBA(){
    paramCount = 1;
  }
  int angle;  
  void resolveStatement(String t){
    angle = t.toDouble();
    action(angle,*TalkerID);
  }
  String buildStatement(){
    return "SBA,"+String(angle);
  }
private:
  static noAction(int,String){
    Serial.println("Action Must Be Attached to SBA");
  }
};
static SBAAction SBA::action = SBA::noAction;
