#include <iostream>
#include <string>
#include "SmartCalendar.h"


Event::Event()
{
    title = "blank";
    description = "blank";
    location = "blank";
    startTime[0] = 0;
    startTime[1] = 0;
    endTime[0] = 0;
    endTime[1] = 0;
    date[0] = 0;
    date[1] = 0;
    date[2] = 0;    //Should this be 2018?
    eventType = 0;
    isFree = false;
    nextEvent = nullptr;
}

Event::Event(bool f){ //allows you to create a new event, specifying if it is free space or not
    title = "blank";
    description = "blank";
    location = "blank";
    startTime[0] = 0;
    startTime[1] = 0;
    endTime[0] = 0;
    endTime[1] = 0;
    date[0] = 0;
    date[1] = 0;
    date[2] = 0;
    eventType = 0;
    isFree = f;
    nextEvent = nullptr;
}

string Event::getTitle()
{
    return title;
}

void Event::setTitle(string t)
{
    title = t;
}

string Event::getDescription()
{
    return description;
}

void Event::setDescription(string d)
{
    description = d;
}

string Event::getLocation()
{
    return location;
}

void Event::setLocation(string l)
{
    location = l;
}

int Event::getStartHour()
{
    return startTime[0];
}

int Event::getStartMinute()
{
    return startTime[1];
}

void Event::setStartTime(int hour, int minute)
{
    startTime[0] = hour;
    startTime[1] = minute;
}

int Event::getEndHour()
{
    return endTime[0];
}

int Event::getEndMinute()
{
    return endTime[1];
}

void Event::setEndTime(int hour, int minute)
{
    endTime[0] = hour;
    endTime[1] = minute;
}

int Event::getMonth()
{
    return date[0];
}

int Event::getDay()
{
    return date[1];
}

int Event::getYear()
{
    return date[2];
}

void Event::setDate(int d[3])
{
    date[0] = d[0];
    date[1] = d[1];
    date[2] = d[2];
}

int Event::getEventType()
{
    return eventType;
}

void Event::setEventType(int e)
{
    eventType = e;
}

void Event::printEvent()
{
    if (startTime[0] < 10)
    {
        std::cout << "0" << startTime[0];
    }
    else
    {
        std::cout << startTime[0];
    }
    if (startTime[1] < 10)
    {
        std::cout << ":0" << startTime[1];
    }
    else
    {
        std::cout << ":" << startTime[1];
    }
    std::cout << "\t" << title << std::endl;
}

bool Event::getIsFree() {
    return isFree;
}

void Event::setIsFree(bool f) {
    isFree = f;
}

void Event::setNextEvent(Event * e){
    nextEvent = e;
}

Event * Event::getNextEvent(){
    return nextEvent;
}

RepeatingEvent::RepeatingEvent()
{
    title = "blank";
    description = "blank";
    location = "blank";
    startTime[0] = 0;
    startTime[1] = 0;
    endTime[0] = 0;
    endTime[1] = 0;
    eventType = 0;
    dayOfWeek = 0;
    startDate[0] = 0;
    startDate[1] = 0;
    startDate[2] = 0;
    endDate[0] = 0;
    endDate[1] = 0;
    endDate[2] = 0;
}

int RepeatingEvent::getDayOfWeek()
{
    return dayOfWeek;
}

void RepeatingEvent::setDayOfWeek(int dw)
{
    dayOfWeek = dw;
}

int RepeatingEvent::getStartMonth()
{
    return startDate[0];
}

int RepeatingEvent::getStartDay()
{
    return startDate[1];
}

int RepeatingEvent::getStartYear()
{
    return startDate[2];
}

void RepeatingEvent::setStartDate(int d[3])
{
    startDate[0] = d[0];
    startDate[1] = d[1];
    startDate[2] = d[2];
}

int RepeatingEvent::getEndMonth()
{
    return endDate[0];
}

int RepeatingEvent::getEndDay()
{
    return endDate[1];
}

int RepeatingEvent::getEndYear()
{
    return endDate[2];
}

void RepeatingEvent::setEndDate(int d[3])
{
    endDate[0] = d[0];
    endDate[1] = d[1];
    endDate[2] = d[2];
}

Day::Day() = default;

