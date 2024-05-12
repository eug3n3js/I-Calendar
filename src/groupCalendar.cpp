#include "groupCalendar.h"

GroupCalendar::GroupCalendar(const std::vector<std::shared_ptr<MonthCalendar>> & calendars_) : calendars(calendars_) {}

void GroupCalendar::print() const {

    for (size_t i = 0; i < calendars.size(); i++){
        calendars[i]->print();
    }
}