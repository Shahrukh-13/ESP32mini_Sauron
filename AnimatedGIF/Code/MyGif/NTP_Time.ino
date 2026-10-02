#include "Define.h" 

void NTP_Time_Init()
{
  NTP.gmtOffset_sec = -18000;
  NTP.daylightOffset_sec = 3600;
  NTP.ntpServer = "pool.ntp.org";
  NTP.Time = "none";
}

void Config_NTP_Time()
{
  configTime(NTP.gmtOffset_sec, NTP.daylightOffset_sec, NTP.ntpServer);
  GetLocalTime();
}

void GetLocalTime()
{
  char chBuffer[81];
  time_t rawtime;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain date and time");
    NTP.Date = "Failed to obtain time";
    NTP.Time = "Failed to obtain time";
    ESP.restart();
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  
  //Serial.println(timeinfo.tm_mday);
  /*tm_sec: seconds after the minute;
  tm_min: minutes after the hour;
  tm_hour: hours since midnight;
  tm_mday: day of the month;
  tm_year: years since 1900;
  tm_wday: days since Sunday;
  tm_yday: days since January 1;
  tm_isdst: Daylight Saving Time flag;*/ 

  //time (&rawtime);
  //Date_Time = asctime(localtime (&rawtime));

  strftime(NTP.chHour, sizeof(NTP.chHour), "%I", & timeinfo);
  strftime(NTP.chMinute, sizeof(NTP.chMinute), "%M", & timeinfo);
  
  // Then obtain day of week, day of month, month and year.
    
  strftime(NTP.chDayofWeek, sizeof(NTP.chDayofWeek), "%A", & timeinfo);
  strftime(NTP.chDayOfMonth, sizeof(NTP.chDayOfMonth), "%d", & timeinfo);
  strftime(NTP.chMonth, sizeof(NTP.chMonth), "%B", & timeinfo);
  strftime(NTP.chYear, sizeof(NTP.chYear), "%Y", & timeinfo);
  strftime(NTP.AM_PM, sizeof(NTP.AM_PM), "%p", & timeinfo);
  
   //sprintf(chBuffer, "%s, %s %s, %s, %s:%s %s", String(chDayofWeek), String(chMonth), String(chDayOfMonth), String(chYear), String(chHour), String(chMinute), String(AM_PM));
   
   sprintf(chBuffer, "%s, %s %s, %s", String(NTP.chDayofWeek), String(NTP.chMonth), String(NTP.chDayOfMonth), String(NTP.chYear));
   NTP.Date = String(chBuffer);
   sprintf(chBuffer, "%s:%s %s", String(NTP.chHour), String(NTP.chMinute), String(NTP.AM_PM));
   NTP.Time = String(chBuffer);
   NTP.Time = NTP.Time.substring(0,NTP.Time.indexOf(':')) + " : " + NTP.Time.substring(NTP.Time.indexOf(':')+1); // Adding a space between for ':' so it is easy to read
  //Serial.print(Date_Time);
}
