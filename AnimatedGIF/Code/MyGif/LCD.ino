#include "Define.h" 

void LCD_Init()
{
  tft.begin();
  tft.setRotation(1);
  tft.invertDisplay(AC.Inverse_Display_Flag); // depending on the variant of LCD being used
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  gif.begin(BIG_ENDIAN_PIXELS);
  gif.open((uint8_t *)GIF_IMAGE, sizeof(GIF_IMAGE), GIFDraw);
  tft.startWrite(); 
  tft.setTextDatum(TC_DATUM);
}

void LCD_Write(String str, uint8_t x, uint8_t y, uint8_t text_font)
{
  if(x > tft.width())
  {
    x = tft.width();
  }
  else
  {
    /*Do Nothing*/
  }

  if(y > tft.height())
  {
    y = tft.height();
  }
  else
  {
    /*Do Nothing*/
  }

   tft.drawString(str, x, y, text_font);
}

void LCD_Screen_Black()
{
  tft.fillScreen(TFT_BLACK);
}