Day::Day(int m, int d) {
    date[0] = m;
    date[1] = d;
    startOfDay = new Event(true);
}

bool Day::checkConflicts(int *start, int *end) { //returns true if there is a conflict
    Event* current = startOfDay;
    bool isConflict = false;
    while (current != nullptr){
        //this if checks to see if the current event occurs before the start of the potential event
        if ((current->getEndHour() < start[0] || (current->getEndHour() == start[0] && current->getEndMinute() < start[1])))
        {
            current = current->getNextEvent();
        }
        //this if checks if the current event occurs after the start of the potential event
        else if ((current->getStartHour() > end[0] || (current->getStartHour() == end[0] && current->getStartMinute() > end[1])))
        {
            current = nullptr;
        }
        //if current does not occur entirely before or entirely after the potential event, there must be a conflict
        else
        {
            isConflict = true;
            current = nullptr;
        }
    }
    return isConflict;
}

void Day::insertEvent(string t, string d, string l, int startHr, int startMin, int endHr, int endMin, int et, bool f) { //this assumes that there are no conflicts and inserts an event in the day
    Event* current = startOfDay;
    Event* prevCurrent = startOfDay;
    Event* newEvent = new Event();
    newEvent->setTitle(t);
    newEvent->setDescription(d);
    newEvent->setStartTime(startHr, startMin);
    newEvent->setEndTime(endHr, endMin);
    newEvent->setEventType(et);
    newEvent->setIsFree(f);

    while (current != nullptr)
    {
        if (current->getIsFree())
        {
            //if the new event belongs in the middle of a block of free time
            if ((current->getStartHour() > startHr || (current->getStartHour() == startHr && current->getStartMinute() < startMin)) && (current->getEndHour() > endHr ||(current->getEndHour() == endHr && current->getEndMinute() > endMin)))
            {
                Event* temp = new Event(true);
                if (endMin != 59)
                {
                    temp->setStartTime(endHr, endMin+1);
                    temp->setEndTime(current->getEndHour(), current->getEndMinute());
                }
                else
                {
                    temp->setStartTime(endHr+1, 0);
                    temp->setEndTime(current->getEndHour(), current->getEndMinute());
                }
                temp->setNextEvent(current->getNextEvent());
                newEvent->setNextEvent(temp);
                current->setNextEvent(newEvent);

                if (startMin == 0)
                {
                    current->setEndTime(startHr-1, 59);
                }
                else {
                    current->setEndTime(startHr, startMin-1);
                }

            }
            //if the new event perfectly lines up with the blcok of free space
            else if (current->getStartHour() == startHr && current->getEndMinute() == startMin && current->getEndHour() == endHr && current->getEndMinute() == endMin)
            {
                current->setIsFree(false);
                current->setTitle(t);
                current->setDescription(d);
                current->setLocation(l);
                current->setEventType(et);
            }
            //if the new event lines up with the begining of the block of free space only
            else if (current->getStartHour() == startHr && current->getStartMinute() == startMin){
                prevCurrent->setNextEvent(newEvent);
                newEvent->setNextEvent(current);
                if (endMin == 59)
                {
                    current->setStartTime(startHr+1, 0);
                }
                else
                {
                    current->setStartTime(startHr, startMin+1);
                }
            }
            //if the new event lines up with the end of the block of free space only
            else if (current->getEndHour() == endHr && current->getEndMinute() == endMin){
                newEvent->setNextEvent(current->getNextEvent());
                current->setNextEvent(newEvent);
                if (startMin == 0)
                {
                    current->setEndTime(startHr-1, 59);
                }
                else
                {
                    current->setEndTime(startHr, startMin-1);
                }
            }
        }
        else
        {
            prevCurrent = current;
            current = current->getNextEvent();
        }

    }

}

Year::Year(int y) { //creates a year with the given number and creates the array of days in that year with their dates
    year = y;
    for (unsigned int i = 0; i < 365; i++)
    {
        int* date = indexToDate(i);
        days[i] = new Day(date[0], date[1]);
    }
}

