#include "locationExpression.h"

LocationExpression::LocationExpression(const std::string& location, const std::string& comparison) : location(location), comparison(comparison) {}

bool LocationExpression::evaluate(const Event& event) const {
    if (comparison == "==") {
        return event.location() == location;
    } else if (comparison == "!=") {
        return event.location() != location;
    } else {
        throw std::logic_error("   ");
    }
}