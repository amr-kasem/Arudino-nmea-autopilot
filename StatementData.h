#ifndef StatementDataFLAG
#define StatementDataFLAG
class StatementData{
public:
  byte paramCount;
  String* TalkerID;
  virtual void resolveStatement(String);
  virtual String buildStatement();
};
#endif
