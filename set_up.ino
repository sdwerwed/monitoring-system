int set_up(void) {

  if (digitalRead(buttonPinDown) == 1 and digitalRead(buttonPinUp) == 1) {
    int casee = 0;
    int buttonPinDown = 17;

    display.clearDisplay();
    display.display();
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.display();
    display.setTextSize(1);
    display.setCursor(0, 0);
    Serial.println("Temperature limit");
    display.println("Orio thermokrasias");
    display.setTextColor(WHITE);
    Serial.println("Phone number");
    display.println("Arithmos kinitou");
    Serial.println("Change time");
    display.println("Allagi oras");
    next_back_menu();
    int i = 1;

    while (1) {

      buttonStateDown = digitalRead(buttonPinDown);
      if (buttonStateDown != lastButtonStateDown) {
        // if the state has changed, increment the counter
        if (buttonStateDown == HIGH) {

          if (i <= 2) {
            i = i + 1;
          }

          if (i == 2) {
            display.clearDisplay();
            display.display();
            display.setCursor(0, 0);
            display.setTextColor(WHITE);
            Serial.println("Temperature limit");
            display.println("Orio thermokrasias");
            display.setTextColor(BLACK, WHITE);
            Serial.println("Phone number");
            display.println("Arithmos kinitou");
            display.setTextColor(WHITE);
            Serial.println("Allagi oras");
            display.println("Allagi oras");
            next_back_menu();
          }
          if (i == 3) {

            display.clearDisplay();
            display.display();
            display.setCursor(0, 0);
            display.setTextColor(WHITE);
            Serial.println("Temperature limit");
            display.println("Orio thermokrasias");
            Serial.println("Phone number");
            display.println("Arithmos kinitou");
            display.setTextColor(BLACK, WHITE);
            Serial.println("Change time");
            display.println("Allagi oras");
            display.setTextColor(WHITE);
            next_back_menu();
          }

        }

        // Delay a little bit to avoid bouncing
        delay(50);
      }
      lastButtonStateDown = buttonStateDown;

      buttonStateUp = digitalRead(buttonPinUp);
      if (buttonStateUp != lastButtonStateUp) {
        // if the state has changed, increment the counter
        if (buttonStateUp == HIGH) {
          if (i > 1)
            i = i - 1;
        }
        if (i == 1) {
          display.clearDisplay();
          display.setTextColor(BLACK, WHITE);
          display.display();
          display.setTextSize(1);
          display.setCursor(0, 0);
          Serial.println("Temperature limit");
          display.println("Orio thermokrasias");
          display.setTextColor(WHITE);
          Serial.println("Phone number");
          display.println("Arithmos kinitou");
          Serial.println("Change time");
          display.println("Allagi oras");
          next_back_menu();
        }

        if (i == 2) {
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.display();
          display.setTextSize(1);
          display.setCursor(0, 0);
          Serial.println("Temperature limit");
          display.println("Orio thermokrasias");
          display.setTextColor(BLACK, WHITE);
          Serial.println("Phone number");
          display.println("Arithmos kinitou");
          display.setTextColor(WHITE);
          Serial.println("Change time");
          display.println("Allagi oras");
          next_back_menu();
        }

        // Delay a little bit to avoid bouncing
        delay(50);
      }
      lastButtonStateUp = buttonStateUp;


      buttonStateEnter = digitalRead(buttonPinEnter);
      if (buttonStateEnter != lastButtonStateEnter) {
        // if the state has changed, increment the counter
        if (buttonStateEnter == HIGH) {
          Serial.println(i);
          if (i == 1) {
            delay(1000);
            set_up_limits();
            break;
          }
          if (i == 2) {
            delay(500);
            set_number_to_call();
            break;
          }
          if (i == 3) {
            delay(500);
            set_year();
            break;
          }
        }

        // Delay a little bit to avoid bouncing
        delay(50);
      }

      lastButtonStateEnter = buttonStateEnter;


  buttonStateBack = digitalRead(buttonPinBack);
  if (buttonStateBack != lastButtonStateBack) {
    // if the state has changed, increment the counter
    if (buttonStateBack == HIGH) {
      return 1;
    }
    
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  lastButtonStateBack = buttonStateBack;


    }
  }
}
