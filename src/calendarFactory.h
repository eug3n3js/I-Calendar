#ifndef CALENDARFACTORY_H
#define CALENDARFACTORY_H

#include <vector>
#include <memory>
#include "event.h"
#include "baseCalendar.h"
#include "dayCalendar.h"
#include "weekCalendar.h"
#include "monthCalendar.h"
#include "groupCalendar.h"

/**
 * @class CalendarFactory
 * @brief Class that generates from vector of events suitable CalendarView
 * */ 
class CalendarFactory {
    std::vector<std::shared_ptr<Event>> events;
public:
/**
 * @brief Constructor of CalendarFactory
 * @param events_ events to form corresponding calendar view
 * */ 
    CalendarFactory(std::vector<std::shared_ptr<Event>> & events_);
/**
 * @brief method that makes suitable calendar View. Returns Calendar object
 * */ 
    std::shared_ptr<BaseCalendar> make_calendar() const;
private:
/**
 * @brief helper method that tries to group event in 1 day interval 
 * */ 
    bool group_by_day() const;
/**
 * @brief helper method that tries to group event in 1 week interval
 * */ 
    bool group_by_week() const;
/**
 * @brief @brief helper method that tries to group event in 1 month interval
 * */ 
    bool group_by_month() const;
/**
 * @brief @brief helper method that tries to group event in a few 1 month intervals
 * */ 
    std::vector<std::vector<std::shared_ptr<Event>>> split() const;
};

#endif