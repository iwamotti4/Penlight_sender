#include <Adafruit_NeoPixel.h>
#define ID 0
#define NEOPIXEL 5
#define button_A 6
#define button_B 7

#define LED 10

//加速度
int accel_x = 0;
int accel_y = 0;
int accel_z = 0;

//振り判定
int shaked = 0;

//一時保存
int spped_log = 0;

//ボタンの状態
unsigned char buttonStateA = 0;
unsigned char buttonStateB = 0;
unsigned char backState = 0;

//スイッチのカウント数
unsigned char switchCount = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, NEOPIXEL, NEO_GRB + NEO_KHZ800);

char trans[50]; // 数字（文字列）の送信用配列

void setup() {
  Serial.begin(115200);
  pinMode(NEOPIXEL, OUTPUT);
  pinMode(button_A, INPUT_PULLUP);
  pinMode(button_B, INPUT_PULLUP);
  neopixelColorBegin(LED);
  switchCount = 0;
}

void loop() {
  accel_x = analogRead(A0);
  accel_y = analogRead(A1);
  accel_z = analogRead(A2);

  //振り判定------------------------------------------
  int s = shake(accel_x,accel_y,accel_z);
  if(s > 900 || s < 800){
    shaked = 1;
  }
  else {
    shaked = 0;
  }

  //ボタン処理------------------------------------------
  buttonStateA = digitalRead(button_A);
  buttonStateB = digitalRead(button_B);

  if (buttonStateA == 0)
  {
    switchCount += 1;
    if (switchCount > 9) {
            switchCount = 0;
    }
  }
  if (buttonStateB == 0)
  {
    if (switchCount == 0 ) {
            switchCount = 10;
    }
    switchCount -= 1;
  }
  //--------------------------------------------------
  neopixelColorChange(switchCount,LED);
  
  //加速度センサーの処理-----------------------------------------
  char *json = &trans[0];
  sprintf(json, "{\"id\":%d,\"x\":%d,\"y\":%d,\"z\":%d,\"color\":%d,\"shake\":%d}", ID, accel_x, accel_y, accel_z, switchCount,shaked);
  int spped = (accel_x + accel_y + accel_z)/3;
    Serial.println(json);
    spped_log = spped;
  delay(200);
}

void neopixelColorBegin(int led){
  strip.begin();
  for (int i = 0; i > led; i--) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void neopixelColorChange(int count,int led){
  char color ="default";
  for (int i = 0; i < led; i++) {
    switch (count) {
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
        strip.setPixelColor(i, strip.Color(255, 165, 0));
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
        strip.setPixelColor(i, strip.Color(255, 100, 100));
        color = "light_pink";
        break;
      case 7:
        strip.setPixelColor(i, strip.Color(255, 255, 0));
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
        strip.setPixelColor(i, strip.Color(255, 50, 50));
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
strip.show();
}

float shake(int x,int y,int z){
  return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

