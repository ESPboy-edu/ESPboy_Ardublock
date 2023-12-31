 #include <avr/pgmspace.h>

#include <Wire.h>
 #include <Adafruit_MCP23X17.h>

#include <EEPROM.h>


int pltX = 56;
int pltY = 120;
int pltXprev = pltX;
int sphY = 102;
int sphYprev = sphY;
int sphX = pltX + 20;
int sphXprev = sphX;
int sphDX = 2;
int sphDY = -1;
byte gameID = 133;
byte scorePrev = 0;
byte scoreGame = 0;
boolean switchFlag = 0;
boolean keyLeft = 0;
boolean keyRight = 0;
boolean keyUp = 0;
boolean keyDown = 0;
boolean keyAct = 0;
boolean keyEsc = 0;

const unsigned char platform[] PROGMEM= {0x1f, 0xff, 0xff, 0xff, 0xf8, 0x7b, 0x33, 0x53, 0x77, 0x5e, 0xf5, 0x55, 0x55, 0x6a, 0xd7, 0xf1,    0x35, 0x53, 0x6a, 0xcf, 0xf5, 0x55, 0x55, 0x6a, 0xd7, 0x75, 0x53, 0x13, 0x37, 0x5e, 0x1f, 0xff,   0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xff, 0xe0};

const unsigned char sphere[] PROGMEM= {0x3c, 0x6e, 0xdf, 0xdf, 0xff, 0xff, 0x7e, 0x3c};

#include <SPI.h>
 #include <Adafruit_GFX.h>
 #include <Adafruit_ST7735.h>
 Adafruit_ST7735 tft1=Adafruit_ST7735((-1),16,(-1));

Adafruit_MCP23X17 mcp;

const unsigned char ESPboylogo[] PROGMEM= { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x1e, 0x00,   0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc1, 0xf8,   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xc3, 0xfc, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d,   0xc7, 0xfe, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0xfe, 0x1e, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xfe, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x05, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xfe, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x82, 0x7c, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc1,   0xf8, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,   0x0b, 0xc0, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xc0, 0xf0, 0x37, 0x00, 0x00, 0x00,   0x00, 0x00, 0x07, 0x81, 0xf8, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xb8,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0xf0, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f,   0xc0, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00,   0x00, 0x0b, 0xc0, 0xf0, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xc1, 0xf8, 0x37, 0x00, 0x00,   0x00, 0x00, 0x00, 0x07, 0x81, 0xf8, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x78, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x01, 0xe0, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03,   0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x02, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0xdc, 0x03, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x3c, 0x00, 0x00,   0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x7e,   0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x70,   0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00,   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,   0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe7, 0xef, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xef,   0xef, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0c, 0x0c, 0x6f, 0x8f, 0x33, 0x00, 0x00, 0x00,   0x07, 0xcf, 0x8c, 0x6f, 0xdf, 0xb3, 0x00, 0x00, 0x00, 0x07, 0xc7, 0xcf, 0xec, 0xd9, 0xb3, 0x00,   0x00, 0x00, 0x07, 0x03, 0xef, 0xcc, 0xd9, 0xb3, 0x00, 0x00, 0x00, 0x07, 0x00, 0x6c, 0x0c, 0xd9,   0xb3, 0x00, 0x00, 0x00, 0x07, 0xef, 0xec, 0x0f, 0xdf, 0xbf, 0x00, 0x00, 0x00, 0x07, 0xef, 0xcc,   0x0f, 0x8f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00};

 #include <Adafruit_NeoPixel.h>
 #ifdef __AVR__
  #include <avr/power.h>
 #endif

Adafruit_NeoPixel pixels_2 = Adafruit_NeoPixel(1, 2, NEO_GRB + NEO_KHZ800);

long temps1=0 ;

