int  year_time = 2016, month_time = 0, day_time = 0, hour_time = 0, minutes_time = 0;
void set_year();
void set_month();
void set_day();
void set_hour();
void set_minutes();

unsigned long start1;
unsigned long timeout1 = 10000;
unsigned long elapsed1;
unsigned long now1;
void start_rtc(void) {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.display();
    display.print("Sfalma stin wra");
    display.display();
    delay(2000);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.display();
    display.print("H wra de litourgei!");
    display.display();
    delay(2000);
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Allagi wras?");
    next_back_menu();
    Serial.println("Enter time YES or NO?");
    display.display();
    start1 = millis();
    
    while (1) {
      now1 = millis();
      elapsed1 = now1 - start1;
      if (elapsed1 > timeout1) break;
      buttonStateEnter = digitalRead(buttonPinEnter);
      buttonStateBack = digitalRead(buttonPinBack);
      if (buttonStateEnter == HIGH) {
        set_year();
        break;
      }
      if (buttonStateBack == HIGH) break;
    }

  }
}


void print_time(void) {
  DateTime now = rtc.now();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 17);
  Serial.print(now.year(), DEC);  display.print("\n"); display.print(now.year(), DEC);
  Serial.print('/');              display.print('/');
  Serial.print(now.month(), DEC); display.print(now.month(), DEC);
  Serial.print('/');              display.print('/');
  Serial.print(now.day(), DEC);    display.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");               display.print(" ");
  Serial.print(now.hour(), DEC);    display.print(now.hour(), DEC);
  Serial.print(':');                display.print(':');
  Serial.print(now.minute(), DEC); display.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);   
  Serial.println();
  display.display();
  delay(2000);
}

