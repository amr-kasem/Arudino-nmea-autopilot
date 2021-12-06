#include "StatementData.h"
#include "cvw.h"
#include "cda.h"
#include "cfb.h"
#include "scg.h"
#include "scm.h"
#include "smv.h"
#include "smw.h"
#include "msc.h"
#include "mrc.h"
#include "mpc.h"
#include "ack.h"
#include "rfb.h"
#include "c2d.h"
#include "c2b.h"
#include "wtm.h"
#include "sod.h"
#include "sba.h"
#include "JCM.h"
#include "hsf.h"
#include "hsr.h"
#include "hsm.h"
#include "sbm.h"
class Statement{
public:
  String TalkerID = "--";
  String StatementID = "---";
  StatementData* Data;
  void setStatementID(String id){
    StatementID = id;
//    Serial.println(id);
    if(id == "CVW")
      Data = new CVW(); 
    else if(id == "CDA")
      Data = new CDA(); 
    else if(id == "CFB")
      Data = new CFB();
    else if(id == "SCG")
      Data = new SCG();
    else if(id == "SCM")
      Data = new SCM();
    else if(id == "SMV")
      Data = new SMV();
    else if(id == "SMW")
      Data = new SMW();
    else if(id == "MSC")
      Data = new MSC();
    else if(id == "MRC")
      Data = new MRC();
    else if(id == "MPC")
      Data = new MPC();
    else if(id == "RFB")
      Data = new RFB();
    else if(id == "C2D")
      Data = new C2D();
    else if(id == "C2B")
      Data = new C2B();
    else if(id == "WTM")
      Data = new WTM();
    else if(id == "SOD")
      Data = new SOD();
    else if(id == "SBA")
      Data = new SBA();
    else if(id == "JCM")
      Data = new JCM();
    else if(id == "HSF")
      Data = new HSF();
    else if(id == "HSR")
      Data = new HSR();
    else if(id == "HSM")
      Data = new HSM();
    else if(id == "SBM")
      Data = new SBM();
    else 
      return;
    Data -> TalkerID = &TalkerID;
  }
  ~Statement(){
    delete Data;
  }
};
