// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#include "app_controller.h"
#include "lib/trigonometry.hpp"
#include <math.h>

using namespace trigonometry;

//using mono::geo::Point;
using mono::geo::Rect;
using mono::String;
using mono::Timer;
using mono::ui::TextLabelView;
using mono::ui::View;

Dial::Dial ()
:
	seconds(0),
	minutes(0),
	hours(0)
{
	screenHeight = 220;
	screenWidth = 176;
	screenMargin = 8;
	dialCenterX = screenWidth / 2;
	dialCenterY = screenHeight - dialCenterX;
	secondsHandLength = dialCenterX - screenMargin;
	minutesHandLength = secondsHandLength;
	hoursHandLength = secondsHandLength - 20;
	viewRect = Rect(0,20,176,220);
}

void Dial::repaint ()
{
	drawDial(false);
	drawSeondsHand(false);
	drawMinutesHand(false);
	drawHoursHand(false);
}

void Dial::drawDial (bool clear)
{
	painter.setForegroundColor(clear ? mono::display::BlackColor : mono::display::BelizeHoleColor);
	painter.drawCircle(dialCenterX,dialCenterY,secondsHandLength + screenMargin - 1);
}

void Dial::clearHands ()
{
	drawSeondsHand(true);
	drawMinutesHand(true);
	drawHoursHand(true);
}

void Dial::drawSeondsHand (bool clear)
{
	painter.setForegroundColor(clear ? mono::display::BlackColor : mono::display::RedColor);
	uint16_t secondsHandX = dialCenterX + cos(minutesToRadians(seconds)) * secondsHandLength;
	uint16_t secondsHandY = dialCenterY + sin(minutesToRadians(seconds)) * secondsHandLength;
	painter.drawLine(dialCenterX,dialCenterY,secondsHandX,secondsHandY);
}

void Dial::drawMinutesHand (bool clear)
{
	painter.setForegroundColor(clear ? mono::display::BlackColor : mono::display::GreenColor);
	uint16_t minutesHandX = dialCenterX + cos(minutesToRadians(minutes)) * minutesHandLength;
	uint16_t minutesHandY = dialCenterY + sin(minutesToRadians(minutes)) * minutesHandLength;
	painter.drawLine(dialCenterX,dialCenterY,minutesHandX,minutesHandY);
}

void Dial::drawHoursHand (bool clear)
{
	painter.setForegroundColor(clear ? mono::display::BlackColor : mono::display::WhiteColor);
	uint16_t hoursHandX = dialCenterX + cos(hoursToRadians(hours)) * hoursHandLength;
	uint16_t hoursHandY = dialCenterY + sin(hoursToRadians(hours)) * hoursHandLength;
	painter.drawLine(dialCenterX,dialCenterY,hoursHandX,hoursHandY);
}

AppController::AppController ()
:
	timer(1000),
	screen(mono::display::BlackColor),
	timeLabel(Rect(0,15,176,20),"Clock")
{
	timeLabel.setAlignment(TextLabelView::ALIGN_CENTER);
	timeLabel.setTextColor(mono::display::EmeraldColor);
	timeLabel.setBackgroundColor(mono::display::BlackColor);
}

void AppController::monoWakeFromReset ()
{
	// Force serial enumeration.
	mono::defaultSerial.printf("");
	start();
}

void AppController::monoWakeFromSleep ()
{
	mono::IApplicationContext::SoftwareReset();
	start();
}

void AppController::monoWillGotoSleep ()
{
	timer.Stop();
}

void AppController::start ()
{
	screen.show();
	timeLabel.show();
	timer.setCallback<AppController>(this,&AppController::updateTime);
	timer.Start();
}

void AppController::updateTime ()
{
	static int hour = 23;
	static int minute = 58;
	static int second = 15;
	++second;
	if (second >= 60)
	{
		second = 0;
		++minute;
		if (minute >= 60) {
			minute = 0;
			++hour;
			if (hour >= 24)
				hour = 0;
		}
	}
	char string[20];
	sprintf(string,"%02i:%02i:%02i",hour,minute,second);
	timeLabel.setText(string);
	timeLabel.show();

	dial.clearHands();
	dial.seconds = second;
	dial.minutes = minute;
	dial.hours = hour;
	dial.show();
}
