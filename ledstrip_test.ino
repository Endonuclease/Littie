#include <FastLED.h>

#define NUM_LEDS 37             // LED灯珠数量
#define DATA_PIN 9              // Arduino输出控制信号引脚
#define LED_TYPE SK6812         // LED灯带型号
#define COLOR_ORDER GRB         // RGB灯珠中红色、绿色、蓝色LED的排列顺序
int analogPin = A0;
int pm = 0;
int color;
uint8_t max_bright = 3;       // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高

CRGB leds[NUM_LEDS];            // 建立光带leds



  

void setup() {
  Serial.begin(9600);
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // 初始化光带
  FastLED.setBrightness(max_bright);                            // 设置光带亮度
}

void loop() {

  pm = analogRead(analogPin);
 // Serial.println(pm);
  color = pm / 3.93;
  Serial.println(color);
  fill_palette (leds, 37, color, 0, RainbowColors_p, 255, LINEARBLEND );
  FastLED.show();
  delay(10);


}
