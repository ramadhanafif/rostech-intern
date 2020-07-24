// Date and time functions using a DS1302 RTC

#include <RTClib.h>

#define RST PB10
#define DAT PB1
#define CLK PB11

/*******************************************
 * RTC OBJECT INITIALIZATION FOR BLUE PILL *
 * RST ------------ PB10                   *
 * DAT ------------ PB1                    *
 * CLK ------------ PB11                   *
 *                                         *
 * DS1302 rtc(RST, CLK, DAT);              *
 *******************************************/

DS1302 rtc(RST, CLK, DAT);

// buffer for DateTime.tostr
char buf[20];

void setup() {
  Serial.begin(9600);
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  DateTime now = rtc.now();

  Serial.println(now.tostr(buf));
  Serial.println();
  delay(100);
}
