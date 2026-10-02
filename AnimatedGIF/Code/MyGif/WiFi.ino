#include "Define.h" 

void WiFi_Init()
{
  WC.wifi_connection_timeout_count = 0;
  
  WC.ssid_i = Read_String_EEPROM(EEPROM_SSID_ADDRESS);
  WC.password_i = Read_String_EEPROM(EEPROM_PASSWORD_ADDRESS);

  WS.Saved_WiFi_SSID = WC.ssid_i;
  WS.Saved_WiFi_Password = WC.password_i;
  
  WC.ssid_i.toCharArray(WC.ssid, WC.ssid_i.length()+1);
  WC.password_i.toCharArray(WC.password, WC.password_i.length()+1);
    
  //connect to WiFi
  Serial.printf("Connecting to %s ", WC.ssid);
  WiFi.begin(WC.ssid, WC.password);
  while (WiFi.status() != WL_CONNECTED && WC.wifi_connection_timeout_count <10) 
  {
    delay(500);
    Serial.print(".");
    LCD_Write("Connecting", tft.width() / 2 + 75, 194, 2);
    WC.wifi_connection_timeout_count++;
  }
  
  if(WC.wifi_connection_timeout_count >=10)
  {
    if(WC.PowerCycle_Count <5)
    {
      WC.PowerCycle_Count++;
      EEPROM.write(EEPROM_POWERCYCLE_COUNT_ADDRESS,WC.PowerCycle_Count);
      EEPROM.commit();
      ESP.restart();
    }
    else
    {
      //disconnect WiFi as it's no longer needed
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      display_menu();
      AC.Display_GIF = 1;
      AC.Display_GIF_Time = 0;
      WC.PowerCycle_Count = 0;
      EEPROM.write(EEPROM_POWERCYCLE_COUNT_ADDRESS,WC.PowerCycle_Count);
      EEPROM.commit();
      LCD_Screen_Black();
      LCD_Write("5 Fails", tft.width() / 2, tft.height() / 2, 4);
      LCD_Write("Display Default GIF", tft.width() / 2, (tft.height() / 2) + 20, 4);
      delay(2000);
    }
  }
}

void WiFi_Reconnect()
{
  WiFi.disconnect();
  WiFi.reconnect();
}
