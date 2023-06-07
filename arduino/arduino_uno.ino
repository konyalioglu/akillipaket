
#include <Servo.h>


Servo ESC1;
Servo ESC2;


uint8_t pwm1 = 0;
uint8_t pwm2 = 0;

uint8_t pwm1_prev = 0;
uint8_t pwm2_prev = 0;

uint8_t max_pwm_rate = 5;


uint8_t rx_status = 0;
byte rx_temp;


char buf[4];

uint8_t killswitch = 0;

volatile int pwm_value = 0;
volatile int prev_time = 0;
 


void setup() {

  ESC1.attach(3, 1000, 2000);
  ESC2.attach(5, 1000, 2000);
  
  Serial.begin(19200);

  ESC1.write(pwm1);
  ESC2.write(pwm2);

  attachInterrupt(0, rising, RISING);
  
  delay(10000);
  
}

void loop() {

  if (Serial.available() > 0) {
    rx_temp = Serial.read();

    if (rx_temp == 0xff && rx_status == 0) {
      buf[0] = rx_temp;
      rx_status += 1;
    }
    else if ( rx_status > 0 && rx_status < 3 ){
      buf[rx_status] = rx_temp;
      rx_status += 1;
    }
    else if ( rx_status == 3  && rx_temp == 0xfc ){
      buf[rx_status] = rx_temp;
      rx_status = 0;
      pwm1 = buf[1];
      pwm2 = buf[2];

    }
    else {
      rx_status = 0;
    }
  }

  if (killswitch) {
    ESC1.write(0);
    ESC2.write(0);
  
    pwm1_prev = pwm1;
    pwm2_prev = pwm2;
  }

  else {
    ESC1.write(pwm1);
    ESC2.write(pwm2);
  
    pwm1_prev = pwm1;
    pwm2_prev = pwm2;
  }
  
}


void rising() {
  attachInterrupt(0, falling, FALLING);
  prev_time = micros();
}
 
void falling() {
  attachInterrupt(0, rising, RISING);
  pwm_value = micros()-prev_time;
  if ( pwm_value > 1500 ){
    killswitch = 1;
  }
  else{
    killswitch = 0;
  }
  //Serial.println(pwm_value);
}
