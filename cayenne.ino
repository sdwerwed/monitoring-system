unsigned long timeout = 1UL * 1000UL * 30UL * 1; //1 min;
unsigned long doNotUploadTime = 1UL * 1000UL ; //1 sec
unsigned long doNotUploadTimeNoInternet = 1UL * 1000UL * 60UL * 1UL ; //3 min
unsigned long doNotUploadTimeWithInternet =  1UL * 1000UL * 60UL * 1; //1 min
bool dataIsUploaded = false;
unsigned long uploadedTime = 0;
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress arduino_ip(150, 140, 216, 102);
IPAddress dns_ip(8, 8, 8, 8);
IPAddress gateway_ip(150, 140, 216, 126);
IPAddress subnet_mask(255, 255, 255, 0);

void cyanaee_run(void )
{
  ////digitalWrite(SS_ETHERNET, LOW);
  digitalWrite(SS_SD_CARD, HIGH);
  Serial.println("Start cyanee");
  int uploaded = 1;
  int not_uploaded = 1;
  int sum = 0;
  int check1[NUMBER_OF_SENSORS + 1];
  unsigned long passedTime = millis() - uploadedTime;
  Serial.print("passed time is ");
  Serial.print(passedTime);
  Serial.println(" ");
  Serial.print("doNotUploadTime is ");
  Serial.print(doNotUploadTime);
  Serial.println(" ");
  ////digitalWrite(SS_ETHERNET, LOW);
  if (passedTime > doNotUploadTime) {
    Serial.println("EDw midenizete to ethernet");
    dataIsUploaded = false;

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
      check_if_uploaded[i] = 0;
    }
  }

  ////digitalWrite(SS_ETHERNET, LOW);
  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    check1[i] = (check_if_uploaded[i] == 0);
    not_uploaded = check1[i] * not_uploaded;
    sum = sum + check1[i];
  }
  ////digitalWrite(SS_ETHERNET, LOW);
  Serial.print("sum is ");
  Serial.print(sum);
  Serial.println(" ");

  ////digitalWrite(SS_ETHERNET, LOW);

  if (!dataIsUploaded and not_uploaded) {
    unsigned long start_time = millis();
    //pinMode(2,OUTPUT);
    //digitalWrite(2, LOW); // ON
    //delay(2000); // to initialize
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Internet..");
    Serial.print("Net setup..");
    display.display();
    ////digitalWrite(SS_ETHERNET, LOW);
    Cayenne.begin(token, arduino_ip, dns_ip, gateway_ip, subnet_mask, arduino_mac);
    display.print(" OK");
    Serial.print(" OK");
    delay(1000);
    display.print("\nInternet..");
    Serial.print("\nUpload data..");
    display.display();
    while (1)
    {
      uploaded = 1;
      unsigned long now_time = millis();
      //Add here: if too much time passed call Cayenne.begin(token);
      Cayenne.run();
      //Serial.println(Ethernet.localIP());
      unsigned long elapsed = now_time - start_time;

      for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        check1[i] = (check_if_uploaded[i] >= 1);
        uploaded = check1[i] * uploaded;
      }

      if (uploaded) {
        Serial.println("Data uploaded");
        display.print(" OK");
        display.display();
        delay(2000);
        doNotUploadTime = doNotUploadTimeWithInternet;
        break;
      }
      if (elapsed > timeout) {
        Serial.println("TIMEOUT");
        doNotUploadTime = doNotUploadTimeNoInternet;
        break;
      }
    }
    //digitalWrite(2, LOW); // OFF
    Serial.println(check_if_uploaded[0]);
    Serial.println(check_if_uploaded[1]);
    dataIsUploaded = true;
    uploadedTime = millis();
  }
  //digitalWrite(SS_ETHERNET, HIGH);
}

CAYENNE_CONNECTED()
{
  CAYENNE_LOG("Connection established");
}
CAYENNE_OUT(V0)
{
  check_if_uploaded[1]++;
  CAYENNE_LOG("CAYENNE_OUT(V0)");
  Cayenne.celsiusWrite(V0, random() * 20 - 10);

}

CAYENNE_OUT(V1)
{
  check_if_uploaded[1]++;
  CAYENNE_LOG(V1, random() * 20 - 10);
  Serial.println("CAYENNE_OUT(V0)");
  Cayenne.celsiusWrite(V1, random() * 20 - 10);

}


CAYENNE_OUT(V2)
{
  Cayenne.celsiusWrite(V2, tempC[2]);
  check_if_uploaded[2]++;
}


CAYENNE_OUT(V3)
{
  Cayenne.celsiusWrite(V3, tempC[3]);
  check_if_uploaded[3]++;
}


CAYENNE_OUT(V4)
{
  Cayenne.celsiusWrite(V4, tempC[4]);
  check_if_uploaded[4]++;
}


CAYENNE_OUT(V5)
{
  Cayenne.celsiusWrite(V5, tempC[5]);
  check_if_uploaded[5]++;
}


CAYENNE_OUT(V6)
{
  Cayenne.celsiusWrite(V6, tempC[6]);
  check_if_uploaded[6]++;
}


CAYENNE_OUT(V7)
{
  Cayenne.celsiusWrite(V7, tempC[7]);
  check_if_uploaded[7]++;
}


CAYENNE_OUT(V8)
{
  Cayenne.celsiusWrite(V7, tempC[8]);
  check_if_uploaded[8]++;
}


CAYENNE_OUT(V9)
{
  Cayenne.celsiusWrite(V7, tempC[9]);
  check_if_uploaded[9]++;
}


CAYENNE_OUT(V10)
{
  Cayenne.celsiusWrite(V7, tempC[10]);
  check_if_uploaded[10]++;
}

CAYENNE_OUT(V11)
{
  Cayenne.celsiusWrite(V1, tempC[11]);
  check_if_uploaded[11]++;
}


CAYENNE_OUT(V12)
{
  Cayenne.celsiusWrite(V2, tempC[12]);
  check_if_uploaded[12]++;
}


CAYENNE_OUT(V13)
{
  Cayenne.celsiusWrite(V3, tempC[13]);
  check_if_uploaded[13]++;
}


CAYENNE_OUT(V14)
{
  Cayenne.celsiusWrite(V4, tempC[14]);
  check_if_uploaded[14]++;
}


CAYENNE_OUT(V15)
{
  Cayenne.celsiusWrite(V5, tempC[15]);
  check_if_uploaded[5]++;
}


CAYENNE_OUT(V16)
{
  Cayenne.celsiusWrite(V6, tempC[16]);
  check_if_uploaded[16]++;
}


CAYENNE_OUT(V17)
{
  Cayenne.celsiusWrite(V7, tempC[17]);
  check_if_uploaded[17]++;
}


CAYENNE_OUT(V18)
{
  Cayenne.celsiusWrite(V7, tempC[18]);
  check_if_uploaded[18]++;
}


CAYENNE_OUT(V19)
{
  Cayenne.celsiusWrite(V7, tempC[19]);
  check_if_uploaded[19]++;
}


CAYENNE_OUT(V20)
{
  Cayenne.celsiusWrite(V7, tempC[20]);
  check_if_uploaded[20]++;
}

