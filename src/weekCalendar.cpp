#include "weekCalendar.h"
#include <iomanip>
#include <iostream>
#include "loadConfig.h"
WeekCalendar::WeekCalendar(const std::vector<std::shared_ptr<Event>> & events_) : events(events_) {}

std::vector<std::vector<EventStruct>> WeekCalendar::create_view() const {
    std::vector<std::vector<std::shared_ptr<Event>>> grouped_events = group_events();
    std::vector<std::vector<EventStruct>> ready_events;
    int width_size ,column_size;
    if (!Conf().loadConfig(column_size, width_size)){
        throw std::logic_error(" ");
    }
    int columns = width_size/column_size;
    int ready_events_size = grouped_events.size()%columns == 0 ? grouped_events.size() / columns : (grouped_events.size() / columns) + 1;
    EventStruct empty = {"", "", "", "", "", "", "", {}, {}};
    ready_events.push_back(std::vector<EventStruct>{});
    for (int i = 0; i < ready_events_size; i++){
        int maxLen = 0;
        std::vector<std::vector<std::shared_ptr<Event>>> events_row;
        if (i == ready_events_size - 1){
            events_row = std::vector<std::vector<std::shared_ptr<Event>>>(grouped_events.begin() + (i)*columns, grouped_events.end());
        } else {
            events_row = std::vector<std::vector<std::shared_ptr<Event>>>(grouped_events.begin() + (i)*columns, grouped_events.begin() + (i+1)*columns);
        }
        
        for (size_t i2 = 0; i2 < events_row.size(); i2++){
            if ((int)events_row[i2].size() > maxLen){
                maxLen = events_row[i2].size();
            }
        }
        for (int i3 = 0; i3 < maxLen; i3++){
            std::vector<EventStruct> row;
            for (size_t i4 = 0; i4 < events_row.size(); i4++){
                if ((int)events_row[i4].size() > i3){
                    row.push_back(convertToStruct(events_row[i4][i3]));
                } else {
                    row.push_back(empty);
                }
            }
            ready_events.push_back(row);
        }
        if (i != ready_events_size - 1){
            ready_events.push_back(std::vector<EventStruct>{});
        }
    }
    return ready_events;
}

std::vector<std::vector<std::shared_ptr<Event>>> WeekCalendar::group_events() const {
    std::vector<std::vector<std::shared_ptr<Event>>> grouped_events;
    std::vector<std::shared_ptr<Event>> day_events;
    Time group = events[0]->date().round_day_up();
    for (size_t i = 0; i < events.size(); i++){
        if (events[i]->date() < group){
            day_events.push_back(events[i]);
        } else {
            grouped_events.push_back(day_events);
            day_events.clear();
            group = events[i]->date().round_day_up();
            day_events.push_back(events[i]);
        }
        if (i == events.size() - 1){
            if (day_events.size() != 0){
                grouped_events.push_back(day_events);
            }
        }
    }
    return grouped_events;
}

void WeekCalendar::print_header(std::vector<EventStruct> data) const{
    int width_size ,column_size;
    if (!Conf().loadConfig(column_size, width_size)){
        throw std::logic_error(" ");
    }
    for (size_t i = 0; i < data.size(); i++){
        std::cout << "Day: " << std::setw(column_size-5) <<  std::left << std::setfill(' ')<< data[i].date.substr(0, 10) << std::setfill(' ') << " ";
    }
    std::cout << std::endl;
}

void WeekCalendar::print() const {
    std::vector<std::vector<EventStruct>> events_ = create_view();
    for (size_t i = 0; i < events_.size(); i++){  
        if (events_[i].size() == 0){
            print_header(events_[i+1]);
        } else {
            printEventRow(events_[i]);
        }
    }
}