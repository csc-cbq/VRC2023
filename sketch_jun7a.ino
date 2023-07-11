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
  for (int i = 0; i < 10; i++) {

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
  int speed;

  if (ps2x.Button(PSB_L2))  // tương tự như trên kiểm tra nút Lên (L2)
  {
    Serial.print("L2 held this hard UP: ");
    Serial.println(ps2x.Analog(PSAB_L2));  // đọc giá trị analog ở nút
  }
  if (ps2x.Button(PSB_L2) == 0) {
    speed = 4090;
  } else {
    speed = 1000;
  }
  Serial.println(speed);


  if (ps2x.Button(PSB_PAD_UP))  // tương tự như trên kiểm tra nút Lên (PAD UP)
  {
    Serial.print("Up held this hard UP: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP));  // đọc giá trị analog ở nút
  }
  if (ps2x.Button(PSB_CROSS))  // tương tự như trên kiểm tra nút Lên (PAD x)
  {
    Serial.print("CROSS held this hard RIGHT : ");
    Serial.println(ps2x.Analog(PSAB_CROSS));  // đọc giá trị analog ở nút
  }
  if (ps2x.Button(PSB_PAD_DOWN))  // tương tự như trên kiểm tra nút Lên (PAD down)
  {
    Serial.print("Up held this hard DOWN: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN));  // đọc giá trị analog ở nút
  }
  if (ps2x.Button(PSB_TRIANGLE))  // tương tự như trên kiểm tra nút Lên (PAD triangle)
  {
    Serial.print("TRIANGLE held this hard RIGHT : ");
    Serial.println(ps2x.Analog(PSAB_TRIANGLE));  // đọc giá trị analog ở nút
  }

  if (ps2x.Button(PSB_PAD_UP)) {


    pwm.setPWM(12, 0, speed);
    pwm.setPWM(13, 0, 0);
  }
  if (ps2x.Button(PSB_PAD_DOWN)) {


    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, speed);
  }
  if (ps2x.Button(PSB_PAD_UP) == 0 and ps2x.Button(PSB_PAD_DOWN) == 0) {
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, 0);
  }
  if (ps2x.Button(PSB_TRIANGLE)) {


    pwm.setPWM(11, 0, speed);
    pwm.setPWM(10, 0, 0);
  }
  if (ps2x.Button(PSB_CROSS)) {


    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, speed);
  }
  if (ps2x.Button(PSB_TRIANGLE) == 0 and ps2x.Button(PSB_CROSS) == 0) {
    pwm.setPWM(11, 0, 0);
    pwm.setPWM(10, 0, 0);
  }
  if (ps2x.Button(PSB_R2) == 0){
    pwm.setPWM(5, 0, 205);

  } else{
     pwm.setPWM(5, 0, 410);
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