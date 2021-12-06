#include "quaternionFilters.h"
#include "MPU9250.h"
#include <Filters.h>


#define I2Cclock 400000
#define I2Cport Wire
#define MPU9250_ADDRESS MPU9250_ADDRESS_AD0  // Use either this line or the next to select which I2C address your device is using

class IMU {
  public:

    double accelerometer[3];
    double rateGyro[3];
    double AHRS[3];
    

    IMU() {
//      myIMU = MPU9250(MPU9250_ADDRESS, I2Cport, I2Cclock);
//      for(int i = 0; i < 9; i++){
//        imuFilters[i].setAsFilter( LOWPASS_BUTTERWORTH, cutoff_F[i/3]);
//        imuStatistics[i].setWindowSecs( 20.0 / cutoff_F[i/3]);
//      }
//
//      Wire.begin();
    }
    void Init() {
//      myIMU.MPU9250SelfTest(myIMU.selfTest);
//      myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);
//      myIMU.initMPU9250();
//      myIMU.initAK8963(myIMU.factoryMagCalibration);
//      myIMU.getAres();
//      myIMU.getGres();
//      myIMU.getMres();
    }
    double Compute() {
//
//      if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
//      {
//        myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values
//        myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes; // - myIMU.accelBias[0];
//        myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes; // - myIMU.accelBias[1];
//        myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes; // - myIMU.accelBias[2];
//
//        myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values
//
//        myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
//        myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
//        myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;
//
//        myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values
//
//        myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes
//                   * myIMU.factoryMagCalibration[0] - myIMU.magBias[0];
//        myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes
//                   * myIMU.factoryMagCalibration[1] - myIMU.magBias[1];
//        myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes
//                   * myIMU.factoryMagCalibration[2] - myIMU.magBias[2];
//      }
//
//      myIMU.updateTime();
//
//      MahonyQuaternionUpdate(myIMU.ax, myIMU.ay, myIMU.az, myIMU.gx * DEG_TO_RAD,
//                             myIMU.gy * DEG_TO_RAD, myIMU.gz * DEG_TO_RAD, myIMU.my,
//                             myIMU.mx, myIMU.mz, myIMU.deltat);
//
//
//
//      myIMU.delt_t = millis() - myIMU.count;
//
//      // update LCD once per half-second independent of read rate
//      if (myIMU.delt_t > 10)
//      {
//
//        myIMU.yaw   = atan2(2.0f * (*(getQ() + 1) * *(getQ() + 2) + *getQ()
//                                    * *(getQ() + 3)), *getQ() * *getQ() + * (getQ() + 1)
//                            * *(getQ() + 1) - * (getQ() + 2) * *(getQ() + 2) - * (getQ() + 3)
//                            * *(getQ() + 3));
//        myIMU.pitch = -asin(2.0f * (*(getQ() + 1) * *(getQ() + 3) - *getQ()
//                                    * *(getQ() + 2)));
//        myIMU.roll  = atan2(2.0f * (*getQ() * *(getQ() + 1) + * (getQ() + 2)
//                                    * *(getQ() + 3)), *getQ() * *getQ() - * (getQ() + 1)
//                            * *(getQ() + 1) - * (getQ() + 2) * *(getQ() + 2) + * (getQ() + 3)
//                            * *(getQ() + 3));
//        myIMU.pitch *= RAD_TO_DEG;
//        myIMU.yaw   *= RAD_TO_DEG;
//
//        myIMU.yaw  -= 8.5;
//        myIMU.roll *= RAD_TO_DEG;
//
//        // update the test value statistics
//
//        // update the two pole Lowpass filter, and statistics
//
//        /*imuFilters[0].input( myIMU.ax );
//        imuStatistics[0].input( imuFilters[0].output() );
//        imuFilters[1].input( myIMU.ay );
//        imuStatistics[1].input( imuFilters[1].output() );
//        imuFilters[2].input( myIMU.az );
//        imuStatistics[2].input( imuFilters[2].output() );
//        imuFilters[3].input( myIMU.gx );
//        imuStatistics[3].input( imuFilters[3].output() );
//        imuFilters[4].input( myIMU.gy );
//        imuStatistics[4].input( imuFilters[4].output() );
//        imuFilters[5].input( myIMU.gz );
//        imuStatistics[5].input( imuFilters[5].output() );
//        imuFilters[6].input( myIMU.roll );
//        imuStatistics[6].input( imuFilters[6].output() );
//        imuFilters[7].input( myIMU.pitch );
//        imuStatistics[7].input( imuFilters[7].output() );*/
//        imuFilters[8].input( myIMU.yaw );
//        imuStatistics[8].input( imuFilters[8].output() );
//        //Serial.println(-myIMU.gz);
//        myIMU.count = millis();
//        myIMU.sumCount = 0;
//        myIMU.sum = 0;
////        accelerometer[0] = imuStatistics[0].mean();
////        accelerometer[1] = imuStatistics[1].mean();
////        accelerometer[2] = imuStatistics[2].mean();
////        rateGyro[0] = imuStatistics[3].mean();
////        rateGyro[1] = imuStatistics[4].mean();
//        rateGyro[2] = -myIMU.gz;//imuStatistics[5].mean();
////        AHRS[0] = imuStatistics[6].mean();
////        AHRS[1] = imuStatistics[7].mean();
        Serial3.println("?EO [3]");
        Serial3.flush();
        Serial.flush();
        if(Serial3.available()){
          String t = Serial3.readString();
          byte separator = t.substring(1).indexOf('?');
          t = t.substring(0,separator);
          separator = t.indexOf('=');
          AHRS[2] = t.substring(separator+1).toInt()/1000.0;
//          Serial.println(AHRS[2]);/
        }
//      }/
    }
  private:
//    MPU9250 myIMU;
//    float windowLength = 20;
//    FilterTwoPole imuFilters[9];                                       // create a two pole Lowpass filter
//    RunningStatistics imuStatistics[9];
//    float cutoff_F[3]={100,50,10};
};
