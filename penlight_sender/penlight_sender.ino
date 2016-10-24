#include <Adafruit_NeoPixel.h>
int count = 0;
String color = "G";
int accel_x = 0;
int accel_y = 0;
int accel_z = 0;
int swit = 0;
String sent ="";

int buttonState = 0; 
const int button_a = 6;
const int button_b = 7;
const int neopixel = 5;
int switchCount = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, neopixel, NEO_GRB + NEO_KHZ800);

char trans[25]; // 数字（文字列）の送信用配列
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  pinMode(neopixel, OUTPUT);
  pinMode(button_a, INPUT_PULLUP);
  pinMode(button_b, INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for(int i=0;i>12;i--){
        strip.setPixelColor(i,strip.Color(0, 0, 0));
  }
  strip.show();
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
    switchCount++;
    if(switchCount > 2){
       switchCount = 0;
    }
  }
  
  for(int i=0;i<12;i++){
    if(switchCount==0){
       strip.setPixelColor(i,strip.Color(255, 0, 0));
    }
    else if(switchCount==1){
       strip.setPixelColor(i,strip.Color(0, 255, 0));
    }
    else{
       strip.setPixelColor(i,strip.Color(0, 0, 255));
    }
  }
//  Serial.print(switchCount);
  strip.show();
//----------------------------------------------------------


//加速度センサーの処理-----------------------------------------
//  if(accel_x>10){//default:y 400
//    digitalWrite(6,LOW);
//    Serial.print(accel_x,HEX);
//    Serial.print(',');
//    Serial.print(accel_y,HEX);
//    Serial.print(',');
//    Serial.print(accel_z,HEX);
//    Serial.print('X');
//    sendAccelData(1,accel_x);
//    sendAccelData(2,accel_y);
//    sendAccelData(3,accel_z);
 char *json = &trans[0];
 sprintf(json, "{\"x\":%d,\"y\":%d,\"z\":%d}", accel_x, accel_y,accel_z);
 Serial.println(json);



//    Serial.println(sent);    
//    if(swit == 1){
      if(accel_x>400){
//        Serial.print(sent);
//        Serial.println("G");
//        Serial.println("Shake!");
        sent = "";
      }
      else if(sent.length()>350){
//        Serial.print(sent);
//        Serial.println("R");
        sent = "";
      }
    swit = 0;
//    }
//  }
//  else{
//    digitalWrite(6,HIGH);
//    Serial.print("|");
//    sent += "|";
//    swit = 1;
//  }
//----------------------------------------------------------
delay(500);
}

void sendAccelData(int header,int value){
  //加速度軸の判定＋ヘッダの送信
  switch(header){
    case 1:
      Serial.write('X');
      break;
    case 2:
      Serial.write('Y');
      break;
    case 3:
      Serial.write('Z');
      break;
    default:
//      print("Error input Data");
      break;
  }
  //下位バイト、上位バイトの送信
    Serial.write(lowByte(value));
    Serial.write(highByte(value));
}

