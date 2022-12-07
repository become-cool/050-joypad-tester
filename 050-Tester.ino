#include <Wire.h>


#define led_I 20
#define led_I_up 18
#define led_I_down 16
#define led_I_left 14
#define led_I_right 13
#define led_I_select 11
#define led_I_start 9
#define led_I_b 7
#define led_I_a 5

#define led_II 21
#define led_II_up 19
#define led_II_down 17
#define led_II_left 15
#define led_II_right 12
#define led_II_select 10
#define led_II_start 8
#define led_II_b 6
#define led_II_a 4

#define BTN_JOY 0
#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 3
#define BTN_RIGHT 4
#define BTN_SELECT 5
#define BTN_START 6
#define BTN_B 7
#define BTN_A 8


#define BIT_UP 0x1
#define BIT_DOWN 0x2
#define BIT_LEFT 0x4
#define BIT_RIGHT 0x8
#define BIT_A 0x10
#define BIT_B 0x20
#define BIT_START 0x40
#define BIT_SELECT 0x80

uint8_t pins[] = {
  led_I,
  led_I_up,
  led_I_down,
  led_I_left,
  led_I_right,
  led_I_select,
  led_I_start,
  led_I_b,
  led_I_a,
  
  led_II,
  led_II_up,
  led_II_down,
  led_II_left,
  led_II_right,
  led_II_select,
  led_II_start,
  led_II_b,
  led_II_a,
} ;


uint8_t joy_I_pins[] = {
  led_I,
  led_I_up,
  led_I_down,
  led_I_left,
  led_I_right,
  led_I_select,
  led_I_start,
  led_I_b,
  led_I_a,
} ;
uint8_t joy_II_pins[] = {
  led_II,
  led_II_up,
  led_II_down,
  led_II_left,
  led_II_right,
  led_II_select,
  led_II_start,
  led_II_b,
  led_II_a,
} ;

void setup() {
  
  Serial.begin(115200) ;

  for(int i=0;i<sizeof(pins);i++){
    Serial.println(pins[i]) ;
    
    pinMode(pins[i], OUTPUT) ;
    
    digitalWrite(pins[i], 0) ;
    delay(50) ;
    digitalWrite(pins[i], 1) ;
  }

  Wire.begin(2,3);   // arduino uno: sda A4, scl A5
  
}

#define READ_BTN(btn) if( byte&BIT_##btn ) {\
      digitalWrite(btns[BTN_##btn], 0) ; \
    } \
    Serial.print(" "#btn">") ; \
    Serial.print(byte) ; \
    Serial.print("&") ; \
    Serial.print(BIT_##btn) ; \
    Serial.print("=") ; \
    Serial.print(byte&BIT_##btn) ;

void read_joy(uint8_t addr, uint8_t * btns) {

  for(int i=0;i<sizeof(joy_I_pins);i++){
    digitalWrite(btns[i], 1) ;
  }
    
  byte error ;
  
  Wire.beginTransmission(addr);
  error = Wire.endTransmission();
  if (error != 0) {
    return ;
  }

  digitalWrite(btns[BTN_JOY], 0) ;

  Wire.requestFrom(addr, 1) ;
  uint8_t byte = Wire.read() ;
  
  Serial.print(byte) ;

  READ_BTN(UP)
  READ_BTN(DOWN)
  READ_BTN(LEFT)
  READ_BTN(RIGHT)
  READ_BTN(A)
  READ_BTN(B)
  READ_BTN(START)
  READ_BTN(SELECT)


  Serial.println(" ") ;
}

void loop() {
  
  read_joy(51, joy_I_pins) ;
  read_joy(52, joy_II_pins) ;

  delay(10) ;
}
