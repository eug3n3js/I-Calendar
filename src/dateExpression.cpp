#include "dateExpression.h"

DateExpression::DateExpression(const Time& date, const std::string& comparison) : date(date), comparison(comparison) {}

bool DateExpression::evaluate(const Event& event) const {
    if (comparison == "<") {
        return event.date() < date;
    } else if (comparison == ">") {
        return date < event.date();
    } else if (comparison == "==") {
        return event.date() == date;
    } else {
        throw std::logic_error("  ");
    }
}