#include "StatementData.h"

typedef void (*SCGAction)(byte,double,double,double);
class SCG : public StatementData{// SET CONTROLLER MODE 
public:
  static SCGAction action;

  SCG(){
    paramCount = 4;
  }
  byte controller;
  double p;
  double i; 
  double d; 
  void resolveStatement(String t){
    byte separator = t.indexOf(',');
    controller = t.substring(0,separator).toInt();
    t = t.substring(separator+1);
    separator = t.indexOf(',');
    p = t.substring(0,separator).toDouble();
    t = t.substring(separator+1);
    separator = t.indexOf(',');
    i = t.substring(0,separator).toDouble();
    t = t.substring(separator+1);
    //separator = t.indexOf(',');
    //d = t.substring(0,separator).toDouble();
    d = t.toDouble();
    action(controller,p,i,d);
  }
  String buildStatement(){
    return "SCG,"+String(controller)+","+String(p)+","+String(i)+","+String(d);
  }
private:
  static noAction(byte, double, double, double){
    Serial.println("Action Must Be Attached to SCG");
  }
};
static SCGAction SCG::action = SCG::noAction;
