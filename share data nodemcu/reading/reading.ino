#include "config.h"

#define FEED_OWNER "feedowner"
#define SHARED_FEED "counter"

AdafruitIO_Feed *sharedFeed = io.feed(SHARED_FEED, FEED_OWNER);


void setup() {
  Serial.begin(115200);
  
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  
  io.connect();
  sharedFeed->onMessage(handleMessage);
  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  sharedFeed->get();
}

void loop() {
  io.run();
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <-  ");
  Serial.println(data->toInt());
}
