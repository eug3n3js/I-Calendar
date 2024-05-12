#include "dayCalendar.h"
#include "baseCalendar.h"
#include "loadConfig.h"
DayCalendar::DayCalendar(const std::vector<std::shared_ptr<Event>> & events_) : events(events_) {}

std::vector<std::vector<EventStruct>> DayCalendar::create_view() const {
    std::vector<std::vector<EventStruct>> ready_events;
    int width_size ,column_size;
    if (!Conf().loadConfig(column_size, width_size)){
        throw std::logic_error(" ");
    }
    int columns = width_size/column_size;
    int events_count = events.size();
    int ready_events_size = events_count%columns == 0 ? events_count / columns : (events_count / columns) + 1;
    for (int i = 0; i < ready_events_size; i++){
        std::vector<EventStruct> events_row;
        if (i == ready_events_size - 1){
            for (int i2 = i*columns; i2 < events_count; i2++){
                events_row.push_back(convertToStruct(events[i2]));
            }
        } else {
            for (int i2 = i*columns; i2 < (i+1)*columns; i2++){
                events_row.push_back(convertToStruct(events[i2]));
            }
        }
        ready_events.push_back(events_row);
    }
    return ready_events;
}

void DayCalendar::print() const {
    std::vector<std::vector<EventStruct>> events_ = create_view();
    for (size_t i = 0; i < events_.size(); i++){
        printEventRow(events_[i]);
    }
}