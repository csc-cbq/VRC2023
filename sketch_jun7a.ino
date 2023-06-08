#include <PS2X_lib.h>
#include <Wire.h> //thư viện I2c của Arduino, do PCA9685 sử dụng chuẩn giao tiếp i2c nên thư viện này bắt buộc phải khai báo 
#include <Adafruit_PWMServoDriver.h> // thư viện PCA9685
#define PS2_DAT 12 // MISO  19
#define PS2_CMD 13 // MOSI  23
#define PS2_SEL 15 // SS     5
#define PS2_CLK 14 // SLK   18
#define pressures false
#define rumble false

PS2X ps2x;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();





void setup() {
 Serial.begin(115200);

//Kết nối với tay cầm bằng hàm ps2x.config_gamepad, thử kết nối lại trong vòng 10 lần nếu quá 10 lần không kết nối được với tay cầm thì sẽ dừng lại

int error = -1; 
for (int i = 0; i < 10; i++) 
{
  delay(1000); 
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble); 
  Serial.print("."); 
  if(!error) 
	break;
} 
pwm.begin(); //khởi tạo PCA9685 
pwm.setOscillatorFrequency(27000000); // cài đặt tần số dao động 
pwm.setPWMFreq(50);
Wire.setClock(400000);
}
void loop() {
  ps2x.read_gamepad(false, false); 
  Serial.print("Stick Values:"); 
  Serial.print(ps2x.Analog(PSS_LY)); 
  Serial.print(","); 
  Serial.print("Stick Values:"); 
  Serial.print(ps2x.Analog(PSS_RY));
  Serial.print("\n");
  float speed;
  int sp;
  const int spd_max = 2048;
  if(ps2x.Analog(PSS_LY) >= 140){
    float speed = (double)(ps2x.Analog(PSS_LY)-128)/128;
    sp = speed*spd_max;
    pwm.setPWM(11,0,sp-5);
    pwm.setPWM(10 ,0, 0);


  } else if (ps2x.Analog(PSS_LY) <=121)
  { 
    float speed = (double)abs(ps2x.Analog(PSS_LY)-128)/128;
    sp = speed*spd_max;
    pwm.setPWM(11,0,0);
    pwm.setPWM(10 ,0, sp-5);

   
  } else{
    pwm.setPWM(11,0,0);
    pwm.setPWM(10 ,0, 0);
  }
  if(ps2x.Analog(PSS_RY)>= 140){
    

     float speed = (double)(ps2x.Analog(PSS_RY)-128)/128;
    sp = speed*spd_max;
    pwm.setPWM(14,0,sp-5);
    pwm.setPWM(15 ,0, 0);


  } else if (ps2x.Analog(PSS_RY) <=121)
  {


     float speed = (double)abs(ps2x.Analog(PSS_RY)-128)/128;
    sp = speed*spd_max;
    pwm.setPWM(14,0,0);
    pwm.setPWM(15 ,0, sp-5);
  } else{
     
    pwm.setPWM(14,0,0);
    pwm.setPWM(15 ,0, 0);
  }


}
