#ifndef WATCHY999_H
#define WATCHY999_H

#include <WatchyRTC.h>
#include "Watchy_Base.h"
#include "resource999.h"

typedef struct timeData {
  char hour1;
  char hour2;
  char min1;
  char min2;
  String hourStr;
  String minStr;
  String monthStr;
  String dateStr;
  String longYearStr;
  String shortYearStr;
  char month1;
  char month2;
  char date1;
  char date2;
  char *monthAbbrev;
  char *dayAbbrev;
} timeData;

typedef struct {
  int row;
  int column;
  int length;
} Word;

extern RTC_DATA_ATTR String tempCondition;
extern RTC_DATA_ATTR timeData latestTime;
extern RTC_DATA_ATTR int lowBattHour;
extern RTC_DATA_ATTR int lowBattMin;
extern RTC_DATA_ATTR bool lowBattFace;
extern RTC_DATA_ATTR bool showCached;
extern const char *ONES[];
extern const char *TENS[];
extern const char* TEENS_SPLIT[][2];

class TimeSayer {
public:
  TimeSayer();
  const Word* words_on[6];
  void setWords(int8_t hour, int8_t minute);
};

class Watchy999 : public WatchyBase {
  public:
    Watchy999();
    //Slides999
    void drawSlidesWatchFace();
    void drawSlidesTime();
    void updateSlidesCache();
    void drawSlidesDate();
    void getSlidesSteps();
    void drawSlidesSteps();
    void drawSlidesAnim();
    void getSlidesRand();
    //dkTime999
    void drawDkAnim();
    void drawDkWatchFace();
    //Tetris
    void drawWatchytrisWatchFace();
    //Synth999
    void drawSynthWatchFace();
    void drawSynthTime();
    void drawSynthDate();
    void drawSynthBattery();
    //Pxl999
    void drawPxlWatchFace();
    //Crushem999
    void drawCeAnim();
    void drawCeWatchFace();
    //lowBatt999
    void drawLowBattWatchFace();
    //G5600
    void drawG5600WatchFace();
    //Doom999
    void drawDoomWatchFace();
    //Slide Time
    void drawPebbleTextFace();
    //Qlocky
//    Qlock();
      void drawQlockyWatchFace();
      void setMinute(int8_t minute);
    //Universal
    timeData getTimeDate();
    void watchFaceSettings();
    void displayWatchFace();
    void drawWatchFace();
    void checkBattery();
    void drawWeather();
    void checkSteps();
    void gotoSleep();
    void centerJustify(const String txt, uint16_t xPos, uint16_t yPos);
    void drawLecoNum(int pDigit, int pX, int pY, bool colorChange);
    void drawPxlNum(int pDigit, int pX, int pY, bool colorChange);
//  private:
    // uint8_t row;
    // uint8_t column;
    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;
    int8_t wordIndex = -1;
    const Word* currentWord;
    TimeSayer timeSayer;
    void nextWord();

};

#endif
