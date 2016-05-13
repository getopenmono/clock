// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#if !defined(__ttt_appcontroller_h)
#define __ttt_appcontroller_h
#include <mono.h>

class Dial
:
	public mono::ui::View
{
public:
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	Dial();
	void clearHands ();
private:
	uint8_t screenHeight;
	uint8_t screenWidth;
	uint8_t screenMargin;
	uint8_t dialCenterX;
	uint8_t dialCenterY;
	uint8_t secondsHandLength;
	uint8_t minutesHandLength;
	uint8_t hoursHandLength;
	virtual void repaint ();
	void drawDial (bool clear);
	void drawSeondsHand (bool clear);
	void drawMinutesHand (bool clear);
	void drawHoursHand (bool clear);
};

class AppController
:
	public mono::IApplication
{
public:
	AppController ();
	void monoWakeFromReset ();
	void monoWillGotoSleep ();
	void monoWakeFromSleep ();
private:
	void start ();
	void updateTime ();
	Dial dial;
	mono::Timer timer;
	mono::ui::BackgroundView screen;
	mono::ui::TextLabelView timeLabel;
};

#endif // __ttt_appcontroller_h
