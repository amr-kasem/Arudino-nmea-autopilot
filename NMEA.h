#include "Statement.h";
class NMEA{
public :
  bool debug_on = true;
  bool verboseDebug = false;

  String sentence;
  HardwareSerial* LogPort;
  bool validate(){
    int len = sentence.length();
    if(sentence[0] == '$' && sentence[len-1]=='\n'&& sentence[len-2]=='\r'&& sentence[len-5]=='*'){
      String chksm = sentence.substring(len-4);
      chksm.toUpperCase(); 

      // Verbose Debugging
      if(verboseDebug) Serial.println("Trying to Validate");
      
      if(checksum(sentence.substring(1,len-5).c_str())== Hex2Byte(chksm.c_str()))
        {
          if(verboseDebug)Serial.println("Message Validated");
          return true;
        }
        return true; // kma kont checksum
      //DEBUGGER INFO
      if(debug_on)Serial.println("checksum should be " + Byte2Hex(checksum(sentence.substring(1,len-5).c_str())));
        
    }
    return false;
  } 
  
  Statement* parseStatement(){ // Convert Sentence to Statement object
    Statement* s = new Statement;
    int len = sentence.length();
    String t = sentence.substring(1,len-5);
    s->TalkerID = t.substring(0,2);
    t = t.substring(2);
    s->setStatementID(t.substring(0,3));
    t = t.substring(4);
    s->Data -> resolveStatement(t);
    
    return s;
  }

  String constructNMEA(Statement *s){
    String t = "AP"+s->Data->buildStatement();
    t = "$"+t+"*"+Byte2Hex(checksum(t.c_str()));
    return t;
  }
private:
  byte checksum(const char *s) {
    byte c = 0;
    while (*s)
        c ^= *s++;
    return c;
  }
  byte Hex2Byte(const char*h){
    byte dL = 0b00000000;
    byte dH = 0b00000000;
    dL = (int)h[1];
    dL -= isDigit(h[1]) ? 48 : 55;
    dH = (int)h[0];
    dH -= isDigit(h[0]) ? 48 : 55;
    return dL+(dH<<4);
  }
  String Byte2Hex(byte b){
    byte dL = 0b00001111 & b;
    byte dH = ((0b11110000 & b)>>4);
    if (dL > 9) dL += 55; else dL += 48;
    if (dH > 9) dH += 55; else dH += 48;
    String h = "__";
    h[0] = dH;
    h[1] = dL;
    return(h);
  }
};
