#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <chrono>
#include <iostream>

/**
 * @class Time
 * @brief Class stores and proccess different operation with time
 * */  
class Time {
public:
    int year;
    int month;
    int day;
    int hour;
    int min;
/**
 * @brief Constructor of Time class
 * @param y years
 * @param m months
 * @param d days
 * @param h hours
 * @param m minutes
 * */  
    Time(int y, int m, int d, int h, int mi);
/**
 * @brief function that counts timedelta between two days. Has different implementation from operator-
 * @param src time to subtract
 * */ 
    Time difference(const Time& src) const;
    Time operator-(const Time& src) const;
    Time operator+(const Time& src) const;
    Time& operator=(const Time& src);
    Time& operator+=(const Time& src);
    Time& operator-=(const Time& src);
    bool operator < (const Time & x) const;
	bool operator == (const Time & x) const;
    friend std::ostream& operator << (std::ostream& in, const Time & t);
/**
 * @brief function that rounds time to the midnigth of next day
 * */ 
    Time round_day_up() const;
/**
 * @brief function that rounds time to the midnigth of next monday
 * */ 
    Time round_week_up() const;
/**
 * @brief function that rounds time to the midnigth of 1 day of next month
 * */ 
    Time round_month_up() const;
/**
 * @brief function controls if date was passed correctly. Contols all attributes
 * */ 
    bool control_date() const;
/**
 * @brief function controls if duration was passed correctly. Contols only day, hour, minute
 * */ 
    bool control_duration() const;

private:
/**
 * @brief helper function that counts timepoint
 * */ 
    std::chrono::system_clock::time_point get_time_point() const;
/**
 * @brief helper function that creates tm_struct
 * */ 
    std::tm get_time_t() const;
};

#endif