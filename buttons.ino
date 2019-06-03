

void setup_buttons(void) {

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); //beep
  pinMode(7, INPUT);
  //pinMode(2, OUTPUT);
  //digitalWrite(2, HIGH); // ethernet module on
  pinMode(buttonPinUp, INPUT);//up
  pinMode(buttonPinDown, INPUT);// down
  pinMode(buttonPinEnter, INPUT);//enter
  pinMode(buttonPinBack, INPUT);//back
}

int button_up() {
  buttonStateUp = digitalRead(buttonPinUp);
  if (buttonStateUp != lastButtonStateUp) {
    // if the state has changed, increment the counter
    if (buttonStateUp == HIGH) {
      return 1;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  return 0;
  lastButtonStateUp = buttonStateUp;
}


int button_down() {
  buttonStateDown = digitalRead(buttonPinDown);
  if (buttonStateDown != lastButtonStateDown) {
    // if the state has changed, increment the counter
    if (buttonStateDown == HIGH) {
      return 1;
    }
    
    // Delay a little bit to avoid bouncing
    delay(50);
  }
   return 0;
  lastButtonStateDown = buttonStateDown;
}

int button_enter() {
  buttonStateEnter = digitalRead(buttonPinBack);
  if (buttonStateEnter != lastButtonStateEnter) {
    // if the state has changed, increment the counter
    if (buttonStateEnter == HIGH) {
      return 1;
    }
    
    // Delay a little bit to avoid bouncing
    delay(50);
  }
   return 0;
  lastButtonStateEnter = buttonStateEnter;
}

int button_back() {
  buttonStateDown = digitalRead(buttonPinDown);
  if (buttonStateBack != lastButtonStateBack) {
    // if the state has changed, increment the counter
    if (buttonStateBack == HIGH) {
      return 1;
    }
    
    // Delay a little bit to avoid bouncing
    delay(50);
  }
   return 0;
  lastButtonStateBack = buttonStateBack;
}
