bool data_writted_to_printer = false;



void check_time_and_print_to_printer(double tempC[20]) {
  //printer.sleep();
  DateTime now = rtc.now();

  if ( now.hour() != 8 and now.hour() != 22) data_writted_to_printer = false;

  if ( (now.hour() == 8 or now.hour() == 22)  && !data_writted_to_printer ) {
    Serial.print("Minute is ");
    Serial.print(now.minute());
    Serial.print("\n");
    Serial.print("Data_writted_to_printer is ");
    Serial.print(data_writted_to_printer);
    Serial.print("\n");
    printer.wake();
    delay(1000);
    printer.println("---------------------------");
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {

      if (temp_limit[i] == 0) {
        printer.print("Se sintirisi");
      }
      else {
        printer.print(tempC[i]);  // write to sd temp and time
        printer.print("C");
      }
      printer.print(' ');
      printer.print(i);
      printer.print(' ');
      printer.print(' ');
      printer.print(now.year(), DEC);
      printer.print('/');
      printer.print(now.month(), DEC);
      printer.print('/');
      printer.print(now.day(), DEC);
      printer.print(' ');
      printer.print(now.hour(), DEC);
      printer.print(':');
      printer.print(now.minute(), DEC);
      if (katapsiktis[i] == 1) {
        printer.print(' ');
        printer.print("K");
      }
      if (katapsiktis[i] == 0) {
        printer.print(' ');
        printer.print("PS");
      }
      printer.print("\n");
    }
    data_writted_to_printer = true;
    printer.sleep();
  }

}
