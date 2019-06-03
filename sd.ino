#define NUMBER_OF_LOG_FILES 11
#define ROWS_SD 4
String inString = "";
int counter = 0;
int lognumber = 0;
int pointer = 0;
String logname;

const unsigned long SDdoNotWriteTime = 1UL * 1000UL * 30UL * 1UL; //30 sec
bool dataIsWritted = false;
unsigned long writtedTime;

unsigned long start3;
unsigned long timeout3 = 10000;
unsigned long elapsed3;
unsigned long now3;

void initialize_SD(void) {
  //pinMode(SS_SD_CARD, OUTPUT); 
  //digitalWrite(SS_ETHERNET, HIGH);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  start3 = millis();
  while (!SD.begin(SS_SD_CARD) and (elapsed3 < timeout3)) {
    now3 = millis();
    elapsed3 = now3 - start3;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.display();
    display.setTextSize(1);
    Serial.println("Card failed, or not present");
    display.println("Den yparxei SD ");
    display.display();
    delay(2000);
    //return;
  }

  display.clearDisplay();
  display.display();
  display.setCursor(0, 0);
  //display.println("card initialized");
  display.display();
  Serial.println("card initialized.");
  pointer_file();
  digitalWrite(SS_SD_CARD, HIGH);
}

void check_time_and_write_on_SD(double *tempC) {

  //pinMode(SS_SD_CARD, OUTPUT); 
  //digitalWrite(SS_ETHERNET, HIGH);

  unsigned long passedTime = millis() - writtedTime;

  if (passedTime > SDdoNotWriteTime) {
    Serial.println("EDw midenizete tis sd");
    dataIsWritted = false;
  }


  if (!dataIsWritted) {
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
      write_data_to_SD(tempC[i], i);
    }

    dataIsWritted = true;
    writtedTime = millis();
  }

    digitalWrite(SS_SD_CARD, HIGH);

  
}

void write_data_to_SD(double dataString, int i) {
  String logname = String(lognumber + String(".txt"));
  if (counter >= ROWS_SD) // 10000 rows is 250kb
  {
    pointer = lognumber++;
    if (lognumber > NUMBER_OF_LOG_FILES) lognumber = 0; // 10 log files
    File dataFile1 = SD.open("pointea.txt", FILE_WRITE);
    Serial.print("\nUpdate to pointer ");
    dataFile1.seek(0);
    dataFile1.println(lognumber);
    Serial.print("\npointea.txt is ");
    while (dataFile1.available()) {
      Serial.write(dataFile1.read());
    }
    Serial.print("\n");
    int nextlognumber = lognumber + 1;
    if (nextlognumber > (NUMBER_OF_LOG_FILES)) nextlognumber = 0;
    String nextlogname = String(nextlognumber + String(".txt"));
    Serial.print("\n lognumber: "); Serial.print(lognumber);
    Serial.print("\n nextlognumber: "); Serial.print(nextlognumber);
    SD.remove(nextlogname);
    dataFile1.close();
    //    logname = String(lognumber + String(".txt"));
    counter = 0;

  }
  File dataFile = SD.open(logname, FILE_WRITE);


  // if the file is available, write to it:
  if (dataFile) {
    Serial.print("\nSaved on ");
    Serial.print(logname);
    Serial.print("\n");
    if (read_from_eeprom(i * 2) == 0) {
      dataFile.print("Σε συντηρηση");
    }
    else {
      dataFile.print(dataString);  // write to sd temp and time
      dataFile.print("C");
    }
    dataFile.print(' ');
    dataFile.print(i);
    dataFile.print(' ');
    DateTime now = rtc.now();
    dataFile.print(' ');
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(' ');
    dataFile.print(now.hour(), DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.println();
    dataFile.close();
    dataIsWritted = true;

    // print to the serial port too:
    dataFile.close();
    counter++;
  }
  // if the file isn't open, pop up an error:
  else {
    dataFile.close();
    display.clearDisplay();
    display.display();
    display.setCursor(0, 0);
    Serial.println("error opening datalog.txt");
    display.println("Sfalma anigamtos arxeiou log");
    display.display();
    SD.begin(SS_SD_CARD);
    delay(2000);

  }
  dataFile.close();

}

void pointer_file() {


  if (SD.exists("pointea.txt"))
  {
    File dataFile1 = SD.open("pointea.txt", FILE_READ);
    if (dataFile1)
    {

      Serial.println("reading pointer");
      display.clearDisplay();
      display.display();
      display.setCursor(0, 0);
      display.println("Diavasma kartas sd");
      display.display();
      delay(100);
      while (dataFile1.available())
      {
        int pointer = (dataFile1.read());
        if (isDigit(pointer))
        {
          // convert the incoming byte to a char
          // and add it to the string:
          inString += (char)pointer;
          Serial.print("Value:");
          Serial.println(lognumber = inString.toInt());
          String inString = "";
        }

      }

    }
    dataFile1.close();
  }
  else
  {
    File dataFile1 = SD.open("pointea.txt", FILE_WRITE);
    if (dataFile1)
    {
      display.clearDisplay();
      display.display();
      display.setCursor(0, 0);
      display.println("reading pointer");
      display.display();
      delay(500);
      Serial.print("\nWrite to pointer ");
      dataFile1.println(lognumber);
      Serial.print("\nPointer is ");
      Serial.print(lognumber);
      Serial.print("\n");
      dataFile1.close();
    }
    else
    {
      dataFile1.close();

      Serial.println("Error opening pointer");
      display.clearDisplay();
      display.display();
      display.setCursor(0, 0);
      display.println("Error opening pointer");
      display.display();
      delay(2000);
    }

  }
}

