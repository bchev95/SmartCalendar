//
// Created by lauren on 3/22/2018.
//

#ifndef SMARTCALENDAR_SMARTCALENDAR_H
#define SMARTCALENDAR_SMARTCALENDAR_H

#endif //SMARTCALENDAR_SMARTCALENDAR_H

using namespace std;

class Event {
private:
    string title;
    string description;
    int time[2];
public:
    Event();
    string getTitle();
    void setTitle(string t);
    string getDescription();
    void setDescription(string d);
    int getHour();
    int getMinute();
    void setTime(int hour, int minute);
    void printEvent();
};