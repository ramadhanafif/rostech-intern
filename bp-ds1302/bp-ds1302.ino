#include <stdio.h>
#include <DS1302.h>

#define YEAR ((((__TIMESTAMP__ [20] - '0') * 10 \
                + (__TIMESTAMP__ [21] - '0')) * 10 \
               + (__TIMESTAMP__ [22] - '0')) * 10 \
              + (__TIMESTAMP__ [23] - '0'))

#define MONTH ((__TIMESTAMP__ [6] == 'n' ? 0 \
               : __TIMESTAMP__ [6] == 'b' ? 1 \
               : __TIMESTAMP__ [6] == 'r' ? (__TIMESTAMP__ [0] == 'M' ? 2 : 3) \
               : __TIMESTAMP__ [6] == 'y' ? 4 \
               : __TIMESTAMP__ [6] == 'n' ? 5 \
               : __TIMESTAMP__ [6] == 'l' ? 6 \
               : __TIMESTAMP__ [6] == 'g' ? 7 \
               : __TIMESTAMP__ [6] == 'p' ? 8 \
               : __TIMESTAMP__ [6] == 't' ? 9 \
               : __TIMESTAMP__ [6] == 'v' ? 10 : 11)+1)

#define DAY_OF_WEEK (__TIMESTAMP__ [2] == 'e' ? 3 \
               : __TIMESTAMP__ [2] == 'd' ? 4 \
               : __TIMESTAMP__ [2] == 'n' ? (__TIMESTAMP__ [0] == 'M' ? 2 : 1) \
               : __TIMESTAMP__ [2] == 'u' ? 5 \
               : __TIMESTAMP__ [2] == 'i' ? 6 : 7 )

#define DAY ((__TIMESTAMP__ [8] - '0') * 10 + (__TIMESTAMP__ [9] - '0'))

#define HRS (__TIMESTAMP__ [11] - '0') *10 + (__TIMESTAMP__ [12] - '0')

#define MIN (__TIMESTAMP__ [14] - '0') *10 + (__TIMESTAMP__ [15] - '0')

#define SEC (__TIMESTAMP__ [17] - '0') *10 + (__TIMESTAMP__ [18] - '0')

namespace {

// Set the appropriate digital I/O pin connections. These are the pin
// assignments for the Arduino as well for as the DS1302 chip. See the DS1302
// datasheet:
//
//   http://datasheets.maximintegrated.com/en/ds/DS1302.pdf
//const int kCePin   = 2;  // Chip Enable
//const int kIoPin   = 4;  // Input/Output
//const int kSclkPin = 5;  // Serial1 Clock

const int kCePin   = PB11;  // Chip Enable
const int kIoPin   = PB10;  // Input/Output
const int kSclkPin = PB1;  // Serial1 Clock

// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);

uint8_t setjam, setmnt, setdtk, setthn, setbln, settgl, sethr;

String dayAsString(const uint8_t day) {
  switch (day) {
    case 1: return "Minggu";
    case 2: return "Senin";
    case 3: return "Selasa";
    case 4: return "Rabu";
    case 5: return "Kamis";
    case 6: return "Jumat";
    case 7: return "Sabtu";
  }
  return "(unknown day)";
}

void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  // Print the formatted string to Serial1 so we can see the time.
  Serial.println(buf);
}

}  // namespace

void setup() {
  Serial.begin(115200);

  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  rtc.writeProtect(false);
  rtc.halt(false);

  // Make a new time object to set the date and time.
  // Sunday, September 22, 2013 at 01:38:50.
  setthn = YEAR;
  setbln = MONTH;
  settgl = DAY;

  setjam = HRS;
  setmnt = MIN;
  setdtk = SEC;
  sethr = DAY_OF_WEEK;

  Time t(setthn, setbln, settgl, setjam, setmnt, setdtk, sethr); // aktifkan untuk update

  // Set the time and date on the chip.
  rtc.time(t);
}

// Loop and print the time every second.
void loop() {
  printTime();
  delay(1000);
}
