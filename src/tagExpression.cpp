#include "tagExpression.h"

TagExpression::TagExpression(const std::string& tag, const std::string& comparison) : tag(tag), comparison(comparison) {}

bool TagExpression::evaluate(const Event& event) const {
    if (comparison == "==") {
        return event.tags().count(tag) > 0;
    } else if (comparison == "!=") {
        return event.tags().count(tag) == 0;
    } else {
        throw std::logic_error("   ");
    }
}