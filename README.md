# sharedatanodemcu

A manual how to connect data from 1 nodemcu with other nodemcu's with Wifi and Adafruit.



## Hardware Required

2x* nodemcu
1x LDR / photoresistor
10k ohm resistor
Breadboard
Micro USB cable
Connecting Wires

*You can have multiple nodemcu's but for this example i use just 2.



### Software Required

```
Arduino IDE (with ESP8266 Library installed)

```

[Arduino IDE](https://www.arduino.cc/en/main/software)
[ESP8266 Library](http://arduino.esp8266.com/stable/package_esp8266com_index.json)



### Prerequisites

What things you need to install the software and how to install them:
```
For this project you will need an adafruit io account.
https://io.adafruit.com
```

[Adafruit](https://io.adafruit.com)

```
Get your AIO Key (right upper corner on adafruitio dashboard).
```
```
Get you Wifi SSID and PASSWORD ready.
```


### Arduino libaries

Open up arduino go to Sketch --> Include libary --> Manage Libaries
(Shift + CMD + I)

And search for the following libaries:

```
Adafruit IO Arduino by:Adafruit
(latest version)
```


### Circuit Connections

We need to connect the led's to the nodemcu's


```
connect you LDR to your nodemcu
```

The LDR output is actually analog in nature, so it gets connected to the A0 pin of the NodeMCU.



### Coding Time

```C
void setup() {
	Serial.begin(9600);   // initialize serial communication at 9600 BPS
}
```
```C
void loop() {

	int sensorValue = analogRead(A0);   // read the input on analog pin 0

	float voltage = sensorValue * (5.0 / 1023.0);   // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)

	Serial.println(voltage);   // print out the value you read

}
```



## Authors

* **Marc Heemskerk** - [Marc Heemskerk](https://github.com/X-Track)
