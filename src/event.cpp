#include "event.h"

Event::Event(const std::string & name, const Time & date, const Time & duration, const std::string & location, const std::set<std::string> & tags, const std::string & note, const std::set<std::string> & participants, const std::pair<std::string, int> & repeats, bool moveable):
    name_(name),
    date_(date),
    duration_(duration),
    location_(location),
    tags_(tags),
    note_(note),
    
    moveable_(moveable)
{
    participants_ = participants;
    repeats_ = repeats;
}

bool Event::isMoveable() const {
    return moveable_;
}

void Event::set_date(const Time date) {
    date_ = date;
}

std::string  Event::name() const{
    return name_;
}

Time Event::date() const{
    return date_;
}

Time Event::duration() const{
    return duration_;
}

std::string Event::location() const{
    return location_;
}

const std::set<std::string> & Event::tags() const{
    return tags_;
}

std::string Event::note() const{
    return note_;
}

std::pair<std::string, int> Event::repeats() const{
    return repeats_;
}

const std::set<std::string> & Event::participants() const{
    return participants_;
}