#include <iostream>
#include <string>
#include "SmartCalendar.h"


Event::Event()
{
    title = "blank";
    description = "blank";
    time[0] = 0;
    time[1] = 0;
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
    return EndTime[0];
}

int Event::getEndMinute()
{
    return EndTime[1];
}

void Event::setEndTime(int hour, int minute)
{
    EndTime[0] = hour;
    EndTime[1] = minute;
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
    date = d;
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
    if (time[0] < 10)
    {
        cout << "0" << time[0];
    }
    else
    {
        cout << time[0];
    }
    if (time[1] < 10)
    {
        cout << ":0" << time[1];
    }
    else
    {
        cout << ":" << time[1];
    }
    cout << "\t" << title << endl;
}

RepeatingEvent::RepeatingEvent()
{
    //Not sure what to put here
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
    startDate = d;
}

int RepeatingEvent::getEndMonth()
{
    return EndDate[0];
}

int RepeatingEvent::getEndDay()
{
    return EndDate[1];
}

int RepeatingEvent::getEndYear()
{
    return EndDate[2];
}

void RepeatingEvent::setEndDate(int d[3])   //CLion kept trying to change input to *d is that correct?
{
    EndDate = d;
}

void printCalendar(Event event[], int x)
{
    for (int i = 0; i < x; i++)
    {
        event[i].printEvent();
    }

}

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
