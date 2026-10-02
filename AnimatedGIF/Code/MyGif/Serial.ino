#include "Define.h" 

void scan_connect_reset()
{  
  while (Serial.available() > 0)
  {            
    //input += (char) Serial.read(); 
    input =Serial.readString();
    //command =input.substring(0,input.length()-2);  //both NL and CR
    command =input.substring(0,input.length());  // No newline
    if(command == "scan")
    {      
      Serial.println("scan start");
      // WiFi.scanNetworks will return the number of networks found
      int n = WiFi.scanNetworks();
      Serial.println("scan done");
      if (n == 0) 
      {
        Serial.println("no networks found");
      } 
      else 
      {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) 
        {            
          // Print SSID and RSSI for each network found
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
          Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          delay(10);
        }
      }
      Serial.println("");
      Serial.print("If you want to connect to a new network, enter 'ssid' and 'passowrd' in following format: ssid,password");
      Serial.println();
    }

    else if(command == "reset")
    {
      ESP.restart();        
    }

    else if(command == "display_inverse")
    {
      AC.Inverse_Display_Flag = !AC.Inverse_Display_Flag;
      EEPROM.write(EEPROM_DISPLAY_INVERSE_FLAG_ADDRESS,AC.Inverse_Display_Flag);
      EEPROM.commit();
      Serial.println();
      Serial.print("Inverse_Display_Flag: ");
      Serial.print(AC.Inverse_Display_Flag);   
      Serial.println(); 
    }
    
    else if(command.indexOf(",") >= 0)
    {
      WC.ssid_i = input.substring(0,input.indexOf(','));
      WC.password_i =   input.substring(input.indexOf(',')+1);
  
      Write_String_EEPROM(EEPROM_SSID_ADDRESS, WC.ssid_i);
      Write_String_EEPROM(EEPROM_PASSWORD_ADDRESS, WC.password_i);
  
      Serial.println();
      Serial.print("new ssid: ");
      Serial.print(WC.ssid_i);
      Serial.print(" , ");
      Serial.print("new password: ");
      Serial.print(WC.password_i);
      Serial.println();
           
      delay(5); 
    }
  }
}

void display_menu()
{
  Serial.println();
  Serial.print("Enter 'scan' to scan for available networks");
  Serial.println();
  Serial.print("If you want to connect to a new network, enter 'ssid' and 'passowrd' in following format: ssid,password");
  Serial.println();
  Serial.print("Enter 'reset' to reset");
  Serial.println();
}
