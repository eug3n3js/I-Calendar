#ifndef BASECALENDAR_H
#define BASECALENDAR_H

#include <memory>
#include <vector>
#include "event.h"


/**
 * @struct EventStruct
 * @brief EventStruct stands for easier way of printing events
 * */  
struct EventStruct{
    std::string name;
    std::string date;
    std::string duration;
    std::string location;
    std::string moveable;
    std::string repeats;
    std::string note;
    std::vector<std::string> participants;
    std::vector<std::string> tags;
};
/**
 * @class BaseCalendar
 * @brief Abstract class that implements basic methods for printing Calendars
 * */  
class BaseCalendar{
public:
/**
 * @brief Virtual method that stands for printing Calendar
 * */  
    virtual void print() const = 0;
/**
 * @brief method that implements printing of single row of events
 * */  
    void printEventRow(const std::vector<EventStruct> & events) const;
/**
 * @brief method that makes from event a eventStruct for next printing
 * @param events vector of Events struct that makes easier to print single attriutes of event
 * */  
    EventStruct convertToStruct(const std::shared_ptr<Event> events) const;
/**
 * @brief Destructor of base calendar
 * */  
    ~BaseCalendar() = default;
};

#endif