#include "csvrw.h"
#include <cstring>

CSVFileRW::CSVFileRW(const std::string & fname){
    if (fname.substr(fname.size() - 4, 4) != ".csv"){
        throw std::logic_error("  ");
    } else {
        filename = fname;
    }
    header = "Name,Date,Duration,Location,Tags,Note,Moveable,RRULE:FREQ,RRULE:COUNT,Participants";
}

std::vector<std::shared_ptr<Event>> CSVFileRW::read() const{
    std::ifstream file(filename);
    std::vector<std::shared_ptr<Event>> data;
    std::string line;
    if (!file.is_open()){
        throw std::logic_error(" ");
    }
    std::getline(file, line);
    if (line != header){
        throw std::logic_error(" ");
    }
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::string field;
        std::stringstream ss(line);
        while (getline(ss, field, ',')) {
            row.push_back(field);
        }
        std::vector<std::shared_ptr<Event>> ev = make_event(row);
        for (size_t i = 0; i < ev.size(); i++)
            data.push_back(ev[i]);
    }
    file.close();
    return data;
}

void CSVFileRW::write(const std::vector<std::shared_ptr<Event>> data) const {
    std::ofstream file(filename);
    if (!file.is_open()){
        throw std::logic_error(" ");
    }
    file << header;
    file << std::endl;
    std::vector<std::shared_ptr<Event>> written_repeated;
    for (size_t i = 0; i < data.size(); i++){
        bool need_to_continue = false;
        if (data[i] -> repeats().second != 0){
            for (size_t i2 = 0; i2 < written_repeated.size(); i2++){
                if (written_repeated[i2]->name() == data[i] -> name() && written_repeated[i2]->location() == data[i] -> location() && written_repeated[i2]->note() == data[i] -> note()){
                    need_to_continue = true;
                    break;
                } 
            }
            if (!need_to_continue){
                written_repeated.push_back(data[i]);
            }
        }
        if (need_to_continue){
            continue;
        }
        std::stringstream stream;
        stream << data[i] -> name() << ",";
        stream << data[i] -> date() << ",";
        stream << data[i] -> duration() << ",";
        stream << data[i] -> location() << ",";
        std::vector<std::string> tags = std::vector<std::string>((*data[i]).tags().begin(), (*data[i]).tags().end());
        for (size_t i2 = 0; i2 < tags.size(); i2++){
            if (i2 == 0){
                stream << tags[i2];
            } else {
                stream << " " << tags[i2];
            }
        }
        stream << ",";
        stream << data[i] -> note() << ",";
        if (data[i] -> isMoveable()){
            stream << "true,";
        } else {
            stream << "false,";
        }
        if(data[i] -> repeats().second == 0){
            stream << "N/A" << "," << "N/A" << ",";
        } else {
            stream << data[i] -> repeats().first << "," << data[i] -> repeats().second << ",";
        }
        if (data[i] -> participants().size() == 0){
            stream << "N/A";
        }
        for (auto it = data[i] -> participants().begin(); it != data[i] -> participants().end(); it++){
            if (it == data[i] -> participants().begin()){
                stream << *it;
            } else {
                stream << " " << *it;
            }
        }
        stream << std::endl;
        file << stream.str();
    }
    file.close();
}

