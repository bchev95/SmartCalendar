//
// Created by lauren on 3/22/2018.
//

#ifndef SMARTCALENDAR_SMARTCALENDAR_H
#define SMARTCALENDAR_SMARTCALENDAR_H

#endif //SMARTCALENDAR_SMARTCALENDAR_H

using namespace std;

class Event {
protected:
    string title;
    string description;
    string location;
    int startTime[2];
    int endTime[2];
    int date[3];
    int eventType;
public:
    Event();
    string getTitle();
    void setTitle(string t);
    string getDescription();
    void setDescription(string d);
    string getLocation();
    void setLocation(string l);
    int getStartHour();
    int getStartMinute();
    void setStartTime(int hour, int minute);
    int getEndHour();
    int getEndMinute();
    void setEndTime(int hour, int minute);
    int getMonth();
    int getDay();
    int getYear();
    void setDate(int d[3]);
    int getEventType();
    void setEventType(int e);
    void printEvent();
};

class RepeatingEvent: public Event
{
private:
    int dayOfWeek;
    int startDate[3];   //The first occurrence of the event
    int endDate[3];     //The last occurrence of the event
public:
    RepeatingEvent();
    int getDayOfWeek();
    void setDayOfWeek(int dw);
    int getStartMonth();
    int getStartDay();
    int getStartYear();
    void setStartDate(int d[3]);
    int getEndMonth();
    int getEndDay();
    int getEndYear();
    void setEndDate(int d[3]);
};

class Day
{

};

class Week
{

};

class Month
{

};

class Year
{

};