#include <Arduino.h>


void Send_Test_Data_to_ESP()
{
   char ReadEsp = 'b';
  while (Serial2.available())
  {
    Serial2.read();
    delay(1000);
  }
  Serial.print("Sending Data");
  Serial2.println("[0]LECS Power on test");
  Serial2.print('#');
  while (ReadEsp != 'a')
  {
    ReadEsp = Serial2.read();
  }
  Serial.print("Test data sent!");
}

// Send unique char "^#" to ESP when it returns 1 wifi is on 
// Does this for 100 seconds then gives up
void check_wifi_is_on(){
    char wifiON='0';
    int c=0;
    while ((c < 200) && (wifiON != '1')) {
      digitalWrite(LED_BUILTIN, HIGH);   // set the LED on
      Serial2.print("^#");
      delay(100);
      wifiON = Serial2.read();
      delay(500);
      c++;
      digitalWrite(LED_BUILTIN, LOW);    // set the LED off
      delay(500);                  // wait for a second
    }
}

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);  

  // start serial console, GPS, and ESP
  Serial.begin(9600);
  Serial2.begin(115200);

  check_wifi_is_on();
  Serial.print("Send Data");

  Serial.println("Send test data to server");
  Send_Test_Data_to_ESP();
}

void loop() {
}