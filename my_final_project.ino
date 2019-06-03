#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Wire.h>
#include "RTClib.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include <SPI.h>
#include <SD.h>
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <CayenneEthernet.h>
#include <Ethernet.h>
#define NUMBER_OF_SENSORS 2
#define OLED_RESET 4
#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#define VIRTUAL_PIN V1
#define VIRTUAL_PIN V0
#define TX_PIN 45 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 43 // Arduino receive   GREEN WIRE   labeled TX on printer
#define PIN_TX    64
#define PIN_RX    63
#define BAUDRATE  9600
#define PHONE_NUMBER " "
#define MESSAGE  "hello,world"
#define ONE_WIRE_BUS 3
#define PIN_TX    64
#define PIN_RX    63
#define BAUDRATE  9600
#define PHONE_NUMBER " "
#define MESSAGE  "hello,world"
#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#define SS_SD_CARD   4
#define SS_ETHERNET 53
Adafruit_SSD1306 display(OLED_RESET);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
RTC_DS1307 rtc;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonStateUp = 0;         // current state of the button
int buttonStateDown = 0;
int buttonStateEnter = 0;
int buttonStateBack = 0;
int lastButtonStateUp = 0;     // previous state of the button
int lastButtonStateDown = 0;     // previous state of the button
int lastButtonStateEnter = 0;     // previous state of the button
int lastButtonStateBack = 0;     // previous state of the button
int buttonPinUp = 16;
int buttonPinDown = 17;
int buttonPinEnter = 15;
int buttonPinBack = 14;
const unsigned long sleepTimeGSM = 2UL * 60UL * 1000UL; // 1 day
bool messageIsSent = false;
bool called_for_power = false;
unsigned long sendTimeGSM;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int hours, years, minutes, seconds;
char token[] = "2kqayd5n2n"; 
int check_if_uploaded[NUMBER_OF_SENSORS + 1] = {0, 0};
int counter_1 = 0;
double tempC[20];
int set_up(void);
String IncDataSerial = ""; // a string for incomming text from GPRS shield over software serial
double temp_limit[20];
boolean initalization_templimit = false;
unsigned long start2;
unsigned long timeout2 = 10000;
unsigned long elapsed2;
unsigned long now2;
int katapsiktis[NUMBER_OF_SENSORS + 1] = {1, 0}; // For thermalprinter katapsiktis or psigio
GPRS gprsTest(PIN_TX, PIN_RX, BAUDRATE); //RX,TX,BaudRate
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);
DeviceAddress Probe01 = { 0x28, 0xFF, 0x37, 0x0C, 0x63, 0x16, 0x03, 0x6A };
DeviceAddress Probe02 = {  0x28, 0xEE, 0x10, 0x34, 0x13, 0x16, 0x02, 0x4A };
void print_to_printer(double tempC[20]);
void set_up_limits();

void setup () {
  Serial.begin(9600);
  sensors.begin();  // see if the card is present and can be initialized:
  mySerial.begin(19200);  // Initialize SoftwareSerial
  pinMode(SS_SD_CARD, OUTPUT);
  //pinMode(SS_ETHERNET, OUTPUT);
  digitalWrite(SS_SD_CARD, HIGH);  // SD Card not active
  //digitalWrite(SS_ETHERNET, HIGH); // Ethernet not active
  printer.begin();        // Init printer (same regardless of serial type)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  initialize_SD();
  setupgsm();
  read_limits_values_from_eeprom();
  setup_buttons();
  Serial.println("Start rtc");
  start_rtc();
  Serial.println("Print_time");
  print_time();
}

void loop () {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  set_up(); //if UP and Down is pressed setup
  cyanaee_run(); // comment this to stop using internet card
  sensors.requestTemperatures();
  tempC[0] = printTemperature(Probe01);
  tempC[1] = printTemperature(Probe02);
  call_sms();
  print_to_oled();
  check_time_and_write_on_SD(tempC);
  check_time_and_print_to_printer(tempC);
  delay(1000);

}


double printTemperature(DeviceAddress deviceAddress)
{

  float tempC = sensors.getTempC(deviceAddress);

  if (tempC == -127.00)
  {
    Serial.println("Error getting temperature  ");
  }
  else
  {

    Serial.print(tempC);
    Serial.print("C\n");
  }

  return tempC;
}

int check_power() {
  return digitalRead(7); //HIGH if there is main power source

}

