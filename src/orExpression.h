#ifndef OREXPRESSION_H
#define OREXPRESSION_H
#include <memory>
#include "expression.h"

/**
 * @class OrExpression
 * @brief This class evaluates Or logical expression operand of filtrating prompt
*/
class OrExpression : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
/**
 * @brief Constructor of the OrExpression
 * @param left pointer to Left expression of Or operand
 * @param right pointer to Right expression of Or operand
 */ 
    OrExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
/**
 * @brief Destructor of the OrExpression
 * 
 * */ 
    ~OrExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */ 
    bool evaluate(const Event& event) const override;
};

#endif