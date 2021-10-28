#include "SPI.h"
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite screen = TFT_eSprite(&tft);

#define GFXFF 1
#define BACKGROUND_COLOR TFT_BLACK

int intArgs[4];

void setup(void)
{
    tft.begin();
    tft.setRotation(3);

    screen.createSprite(tft.width(), tft.height());

    screen.setTextColor(TFT_WHITE);
    screen.setFreeFont(&FreeSansBold12pt7b);

    screen.fillScreen(BACKGROUND_COLOR);

    screen.pushSprite(0, 0);
}

void loop()
{
  handleSerialCommand();
}

void handleSerialCommand()
{
  char *line = readLine();

  if (line != NULL)
  {    
    Serial.println(line);
    
    char *cmd = strtok(line, " ");

    if (strcasecmp(cmd, "us") == 0)
    {
      screen.pushSprite(0, 0);
    }
    else if (strcasecmp(cmd, "fs") == 0)
    {
        char *fillColor = strtok(NULL, " ");

        if (fillColor != NULL)
        {
          screen.fillRect(0, 0, tft.width(), tft.height(), (uint)strtol(fillColor, 0, 16));
        }
    }
    else if (strcasecmp(cmd, "dr") == 0)
    {
      if (getIntArgs(4))
      {
        char *drawColor = strtok(NULL, " ");

        if (drawColor != NULL)
        {
          screen.drawRect(intArgs[0], intArgs[1], intArgs[2], intArgs[3], (uint)strtol(drawColor, 0, 16));
        }
      }
    }
    else if (strcasecmp(cmd, "fr") == 0)
    {
      if (getIntArgs(4))
      {
        char *drawColor = strtok(NULL, " ");

        if (drawColor != NULL)
        {
          screen.fillRect(intArgs[0], intArgs[1], intArgs[2], intArgs[3], (uint)strtol(drawColor, 0, 16));
        }
      }    
    }
    else if (strcasecmp(cmd, "tf") == 0)
    {
      char *font = strtok(NULL, "");

      if (font != NULL)
      {
        if (strcasecmp(font, "FSSB9") == 0)
        {
          screen.setFreeFont(&FreeSansBold9pt7b);
        }
        else if (strcasecmp(font, "FSSB12") == 0)
        {
          screen.setFreeFont(&FreeSansBold12pt7b);          
        }
        else if (strcasecmp(font, "FSSB18") == 0)
        {
          screen.setFreeFont(&FreeSansBold18pt7b);          
        }
        else if (strcasecmp(font, "FSSB24") == 0)
        {
          screen.setFreeFont(&FreeSansBold24pt7b);          
        }
      }
    }
    else if (strcasecmp(cmd, "tc") == 0)
    {
        char *textColor = strtok(NULL, "");

        if (textColor != NULL)
        {
          screen.setTextColor((uint)strtol(textColor, 0, 16));
        }      
    }
    else if (strcasecmp(cmd, "ta") == 0)
    {
      char *alignment = strtok(NULL, "");

      if (strcasecmp(alignment, "tc") == 0)
      {
        screen.setTextDatum(TC_DATUM);
      }
      else if (strcasecmp(alignment, "tr") == 0)
      {
        screen.setTextDatum(TR_DATUM);
      }      
      else if (strcasecmp(alignment, "ml") == 0)
      {
        screen.setTextDatum(ML_DATUM);
      }    
      else if (strcasecmp(alignment, "mc") == 0)
      {
        screen.setTextDatum(TL_DATUM);
      }    
      else if (strcasecmp(alignment, "tl") == 0)
      {
        screen.setTextDatum(MC_DATUM);
      }    
      else if (strcasecmp(alignment, "mr") == 0)
      {
        screen.setTextDatum(MR_DATUM);
      }    
      else if (strcasecmp(alignment, "bl") == 0)
      {
        screen.setTextDatum(BL_DATUM);
      }    
      else if (strcasecmp(alignment, "bc") == 0)
      {
        screen.setTextDatum(BC_DATUM);
      }    
      else if (strcasecmp(alignment, "br") == 0)
      {
        screen.setTextDatum(BR_DATUM);
      }    
    }
    else if (strcasecmp(cmd, "dt") == 0)
    {
      if (getIntArgs(2))
      {
        char *text = strtok(NULL, "");

        if (text != NULL)
        {
          screen.drawString(text, intArgs[0], intArgs[1], GFXFF);
        }
      }
    }
  }
}

bool getIntArgs(int numIntArgs)
{
  for (int i = 0; i < numIntArgs; i++)
  {
    char *intStr = strtok(NULL, " ");

    if (intStr == NULL)
      return false;

    intArgs[i] = atoi(intStr);
  }

  return true;
}

const int numChars = 256;
char receivedChars[numChars];
byte ndx = 0;

char *readLine()
{
  char rc;
 
  while (Serial.available() > 0)
  {
    rc = Serial.read();
    
    if (rc != '\n')
    {
      receivedChars[ndx] = rc;      
      ndx++;

      if (ndx >= numChars)
      {
        ndx = numChars - 1;
      }
    }
    else
    {    
      receivedChars[ndx] = '\0';
      ndx = 0;

      return receivedChars;
    }
  }

  return NULL;
}
