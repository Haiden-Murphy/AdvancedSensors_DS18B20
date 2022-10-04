//****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
//****************************************************************** 
//Statment of Authorship: 
///I, Haiden Murphy, student number 000839028 
//certify that this material is my original work. No other person's 
//work has been used without due acknowledgment and I have not made 
//my workavailable to anyone else.
//****************************************************************** 

// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 

// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire);

//numberOfDevices is declared as an int
int numberOfDevices;
//this variable is used to store the found device address
DeviceAddress tempAddress;

/**
 * Setup, sets up the program before running through the loop by using the 
 * Serial.begin() line. this is where the address of the device is displayed.
 * An if else stantment is used to print error message if numberOfDevices == 0
 * else it will print the addres of the device once to the terminal.
 **/
void setup() 
{//setup
  //configure the USB serial monitor 
  Serial.begin(115200); 
 
  //Start the DS18B20 sensor 
  DS18B20.begin();

  //numberOfDevices becomes the device count of the project
  numberOfDevices = DS18B20.getDeviceCount();
  //formatting
  Serial.println("");
  //title displays to screen
  Serial.println("Temperature Application");

  //if the number of devices is equal to 0 then print error
  if (numberOfDevices == 0)
  {
    //error/warning message
    Serial.println("No DS18B20 temperature sensors are installed!");
  }
  //else a for loop goes and searches for the amount of devices and
  //prints the address
  else
  {//else
    //for loop looks for devices
    for(int i=0;i<numberOfDevices; i++) 
    {//for
        // Search the wire for address
        if(DS18B20.getAddress(tempAddress, i)) 
        {//ifaddress
          Serial.print("Found DS18B20 sensor with address: ");
          //second for loop, the for loop that prints the address
          for (uint8_t i = 0; i < 8; i++) 
          {//for2
            if (tempAddress[i] < 16) Serial.print("0");
              //prints the temp address in hexidecimal
              Serial.print(tempAddress[i], HEX);
              
          }//for2
          Serial.println();
        }//ifaddress
    }//for
  }//else
}//setup


/**
 * The loop function has a group of if else statments the print out cold!, cold, 
 * perfect, warm, hot, and hot! depending on the current temperature being picked
 * up by the sensor. Another if statement checks if the temperature is not equal to 
 * -127.0 degrees celcius and if not the program will continue to run. But if it 
 * does equal the if statments will not find a value to print to the terminal.
 **/
void loop() 
{//loop
  //fTemp is declared a float variable
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures();
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0);

  //if the temperature being displyed is -127.0 (sensor disconnected) then print 
  if (fTemp != -127.0)
  {//ifnot-127
    // print the temp to the USB serial monitor 
    Serial.print("Current temperature is: " + String(fTemp) + "° C"); 

    //if and if else statmnets that allow to temperature to be read as cold, warm, etc.
    if(fTemp <= 10)
    {
      Serial.print(" or cold!");
    }
    else if(fTemp >= 35)
    {
      Serial.print(" or hot!");
    }
    else if(fTemp >= 30)
    {
      Serial.print(" or hot");
    }
    else if(fTemp >= 25)
    {
      Serial.print(" or warm");
    }
    else if(fTemp >= 15)
    {
      Serial.print(" or perfect");
    }
    else if(fTemp >= 10)
    {
      Serial.print(" or cool");
    }
    //formatting
    Serial.println();
  }//ifnot-127
 
  // wait 2s (2000ms) before doing this again 
  delay(2000); 
}//loop