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

Day::Day() = default;

Day::Day(int m, int d) {
    date[0] = m;
    date[1] = d;
    startOfDay = Event(true);
}

bool Day::checkConflicts(int *start, int *end) { //returns true if there is a conflict
    Event* current = startOfDay;
    bool isConflict = false;
    while (current != nullptr){
        //this if checks to see if the current event occurs before the start of the potential event
        if ((current->getEndHour() < start[0] || (current->getEndHour() == start[0] && current->getEndMinute() < start[1])))
        {
            current = current->nextEvent;
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
    Event newEvent;
    newEvent.setTitle(t);
    newEvent.setDescription(d);
    newEvent.setStartTime(startHr, startMin);
    newEvent.setEndTime(endHr, endMin);
    newEvent.setEventType(et);
    newEvent.setIsFree(f);

    while (current != nullptr)
    {
        if (current->getIsFree())
        {
            //if the new event belongs in the middle of a block of free time
            if ((current->getStartHour() > startHr || (current->getStartHour() == startHr && current->getStartMinute() < startMin)) && (current->getEndHour() > endHr ||(current->getEndHour() == endHr && current->getEndMinute() > endMin)))
            {
                Event* temp(true);
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
                temp->nextEvent = current->nextEvent;
                newEvent.nextEvent = temp;
                current->nextEvent = newEvent;

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
                prevCurrent->nextEvent = newEvent;
                newEvent.nextEvent = current;
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
                newEvent.nextEvent = current->nextEvent;
                current->nextEvent = newEvent;
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
            current = current->nextEvent;
        }

    }

}

Year::Year(int y) { //creates a year with the given number and creates the array of days in that year with their dates
    year = y;
    for (unsigned int i = 0; i < (unsigned)days.size(); i++){
        int* date = indexToDate(i);
        days[i] = Day(date[0], date[1]);
    }
}

Calendar::Calendar() { //creates a new calendar and adds the year 2018 to it
    years.push_back(Year(2018));
}

void Calendar::addYear(int y) { // adds a new year to the calendar
    years.push_back(Year(y));
}

int* indexToDate(int i){ //takes the index of the day and converts it to the actual date
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

int dateToIndex(int date[2]){ //takes the date of a day and converts it to the index
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

//this neeeds to be changed
Event addEvent(Event dab)
{
    int hour;
    int minute;
    string title;
    cout << "What would you like me to call this event?";
    cin >> title;
    dab.setTitle(title);
    cout << "What hour of the day does " << dab.getTitle() << " begin?";
    cin >> hour;
    cout << "What minute of the day does " << dab.getTitle() << " begin?";
    cin >> minute;
    cout << "Thank you. I am now adding this event into your SmartCalendar™" << endl;
    dab.setTime(hour, minute);
    return dab;
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
    cout << "---------------------------------------------------" << endl;
    cout << "Hello, I am HAL 2018, your personal SmartCalendar™." << endl;
    cout << "---------------------------------------------------" << endl;

    bool keepGoing = true; //Whether to keep running the loop.
    string userChoice; //To determine which calendar function to use.
    int numberOfEvents = 10; //Max number of events.
    Event events[numberOfEvents]; //Creating the events.
    int eventCount = 0; //For keeping track of how many events are in the calendar.

    do
    {
        cout << "Please enter the a number 1-3 to select how I can assist you:" << endl;
        userChoice = printMenu();
        if (!userChoice.compare("1")) //Add event.
        {
            events[eventCount] = addEvent(events[eventCount]);
            eventCount++;
        }
        else if (!userChoice.compare("2")) //Print calendar.
        {
            printCalendar(events, numberOfEvents);
        }
        else if (!userChoice.compare("3")) //Exit program.
        {
            keepGoing = false;
            cout << "I guess it is time for us to part ways..." << endl;
            cout << "Until next time." << endl;
        }
        else //Catching user error.
        {
            cout << "I apologize, but my creator's incompetence restrict me from understanding what you have just inputted... Reprompting you now." << endl;
        }
        cout << endl;
        if (eventCount == 10) //Stops the program once the calendar is filled.
        {
            cout << "Your calendar is full. Since I am not finished, I do not have the ability to keep going. I will print your calendar as my parting gift." << endl;
            cout << "Farewell." << endl << endl;
            printCalendar(events, numberOfEvents);
        }
    } while (keepGoing);

    return 0;
}
