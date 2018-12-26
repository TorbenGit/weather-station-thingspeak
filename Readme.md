Weather station with a ESP8266 and DHT11 or DHT22. The ESP will send the Data to your ThingSpeak Account.

You just have to edit the secrets.h file except you want to change the interval of sending data. (current interval: 15minutes)
You have to use a 4.7k Resistor.

You need this libraries: DHT: https://github.com/adafruit/Adafruit_Sensor and https://github.com/adafruit/DHT-sensor-library

ThingSpeak: https://github.com/mathworks/thingspeak-arduino
