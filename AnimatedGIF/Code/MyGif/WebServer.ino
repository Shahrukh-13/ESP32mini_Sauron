#include "Define.h" 

const char* PARAM_INPUT_1  = "input1";
const char* PARAM_INPUT_2  = "input2";
const char* PARAM_INPUT_3  = "input3";
const char* PARAM_INPUT_4  = "input4";
String temp_str;
uint16_t temp_int;

void Update_WebPage()
{
  WS.html = "<!DOCTYPE HTML><html><head>";
  WS.html+= "<title>ESP Input Form</title>";
  WS.html+= "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  WS.html+= "<title>ESP Input Form</title>";
  WS.html+= "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  WS.html+= "</head><body>";

  // Heading: print connected network SSID
  WS.html+= "<h2>";
  WS.html+= "Connected to SSID: " + WC.ssid_str;
  WS.html+= "<br><br>"; //new line in heading
  WS.html+= "</h2>";

  // Heading: print connected network SSID
  WS.html+= "<h3>";
  WS.html+= "Saved SSID: " + WS.Saved_WiFi_SSID;
  WS.html+= "<br>"; //new line in heading
  WS.html+= "</h3>";
  
  // Input field for New WiFi SSID
  WS.html+= "<form action=\"/get\">";
  WS.html+= "New WiFi SSID: <input type=\"text\" name=\"input1\">";
  WS.html+= "<br><br>";
  
  // Input field for New WiFi Password
  WS.html+= "New WiFi Password: <input type=\"password\" name=\"input2\">";
  WS.html+= "<input type=\"submit\" value=\"Submit\">";
  WS.html+= "</form><br><br>";

  // Heading to display current saved Display Flag value in EEPROM
  WS.html+= "<h3>";
  WS.html+= "Saved Display Falg Value: " + String(AC.Inverse_Display_Flag);
  WS.html+= "<br>"; //new line in heading
  WS.html+= "</h3>";

  // Input button for Inverting dislay flag in EEPROM
  WS.html+= "<form action=\"/get\">";
  WS.html+= "Inverse Display: <input type=\"submit\" name=\"input3\" value=\"Submit\">";
  WS.html+= "</form><br><br>";

  // Input button to Reset ESP32
  WS.html+= "<form action=\"/get\">";
  WS.html+= "Reset ESP32: <input type=\"submit\" name=\"input4\" value=\"Submit\">";
  WS.html+= "</form><br><br>";
  
  WS.html+= "</body></html>";
  
  WS.html.toCharArray(WS.index_html, WS.html.length()+1);
}

void Send_WebPage()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", WS.index_html);
  });
}

void Get_WebPage()
{    
  // Send a GET request to <ESP_IP>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) 
  {
    String temp_str;
    uint16_t temp_int;
        
    // GET input1 and input2 value on <ESP_IP>/get?input1=<VAL>&input2=<VAL>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) 
    {
      WS.New_WiFi_SSID = request->getParam(PARAM_INPUT_1)->value();
      WS.New_WiFi_Password = request->getParam(PARAM_INPUT_2)->value();
      if(WS.New_WiFi_SSID != WS.Saved_WiFi_SSID)
      {
        #ifdef SERIAL_DEBUG
          Serial.println(WS.New_WiFi_SSID);
        #endif
        WS.Saved_WiFi_SSID = WS.New_WiFi_SSID;
        Write_String_EEPROM(EEPROM_SSID_ADDRESS,WS.New_WiFi_SSID);
        WS.Saved_WiFi_SSID = Read_String_EEPROM(EEPROM_SSID_ADDRESS);
      }
      if(WS.New_WiFi_Password != WS.Saved_WiFi_Password)
      {
        #ifdef SERIAL_DEBUG
          Serial.println(WS.New_WiFi_Password);
        #endif
        WS.Saved_WiFi_Password = WS.New_WiFi_Password;
        Write_String_EEPROM(EEPROM_PASSWORD_ADDRESS,WS.New_WiFi_Password);
        WS.Saved_WiFi_Password = Read_String_EEPROM(EEPROM_PASSWORD_ADDRESS);
      }
    }
        
    else if(request->hasParam(PARAM_INPUT_3))
    {
      AC.Inverse_Display_Flag = !AC.Inverse_Display_Flag;
      EEPROM.write(EEPROM_DISPLAY_INVERSE_FLAG_ADDRESS, AC.Inverse_Display_Flag);
      EEPROM.commit();
      AC.Inverse_Display_Flag = EEPROM.read(EEPROM_DISPLAY_INVERSE_FLAG_ADDRESS);
      #ifdef SERIAL_DEBUG
        Serial.println(AC.Inverse_Display_Flag);
      #endif
    }

    else if(request->hasParam(PARAM_INPUT_4))
    {
      ESP.restart();
    }
    
    Update_WebPage();
    
    request->send_P(200, "text/html", WS.index_html);
  });
}

void notFound(AsyncWebServerRequest *request) 
{
  request->send(404, "text/plain", "Not found");
}
