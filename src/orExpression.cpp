#include "orExpression.h"

OrExpression::OrExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : left(left), right(right) {}

bool OrExpression::evaluate(const Event& event) const {
    return left->evaluate(event) || right->evaluate(event);
}