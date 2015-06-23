// #include<Wire.h>
// const int MPU[2]={0x68,0x69};  // I2C address of the MPU-6050
// // int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
// void setup(){
//   Wire.begin();
  
//   initMPU6050(MPU[0]);
//   initMPU6050(MPU[1]);
  
//   Serial.begin(9600);
// }
// void loop(){
//   Wire.beginTransmission(MPU[0]);
//   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//   Wire.endTransmission(false);
//   Wire.requestFrom(MPU[0],14,true);  // request a total of 14 registers
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // a_x
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // a_y
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // a_z
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // t
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // r_x
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // r_y
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // r_z
  
//   Wire.beginTransmission(MPU[1]);
//   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//   Wire.endTransmission(false);
//   Wire.requestFrom(MPU[1],14,true);  // request a total of 14 registers
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // a_x
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // a_y
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // a_z
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // t
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // r_x
//   Serial.print(Wire.read()<<8|Wire.read());Serial.print(" "); // r_y
//   Serial.print(Wire.read()<<8|Wire.read());Serial.println("");// r_x

//   // AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
//   // AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//   // AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//   // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//   // GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//   // GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//   // GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
//   // Serial.println("---MPU[0]");
//   // Serial.print("AcX = "); Serial.print(AcX);
//   // Serial.print(" | AcY = "); Serial.print(AcY);
//   // Serial.print(" | AcZ = "); Serial.print(AcZ);
//   // Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//   // Serial.print(" | GyX = "); Serial.print(GyX);
//   // Serial.print(" | GyY = "); Serial.print(GyY);
//   // Serial.print(" | GyZ = "); Serial.println(GyZ);
//   // AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
//   // AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//   // AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//   // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//   // GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//   // GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//   // GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)  
  
//   // Serial.println("---MPU[1]");
//   // Serial.print("AcX = "); Serial.print(AcX);
//   // Serial.print(" | AcY = "); Serial.print(AcY);
//   // Serial.print(" | AcZ = "); Serial.print(AcZ);
//   // Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//   // Serial.print(" | GyX = "); Serial.print(GyX);
//   // Serial.print(" | GyY = "); Serial.print(GyY);
//   // Serial.print(" | GyZ = "); Serial.println(GyZ);
//   delay(50);
// }

// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU[2]={0x68,0x69};  // I2C address of the MPU-6050
int16_t AcX[2] = {0,0},
        AcY[2] = {0,0},
        AcZ[2] = {0,0},
        Tmp[2] = {0,0},
        GyX[2] = {0,0},
        GyY[2] = {0,0},
        GyZ[2] = {0,0};
void setup(){
  Wire.begin();
  initMPU6050(MPU[0]);
  initMPU6050(MPU[1]);
  Serial.begin(9600);
}
void loop(){
  while (!Serial) {
    // wait for serial port to connect. Needed for Leonardo only
  }
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

  Wire.beginTransmission(MPU[1]);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU[1],14,true);  // request a total of 14 registers
  AcX[1]=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY[1]=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ[1]=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp[1]=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX[1]=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY[1]=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ[1]=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Serial.print(AcX[0]/17000.0);Serial.print(",");
  Serial.print(AcY[0]/17000.0);Serial.print(",");
  Serial.print(AcZ[0]/17000.0);Serial.print(",");
  // Serial.print(Tmp[0]/340.00+36.53);Serial.print(",");
  Serial.print(GyX[0]);Serial.print(",");
  Serial.print(GyY[0]);Serial.print(",");
  Serial.print(GyZ[0]);Serial.print(",");

  Serial.print(AcX[1]/17000.0);Serial.print(",");
  Serial.print(AcY[1]/17000.0);Serial.print(",");
  Serial.print(AcZ[1]/17000.0);Serial.print(",");
  // Serial.print(Tmp[1]/340.00+36.53);Serial.print(",");
  Serial.print(GyX[1]);Serial.print(",");
  Serial.print(GyY[1]);Serial.print(",");
  Serial.print(GyZ[1]);Serial.println("");
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