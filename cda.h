#include "StatementData.h"

typedef void (*CDAAction)(double,double);
class CDA : public StatementData{// COMMAND DISTANCE AND ANGLE
public:
  static CDAAction action;

  CDA(){
    paramCount = 2;
  }
  double distance;
  double theta;  
  void resolveStatement(String t){
    byte separator = t.indexOf(',');
    distance = t.substring(0,separator).toDouble();
    t = t.substring(separator+1);
    theta = t.toDouble();
    action(distance,theta);
  }
  String buildStatement(){
    return "CDA,"+String(distance)+","+String(theta);
  }
private:
  static noAction(double x,double y){
    Serial.println("Action Must Be Attached to CDA");
  }
};
static CDAAction CDA::action = CDA::noAction;
