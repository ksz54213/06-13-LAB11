#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "AA201-2G";
char _lwifi_pass[] = "iteaa201";
MCSDevice mcs("DuH3qJzm", "0rET0hA6xyVaXEcJ");

MCSControllerOnOff LED("Control");
MCSDisplayOnOff remote("LED2");

void setup()
{
  Serial.begin(9600);

  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");
  mcs.addChannel(LED);mcs.addChannel(remote);
  pinMode(7, OUTPUT);
  remote.set(0);
}


void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  mcs.process(1000);

  if (LED.value() == 1) {
    digitalWrite(7, HIGH);
   remote.set(1);
  } else {
    digitalWrite(7, LOW);
    remote.set(0);
  }

  delay(200);
 

}