int* Year::indexToDate(int i){ //takes the index of the day and converts it to the actual date
    int date[2] = {0, 0};
    int month = 1;
    int day = 1;
    for (int j = 0; j < i; j++)
    {
        if (j == 31){
            month++;
            day = 1;
        }
        else if (j == 59)
        {
            month++;
            day = 1;
        }
        else if (j == 90)
        {
            month++;
            day = 1;
        }
        else if (j == 120)
        {
            month++;
            day = 1;

        }
        else if (j == 151)
        {
            month++;
            day = 1;
        }
        else if (j == 181)
        {
            month++;
            day = 1;
        }
        else if (j == 212)
        {
            month++;
            day = 1;
        }
        else if (j == 243)
        {
            month++;
            day = 1;
        }
        else if (j == 273)
        {
            month++;
            day = 1;
        }
        else if (j == 304)
        {
            month++;
            day = 1;
        }
        else if (j == 334)
        {
            month++;
            day = 1;
        }
        else
        {
            day++;
        }
    }
    date[0] = month;
    date[1] = day;
    return date;

}

Calendar::Calendar() = default;

Year Calendar::findYear(int y){
    int j = years.size();
    for(int i = 0; i < j; i++)
    {
        if(years[i] == y)
        {
            return years[i];
        }
    }
    return null;
}

void Calendar::addEvent(){
    // Get input from user
    std::cout << "What year will your event occur in?\n";
    int yearNum;
    std::cin >> yearNum;

    // Check that the year has been created
    Year theYear = findYear(yearNum);
    if(theYear == null)
    {
        addYear(yearNum);
    }

    // Get date and time from user
    std::cout << "What month (number) " << yearNum << " will your event occur in?\n";
    int theMonth;
    std::cin >> theMonth;
    std::cout << "What day of the month will your event occur on?\n";
    int theDay;
    std::cin >> theDay;
    std::cout << "What hour (military time) will your event start at?\n";
    int theStartHour;
    std::cin >> theStartHour;
    std::cout << "What minute of the " << theStartHour << " hour will your event start?\n";
    int theStartMinute;
    std::cin >> theStartMinute;
    std::cout << "What hour (military time) will your event end at?\n";
    int theEndHour;
    std::cin >> theEndHour;
    std::cout << "What minute of the " << theEndHour << " hour will your event start?\n";
    int theEndMinute;
    std::cin >> theEndMinute;

    // Get index of date
    int date[2] = {theMonth, theDay};
    dateToIndex(date);
    // Check that there are no conflicts on that date at that time
    // Get information from user
}

void Calendar::addRepeatingEvent(){
    // Get input from user:
    // Check that the year has been created
    // Check that there are no conflicts on any date at that time
    // Get information from user
}

Year* Calendar::getYears(){}

void Calendar::addYear(int y) { // adds a new year to the calendar
    years.push_back(Year(y));
}

int Calendar::dateToIndex(int date[2]){ //takes the date of a day and converts it to the index
    int index = 0;
    if (date[0] == 1)
    {
        index = date[1] - 1;
    }
    else if (date[0] == 2)
    {
        index = date[1] + 30;
    }
    else if (date [0] == 3)
    {
        index =  date[0] + 58;
    }
    else if (date[0] == 4)
    {
        index = date[1] + 89;
    }
    else if (date[0] == 5)
    {
        index = date[1] + 119;
    }
    else if (date[0] == 6)
    {
        index =  date[1] + 150;
    }
    else if (date[0] == 7)
    {
        index = date[1] + 180;
    }
    else if (date[0] == 8)
    {
        index = date[1] + 211;
    }
    else if (date[0] == 9)
    {
        index = date[1] + 242;
    }
    else if (date[0] == 10)
    {
        index = date[1] + 272;
    }
    else if (date[0] == 11)
    {
        index = date[1] + 303;
    }
    else if (date[0] == 12){
        index = date[1] + 333;
    }
    return index;
}

//this needs to be changed
void printCalendar(Event event[], int x)
{
    for (int i = 0; i < x; i++)
    {
        event[i].printEvent();
    }
}

string printMenu()
{
    string response;
    cout << "1. Add an event." << endl;
    cout << "2. Print out calendar." << endl;
    cout << "3. Leave me alone." << endl;
    cin >> response;
    return response;
}

int main()
{
    // When starting the cale
    return 0;
}
