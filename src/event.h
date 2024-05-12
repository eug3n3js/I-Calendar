#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <set>
#include "time.h"


/**
 * @class Event
 * @brief Class that implements Events objects in Icalendar. Stores all nessesary information about events
 * */  
class Event {
	std::string name_;
    Time date_;
    Time duration_;
    std::string location_;
    std::set<std::string> tags_;
    std::string note_;
	std::pair<std::string, int> repeats_;
	std::set<std::string> participants_;
    bool moveable_;
public:
/**
 * @brief Constructor of Event
 * @param name name of event
 * @param date time of start od event
 * @param duration time how long is this event
 * @param location place where event will be
 * @param tags set that store tags for every event
 * @param note some description of event
 * @param participants set that store participants for every event
 * @param repeats variable that store pair<string,int> that defines frequency 
 * of repeating event and how many times this will happend
 * @param moveable variable that store if event can be moved if collision happens
 * */ 
	Event(const std::string & name, const Time & date, const Time & duration, const std::string & location, const std::set<std::string> & tags, const std::string & note, const std::set<std::string> & participants, const std::pair<std::string, int> & repeats, bool moveable);
/**
 * @brief getter of name
 * */
	std::string name() const;
/**
 * @brief getter of date
 * */
    Time date() const;
/**
 * @brief getter of duration
 * */
    Time duration() const;
/**
 * @brief getter of location
 * */
    std::string location() const;
/**
 * @brief getter of tags
 * */
    const std::set<std::string> & tags() const;
/**
 * @brief getter of note
 * */
    std::string note() const;
/**
 * @brief getter of repeats value
 * */
	std::pair<std::string, int> repeats() const;
/**
 * @brief getter of participants
 * */
	const std::set<std::string> & participants() const;
/**
 * @brief getter of moveable value
 * */
    bool isMoveable() const;
/**
 * @brief setter of date
 * */
    void set_date(const Time date);
};

#endif