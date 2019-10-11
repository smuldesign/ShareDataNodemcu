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
Arduino - https://www.arduino.cc/en/main/software
ESP8266 - http://arduino.esp8266.com/stable/package_esp8266com_index.json
```



### Prerequisites

What things you need to install the software and how to install them:
```
For this project you will need an adafruit io account.
https://io.adafruit.com
```
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


## Circuit Connections

We need to connect the led's to the nodemcu's


```
connect you LDR to your nodemcu
```

The LDR output is actually analog in nature, so it gets connected to the A0 pin of the NodeMCU.


## Authors

* **Rico Zethof** - [RicoZethof](https://github.com/rico1136)
* **Marc Heemskerk** - [MarcHeemskerk](https://github.com/X-Track)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
