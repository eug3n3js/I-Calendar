#ifndef GROUPCALENDAR_H
#define GROUPCALENDAR_H
#include "baseCalendar.h"
#include "monthCalendar.h"

/**
 * @class GroupCalendar
 * @brief Class that implements printing of events that cannot be grouped in 1 month interval
 * */  
class GroupCalendar: public BaseCalendar{
    std::vector<std::shared_ptr<MonthCalendar>> calendars;
public:
/**
 * @brief Constructor of GroupCalendar
 * @param calendars_ vector of MonthCalendar pointers to be printed
 * */ 
    GroupCalendar(const std::vector<std::shared_ptr<MonthCalendar>> & calendars_);
/**
 * @brief Overrided method that implements printing of events. Call print() methods of corresponding MonthCalendars
 * */ 
    void print() const override;

};

#endif