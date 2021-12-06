#include "StatementData.h"

typedef void (*C2DAction)(String);
class C2D : public StatementData{// COMMAND DISTANCE AND ANGLE
public:
  static C2DAction action;

  C2D(){
    paramCount = 2;
  }
  String cmd;  
  void resolveStatement(String t){
    action(t);
  }
  String buildStatement(){
    return "C2D,"+cmd;
  }
private:
  static noAction(String){
    Serial.println("Action Must Be Attached to C2D");
  }
};
static C2DAction C2D::action = C2D::noAction;
