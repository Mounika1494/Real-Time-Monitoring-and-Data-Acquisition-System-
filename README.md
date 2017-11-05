# Real time Monitoring and Data Acquisition System
Data acquisition of Temperature (TMP102) and Light (APDS 9301) Sensors with Message Queues and using priority preemptive threads
on a Beaglebone green.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

* Connect the TMP102 and APDS 9301 to the i2c2 bus of Beaglebone.
* We are used CMOCKA Unit test framework. Ensure you have installed it.

### Installing

A step by step series of examples that tell you have to get a development env running

First git clone the repo on the machine you want to test.

```
https://github.com/Mounika1494/Real-Time-Monitoring-and-Data-Acquisition-System-
```

Then run make

```
make
```

Output generated will be RT_LOGGER. You should give file name where you want to store sensor data and logger data
Note: You should run being a root or use sudo

```
sudo ./RT_LOGGER
```

### Using

* The data of sensors will be logged in <user_defined>.txt and all status/errors in <user_defined>.txt
* When you want to stop logging do a Ctrl+C
* Watch out for last led on the beagle bone. If the frequency of blink is too high then check your connections. The program     automatically recovers if you are able to correct the connections (even during runtime). On no error the frequency will be   less.  
* If you want to test your connections and sensors working there are unit tests in tests/ folder
* Change accordingly in Makefile and do a make
* For sample outputs/architecture see RealtimeDataAcquistion.pdf

## Authors

* **Jayakrishnan HJ** - https://github.com/hjjayakrishnan
* **Mounika Edula** - https://github.com/Mounika1494
