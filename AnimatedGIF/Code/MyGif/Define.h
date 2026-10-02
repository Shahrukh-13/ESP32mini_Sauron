#ifndef DEFINE_H
#define DEFINE_H

#include <WiFi.h>
#include <TFT_eSPI.h>
#include <AnimatedGIF.h>
#include <EEPROM.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Sauron.h" 
#include "time.h"   

#define EEPROM_SSID_ADDRESS                   0
#define EEPROM_PASSWORD_ADDRESS               101
#define EEPROM_POWERCYCLE_COUNT_ADDRESS       202
#define EEPROM_DISPLAY_INVERSE_FLAG_ADDRESS   203

#define NORMAL_SPEED  // Comment out for rame rate for render speed test
#define GIF_IMAGE Sauron


AnimatedGIF gif;
TFT_eSPI tft = TFT_eSPI();

//Declare the asynchronous web server object on port 80
AsyncWebServer server(80);

struct wifi_config
{
  uint8_t wifi_connection_timeout_count;
  uint8_t PowerCycle_Count;
  bool wifi_flag;
  String ssid_i;
  String password_i; 
  char ssid[50];
  char password[50];
};

struct ntp_time
{
  long gmtOffset_sec;
  int daylightOffset_sec;
  String Date;
  String Year;
  String Time;
  char chDayOfMonth[3];                                    // Day of month (0 through 31).
  char chDayofWeek[4];                                     // Day of week (Sunday through Saturday).
  char chHour[3];                                          // Hour.
  char chMinute[3];                                        // Minute.
  char chMonth[4];                                         // Month.
  char* ntpServer;
  char chSecond[3];                                        // Second.
  char chYear[5];                                          // Year.
  char AM_PM[3];                                           // AM/PM.
};

struct app_config
{
  bool Display_GIF;
  bool Display_GIF_Time;
  uint8_t Inverse_Display_Flag;
};

struct webserver_info
{
  String html;
  char index_html[2500];
  String Saved_WiFi_SSID;
  String Saved_WiFi_Password; 
  String New_WiFi_SSID;
  String New_WiFi_Password; 
  uint8_t Plant1_Valve_Open_Sec;
};

struct wifi_config WC;
struct app_config AC;
struct ntp_time NTP;
struct webserver_info WS;

#endif // DEFINE_H
