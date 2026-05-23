#include <Wire.h>
#include <MPU6050.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
MPU6050 mpu;

int16_t ax, ay, az;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  mpu.initialize();
  mpu.setI2CBypassEnabled(true);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected ✅");
  } else {
    Serial.println("MPU6050 Failed ❌");
  }

  SerialBT.begin("SmartHelmet");
}

void loop() {

  mpu.getAcceleration(&ax, &ay, &az);

  int totalAcc = abs(ax) + abs(ay) + abs(az);

  Serial.println(totalAcc);

  if (totalAcc > 30000) {
    Serial.println("🚨 ACCIDENT DETECTED");
    SerialBT.println("ACCIDENT");
    delay(5000);
  }

  delay(200);
}