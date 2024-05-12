#include "calendarFactory.h"

CalendarFactory::CalendarFactory(std::vector<std::shared_ptr<Event>> & events_): events(events_){}

std::shared_ptr<BaseCalendar> CalendarFactory::make_calendar() const{
     std::shared_ptr<BaseCalendar> view;
    if (group_by_day()){
        view = std::shared_ptr<BaseCalendar>(new DayCalendar(events));
    }
    else if (group_by_week()){
        view = std::shared_ptr<BaseCalendar>(new WeekCalendar(events));
    } else if (group_by_month()){
        view = std::shared_ptr<BaseCalendar>(new MonthCalendar(events));
    } else {
        std::vector<std::shared_ptr<MonthCalendar>> calendars;
        std::vector<std::vector<std::shared_ptr<Event>>> grouped = split();
        for (size_t i = 0; i < grouped.size(); i++){
            calendars.push_back(std::shared_ptr<MonthCalendar>(new MonthCalendar(grouped[i])));
        }
        view =  std::shared_ptr<GroupCalendar>(new GroupCalendar(calendars));
    }
    return view;

}

bool CalendarFactory::group_by_day() const{
    if (events[events.size()-1]->date() < events[0]->date().round_day_up()){
        return true;
    }
    return false;
}

bool CalendarFactory::group_by_week() const {
    if (events[events.size()-1]->date() < events[0]->date() + Time(0, 0, 7, 0, 0)){
        return true;
    }
    return false;
}

bool CalendarFactory::group_by_month() const {
    if (events[events.size()-1]->date() < events[0]->date().round_month_up()){
        return true;
    }
    return false;
}

std::vector<std::vector<std::shared_ptr<Event>>> CalendarFactory::split() const{
    std::vector<std::vector<std::shared_ptr<Event>>> grouped_events;
    std::vector<std::shared_ptr<Event>> month_events;
    Time group = events[0]->date().round_month_up();
    for (size_t i = 0; i < events.size(); i++){
        if (events[i]->date() < group){
            month_events.push_back(events[i]);
        } else {
            grouped_events.push_back(month_events);
            month_events.clear();
            group = events[i]->date().round_month_up();
            month_events.push_back(events[i]);
        }
        if (i == events.size() - 1){
            if (month_events.size() != 0){
                grouped_events.push_back(month_events);
            }
        }
    }
    return grouped_events;
}