bool CSVFileRW::is_int(std::string s) const {
    auto it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::vector<std::shared_ptr<Event>> CSVFileRW::make_event(const std::vector<std::string> & row) const {
    if (row.size() != 10){
        throw std::logic_error("  ");
    }
    
    std::string name = row[0];
    if (name.size() == 0){
        throw std::logic_error("  ");
    }
    std::vector<std::string> dates;
    std::string field;
    std::stringstream ss;
    ss << row[1];
    while (getline(ss, field, '-')) {
        dates.push_back(field);
    }
    if (dates.size() != 5){
        throw std::logic_error("  ");
    }
    for (int i = 0; i < 5; i++){
        if (!is_int(dates[i])){
            throw std::logic_error("  ");
        }
    }
    Time date = Time(stoi(dates[0]), stoi(dates[1]), stoi(dates[2]), stoi(dates[3]), stoi(dates[4]));
    if (!date.control_date()){
        throw std::logic_error("  ");
    }
    std::vector<std::string> durations;
    ss.clear();
    ss << row[2];
    while (getline(ss, field, '-')) {
        durations.push_back(field);
    }
    if (durations.size() != 2){
        throw std::logic_error("  ");
    }
    for (int i = 0; i < 2; i++){
        if (!is_int(durations[i])){
            throw std::logic_error("  ");
        }
    }
    Time duration = Time(0, 0, 0, std::stoi(durations[0]), std::stoi(durations[1]));
    if (!duration.control_duration()){
        throw std::logic_error("  ");
    }

    std::string location = row[3];
    if (location.size() == 0){
        throw std::logic_error("  ");
    }

    std::vector<std::string> tags;
    ss.clear();
    ss << row[4];
    while (std::getline(ss, field, ' ')) {
        tags.push_back(field);
    }
    for (size_t i = 0; i < tags.size(); i++){
        if (tags[i].size() == 0){
            throw std::logic_error("  ");
        }
    }

    std::string note = row[5];
    if (note.size() == 0){
        throw std::logic_error("  ");
    }
    std::string move = row[6];
    bool moveable;
    if (move == "true"){
        moveable = true;
    } else if (move == "false"){
        moveable = false;
    } else {
        throw std::logic_error("  ");
    }

    std::pair<std::string, int> repeats;
    if (row[7] == "N/A"){
        repeats = std::pair<std::string, int>("", 0);
    } else if (row[7] == "WEEKLY" || row[7] == "DAILY" || row[7] == "MONTHLY"){
        if (is_int(row[8])){
            repeats = std::pair<std::string, int>(row[7], stoi(row[8]));
        } else {
            throw std::logic_error("  ");
        }
    } else {
        throw std::logic_error("  ");
    }

    std::vector<std::string> participants;
    ss.clear();
    ss << row[9];
    if (row[9] != "N/A" && row[9] != "N/A\n"){
        while (getline(ss, field, ' ')) {
            participants.push_back(field);
        }
    }
    for (size_t i = 0; i < participants.size(); i++){
        if (participants[i].size() == 0){
            throw std::logic_error("  ");
        }
    }
    std::vector<std::shared_ptr<Event>> ready;
    if (repeats.second > 1) {
        Time base_time = date;
        for (int i = 0; i < repeats.second; i++){
            if (repeats.first == "DAILY"){
                ready.push_back(std::shared_ptr<Event>(new Event(name, base_time, duration, location, std::set<std::string>(tags.begin(), tags.end()), note, std::set<std::string>(participants.begin(), participants.end()), repeats, moveable)));
                base_time += Time(0, 0, 1, 0, 0);
            } else if (repeats.first == "WEEKLY"){
                ready.push_back(std::shared_ptr<Event>(new Event(name, base_time, duration, location, std::set<std::string>(tags.begin(), tags.end()), note, std::set<std::string>(participants.begin(), participants.end()), repeats, moveable)));
                base_time += Time(0, 0, 7, 0, 0);
            } else {
                ready.push_back(std::shared_ptr<Event>(new Event(name, base_time, duration, location, std::set<std::string>(tags.begin(), tags.end()), note, std::set<std::string>(participants.begin(), participants.end()), repeats, moveable)));
                base_time += Time(0, 1, 0, 0, 0);
            }
        }
    } else {
        ready.push_back(std::shared_ptr<Event>(new Event(name, date, duration, location, std::set<std::string>(tags.begin(), tags.end()), note, std::set<std::string>(participants.begin(), participants.end()), repeats, moveable)));
    }
    return ready;
}