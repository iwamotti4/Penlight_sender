#include <Adafruit_NeoPixel.h>
String color = "default";
int accel_x = 0;
int accel_y = 0;
int accel_z = 0;

unsigned char buttonState = 0;
const int neopixel = 5;
const int button_a = 6;
const int button_b = 7;
unsigned char switchCount = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, neopixel, NEO_GRB + NEO_KHZ800);

char trans[35]; // 数字（文字列）の送信用配列

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(neopixel, OUTPUT);
  pinMode(button_a, INPUT_PULLUP);
  pinMode(button_b, INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  for (int i = 0; i > 12; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  Serial.println(switchCount);
  switchCount = 0;

}

void loop() {
  // put your main code here, to run repeatedly:

  accel_x = analogRead(A3);
  accel_y = analogRead(A4);
  accel_z = analogRead(A5);

  //ボタン,Neopixel処理------------------------------------------
  buttonState = digitalRead(button_a);

  if (buttonState == HIGH)
  {
    switchCount += 1;
//    Serial.println(color);
    if (switchCount > 11) {
            switchCount = 0;
    }
  }

  //  for(int i=0;i<12;i++){
  //    if(switchCount==0){
  //       strip.setPixelColor(i,strip.Color(255, 0, 0));
  //    }
  //    else if(switchCount==1){
  //       strip.setPixelColor(i,strip.Color(0, 255, 0));
  //    }
  //    else{
  //       strip.setPixelColor(i,strip.Color(0, 0, 255));
  //    }
  //  }

  for (int i = 0; i < 12; i++) {
    switch (switchCount) {
      case 0:
        strip.setPixelColor(i, strip.Color(255, 0, 0));
        color = "red";
        break;
      case 1:
        strip.setPixelColor(i, strip.Color(0, 0, 255));
        color = "blue";
        break;
      case 2:
        strip.setPixelColor(i, strip.Color(255, 255, 255));
        color = "white";
        break;
      case 3:
        strip.setPixelColor(i, strip.Color(0, 0, 0));
        color = "orange";
        break;
      case 4:
        strip.setPixelColor(i, strip.Color(0, 255, 0));
        color = "green";
        break;
      case 5:
        strip.setPixelColor(i, strip.Color(255, 0, 255));
        color = "purple";
        break;
      case 6:
        strip.setPixelColor(i, strip.Color(0, 0, 0));
        color = "light_pink";
        break;
      case 7:
        strip.setPixelColor(i, strip.Color(0, 255, 255));
        color  = "yellow";
        break;
      case 8:
        strip.setPixelColor(i, strip.Color(100, 255, 100));
        color = "light_green";
        break;
      case 9:
        strip.setPixelColor(i, strip.Color(100, 100, 255));
        color = "light_blue";
        break;
      case 10:
        strip.setPixelColor(i, strip.Color(255, 100, 100));
        color =  "pink";
        break;
      case 11:
        strip.setPixelColor(i, strip.Color(255, 100, 255));
        color = "light_purple";
        break;
      default:
        break;
    }
  }


  //  Serial.print(switchCount);
  strip.show();
  //----------------------------------------------------------


  //加速度センサーの処理-----------------------------------------
  char *json = &trans[0];
  sprintf(json, "{\"x\":%d,\"y\":%d,\"z\":%d,\"color\":%x}", accel_x, accel_y, accel_z, switchCount);
  Serial.println(json);
  //----------------------------------------------------------
  delay(200);
}
