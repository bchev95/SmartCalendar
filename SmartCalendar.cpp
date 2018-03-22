#include <iostream>
#include <string>
#include "SmartCalendar.h"

using namespace std;

class Event
{
private:
    string title;
    string description;
    int time[2];
public:
    Event()
    {
        title = "blank";
        description = "blank";
        time[0] = 0;
        time[1] = 0;
    }
    string getTitle()
    {
        return title;
    }
    void setTitle(string t)
    {
        title = t;
    }
    string getDescription()
    {
        return description;
    }
    void setDescription(string d)
    {
        description = d;
    }
    int getHour()
    {
        return time[0];
    }
    int getMinute()
    {
        return time[1];
    }
    void setTime(int hour, int minute)
    {
        time[0] = hour;
        time[1] = minute;
    }
    void printEvent()
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

};

void printCalendar(Event event[], int x){
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
            cout << "I apoligize, but my creator's incompetence restrict me from understanding what you have just inputted... Reprompting you now." << endl;
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
