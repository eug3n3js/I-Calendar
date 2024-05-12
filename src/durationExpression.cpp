#include "durationExpression.h"

DurationExpression::DurationExpression(const Time& duration_, const std::string& comparison_) : duration(duration_), comparison(comparison_){

}
bool DurationExpression::evaluate(const Event& event) const {
    if (comparison == "<") {
        return event.duration() < duration;
    } else if (comparison == ">") {
        return duration < event.duration();
    } else if (comparison == "==") {
        return event.duration() == duration;
    } else {
        throw std::logic_error("  ");
    }
}