int set_number_to_call() {
  int B[10], A[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
  int i = 0;
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  display.setFont(0);
  display.setCursor(0, 0);
  Serial.print("\nNumber is ");

  for (i = 0; i < 10; i++) {
    B[i] = read_from_eeprom(80 + 2 * i); // Read phone number to EEPROM. Allocate 10*2 byte from 80 to 90
    Serial.print(B[i]);
    display.print(B[i]);
  }
  i = 0;

  display.print("\nAllagi arithmou?");
  display.display();
  next_back_menu();
  delay(2000);
  while (1) {
    if (digitalRead(buttonPinEnter)) break;
    if (digitalRead(buttonPinBack)) return 1;
  }
  while (1) {
    Serial.print("\nA[i]="); Serial.print(A[i]);
    Serial.print("\ni="); Serial.print(i);

    display.print(i); display.print(" psifio");
    display.setTextColor(WHITE);
    display.setFont(&FreeMono9pt7b);
    display.setCursor(0, 10);
    display.clearDisplay();
    display.print(i + 1); display.print(" psifio: ");
    display.print(A[i]);

    display.setCursor(0, 25);
    display.setFont(&FreeMono9pt7b);
    next_back_menu();
    display.display();
    
    buttonStateUp = digitalRead(buttonPinUp);
    // compare the buttonState to its previous state
    if (buttonStateUp != lastButtonStateUp) {   // If UP increase digit value
      display.display();
      // if the state has changed, increment the counter
      if (buttonStateUp == HIGH) {
        if (  A[i] < 9) {
          A[i]++;
        }
        display.clearDisplay();
        display.setFont(&FreeMono9pt7b);
        display.setCursor(0, 10);
        display.clearDisplay();
        display.print(i + 1); display.print(" psifio: ");
        display.print(A[i]);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateUp = buttonStateUp;



    buttonStateDown = digitalRead(buttonPinDown);//  If DOWN decrease digit value
    // compare the buttonState to its previous state
    if (buttonStateDown != lastButtonStateDown) {
      // if the state has changed, increment the counter
      if (buttonStateDown == HIGH) {
        // if the current state is HIGH then the button
        // wend from off to on:
        if (A[i] > 0 and A[i] <= 9 ) {
          A[i]--;
        }
        display.clearDisplay();
        display.setFont(&FreeMono9pt7b);
        display.setCursor(0, 10);
        display.clearDisplay();
        display.print(i + 1); display.print(" psifio: ");
        display.print(A[i]);
        display.display();
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateDown = buttonStateDown;


    buttonStateEnter = digitalRead(buttonPinEnter); // If ENTER next digit
    // compare the buttonState to its previous state
    if (buttonStateEnter != lastButtonStateEnter) {
      // if the state has changed, increment the counter
      if (buttonStateEnter == HIGH) {
        i++;
        if (i >= 10) {
          break;
        }
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateEnter  = buttonStateEnter;

    buttonStateBack = digitalRead(buttonPinBack); //If BACK previous digit
    // compare the buttonState to its previous state
    if (buttonStateBack != lastButtonStateBack) {
      // if the state has changed, increment the counter
      if (buttonStateBack == HIGH ) {
        if (i > 0 and i < 9) {
          i--;
        }
      }

      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonStateBack  = buttonStateBack;

  }
  display.clearDisplay();

  display.setFont(&FreeMono9pt7b);
  display.setCursor(0, 10);
  display.clearDisplay();

  //display.setCursor(0, 0);
  for (i = 0; i < 10; i++) {
    display.print(A[i]);
    save_to_eeprom(80 + 2 * i, A[i]); // Save phone number to EEPROM. Allocate 10 byte from 80 to 100
  }
  next_back_menu();
  delay(2000);
  while (1) {
    if (digitalRead(buttonPinEnter) == 1) break;
    if (digitalRead(buttonPinBack) == 1) {
      set_number_to_call();
      break;
    }
  }
}
