#include <Wire.h>

float prevX = 1, prevY = 1, prevZ = 1; 
bool state; 
byte rc;
void setup() {
  // put your setup code here, to run once:
  Wire.beginTransmission(104);
  Wire.write(107);
  Wire.write(0);
  rc = Wire.endTransmission(true);
  Wire.beginTransmission(104);
  Wire.write(28);
  Wire.write(2 << 3);
  rc = Wire.endTransmission(true);
  // Serial.begin(9600);
  pinMode(13, OUTPUT);
  // Serial.print("Setup complete");
  state = false;
}

void loop() {
  Wire.beginTransmission(104); 
  // Serial.print("start");
 Wire.write(59);
//  Serial.print("port");
 // follower address 104 for MPU6050
 // follower register 59 for acc. in x
  rc=Wire.endTransmission(false);// transmit register
  // Serial.print("transmit");
  Wire.requestFrom(104,6,true); // start listening for 6 bytes
  // Serial.print("action listener"); 
  int16_t xHigh=Wire.read();
  // read data from follower
  int16_t xLow =Wire.read();
  int16_t x = xHigh << 8 | xLow;
  float xf = x * 9.81/4096;
  int16_t yHigh=Wire.read();
  int16_t yLow=Wire.read();
  int16_t y = yHigh << 8 | yLow;
  float yf = y * 9.81/4096;
  int16_t zHigh=Wire.read();
  int16_t zLow=Wire.read();
  int16_t z = zHigh << 8 | zLow;
  float zf = z * -9.81/4096;
  if (zf < 0) {
    state = false;
    // Serial.println("up");
  }
  if (zf > 0 && state == false) {
    digitalWrite(13, HIGH);  
    state = true;
    // Serial.println("Down");
  } //else {
  //   digitalWrite(13, LOW);
  // } upside down check

  if (((((prevX < 0) != (xf<0)) && abs(xf) > 3)) || (((prevY<0) != (yf<0)) && abs(yf) > 3) || (((prevZ<0) != (zf<0)) && abs(zf) > 15)) {
    digitalWrite(13, LOW);
    // Serial.println("Shook");  
  }
  prevX = xf;
  prevY = yf; 
  prevZ = zf;
  // Serial.println("x: " + String(xf));
  // Serial.println("y: " + String(yf));
  // Serial.println("z: " + String(zf));
  delay(10);
}
