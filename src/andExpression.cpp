#include "andExpression.h"


AndExpression::AndExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : left(left), right(right) {}

bool AndExpression::evaluate(const Event& event) const {
    return left->evaluate(event) && right->evaluate(event);
}