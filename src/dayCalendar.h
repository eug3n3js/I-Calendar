#ifndef DAYCALENDAR_H
#define DAYCALENDAR_H
#include <vector>
#include <memory>
#include "event.h"
#include "baseCalendar.h"

/**
 * @class DayCalendar
 * @brief Class that implements printing of events grouped in one day time interval
 * */  
class DayCalendar: public BaseCalendar{
    std::vector<std::shared_ptr<Event>> events;
public:
/**
 * @brief Constructor of DayCalendar
 * @param event_ vector of events to be printed
 * */ 
    DayCalendar(const std::vector<std::shared_ptr<Event>> & events_);
/**
 * @brief Overrided method that implements printing of events
 * */ 
    void print() const override;

private:
/**
 * @brief Helper function that creates corresponding formatted events for print func
 * */ 
    std::vector<std::vector<EventStruct>> create_view() const;
};

#endif