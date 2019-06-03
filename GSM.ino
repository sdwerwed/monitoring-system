void setupgsm(void) {

  Serial.print("Out gpstestinit is ");
  Serial.print(gprsTest.init());
  Serial.print("\n");
  Serial.println("GPRS success");
  display.clearDisplay();
  display.display();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("\nSIM OK");
  display.display();
}


void call_sms(void) {

  int check = 0;
  int checkSensor[NUMBER_OF_SENSORS + 1];
  int j = 0;
  unsigned long passedTime = millis() - sendTimeGSM;
  if (passedTime > sleepTimeGSM)
    messageIsSent = false;

  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    if ((tempC[i] > temp_limit[i]) and ( temp_limit[i] = ! 0) ) {
      check++; // Number of sensors that are triggered
      checkSensor[j++] == i; // Save on array the number of the sensor that is triggered
    }
  }
  j = 0;

  if ( (check_power() == 0 or check != 0) and !messageIsSent) {
    display.clearDisplay();
    display.display();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    Serial.println("Alarm sound...");
    pinMode(4, OUTPUT);
    digitalWrite(5, HIGH);// beep sound
    delay(1000);
    digitalWrite(5, LOW);// beep sound
    delay(1000);
    digitalWrite(5, HIGH);// beep sound
    delay(1000);
    digitalWrite(5, LOW);// beep sound
    
    Serial.println("Start to call...");
    display.print("\nTilefono...");
    display.display();

    Serial.print("\n");
    int  m = gprsTest.callUp(PHONE_NUMBER);
    delay(2000);
    Serial.print("\n");
    if (m == 1 ) {
      Serial.println("Call success");
      Serial.print("\n");
      delay(5000);
      messageIsSent = true;
      sendTimeGSM = millis();
    }
  }
}
