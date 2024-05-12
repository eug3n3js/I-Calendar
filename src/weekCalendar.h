#ifndef WEEKCALENDAR_H
#define WEEKCALENDAR_H
#include "baseCalendar.h"

/**
 * @class WeekCalendar
 * @brief Class that implements printing of events that cannot be grouped in 1 week interval
 * */  
class WeekCalendar: public BaseCalendar{
    std::vector<std::shared_ptr<Event>> events;
public:
/**
 * @brief Constructor of WeekCalendar
 * @param event_ vector of pointers to events to be printed
 * */ 
    WeekCalendar(const std::vector<std::shared_ptr<Event>> & events_);
/**
 * @brief Overrided method that implements printing of events
 * */ 
    void print() const override;
private:
/**
 * @brief Helper function that creates corresponding formatted events for print func
 * */ 
    std::vector<std::vector<EventStruct>> create_view() const;
/**
 * @brief Helper function that groups events for creating a view
 * */ 
    std::vector<std::vector<std::shared_ptr<Event>>> group_events() const;
/**
 * @brief Helper function that prints headers of stuctured calendar
 * */ 
    void print_header(std::vector<EventStruct> data) const;
};

#endif