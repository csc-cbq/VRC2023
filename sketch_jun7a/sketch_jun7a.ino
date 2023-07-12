#include <PS2X_lib.h>
#include <Wire.h>                     //thư viện I2c của Arduino, do PCA9685 sử dụng chuẩn giao tiếp i2c nên thư viện này bắt buộc phải khai báo
#include <Adafruit_PWMServoDriver.h>  // thư viện PCA9685
#define PS2_DAT 12                    // MISO  19
#define PS2_CMD 13                    // MOSI  23
#define PS2_SEL 15                    // SS     5
#define PS2_CLK 14                    // SLK   18
#define pressures false
#define rumble false

PS2X ps2x;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(115200);

  //Kết nối với tay cầm bằng hàm ps2x.config_gamepad, thử kết nối lại trong vòng 10 lần nếu quá 10 lần không kết nối được với tay cầm thì sẽ dừng lại

  int error = -1;
  for (int i = 0; i < 100; i++) {

    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    Serial.print(".");
    delay(500);
    if (!error)
      break;
  }
  pwm.begin();                           //khởi tạo PCA9685
  pwm.setOscillatorFrequency(27000000);  // cài đặt tần số dao động
  pwm.setPWMFreq(50);
  Wire.setClock(400000);

  pwm.setPWM(8, 0, 0);
  pwm.setPWM(9, 0, 0);
  pwm.setPWM(10, 0, 0);
  pwm.setPWM(11, 0, 0);
  pwm.setPWM(12, 0, 0);
  pwm.setPWM(13, 0, 0);
  pwm.setPWM(14, 0, 0);
  pwm.setPWM(15, 0, 0);
}
void loop() {
  ps2x.read_gamepad(false, false);
  int speed = 1200;
  if (ps2x.Button(PSB_L2)) {
    speed = 400;
  }
  Serial.println(speed);

  if (ps2x.Button(PSB_PAD_UP)) {


    pwm.setPWM(12, 0, speed);
    pwm.setPWM(13, 0, 0);
    pwm.setPWM(11, 0, speed);
    pwm.setPWM(10, 0, 0);
  }
  if (ps2x.Button(PSB_PAD_DOWN)) {


    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, speed);
     pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, speed);
  }
  if (ps2x.Button(PSB_PAD_UP) == 0 and ps2x.Button(PSB_PAD_DOWN) == 0) {
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, 0);
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, 0);
  }
  if (ps2x.Button(PSB_SQUARE) == 0){
    pwm.writeMicroseconds(5, 2000);
    

  } else{
    pwm.writeMicroseconds(5, 1500);
  }

  
  if (ps2x.Button(PSB_R2)) {


    pwm.setPWM(14, 0, 400);
    pwm.setPWM(15, 0, 0);
  } else{
    pwm.setPWM(14, 0, 0);
    pwm.setPWM(15, 0, 300);
  }
  if(ps2x.Button(PSB_PAD_RIGHT)){
    pwm.setPWM(12, 0, speed);
    pwm.setPWM(13, 0, 0);
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, speed);
  }
  if(ps2x.Button(PSB_PAD_LEFT)){
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, speed);
    pwm.setPWM(11, 0, speed);
    pwm.setPWM(10, 0, 0);
  }
  if (ps2x.Button(PSB_CIRCLE)) {
    pwm.setPWM(14, 0, 0);
    pwm.setPWM(15, 0, 2000);
  }


}

// #include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>

// Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();  // Create a PCA9685 object

// void setup() {
//   pca.begin();         // Initialize the PCA9685 module
//   pca.setPWMFreq(50);  // Set the PWM frequency (usually 50Hz for servos)
//   pca.writeMicroseconds(5, 1000); // rotate 1000 for 180 degree // rotate 2000 for 90 degree
// }

// void loop() {
//   // Set servo position to 90 degrees
// }