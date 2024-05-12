#include "baseCalendar.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "loadConfig.h"

void BaseCalendar::printEventRow(const std::vector<EventStruct> & events) const {
    int numColumns = events.size();
    int width_size ,column_size;
    if (!Conf().loadConfig(width_size, column_size)){
        throw std::logic_error(" ");
    }
    int maxParticipants = 0;
    for (EventStruct event : events) {
        if ((int)event.participants.size() > maxParticipants) {
            maxParticipants = event.participants.size();
        }
    }
    int maxTags = 0;
    for (EventStruct event : events) {
        if ((int)event.tags.size() > maxTags) {
            maxTags = event.tags.size();
        }
    }
    int maxNote = 0;
    for (EventStruct event : events) {
        int note_size = event.note.size();
        int row_size = note_size%width_size == 0 ? note_size / width_size : (note_size / width_size) + 1;
        if (row_size > maxNote) {
            maxNote = row_size;
        }
    }
    int numRows = maxParticipants + maxTags + maxNote + 15;  
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            const EventStruct& event = events[col];
            if (row == 0) {
                if (event.name != ""){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ') << "Name:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row == 1) {
                std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.name << " ";
            } else if (row == 2) {
                if (event.name != ""){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Location:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }  
            } else if (row == 3) {
                std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.location << " ";
            } else if (row == 4) {
                if (event.name != ""){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Date:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row == 5) {
                std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.date << " ";
            } else if (row == 6) {
                if (event.name != ""){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Duration:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row == 7) {
                std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.duration << " ";
            } else if (row == 8) {
                if (event.name != ""){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Is moveable:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row == 9) {
                if (event.moveable == "1"){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "true" << " ";
                } else if (event.moveable == "0") {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "false" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row == 10) {
                if (event.repeats != ""){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Repeats:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row == 11) {
                std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.repeats << " ";
            } else if (row == 12) {
                if (event.name != ""){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Notes:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row > 12 && row < 12 + maxNote + 1) {
                int note_size = event.note.size();
                int row_size = note_size%width_size == 0 ? note_size / width_size : (note_size / width_size) + 1;
                if (row_size > row - 13){
                    if (row_size - 1 > row - 13){
                        std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.note.substr((row - 13)*width_size,(row - 12)*width_size) << " ";
                    } else {
                        std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.note.substr((row - 13)*width_size, event.note.size() - (row - 13)*width_size) << " ";
                    }
                } else {
                    for (int i = 0; i < width_size+1; i++){
                        std::cout << " ";
                    }
                }
            } else if (row == 12 + maxNote + 1){
                if ((int)event.participants.size() != 0){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Participants:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else if (row > 12 + maxNote + 1 && row < 12 + maxNote + maxParticipants + 2) {
                if ((int)event.participants.size() > row - 12 - maxNote - 2){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.participants[row - 12 - maxNote - 2] << " ";
                } else {
                    for (int i = 0; i < width_size+1; i++){
                        std::cout << " ";
                    }
                }
            } else if (row == 12 + maxNote + maxParticipants + 2) {
                if (event.tags.size() != 0){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "Tags:" << " ";
                } else {
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< "" << " ";
                }
            } else {
                if ((int)event.tags.size() > row - 12 - maxNote - maxParticipants - 3){
                    std::cout << std::setw(width_size) << std::left << std::setfill(' ')<< event.tags[row - 12 - maxNote - maxParticipants - 3] << " ";
                } else {
                    for (int i = 0; i < width_size+1; i++){
                        std::cout << " ";
                    }
                }
            }
        }
        std::cout << "\n";  // Move to the next row
    }
    std::cout << '\n';  // Move to the next row
}

EventStruct BaseCalendar::convertToStruct(const std::shared_ptr<Event> event) const {
    EventStruct event_struct;
    std::stringstream stream;
    event_struct.name = event -> name();
    event_struct.location = event -> location();
    stream << event -> date();
    event_struct.date = stream.str();
    stream.str(std::string());
    stream << event -> duration();
    event_struct.duration = stream.str();
    stream.str(std::string());
    stream << event -> isMoveable();
    event_struct.moveable = stream.str();
    stream.str(std::string());
    event_struct.note = event -> note();
    if(event -> repeats().second == 0){
        stream << event -> repeats().first;
    } else {
        stream << event -> repeats().first << " " << event -> repeats().second;
    }
    event_struct.repeats = stream.str();
    stream.str(std::string());
    event_struct.participants = std::vector<std::string>(event -> participants().begin(), event -> participants().end());
    event_struct.tags = std::vector<std::string>(event -> tags().begin(), event -> tags().end());
    return event_struct;
}
