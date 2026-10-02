#include "Define.h" 

String input = "";
String command = "";

void setup() 
{
  Serial.begin(115200);
  EEPROM_Init();
  LCD_Init();
  NTP_Time_Init();
  pinMode(39, INPUT); 

  if(digitalRead(39) == LOW)
  {
    display_menu();
    AC.Display_GIF = 0;
    AC.Display_GIF_Time = 0;
  }
  else
  {
    AC.Display_GIF = 1;
    AC.Display_GIF_Time = 1;
    WiFi_Init();
  }

  if(AC.Display_GIF == 1 && AC.Display_GIF_Time == 1)
  {
    Serial.println(" CONNECTED");
    LCD_Screen_Black();
    LCD_Write("Connected", tft.width() / 2, tft.height() / 2, 4);
    LCD_Write(WiFi.localIP().toString(), tft.width() / 2, (tft.height() / 2) + 30, 4);
            
    //init and get the time
    Config_NTP_Time();
   
    //disconnect WiFi as it's no longer needed
    //WiFi.disconnect(true);
    //WiFi.mode(WIFI_OFF);
    tft.fillScreen(TFT_BLACK);
    
    //Update WebPage
    Update_WebPage();    
    
    // Send web page with input fields to client
    Send_WebPage(); 
    
    // Send a GET request to <ESP_IP>
    Get_WebPage();
    
    server.onNotFound(notFound);
    server.begin();
  }
}

void loop()
{
  if(AC.Display_GIF == 0 && AC.Display_GIF_Time == 0)
  {
    scan_connect_reset();
  }
  if(AC.Display_GIF == 1 && AC.Display_GIF_Time == 0)
  { 
    gif.playFrame(false, NULL);
    scan_connect_reset();
  }
  else if(AC.Display_GIF == 1 && AC.Display_GIF_Time == 1)
  {
    //tft.drawString(Date_Time, 0, 0, 4);;
    tft.drawString(NTP.Date, tft.width() / 2 + 75, 194, 2);
    tft.drawString(NTP.Time, tft.width() / 2 + 75, 214, 2);
    gif.playFrame(false, NULL);
    GetLocalTime(); 
  } 
}