void mainGame() {
  scoreGame = 0;
  sphY = 102;
  sphYprev = sphY;
  sphX = pltX + 20;
  sphXprev = sphX;
  sphDX = 2;
  sphDY = -1;
  tft1.fillScreen(ST7735_BLACK);
       tft1.setCursor(2, 0);
     tft1.setTextColor(ST7735_YELLOW,0);
      tft1.setTextSize(1);
     tft1.println("SCORE:");
         tft1.setCursor(40, 0);
     tft1.setTextColor(ST7735_WHITE,0);
      tft1.setTextSize(1);
     tft1.println(String(scoreGame));
    tft1.drawFastVLine(0, 9, 128, 0xFFFF); tft1.drawFastVLine(127, 9, 128, 0xFFFF); tft1.drawFastHLine(0, 9, 128, 0xFFFF);
  while (1 == 1){
    delay(0);
    getKeys();
    if (keyRight && pltX < 86) {
      pltX = pltX + 1;
    }
    if (keyLeft && pltX > 2) {
      pltX = pltX - 1;
    }
    if (sphX > 117 || sphX < 3) {
      sphDX = 0 - sphDX;
      noTone(0);
      tone(0, 10, 10);
    }
    if (sphY > 118 || sphY < 11) {
      sphDY = 0 - sphDY;
      noTone(0);
      tone(0, 10, 10);
    }
    sphX = sphX + sphDX;
    sphY = sphY + sphDY;
    tft1.drawBitmap(pltXprev,pltY,platform,40,8,ST7735_BLACK);
    tft1.drawBitmap(pltX,pltY,platform,40,8,ST7735_MAGENTA);
    tft1.drawBitmap(sphXprev,sphYprev,sphere,8,8,ST7735_BLACK);
    tft1.drawBitmap(sphX,sphY,sphere,8,8,ST7735_YELLOW);
    if (sphY > pltY - 8) {
      if (sphX > pltX - 8 && sphX < pltX + 40) {
             tft1.setCursor(40, 0);
           tft1.setTextColor(ST7735_BLACK,0);
            tft1.setTextSize(1);
           tft1.println(String(scoreGame));
          scoreGame = scoreGame + 1;
             tft1.setCursor(40, 0);
           tft1.setTextColor(ST7735_WHITE,0);
            tft1.setTextSize(1);
           tft1.println(String(scoreGame));
          sphDY = 0 - sphDY;
        tone(0, 100, 30);
      } else {
        tone(0,50,1500);
         delay(1500);
        break;
         }
    }
    pltXprev = pltX;
    sphXprev = sphX;
    sphYprev = sphY;
    delay(1);
  }
}

void initESPboy() {
   mcp.digitalWrite(8, 0);
  mcp.digitalWrite(9, 1);
    for (int i=0;i<8;i++)mcp.pinMode(i, INPUT_PULLUP);
  tft1.drawBitmap(30,24,ESPboylogo,68,64,ST7735_YELLOW);
       tft1.setCursor(15, 102);
     tft1.setTextColor(ST7735_YELLOW,0);
      tft1.setTextSize(1);
     tft1.println("Ardublock SQUASH");
    pixels_2.setBrightness(10);
   pixels_2.setPixelColor(1-1, pixels_2.Color(255,255,0));
   pixels_2.show();
   delay(1000);
  pixels_2.setBrightness(0);
   pixels_2.setPixelColor(1-1, pixels_2.Color(0,0,0));
   pixels_2.show();
   tft1.fillScreen(ST7735_BLACK);
  pinMode(2, OUTPUT);
   digitalWrite(2, 1);
}

void getKeys() {
  uint8_t keysReaded = ~mcp.readGPIOAB() & 255;
  keyLeft = keysReaded & 1;
  keyUp = keysReaded & 2;
  keyDown = keysReaded & 4;
  keyRight = keysReaded & 8;
  keyAct = keysReaded & 16;
  keyEsc = keysReaded & 32;
}

