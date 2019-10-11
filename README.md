# Share Data Between Nodemcu's

This is a manual how you can sent data from nodemcu to nodemcu with adafruit feeds.



## Hardware Required

* 2x* nodemcu  
* Micro USB cable  
* Powerbank/ External powersource

*You can have multiple nodemcu's but for this example I use just 2.


### Software Required

```
Arduino IDE (with ESP8266 Library installed)
```

* [Arduino IDE](https://www.arduino.cc/en/main/software)
* [ESP8266 Library](http://arduino.esp8266.com/stable/package_esp8266com_index.json)



### Prerequisites

What things you need to install the software and how to install them:

* For this project you will need an adafruit io account.   
[Adafruit](https://io.adafruit.com)

* Get your AIO Key (right upper corner on adafruitio dashboard).
* Get you Wifi SSID and PASSWORD ready.


### Arduino libaries
```
Open up arduino go to Sketch --> Include libary --> Manage Libaries
(Shift + CMD + I)
```
And search for the following libaries:

* Adafruit IO Arduino by:Adafruit   
[(latest version)](https://github.com/adafruit/Adafruit_IO_Arduino)


### Adafruit Create New Feed
```
Go to you Dashboard --> Feeds --> Action --> Create new feed
```
Create a nieuw feed and name it "counter"


## Coding Time
### Open arduino

#### Setup Config.h

Open File --> Exampels --> Adafruit IO Arduino --> adafruit_00_publish

In the file navigate to the second tab named: config.h

Change this section to your own information form adafruit
```C
#define IO_USERNAME   "your_username"
#define IO_KEY        "your_key"
```

change this information to your own WIFI information
```C
#define WIFI_SSID   "your_ssid"
#define WIFI_PASS   "your_pass"
```
You can delete the FONA and ETHERNET sections because we work with WIFI.
You should left something with this of you are on wifi:
```C
#define IO_USERNAME   "your_username"
#define IO_KEY        "your_key"

#define WIFI_SSID   "your_ssid"
#define WIFI_PASS   "your_pass"

#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
    #define SPIWIFI SPI
    #define SPIWIFI_SS 10  // Chip select pin
    #define NINA_ACK 9    // a.k.a BUSY or READY pin
    #define NINA_RESETN 6 // Reset pin
    #define NINA_GPIO0 -1 // Not connected
  #endif
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS, NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
```

### Sent data to Adafruit

Navigate back to the first tab Adafruitio_00_publish.
You can leave everything there and upload it to you nodemcu to test.

If you did the previouse steps correct you should see this in the serial monitor:

Sending data to adafruit in serialmonitor: 
![alt text](https://github.com/smuldesign/sharedatanodemcu/blob/master/images/serialmonitor.png "Logo Title Text 1")
`Note: make sure your serial monitor is on 115200`


check your adafruit feed, you should see something like this.
![alt text](https://github.com/smuldesign/sharedatanodemcu/blob/master/images/adafruit.png "Logo Title Text 1")
`Note: if it doesn't work look though the previous steps and look for things you missed`

### Read data from Adafruit

Open File --> Exampels --> Adafruit IO Arduino --> adafruit_21_read_feed

Navigate to the config.h
This config is a copy of the config form the Adafruitio_00_publish example.
copy and past it and change the varribles to your own.
```C
#define IO_USERNAME   "your_username"
#define IO_KEY        "your_key"

#define WIFI_SSID   "your_ssid"
#define WIFI_PASS   "your_pass"

#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
    #define SPIWIFI SPI
    #define SPIWIFI_SS 10  // Chip select pin
    #define NINA_ACK 9    // a.k.a BUSY or READY pin
    #define NINA_RESETN 6 // Reset pin
    #define NINA_GPIO0 -1 // Not connected
  #endif
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS, NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
}
```
Navigate back to the first tab adafruit_21_read_feed.

change feed owner and define the shared_feed

```C
#define FEED_OWNER "feedowner"
#define SHARED_FEED "counter"
```
Also change this.
```C
AdafruitIO_Feed *sharedFeed = io.feed("counter", FEED_OWNER);
```
For this.
```C
AdafruitIO_Feed *sharedFeed = io.feed(SHARED_FEED, FEED_OWNER);
```

You should left with something that look like this:

```C
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
```

## Final codes

### Adafruitio_00_publish

```C
#include "config.h"

int count = 0;
AdafruitIO_Feed *counter = io.feed("counter");

void setup() {

  Serial.begin(115200);

  while(! Serial);
  Serial.print("Connecting to Adafruit IO");

  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();

  Serial.print("sending -> ");
  Serial.println(count);
  counter->save(count);
  count++;
  
  delay(3000);
}
```

### adafruit_21_read_feed
Upload the second code to the other nodemcu

```C++
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
```
### config.h

```C
#define IO_USERNAME  "your_username"
#define IO_KEY       "your_key"

#define WIFI_SSID   "your_ssid"
#define WIFI_PASS   "your_pass"

#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
    #define SPIWIFI SPI
    #define SPIWIFI_SS 10  // Chip select pin
    #define NINA_ACK 9    // a.k.a BUSY or READY pin
    #define NINA_RESETN 6 // Reset pin
    #define NINA_GPIO0 -1 // Not connected
  #endif
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS, NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
  AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
```

### Testing

1. Put the first nodemcu (publish) in a powersource other than your laptop.
2. Put the second nodemcu (feed reader) in your laptop port.
3. Check your serial monitor and you see that you recive data from an other nodemcu.


Sending data to adafruit in serialmonitor: 
![alt text](https://github.com/smuldesign/sharedatanodemcu/blob/master/images/serialmonitor.png "Logo Title Text 1")
`Note: make sure your serial monitor is on 115200`
check your adafruit feed, you should see something like this.
![alt text](https://github.com/smuldesign/sharedatanodemcu/blob/master/images/reviced.png "Logo Title Text 1")
`Note: if it doesn't work look though the previous steps and look for things you missed`


## Questions
For questions you can contact me:
thisisfakegmail@gmail.com



## Author

* **Marc Heemskerk** - [Marc Heemskerk](https://github.com/X-Track)
