#include "nameExpression.h"

NameExpression::NameExpression(const std::string& name_, const std::string& comparison_): name(name_), comparison(comparison_) {}

bool NameExpression::evaluate(const Event& event) const {
    if (comparison == "==") {
        return event.name() == name;
    } else if (comparison == "!=") {
        return event.name() != name;
    } else {
        throw std::logic_error("   ");
    }
}