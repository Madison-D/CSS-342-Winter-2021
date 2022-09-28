//
// Created by Yusuf Pisan on 4/2/18.
// Assignment 2 
// Madison Dienhart
// 1/24/2021
//
#include <iostream>
#include "timespan.h"

using namespace std;

ostream& operator<<(ostream& out, const TimeSpan& ts) { 
	out << ts.getHour() << ":" << ts.getMinute() << ":" << ts.getSecond();
	return out;
	}

istream& operator>>(istream& in, TimeSpan& ts)
{
	float hours, minutes, seconds;
	in >> hours >> minutes >> seconds;
	ts.setTime(hours, minutes, seconds);
	return in;
}

/*TimeSpan::TimeSpan(int Hour, int Minute, int Second)
{
}*/

// explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
TimeSpan::TimeSpan(double hour, double minute, double second) : hours(hour), minutes(minute), seconds(second)
{
}

// hour component
int TimeSpan::getHour() const { 
	return hours;
}

// minute component
int TimeSpan::getMinute() const { 
	return minutes; 
}

// second component
int TimeSpan::getSecond() const { 
	return seconds; 
}

// true if timespan is 0 or larger
bool TimeSpan::isPositive() const { 
	if (hours > 0 && minutes > 0 && seconds > 0)
		return true;
	else
	return false;
}

bool TimeSpan::setTime(double hour, double minute, double second)
{
	hours = hour;
	minutes = minute;
	seconds = second;
	return true;
}

// add
TimeSpan TimeSpan::operator+(const TimeSpan& ts) const {
	int hr = hours + ts.getHour();
	int min = minutes + ts.getMinute();
	int sec = seconds + ts.getSecond();
	TimeSpan tsSum(hr, min, sec);
	return tsSum;
}

// subtract
TimeSpan TimeSpan::operator-(const TimeSpan& ts) const {
	int hr = hours - ts.getHour();
	int min = minutes - ts.getMinute();
	int sec = seconds - ts.getSecond();
	TimeSpan tsSub(hr, min, sec);
	return tsSub;
}

// multiply with an integer
TimeSpan TimeSpan::operator*(unsigned int number) const {
	int hr = hours * number;
	int min = minutes * number;
	int sec = seconds * number;
	TimeSpan tsLarge(hr, min, sec);
	return tsLarge;
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& ts)
{
	hours += ts.getHour();
	minutes += ts.getMinute();
	seconds += ts.getSecond();
	return *this;
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& ts)
{
	hours -= ts.getHour();
	minutes -= ts.getMinute();
	seconds -= ts.getSecond();
	return *this;
}

bool TimeSpan::operator<(const TimeSpan& ts) const
{
	if (hours < ts.hours && minutes < ts.minutes && seconds < ts.seconds)
		return true;
	else
		return false;
}

bool TimeSpan::operator>(const TimeSpan& ts) const
{
	if (hours > ts.hours && minutes > ts.minutes && seconds > ts.seconds)
		return true;
	else
		return false;
}

bool TimeSpan::operator<=(const TimeSpan& ts) const
{
	if (hours <= ts.hours && minutes <= ts.minutes && seconds <= ts.seconds)
		return true;
	else
		return false;
}

bool TimeSpan::operator>=(const TimeSpan& ts) const
{
	if (hours >= ts.hours && minutes >= ts.minutes && seconds >= ts.seconds)
		return true;
	else
		return false;
}

// equality ==
bool TimeSpan::operator==(const TimeSpan& ts) const { 
	if (hours == ts.hours && minutes == ts.minutes && seconds == ts.seconds)
		return true;
	else
		return false;
}

// inequality !=
bool TimeSpan::operator!=(const TimeSpan& ts) const {
	if (hours != ts.hours && minutes != ts.minutes && seconds != ts.seconds)
		return true;
	else
		return false;
}
