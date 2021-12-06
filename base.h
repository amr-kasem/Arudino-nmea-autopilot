#include <PID_v1.h>
#define PIN_INPUT A15
#define PIN_OUTPUT 4
#include <Filters.h>
int sensorPin = A15;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

class BASE {
  private:
    double Setpoint, Input, Output;
    int real_output;
    bool dir = false;
    //Specify the links and initial tuning parameters
    double Kp = 10.3, Ki = 0.0065, Kd = 0.963;
    PID* myPID;

    float testFrequency = 20;                     // test signal frequency (Hz)

    float windowLength = 20.0 / testFrequency;   // how long to average the signal, for statistist
    FilterTwoPole filterTwoLowpass;                                       // create a two pole Lowpass filter
    RunningStatistics filterTwoLowpassStats;
  public :
    //int angle = 0;
    BASE() {

      Input = analogRead(PIN_INPUT);
      Setpoint = 370;
      myPID = new PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
      //turn the PID on
      myPID->SetMode(AUTOMATIC);
      myPID->SetOutputLimits(-255, 255);
      filterTwoLowpass.setAsFilter( LOWPASS_BUTTERWORTH, testFrequency );
      filterTwoLowpassStats.setWindowSecs( windowLength );
    };
    void CMD(String t) {

    }
    Compute() {
      sensorValue = analogRead(sensorPin);
      filterTwoLowpass.input( sensorValue );
      filterTwoLowpassStats.input( filterTwoLowpass.output() );
      Input = (int)filterTwoLowpassStats.mean();
//      Serial.print(Setpoint);
//      Serial.print(",");
//      Serial.print(Input);
//      Serial.print(",");

      if (abs(Setpoint - Input ) < 3 )
        Input = Setpoint;

      myPID->Compute();


      if (abs(Output ) < 2)
        Output = 0;
//            Serial.println(Output);/

      analogWrite(PIN_OUTPUT, abs(Output));
      if (Output > 0)
        dir = true;
      if (Output < 0)
        dir = false;
      digitalWrite(5, dir);
//      Serial.println(Input);/
//      Serial.print(",");
//      Serial.println(Setpoint);
    }
    void SBA(int a) {
      Setpoint = a;
    }
};
