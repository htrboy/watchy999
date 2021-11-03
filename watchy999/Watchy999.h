#ifndef WATCHY999_H
#define WATCHY999_H

#include "Watchy_Base.h"
#include "resource999.h"

typedef struct timeData{
    char hour1;
    char hour2;
    char min1;
    char min2;
    String hourStr;
    String minStr;
    String monthStr;
    String dateStr;
    char month1;
    char month2;
    char date1;
    char date2;
    char *monthAbbrev;
    char *dayAbbrev;
}timeData;

extern RTC_DATA_ATTR String tempCondition;
extern RTC_DATA_ATTR timeData latestTime;
extern RTC_DATA_ATTR int lowBattHour;
extern RTC_DATA_ATTR int lowBattMin;
extern RTC_DATA_ATTR bool lowBattFace;

class Watchy999 : public WatchyBase{
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
        //Universal
        timeData getTimeDate();
        void drawWatchFace();
        void checkBattery();
        void drawWeather();
        void checkSteps();
        
};

#endif