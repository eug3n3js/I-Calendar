#include "time.h"
#include <iomanip>

Time::Time(int y, int m, int d, int h, int mi) {
    year = y;
    month = m;
    day = d;
    hour = h;
    min = mi;
}

Time Time::difference(const Time& src) const {
    auto time_point1 = get_time_point();
    auto time_point2 = src.get_time_point();
    std::chrono::duration<double> diff_seconds = time_point1 - time_point2;
    long long total_seconds = std::chrono::duration_cast<std::chrono::seconds>(diff_seconds).count();
    int days = total_seconds / (24 * 60 * 60);
    int hours = (total_seconds / (60 * 60)) % 24;
    int minutes = (total_seconds / 60) % 60;
    return Time(0, 0, days, hours, minutes);
}

Time Time::operator-(const Time& src) const {
    auto time_tm = src.get_time_t();
    auto time_tm2 = get_time_t();
    time_tm2.tm_year -= time_tm.tm_year;
    time_tm2.tm_mon -= time_tm.tm_mon;
    time_tm2.tm_mday -= time_tm.tm_mday;
    time_tm2.tm_hour -= time_tm.tm_hour;
    time_tm2.tm_min -= time_tm.tm_min;
    std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(mktime(&time_tm2));
    time_t result_time = std::chrono::system_clock::to_time_t(timepoint);
    tm result_tm_local = *std::localtime(&result_time);
    return Time(result_tm_local.tm_year + 1900, result_tm_local.tm_mon + 1, result_tm_local.tm_mday, result_tm_local.tm_hour, result_tm_local.tm_min);
}

Time Time::operator+(const Time& src) const {
    auto time_tm = get_time_t();
    auto time_tm2 = src.get_time_t();
    time_tm2.tm_year += time_tm.tm_year;
    time_tm2.tm_mon += time_tm.tm_mon;
    time_tm2.tm_mday += time_tm.tm_mday;
    time_tm2.tm_hour += time_tm.tm_hour;
    time_tm2.tm_min += time_tm.tm_min;
    std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(mktime(&time_tm2));
    time_t result_time = std::chrono::system_clock::to_time_t(timepoint);
    tm result_tm_local = *localtime(&result_time);
    return Time(result_tm_local.tm_year + 1900, result_tm_local.tm_mon + 1, result_tm_local.tm_mday, result_tm_local.tm_hour, result_tm_local.tm_min);
}

Time& Time::operator=(const Time& src){
    year = src.year;
    month = src.month;
    day = src.day;
    hour = src.hour;
    min = src.min;
    return *this;
}

Time& Time::operator+=(const Time& src){
    *this = *this + src;
    return *this;
}

Time& Time::operator-=(const Time& src){
    *this = *this - src;
    return *this;
}

bool Time::operator < (const Time & x) const {
    if ( year != x . year )
    return year < x . year;
    if ( month != x . month )
    return month < x . month;
    if ( day != x . day )
    return day < x . day;
    if ( hour != x . hour )
    return hour < x . hour;
    return min < x . min;
}

bool Time::operator == (const Time & x) const {
    return year == x . year && month == x . month && day == x . day && hour == x . hour && min == x . min;
}

std::chrono::system_clock::time_point Time::get_time_point() const {
    auto tm = get_time_t();
    auto time_point = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return time_point;
}

tm Time::get_time_t() const {
    std::tm time = {};
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = min;
    if (year == 0 && month == 0) {
        time.tm_year = 0;
        time.tm_mon = 0;
    }
    return time;
}

std::ostream& operator << (std::ostream& in, const Time & t) {
    if (t.year != 0){
        in << std::setw(4) << std::setfill('0') << t.year;
    }
    if (t.month != 0){
        in << "-";
        in << std::setw(2) << std::setfill('0') << t.month;
    }
    if (t.day != 0){
        in << "-";
        in << std::setw(2) << std::setfill('0') <<  t.day;
        in << "-";
    }
    in << t.hour;
    in << "-";
    in << t.min;
    return in;
}

Time Time::round_day_up() const{
    auto time_tm = get_time_t();
    time_tm.tm_mday += 1;
    time_tm.tm_hour = 0;
    time_tm.tm_min = 0;
    std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(mktime(&time_tm));
    time_t result_time = std::chrono::system_clock::to_time_t(timepoint);
    tm result_tm_local = *localtime(&result_time);
    return Time(result_tm_local.tm_year + 1900, result_tm_local.tm_mon + 1, result_tm_local.tm_mday, result_tm_local.tm_hour, result_tm_local.tm_min);
}

Time Time::round_week_up() const{
    auto time_tm = get_time_t();
    time_tm.tm_mday += (7 - time_tm.tm_wday);
    time_tm.tm_hour = 0;
    time_tm.tm_min = 0;
    std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(mktime(&time_tm));
    time_t result_time = std::chrono::system_clock::to_time_t(timepoint);
    tm result_tm_local = *localtime(&result_time);
    return Time(result_tm_local.tm_year + 1900, result_tm_local.tm_mon + 1, result_tm_local.tm_mday, result_tm_local.tm_hour, result_tm_local.tm_min);
}

Time Time::round_month_up() const{
    auto time_tm = get_time_t();
    time_tm.tm_mday = 0;
    time_tm.tm_hour = 0;
    time_tm.tm_min = 0;
    time_tm.tm_mon += 1;
    std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(mktime(&time_tm));
    time_t result_time = std::chrono::system_clock::to_time_t(timepoint);
    tm result_tm_local = *localtime(&result_time);
    return Time(result_tm_local.tm_year + 1900, result_tm_local.tm_mon + 1, result_tm_local.tm_mday, result_tm_local.tm_hour, result_tm_local.tm_min);
}

bool Time::control_date() const {
    auto time_tm = get_time_t();
    time_tm.tm_hour -= 1;
    if (min < 0 || min > 59 || hour < 0 || hour > 23) {
        return false;
    }
    std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(mktime(&time_tm));
    time_t result_time = std::chrono::system_clock::to_time_t(timepoint);
    tm result_tm_local = *localtime(&result_time);
    Time new_time = Time(result_tm_local.tm_year + 1900, result_tm_local.tm_mon + 1, result_tm_local.tm_mday, result_tm_local.tm_hour, result_tm_local.tm_min);
    if (new_time == *this){
        return true;
    } else {
        auto time_tm = get_time_t();
        std::chrono::system_clock::time_point timepoint = std::chrono::system_clock::from_time_t(mktime(&time_tm));
        time_t result_time = std::chrono::system_clock::to_time_t(timepoint);
        tm result_tm_local = *localtime(&result_time);
        Time new_time = Time(result_tm_local.tm_year + 1900, result_tm_local.tm_mon + 1, result_tm_local.tm_mday, result_tm_local.tm_hour, result_tm_local.tm_min);
        if (new_time == *this){
            return true;
        }
        return false;
    }
}
    
bool Time::control_duration() const {
    if (min >= 0 && min < 60){
        if(hour >= 0 && hour < 24){
            if(day >= 0 && day < 100){
                return true;
            }
        }
    }
    return false;
}
