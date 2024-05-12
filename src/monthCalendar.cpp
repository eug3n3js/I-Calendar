#include "monthCalendar.h"
#include <iomanip>
#include <cstring>
#include "loadConfig.h"

MonthCalendar::MonthCalendar(const std::vector<std::shared_ptr<Event>> & events_) : events(events_) {}

std::vector<std::vector<EventStruct>> MonthCalendar::create_view() const {
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

std::vector<std::vector<std::shared_ptr<Event>>> MonthCalendar::group_events() const {
    std::vector<std::vector<std::shared_ptr<Event>>> grouped_events;
    std::vector<std::shared_ptr<Event>> week_events;
    Time group = events[0]->date().round_week_up();
    for (size_t i = 0; i < events.size(); i++){
        if (events[i]->date() < group){
            week_events.push_back(events[i]);
        } else {
            grouped_events.push_back(week_events);
            week_events.clear();
            group = events[i]->date().round_week_up();
            week_events.push_back(events[i]);
        }
        if (i == events.size() - 1){
            if (week_events.size() != 0){
                grouped_events.push_back(week_events);
            }
        }
    }
    return grouped_events;
}

void MonthCalendar::print_header(std::vector<EventStruct> data) const{
    std::vector<std::string> months_names = {
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
    };
    int width_size ,column_size;
    if (!Conf().loadConfig(column_size, width_size)){
        throw std::logic_error(" ");
    }
    for (size_t i = 0; i < data.size(); i++){
        int month_int = stoi(data[i].date.substr(5, 2)) - 1;
        std::cout << std::setw(column_size) << std::setfill(' ') << std::left << months_names[month_int]<< " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (size_t i = 0; i < data.size(); i++){
        std::cout << "Week: " << std::setw(column_size - 6) << std::setfill(' ') << std::left  << i + 1 << std::setfill(' ')<< " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void MonthCalendar::print() const {
    std::vector<std::vector<EventStruct>> events_ = create_view();
    for (size_t i = 0; i < events_.size(); i++){  
        if (events_[i].size() == 0){
            print_header(events_[i+1]);
        } else {
            printEventRow(events_[i]);
        }
    }
}