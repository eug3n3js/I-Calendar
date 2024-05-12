#include "parser.h"
#include <cstring>
#include "andExpression.h"
#include "orExpression.h"
#include "notExpression.h"
#include "dateExpression.h"
#include "durationExpression.h"
#include "locationExpression.h"
#include "tagExpression.h"
#include "moveExpression.h"
#include "nameExpression.h"
#include "participantsExpression.h"
#include "time.h"

Parser::Parser(const std::string& expression) : expression(expression), pos(0) {}

std::shared_ptr<Expression> Parser::parse() {
    std::shared_ptr<Expression> exp = parseExpression();
    if (pos < (int)expression.size()){
        throw std::logic_error("  ");
    }
    return exp;
}

std::shared_ptr<Expression> Parser::parseExpression() {
    std::shared_ptr<Expression> left = parseTerm();
    while (pos < (int)expression.size() && (expression[pos] == '&' || expression[pos] == '|')) {
        char op = expression[pos++];
        std::shared_ptr<Expression> right = parseTerm();
        if (op == '&') {
            left = std::shared_ptr<Expression>(new AndExpression(left, right));
        } else if (op == '|') {
            left = std::shared_ptr<Expression>(new OrExpression(left, right));
        }
    }
    return left;
}

std::shared_ptr<Expression> Parser::parseTerm() {
    if (pos < (int)expression.size() && expression[pos] == '!') {
        pos++;
        std::shared_ptr<Expression> operand = parseFactor();
        return std::shared_ptr<Expression>(new NotExpression(operand));
    } else {
        return parseFactor();
    }
}

std::shared_ptr<Expression> Parser::parseFactor() {
    if (pos < (int)expression.size() && expression[pos] == '(') {
        pos++;
        std::shared_ptr<Expression> result = parseExpression();
        if (pos < (int)expression.size() && expression[pos] == ')') {
            pos++;
        } else {
            throw std::logic_error("  ");
        }
        return result;
    } else if (pos < (int)expression.size() && expression[pos] == 'D') {
        pos++;
        std::string op = parseComparisonOperator();
        Time date = parseDate();
        return std::shared_ptr<Expression>(new DateExpression(date, op));
    } else if (pos < (int)expression.size() && expression[pos] == 'd') {
        pos++;
        std::string op = parseComparisonOperator();
        Time duration = parseDuration();
        return std::shared_ptr<Expression>(new DurationExpression(duration, op));
    } else if (pos < (int)expression.size() && expression[pos] == 'P') {
        pos++;
        std::string op = parseComparisonOperator();
        std::string location = parseString();
        return std::shared_ptr<Expression>(new LocationExpression(location, op));
    } else if (pos < (int)expression.size() && expression[pos] == 'T') {
        pos++;
        std::string op = parseComparisonOperator();
        std::string tag = parseString();
        return std::shared_ptr<Expression>(new TagExpression(tag, op));
    } else if (pos < (int)expression.size() && expression[pos] == 'M') {
        pos++;
        std::string op = parseComparisonOperator();
        std::string moveable = parseString();
        return std::shared_ptr<Expression>(new MoveExpression(moveable, op));
    } else if (pos < (int)expression.size() && expression[pos] == 'N') {
        pos++;
        std::string op = parseComparisonOperator();
        std::string name = parseString();
        return std::shared_ptr<Expression>(new NameExpression(name, op));
    } else if (pos < (int)expression.size() && expression[pos] == 'A') {
        pos++;
        std::string op = parseComparisonOperator();
        std::string participant = parseString();
        return std::shared_ptr<Expression>(new ParticipantsExpression(participant, op));
    } else {
        throw std::logic_error("  ");
    }
}

Time Parser::parseDate() {
    if (pos + 10 <= (int)expression.size()) {
        std::string year, month, day;
        size_t pos1 = 0;
        std::string time = expression.substr(pos, 10);
        pos += 10;
        pos1 = time.find('-');
        if (pos1==std::string::npos){
            throw std::logic_error("  ");
        }
        year = time.substr(0, pos1);
        time.erase(0, pos1 + 1);
        pos1 = time.find('-');
        if (pos1==std::string::npos){
            throw std::logic_error("  ");
        }
        month = time.substr(0, pos1);
        time.erase(0, pos1 + 1);
        if (time.size()==0){
            throw std::logic_error("  ");
        }
        day = time;
        if (isNumber(year) && isNumber(year) && isNumber(year)){
            Time t = Time(std::stoi(year), std::stoi(month), std::stoi(day), 0, 0);
            if (!t.control_date()){
                throw std::logic_error("  ");
            }
            return t;
        } else {
            throw std::logic_error("  ");
        }
    } else {
        throw std::logic_error("  ");
    }
}

Time Parser::parseDuration() {
    if (pos + 5 <= (int)expression.size()) {
        std::string hour, min;
        size_t pos1 = 0;
        std::string time = expression.substr(pos, 10);
        pos += 5;
        pos1 = time.find('-');
        if (pos1==std::string::npos){
            throw std::logic_error("  ");
        }
        hour = time.substr(0, pos1);
        time.erase(0, pos1 + 1);
        if (time.size()==0){
            throw std::logic_error("  ");
        }
        min = time;
        if (isNumber(hour) && isNumber(min) ){
            Time t = Time(0, 0, 0, std::stoi(hour), std::stoi(min));
            if (!t.control_duration()){
                throw std::logic_error("  ");
            }
            return t;
        } else {
            throw std::logic_error("  ");
        }
    } else {
        throw std::logic_error("  ");
    }
}

std::string Parser::parseString() {
    std::string word;
    std::string unexpected_chars = "()<>|&!=";
    
    while (pos < (int)expression.size() && unexpected_chars.find(expression[pos]) == std::string::npos){
        if (expression[pos] == '_'){
            word.push_back(' ');
        }else {
            word.push_back(expression[pos]);
        }
        pos++;
    }
    return word;
}

std::string Parser::parseComparisonOperator() {
    if (pos + 2 < (int)expression.size()){
        std::string op = expression.substr(pos, 2);
        if (op == "!=" || op == "=="){
            pos += 2;
            return op;
        }
        if (op[0] == '<' || op[0] == '>'){
            pos ++;
            return std::string(1, op[0]);
        }
        throw std::logic_error("  ");
    } else {
        throw std::logic_error("  ");
    }

}

bool Parser::isNumber(const std::string& s) {
    auto it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}