void set_year(void) {
  Serial.println("Enter year");

  //check if timeout1 occured


  display.setFont();
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
  display.print("Xronos ");
  display.display();
  delay(1000);

  while (1) {
    buttonStateUp = digitalRead(buttonPinUp);

    // compare the buttonState to its previous state
    if (buttonStateUp != lastButtonStateUp) {
      // if the state has changed, increment the counter
      if (buttonStateUp == HIGH) {
        year_time++;
        Serial.println(year_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Xronos ");
        display.display();
        display.print(year_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateUp = buttonStateUp;



    buttonStateDown = digitalRead(buttonPinDown);
    // compare the buttonState to its previous state
    if (buttonStateDown != lastButtonStateDown) {
      // if the state has changed, increment the counter
      if (buttonStateDown == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        year_time--;
        Serial.println(year_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Xronos ");
        display.display();
        display.print(year_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateDown = buttonStateDown;


    buttonStateEnter = digitalRead(buttonPinEnter);
    // compare the buttonState to its previous state
    if (buttonStateEnter != lastButtonStateEnter) {
      // if the state has changed, increment the counter
      if (buttonStateEnter == HIGH) {

        set_month();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateEnter  = buttonStateEnter;



  }

}


void set_month(void) {
  Serial.println("Enter month");
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
  display.print("Minas ");
  display.display();
  delay(1000);
  while (1) {

    buttonStateUp = digitalRead(buttonPinUp);

    // compare the buttonState to its previous state
    if (buttonStateUp != lastButtonStateUp) {
      // if the state has changed, increment the counter
      if (buttonStateUp == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        month_time++;
        Serial.println(month_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Minas ");
        display.display();
        display.print(month_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateUp = buttonStateUp;



    buttonStateDown = digitalRead(buttonPinDown);
    // compare the buttonState to its previous state
    if (buttonStateDown != lastButtonStateDown) {
      // if the state has changed, increment the counter
      if (buttonStateDown == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        month_time--;
        Serial.println(month_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Minas ");
        display.display();
        display.print(month_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateDown = buttonStateDown;


    buttonStateEnter = digitalRead(buttonPinEnter);
    // compare the buttonState to its previous state
    if (buttonStateEnter != lastButtonStateEnter) {
      // if the state has changed, increment the counter
      if (buttonStateEnter == HIGH) {
        set_day();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateEnter  = buttonStateEnter;


    buttonStateBack = digitalRead(buttonPinBack);
    // compare the buttonState to its previous state
    if (buttonStateBack != lastButtonStateBack) {
      // if the state has changed, increment the counter
      if (buttonStateBack == HIGH) {
        set_year();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateBack  = buttonStateBack;



  }
}

void set_day(void) {
  Serial.println("Set day");
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
  display.print("Hmera ");
  display.display();
  delay(1000);


  while (1) {
    buttonStateUp = digitalRead(buttonPinUp);

    // compare the buttonState to its previous state
    if (buttonStateUp != lastButtonStateUp) {
      // if the state has changed, increment the counter
      if (buttonStateUp == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        day_time++;
        Serial.println(day_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Enter day ");
        display.display();
        display.print(day_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateUp = buttonStateUp;



    buttonStateDown = digitalRead(buttonPinDown);
    // compare the buttonState to its previous state
    if (buttonStateDown != lastButtonStateDown) {
      // if the state has changed, increment the counter
      if (buttonStateDown == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        day_time--;
        Serial.println(day_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Hmera ");
        display.display();
        display.print(day_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateDown = buttonStateDown;


    buttonStateEnter = digitalRead(buttonPinEnter);
    // compare the buttonState to its previous state
    if (buttonStateEnter != lastButtonStateEnter) {
      // if the state has changed, increment the counter
      if (buttonStateEnter == HIGH) {

        set_hour();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateEnter  = buttonStateEnter;

    buttonStateBack = digitalRead(buttonPinBack);
    // compare the buttonState to its previous state
    if (buttonStateBack != lastButtonStateBack) {
      // if the state has changed, increment the counter
      if (buttonStateBack == HIGH) {
        set_month();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateBack  = buttonStateBack;



  }
}




void set_hour(void) {
  Serial.println("Enter hour 24 format");
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
  display.print("Wra ");
  display.display();
  delay(1000);


  while (1) {
    buttonStateUp = digitalRead(buttonPinUp);

    // compare the buttonState to its previous state
    if (buttonStateUp != lastButtonStateUp) {
      // if the state has changed, increment the counter
      if (buttonStateUp == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        hour_time++;
        Serial.println(hour_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Wra ");
        display.display();
        display.print(hour_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateUp = buttonStateUp;



    buttonStateDown = digitalRead(buttonPinDown);
    // compare the buttonState to its previous state
    if (buttonStateDown != lastButtonStateDown) {
      // if the state has changed, increment the counter
      if (buttonStateDown == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        hour_time--;
        Serial.println(hour_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Wra ");
        display.display();
        display.print(hour_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateDown = buttonStateDown;


    buttonStateEnter = digitalRead(buttonPinEnter);
    // compare the buttonState to its previous state
    if (buttonStateEnter != lastButtonStateEnter) {
      // if the state has changed, increment the counter
      if (buttonStateEnter == HIGH) {

        set_minutes();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateEnter  = buttonStateEnter;

    buttonStateBack = digitalRead(buttonPinBack);
    // compare the buttonState to its previous state
    if (buttonStateBack != lastButtonStateBack) {
      // if the state has changed, increment the counter
      if (buttonStateBack == HIGH) {
        set_day();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateBack  = buttonStateBack;



  }
}

void set_minutes(void) {
  Serial.println("Set minutes");
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
  display.print("Lepta ");
  display.display();
  delay(1000);


  while (1) {
    buttonStateUp = digitalRead(buttonPinUp);

    // compare the buttonState to its previous state
    if (buttonStateUp != lastButtonStateUp) {
      // if the state has changed, increment the counter
      if (buttonStateUp == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        minutes_time++;
        Serial.println(minutes_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Lepta ");
        display.display();
        display.print(minutes_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateUp = buttonStateUp;



    buttonStateDown = digitalRead(buttonPinDown);
    // compare the buttonState to its previous state
    if (buttonStateDown != lastButtonStateDown) {
      // if the state has changed, increment the counter
      if (buttonStateDown == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        minutes_time--;
        Serial.println(minutes_time);
        display.setCursor(0, 0);
        display.clearDisplay();
        display.display();
        display.print("Lepta ");
        display.display();
        display.print(minutes_time);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateDown = buttonStateDown;


    buttonStateEnter = digitalRead(buttonPinEnter);
    // compare the buttonState to its previous state
    if (buttonStateEnter != lastButtonStateEnter) {
      // if the state has changed, increment the counter
      if (buttonStateEnter == HIGH) {
        rtc.adjust(DateTime(year_time, month_time, day_time, hour_time, minutes_time, 0));
        Serial.println("FINISH");
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateEnter  = buttonStateEnter;

    buttonStateBack = digitalRead(buttonPinBack);
    // compare the buttonState to its previous state
    if (buttonStateBack != lastButtonStateBack) {
      // if the state has changed, increment the counter
      if (buttonStateBack == HIGH) {
        set_hour();
        break;
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateBack  = buttonStateBack;

  }



}
