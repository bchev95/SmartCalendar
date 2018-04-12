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

std::string Event::getTitle()
{
    return title;
}

void Event::setTitle(std::string t)
{
    title = t;
}

std::string Event::getDescription()
{
    return description;
}

void Event::setDescription(std::string d)
{
    description = d;
}

std::string Event::getLocation()
{
    return location;
}

void Event::setLocation(std::string l)
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

Day::Day() = default;

Day::Day(int m, int d) {
    date[0] = m;
    date[1] = d;
    startOfDay = new Event(true);
    startOfDay->setStartTime(12, 0);
    startOfDay->setEndTime(23, 59);
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

void Day::insertEvent(std::string t, std::string d, std::string l, int startHr, int startMin, int endHr, int endMin, int et, bool f) { //this assumes that there are no conflicts and inserts an event in the day
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


bool Day::findEvent(std::string eName){ //checks to see if an event with the given name exists, returns true if it does exist
  Event* current = startOfDay;
  while (current != nullptr){
      //checks to see if current event name is the given event name
      if (current->getTitle() == eName)
      {
          return true;
      }
      else
      {
        return false;
      }
    }
    return false;
}

void Day::removeEvent(std::string eName) //removes the event from the day
{
  Event* current = startOfDay;
  Event* previous = startOfDay;
  while (current != nullptr)
  {
    if (current->getTitle() != eName)
    {
      previous = current;
      current = current->getNextEvent();
    }
  }
  if (current == startOfDay)
  {
    if (current->getNextEvent()->getIsFree())
    {
      startOfDay = current->getNextEvent();
      delete current;
      startOfDay->setStartTime(12, 0);
    }
    else
    {
      current->setTitle("blank");
      current->setIsFree(true);
      current->setDescription("blank");
      current->setLocation("blank");
      current->setEventType(0);
    }

  }
  else if (current->getNextEvent() == nullptr)
  {
    if (previous->getIsFree())
    {
      previous->setEndTime(23, 59);
      previous->setNextEvent(nullptr);
      delete current;
    }
    else
    {
        current->setIsFree(true);
        current->setTitle("blank");
        current->setDescription("blank");
        current->setLocation("blank");
        current->setEventType(0);
    }
  }
  else
  {
    if (previous->getIsFree() && current->getNextEvent()->getIsFree())
    {
      previous->setEndTime(current->getNextEvent()->getEndHour(), current->getNextEvent()->getEndMinute());
      previous->setNextEvent(current->getNextEvent()->getNextEvent());
      delete current->getNextEvent();
      delete current;
    }
    else if (previous->getIsFree())
    {
      previous->setEndTime(current->getEndHour(), current->getEndMinute());
      previous->setNextEvent(current->getNextEvent());
      delete current;
    }
    else if (current->getNextEvent()->getIsFree())
    {
      current->getNextEvent()->setStartTime(current->getStartHour(), current->getStartMinute());
      previous->setNextEvent(current->getNextEvent());
      delete current;
    }
    else
    {
      current->setIsFree(true);
      current->setTitle("blank");
      current->setDescription("blank");
      current->setLocation("blank");
      current->setEventType(0);
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

Day * Year::getADay(int index){
    return days[index];
}

int Year::getYear() {
    return year;
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

int Calendar::findYear(int y){
    int j = years.size();
    for(int i = 0; i < j; i++)
    {
        if(years[i].getYear() == y)
        {
            return i;
        }
    }
    return (-1);
}

void Calendar::addEvent(){
    // Get year from user
    std::cout << "What year will your event occur in?\n";
    int yearNum;
    std::cin >> yearNum;

    // Check that the year has been created
    int yearIndex = findYear(yearNum);
    if(yearIndex == -1)
    {
        if(!(addYear(yearNum))){
            std::cout << "Invalid year\n";
            return;
        }
    }

    // Get date and time from user
    std::cout << "What month (number) " << yearNum << " will your event occur in?\n";
    int theMonth;
    std::cin >> theMonth;
    std::cout << "What day of the month will your event occur on?\n";
    int theDayNum;
    std::cin >> theDayNum;
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
    int date[2] = {theMonth, theDayNum};
    int dateIndex = dateToIndex(date);

    // Check that there are no conflicts on that date at that time
    Year theYear = years[yearIndex];
    Day * theDay = theYear.getADay(dateIndex);
    int startTime[2] = {theStartHour, theStartMinute};
    int endTime[2] = {theEndHour, theEndMinute};
    if(theDay->checkConflicts(startTime, endTime)) {
        std::cout << "There is a conflict with this time";
        return;
    }

    // Get information from user
    std::cout << "What is the name of this event?\n";
    std::string eventName;
    std::cin >> eventName;
    std::cout << "Where will " << eventName << " take place?\n";
    std::string eventLocation;
    std::cin >> eventLocation;
    std::cout << "What is the description of " << eventName << "?\n";
    std::string eventDescription;
    std::cin >> eventDescription;
    std::cout << "What is the event type of " << eventName << "?\n";
    int eventType;
    std::cin >> eventType;

    // Insert the event into the day
    theDay->insertEvent(eventName, eventDescription, eventLocation, theStartHour, theStartMinute, theEndHour, theEndMinute, eventType, false);
}

void Calendar::addRepeatingEvent(){
    // Get year from user:
    std::cout << "What year will your event occur in?\n";
    int yearNum;
    std::cin >> yearNum;

    // Check that the year has been created
    int yearIndex = findYear(yearNum);
    if(yearIndex == -1)
    {
        if(!(addYear(yearNum))){
            std::cout << "Invalid year\n";
            return;
        }
    }

    // Get the start and end days of the event from the user
    std::cout << "What month (number) " << yearNum << " will your event start occurring?\n";
    int theStartMonth;
    std::cin >> theStartMonth;
    std::cout << "What day of the month will your event start occurring?\n";
    int theStartDay;
    std::cin >> theStartDay;
    std::cout << "What month (number) " << yearNum << " will your event stop occurring?\n";
    int theEndMonth;
    std::cin >> theEndMonth;
    std::cout << "What day of the month will your event stop occurring?\n";
    int theEndDay;
    std::cin >> theEndDay;

    // Get the days of the week that the event will occur on
    int eventDays[7] = {};
    for (int i = 0; i < 7; i++)
    {
        int j = i + 1;
        std::cout << "What is the " << j <<"st/nd/rd/th day of the week the day will occur on?"
                << "(Enter 0 if all the days have already been entered)\n";
        std::cin >> eventDays[i];

        // Check to make sure there is at least one day of the week that the event occurs on
        if(eventDays[1] == 0){
            std::cout << "Invalid entry\n";
            return;
        }
    }

    // Get the start and end times of the event
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


    // Check that there are no conflicts on any date at that time


    // Get information from user
    std::cout << "What is the name of this event?\n";
    std::string eventName;
    std::cin >> eventName;
    std::cout << "Where will " << eventName << " take place?\n";
    std::string eventLocation;
    std::cin >> eventLocation;
    std::cout << "What is the description of " << eventName << "?\n";
    std::string eventDescription;
    std::cin >> eventDescription;
    std::cout << "What is the event type of " << eventName << "?\n";
    int eventType;
    std::cin >> eventType;

    // Insert the event into the applicable days

}

std::vector<Year> Calendar::getYears(){
    return years;
}

bool Calendar::addYear(int y) { // adds a new year to the calendar & returns false if the year does not follow the succession
    if(((years.back().getYear()) + 1) == y) {
        years.push_back(Year(y));
        return true;
    }
    else
        return false;
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

void Calendar::deleteEvent()
{
  // Get year from user
  std::cout << "What year will your event occur in?\n";
  int yearNum;
  std::cin >> yearNum;

  // Check that the year has been created
  int yearIndex = findYear(yearNum);
  if(yearIndex == -1)
  {
        std::cout << "Invalid year\n";
        return;

  }

  // Get date and time from user
  std::cout << "What month (number) " << yearNum << " does your event occur in?\n";
  int theMonth;
  std::cin >> theMonth;
  std::cout << "What day of the month does your event occur on?\n";
  int theDayNum;
  std::cin >> theDayNum;

  // Get index & object of date
  int date[2] = {theMonth, theDayNum};
  int dateIndex = dateToIndex(date);
  Year theYear = years[yearIndex];
  Day * theDay = theYear.getADay(dateIndex);

  // Deleting the event
  std::cout << "What is the name of the event that you will be deleting?\n";
  std::string eventName;
  std::cin >> eventName;
  if(theDay->findEvent(eventName))
  {
    theDay->removeEvent(eventName);
  }
  else
  {
    std::cout << "Invalid event\n";
    return;
  }
}

//this needs to be changed
void printCalendar(Event event[], int x)
{
    for (int i = 0; i < x; i++)
    {
        event[i].printEvent();
    }
}

std::string printMenu()
{
    std::string response;
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
