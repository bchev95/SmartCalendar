//
// Created by lauren on 3/22/2018.
//

#ifndef SMARTCALENDAR_SMARTCALENDAR_H
#define SMARTCALENDAR_SMARTCALENDAR_H

#endif //SMARTCALENDAR_SMARTCALENDAR_H

#include <vector>

using namespace std;

class Event                 // Nodes of a linked list
{
protected:
    std::string title;
    std::string description;
    std::string location;
    int startTime[2];
    int endTime[2];
    int date[3];
    int eventType;
    Event * nextEvent;
    bool isFree;
public:
    Event();
    Event(bool f);
    std::string getTitle();
    void setTitle(std::string t);
    std::string getDescription();
    void setDescription(std::string d);
    std::string getLocation();
    void setLocation(std::string l);
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
    bool getIsFree();
    void setIsFree(bool f);
    void setNextEvent(Event * e);
    Event * getNextEvent();
    void printEvent();
};

class Day
{
private:
    Event * startOfDay;     // Head of linked list
    int dayOfWeek;          // Sunday == 1
    int date[2];
public:
    Day();
    Day(int m, int d);
    void insertEvent(std::string t, std::string d, std::string l, int startHr, int startMin, int endHr, int endMin, int et, bool f);
    bool checkConflicts(int start[2], int end[2]);
    bool findEvent(std::string eName);
    void removeEvent(std::string eName);
    void printDay();
};


class Year
{
private:
    int year;
    Day* days[365];
public:
    Year(int y);
    Day* getDays();
    Day * getADay(int index);
    int* indexToDate(int i);    // Takes the index of the day and converts it to the actual date
    int getYear();
    void printYear();
};

class Calendar
{
private:
    std::vector<Year> years;
public:
    Calendar();
    int findYear(int y);
    void addEvent();
    void addRepeatingEvent();
    std::vector<Year> getYears();
    bool addYear(int y);
    int dateToIndex(int date[2]);
    void deleteEvent();
    void printEvent();          // Method to print a specific event -> needs to be implemented
    void printCalendar();
};
