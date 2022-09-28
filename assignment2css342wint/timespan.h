//
// Created by Yusuf Pisan on 4/2/18.
// Assignment 2 
// Madison Dienhart
// 1/24/2021
//

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>

using namespace std;

class TimeSpan {
	friend ostream& operator<<(ostream& out, const TimeSpan& ts);
	friend istream& operator>>(istream& in, TimeSpan& ts);

public:
	//explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
	explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);

	// add
	TimeSpan operator+(const TimeSpan& ts) const;

	// subtract
	TimeSpan operator-(const TimeSpan& ts) const;

	// check equality
	bool operator==(const TimeSpan& ts) const;

	// check if not equal
	bool operator!=(const TimeSpan& ts) const;

	// multiply timespan by an unsigned number
	TimeSpan operator*(unsigned int number) const;

	//all other operators: 
	//+=
	TimeSpan& operator+=(const TimeSpan& ts);
	//-=
	TimeSpan& operator-=(const TimeSpan& ts);
	//<
	bool operator<(const TimeSpan& ts) const;
	//>
	bool operator>(const TimeSpan& ts) const;
	//<=
	bool operator<=(const TimeSpan& ts) const;
	//>=
	bool operator>=(const TimeSpan& ts) const;

	// hour component of timespan
	int getHour() const;

	// minute component of timespan
	int getMinute() const;

	// second component of timespan
	int getSecond() const;

	// true if timespan is 0 or larger
	bool isPositive() const;

	//sets the time for use in other functions
	bool setTime(double hour, double minute, double second);

private:
	//private variables
	int hours;
	int minutes;
	int seconds;
};

#endif // ASS2_TIMESPAN_H