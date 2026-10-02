#include "Define.h" 

void EEPROM_Init()
{
  EEPROM.begin(512);
  /*Reset the PowerCycle_Count to 0 on fresh EEPROM*/
  WC.PowerCycle_Count = EEPROM.read(EEPROM_POWERCYCLE_COUNT_ADDRESS);
  if(WC.PowerCycle_Count == 0xFF)
  {
    WC.PowerCycle_Count = 0;
    EEPROM.write(EEPROM_POWERCYCLE_COUNT_ADDRESS,WC.PowerCycle_Count);
    EEPROM.commit();
    WC.PowerCycle_Count = EEPROM.read(EEPROM_POWERCYCLE_COUNT_ADDRESS);
  }

  /*Reset the Inverse_Display_Flag to 1 on fresh EEPROM*/
  AC.Inverse_Display_Flag = EEPROM.read(EEPROM_DISPLAY_INVERSE_FLAG_ADDRESS);
  if(AC.Inverse_Display_Flag == 0xFF)
  {
    AC.Inverse_Display_Flag = 1;
    EEPROM.write(EEPROM_DISPLAY_INVERSE_FLAG_ADDRESS,AC.Inverse_Display_Flag);
    EEPROM.commit();
    AC.Inverse_Display_Flag = EEPROM.read(EEPROM_DISPLAY_INVERSE_FLAG_ADDRESS);
  }
}


void Write_String_EEPROM(uint16_t add,String data)
{
  uint16_t _size = data.length();
  uint16_t i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}


String Read_String_EEPROM(uint16_t add)
{
  char data[100]; //Max 100 Bytes
  uint16_t len=0;
  uint8_t k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
