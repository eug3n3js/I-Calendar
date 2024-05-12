#include "moveExpression.h"

MoveExpression::MoveExpression(const std::string& moveable_, const std::string& comparison_):
    moveable(moveable_), 
    comparison(comparison_)
{
}
bool MoveExpression::evaluate(const Event& event) const{
    if (moveable == "true"){
        if (comparison == "=="){
            return event.isMoveable();
        }
        if (comparison == "!="){
            return !event.isMoveable();
        }
        throw std::logic_error("  ");
    }
    else if (moveable == "false"){
        if (comparison == "=="){
            return !event.isMoveable();
        }
        if (comparison == "!="){
            return event.isMoveable();
        }
        throw std::logic_error("  ");
    } else {
        throw std::logic_error("  ");
    }
}