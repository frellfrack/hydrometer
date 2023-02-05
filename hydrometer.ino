#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const char DEGREE_SYMBOL[] = { 0xB0, '\0' };


//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(0x3C, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


Adafruit_BME280 bme; 
void u8g2_prepare(void) {
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_9x18B_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Wire.begin();
  bme.begin(0x76);
  u8g2.begin();
  
  u8g2_prepare();
}


void printValues() 
{

    char str[80];
    char buff[7];
    char buff2[7];
    float temp = bme.readTemperature();
    float hum = bme.readHumidity();

    
    sprintf(str, "Temperature:%s,Humidity:%s", dtostrf(temp,4,2,buff),dtostrf(hum,4,2,buff2));
    
    Serial.println(str);
 
    u8g2.clearBuffer(); // clear the internal memory

    sprintf(str, "%s C", buff);    
    u8g2.drawStr(32,9, str);
    u8g2.drawUTF8(82,6
    , DEGREE_SYMBOL);

    u8g2.drawFrame(1,1,127,63);
    u8g2.drawLine(0,32, 128,32);

    sprintf(str, "%s%%", buff2);
    u8g2.drawStr(35,42,str);
    u8g2.sendBuffer();
}  

void loop() {
  printValues();
  delay(1000);
}
