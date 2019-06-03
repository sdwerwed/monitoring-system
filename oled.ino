
void print_to_oled(void) {
  display.clearDisplay();
  // display.display();
  // display.setFont(&FreeMonoBold24pt7b);
  display.setFont(&FreeMono12pt7b);
  display.setTextSize(1.2);
  display.setCursor(0, 15);
  //display.setTextColor(WHITE);
  display.print(tempC[counter_1]);
  display.setFont();
  display.setTextSize(1.8);
  display.setCursor(105, 0);
  display.print(counter_1 + 1);
  display.setCursor(105, 10);
  display.print("C");
  print_time();
  delay(1000);
  counter_1++;
  if (counter_1 == NUMBER_OF_SENSORS) counter_1 = 0;
}

int next_back_menu() {
  display.setTextSize(1);
  display.setFont();
  display.setCursor(0, 25);
  Serial.println("No            Yes");
  display.println("Back             Next");
  display.setCursor(56, 25);
  display.write(24); display.write(25);
  display.display();
}
