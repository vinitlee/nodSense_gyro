#include<Wire.h>
// Addresses
const int MPU[2]={0x68,0x69};

// Storage
int16_t AcX[2] = {0,0},
        AcY[2] = {0,0},
        AcZ[2] = {0,0},
        
        Tmp[2] = {0,0},
        
        GyX[2] = {0,0},
        GyY[2] = {0,0},
        GyZ[2] = {0,0};

float   GyE[2] = {0.,0.},
        GyS[2] = {0.,0.},
        GyN[2] = {0.,0.};

// History
// I only made one because by this time only one channel was
// necessary; feel free to double it up yo.
float   HsE[14] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.},
        HsS[14] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.},
        HsN[14] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
// Time keeper
int t = 0;

void setup() {
  Wire.begin();
  initMPU6050(MPU[0]);
  // initMPU6050(MPU[1]);
  Serial.begin(9600);
}
void loop() {
  while (!Serial) {
    // wait for serial port to connect
  }

  // Collect Data

  // Channel A
  Wire.beginTransmission(MPU[0]);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU[0],14,true);  // request a total of 14 registers
  AcX[0]=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY[0]=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ[0]=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp[0]=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX[0]=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY[0]=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ[0]=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // // Channel B
  // Wire.beginTransmission(MPU[1]);
  // Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  // Wire.endTransmission(false);
  // Wire.requestFrom(MPU[1],14,true);  // request a total of 14 registers
  // AcX[1]=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  // AcY[1]=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  // AcZ[1]=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  // Tmp[1]=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  // GyX[1]=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  // GyY[1]=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  // GyZ[1]=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // Basis Change
  // -0.6225    0.6437   -0.4470
  //  0.5554    0.7651    0.3284
  // -0.5295    0.0753    0.8459
  GyE[0] = -0.6225*GyX[0] + 0.6437*GyY[0] - 0.4470*GyZ[0];
  GyS[0] =  0.5554*GyX[0] + 0.7651*GyY[0] + 0.3284*GyZ[0];
  GyN[0] = -0.5295*GyX[0] + 0.0753*GyY[0] + 0.8459*GyZ[0];

  // // -0.7414    0.4631    0.4861
  // //  0.5076    0.8606   -0.0458
  // //  0.4492   -0.1961    0.8719
  // GyE[1] = -0.7414*GyX[1] + 0.4631*GyY[1] + 0.4861*GyZ[1];
  // GyS[1] =  0.5076*GyX[1] + 0.8606*GyY[1] - 0.0458*GyZ[1];
  // GyN[1] =  0.4492*GyX[1] - 0.1961*GyY[1] + 0.8719*GyZ[1];

  // Write to History
  HsE[t] = GyE[0]/100;
  HsS[t] = GyS[0]/100;
  HsN[t] = GyN[0]/100;
  t = (t+1) % 14;

  // Calculate Energy of Window
  // and Communicate
  int power = 0;
  for(int i=0; i<10; i++){
      power += HsE[i] * HsE[i];
  }
  Serial.print(power);Serial.print(",");
  power = 0;
  for(int i=0; i<10; i++){
      power += HsS[i] * HsS[i];
  }
  Serial.print(power);Serial.print(",");
  power = 0;
  for(int i=0; i<10; i++){
      power += HsN[i] * HsN[i];
  }
  Serial.print(power);Serial.println("");
  // Serial.print("[");
  // for(int i=0; i<10; i++){
  //   Serial.print(HsS[i]);
  //   Serial.print(",");
  // }
  // Serial.print("]");
  // Serial.println("");

  delay(50);
}
void initMPU6050(int address) {
  Wire.beginTransmission(address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(10);
  Wire.beginTransmission(address);
  Wire.write(0x1B);
  Wire.write(B00001000);
  Wire.endTransmission(true);
}