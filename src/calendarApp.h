#ifndef CALENDARAPP_H
#define CALENDARAPP_H

#include <cstring>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <sstream>
#include "time.h"
#include "event.h"
#include "csvrw.h"
#include "parser.h"
#include "expression.h"
#include "calendarFactory.h"
#include "baseCalendar.h"
#include "dayCalendar.h"
#include "weekCalendar.h"
#include "monthCalendar.h"

/**
 * @struct cmp
 * @brief cmp stands for comparing events while adding to event_list
 * */ 
struct cmp{
/**
 * @brief comparator of events
 * */ 
	bool operator() (const std::shared_ptr<Event> a, const std::shared_ptr<Event> b) const;
};
/**
 * @class CallendarApp
 * @brief Main class that stands for processing user requests and resolving collisions while adding events
 * */  
class CalendarApp{
	std::set<std::shared_ptr<Event>, cmp> event_list;
public:
/**
 * @brief Constructor of CalendarApp class
 * */  
	CalendarApp() = default;
/**
 * @brief Function that stands for processing user requests. Return true if calendar have to be closed (call by user or eof)
 * */
	bool process_request();
private:
/**
 * @brief Function that prints main menu 
 * */
	void print_menu() const;
/**
 * @brief Helper function that checks if string can be converted into word
 * @param s controlled string 
 * */
	bool is_number(const std::string& s) const;
/**
 * @brief Function that iterates throgh all events and return list of events that met filtering expression
 * @param expression expression to be filtered by
 * */
	std::vector<std::shared_ptr<Event>> get_events_by_filter(const std::shared_ptr<Expression> expression) const;
/**
 * @brief Function that checks if collision appeared while adding new event. Returns vector of iterators pointing 
 * on events that collides
 * */
    std::vector<std::set<std::shared_ptr<Event>, cmp>::iterator> detect_collision() const;
/**
 * @brief Function that finds solution to resolve collision between events. By default has 2 resolve of collision:
 *  delete first event or add anyway (do nothing).
 * If one of events is moveable function can try to find nearest time and move colliding event on it.
 * @param el Takes as argument vector of iterators pointing 
 * on events that collides.

 * */
    void resolve_collision(std::vector<std::set<std::shared_ptr<Event>, cmp>::iterator> el); 
};

#endif