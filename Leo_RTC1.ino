#include <TimeLib.h>  // to handle the timing
#include <DS1307RTC.h> // to handle the DS1307RTC
bool debug = false; // debug off
String errore =""; //string for error check across the libraries

void setup() {
Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
while (!Serial) {
    ;               // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
String Date = ReadDateTime(); 
Serial.print(Date);
Serial.println();
delay(1500); 

  if( errore!="") {
  //here the code of the error
  }
}


/*
Leo_RTC1, 
DS1307 function ver 23-9-2018

Need the :                  
#include <DS1307RTC.h> // to handle the DS1307RTC (this lib call also wire.h for the I2C)
#include <TimeLib.h> // to handle the timing
String errore =""; //string for error check across the libraries

Errors :
rtc01 error is = The DS1307 is stopped.  Please run the SetTime.
rtc02 error is = DS1307 read error!  Please check the circuitry.

Debug:
bool debug = false; // debug off

if debug = true  will print on the serial print all the data and errors.
 */

String ReadDateTime(){

String date;  // internal variable to handle the date

//Date from RTC
 tmElements_t tm;
  
  if (RTC.read(tm)) {
    date = String(tmYearToCalendar(tm.Year)) + "/" + String(tm.Month) + "/" + String(tm.Day)+",";
    date += String(tm.Hour) + ":" + String(tm.Minute) + ":" + String(tm.Second)+",";  
    
    if (debug == true){  //write to the serial all the data that has been read.
    Serial.print("Ok, Time:");
    Serial.print (tm.Hour);
    Serial.write(':');
    Serial.print (tm.Minute);
    Serial.write(':');
    Serial.print (tm.Second);
    Serial.print(", Date: ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
    }
    
    }else {
      if (RTC.chipPresent()) {
      if(debug) Serial.println("Error #rtc01: The DS1307 is stopped.  Please run the SetTime");
      if(debug) Serial.println();
      errore = "#rtc01";
      return("0");
      } else {
        if(debug) Serial.println("Error #rtc02: DS1307 read error!  Please check the circuitry.");
        if(debug) Serial.println();
        errore = "#rtc02";
        return("0");
      }
    delay(9000); // in case of errors wait 9 seconds
    }
 return(date);
}



