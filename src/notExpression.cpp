#include "notExpression.h"

NotExpression::NotExpression(std::shared_ptr<Expression> operand) : operand(operand) {}

bool NotExpression::evaluate(const Event& event) const {
    return !operand->evaluate(event);
}