void loadScore() {
  scorePrev = EEPROM.read(10);
  if (scorePrev == gameID) {
    scorePrev = EEPROM.read(11);
  } else {
    scorePrev = 0;
    scoreGame = 0;
    saveScore();
  }
}

void startScreen() {
  tft1.fillScreen(ST7735_BLACK);
       tft1.setCursor(46, 10);
     tft1.setTextColor(ST7735_YELLOW,0);
      tft1.setTextSize(1);
     tft1.println("ESPboy");
         tft1.setCursor(10, 28);
     tft1.setTextColor(ST7735_GREEN,0);
      tft1.setTextSize(2);
     tft1.println("Ardublock");
         tft1.setCursor(10, 54);
     tft1.setTextColor(ST7735_MAGENTA,0);
      tft1.setTextSize(3);
     tft1.println("SQUASH");
         tft1.setCursor(34, 89);
     tft1.setTextColor(ST7735_RED,0);
      tft1.setTextSize(1);
     tft1.println("HIGH SCORE");
    loadScore();
       tft1.setCursor((136-((String)scorePrev).length()*12)/2, 100);
     tft1.setTextColor(ST7735_RED,0);
      tft1.setTextSize(1);
     tft1.println(String(scorePrev));
    pressAct();
}

void saveScore() {
  EEPROM.write(10,gameID);
   EEPROM.write(11,scoreGame);
   EEPROM.commit();
}

void pressAct() {
  while (keyAct == 0){
    getKeys();
    if ((millis()-temps1)>=1*1000) {
      temps1=millis();
      switchFlag = !switchFlag;
    }
    if (switchFlag) {
           tft1.setCursor(10, 120);
         tft1.setTextColor(ST7735_WHITE,0);
          tft1.setTextSize(1);
         tft1.println("press [Act] button");
        } else {
           tft1.setCursor(10, 120);
         tft1.setTextColor(ST7735_BLACK,0);
          tft1.setTextSize(1);
         tft1.println("press [Act] button");
        }
  }
  waitUnpressed();
}

void gameOver() {
  tft1.fillScreen(ST7735_BLACK);
       tft1.setCursor(10, 18);
     tft1.setTextColor(ST7735_MAGENTA,0);
      tft1.setTextSize(3);
     tft1.println("SQUASH");
         tft1.setCursor(34, 48);
     tft1.setTextColor(ST7735_YELLOW,0);
      tft1.setTextSize(2);
     tft1.println("SCORE");
         tft1.setCursor((128-((String)scoreGame).length()*12)/2, 70);
     tft1.setTextColor(ST7735_WHITE,0);
      tft1.setTextSize(2);
     tft1.println(String(scoreGame));
    if (scoreGame > scorePrev) {
         tft1.setCursor(16, 93);
       tft1.setTextColor(ST7735_RED,0);
        tft1.setTextSize(1);
       tft1.println("CONGRATULATIONS!");
           tft1.setCursor(34, 103);
       tft1.setTextColor(ST7735_RED,0);
        tft1.setTextSize(1);
       tft1.println("HIGH SCORE");
      saveScore();
  }
  pressAct();
}

void waitUnpressed() {
  while (keyAct == 1){
    getKeys();
    delay(100);
  }
}


void setup() {
  pinMode(0, OUTPUT);
    EEPROM.begin(100);

     tft1.initR(INITR_REDTAB);
  tft1.setRotation(0);
 tft1.fillScreen(ST7735_BLACK);

  mcp.begin_I2C();

  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  pixels_2.begin();

}

void loop() {
    initESPboy();
    while (1 == 1){
      startScreen();
      tft1.fillScreen(ST7735_BLACK);
           tft1.setCursor(14, 40);
         tft1.setTextColor(ST7735_RED,0);
          tft1.setTextSize(3);
         tft1.println("READY!");
        delay(1500);
      mainGame();
      waitUnpressed();
      gameOver();
      waitUnpressed();
    }

}  
