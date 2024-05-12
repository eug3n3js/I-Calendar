#ifndef TAGEXPRESSION_H
#define TAGEXPRESSION_H
#include "expression.h"

/**
 * @class ParticipantsExpression
 * @brief This class stands for evaluating events by testing existence of scific tag in Tags attribute of event
*/
class TagExpression : public Expression {
    std::string tag;
    std::string comparison;
public:
/**
 * @brief Constructor of the TagExpression
 * @param tag string that represents Tag that have to be in this event
 * @param comparison string that represents comparing operator for evaluating events ==, !=
 */ 
    TagExpression(const std::string& tag, const std::string& comparison);
/**
 * @brief Destructor of the TagExpression
 * 
 * */ 
    ~TagExpression() = default;
/**
 * @brief Overrided method that evaluetes Event for fitting this expression
 * @param event Event that will be evaluated
 * 
 * */  
    bool evaluate(const Event& event) const override;
};

#endif