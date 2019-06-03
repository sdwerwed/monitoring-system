
void read_limits_values_from_eeprom(void) {
  if (initalization_templimit == false) {
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
      temp_limit[i] = read_from_eeprom(i * 2);
    }
  }
}


void set_up_limits() {
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.display();
  Serial.println("1111");
  start2 = millis();
  while (1) {
    now2 = millis();
    elapsed2 = now2 - start2;
    if (elapsed2 > timeout2) break;
    Serial.println("22222");
    set_temp_limit(0);
    break;
    if (digitalRead(buttonPinBack) == 1) break;
  }
  display.clearDisplay();
  display.display();
}


int set_temp_limit(int index) {

  if (initalization_templimit == false) {
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
      temp_limit[i] = read_from_eeprom(i * 2);
    }
    initalization_templimit = true;
  }




  if (index < NUMBER_OF_SENSORS) {
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setCursor(0, 0);
    Serial.print("Set limits for sensor/index "); display.print("Psigio "); display.print(index + 1);
    Serial.print(index);
    Serial.print(" it has this limit ");
    Serial.print(read_from_eeprom(index * 2));  display.print(" Orio thermokrasias ");
    if (read_from_eeprom(index * 2) == 0) {
      display.print(" OFF");
    } else display.print(read_from_eeprom(index * 2));
    Serial.print("\n"); display.display();
  }
  if (elapsed2 > timeout2) return 0;;
  delay(200);

  if (index >= NUMBER_OF_SENSORS) {
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
      Serial.println(temp_limit[i]);
      save_to_eeprom(i * 2, temp_limit[i]);
    }

    Serial.println("Read from eeprom");
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
      Serial.println(read_from_eeprom(i * 2));
    }

    boolean initalization_templimit = false;
    Serial.println("Temp limits are updated");
    return 1;
  }
  while (1) {

    buttonStateUp = digitalRead(buttonPinUp);

    // compare the buttonState to its previous state
    if (buttonStateUp != lastButtonStateUp) {
      // if the state has changed, increment the counter
      if (buttonStateUp == HIGH) {
        temp_limit[index]++;
        display.clearDisplay();
        Serial.println(temp_limit[index]);
        display.display();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.print("Psigio ");
        display.print(index + 1);
        display.print(" Orio thermokrasias ");
        if (temp_limit[index] == 0) {
          display.println(" OFF");
        }
        else {
          display.print(temp_limit[index]);
          display.print("C");
        }
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
        temp_limit[index]--;
        display.clearDisplay();
        Serial.println(temp_limit[index]);
        display.display();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.print("Psigio ");
        display.print(index + 1);
        display.print(" Orio thermokrasias ");
        if (temp_limit[index] == 0) {
          display.println(" OFF");
        }
        else {
          display.print(temp_limit[index]);
          display.print("C");
        }
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

        temp_limit[index] = temp_limit[index];
        index++;
        set_temp_limit(index);
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
      if (buttonStateBack == HIGH and index != 0) {
        index--;
        set_temp_limit(index);
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



