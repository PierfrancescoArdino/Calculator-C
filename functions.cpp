#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<std::string> createPostfix(std::string s){
    std::stack<std::string> stack;
    std::vector<std::string> res;
    std::string term;
    std::string number = "";
    std::string op = "";
    for(char &tmp : s)
    {
        std::ostringstream s;
        s << tmp;
        term = s.str();
        if(term == ")")
        {
            if(number != "")
            {
                res.push_back(number);
                number = "";
            }
            if(op!="")
            {
                op ="";
            }
            std::string top = stack.top().c_str();
            while (top != "(")
            {
                res.push_back(top);
                stack.pop();
                if(stack.empty())
                    break;
                top = stack.top();
            }
            if(!stack.empty())
            {
                stack.pop();
            }
            if(top != "("){
                std::cerr<< "Error, mismatch in left parenthesis" << std::endl;
                exit(0);
            }
        }
        else if(term == "("){
            if(number != "")
            {
                res.push_back(number);
                number = "";
            }
            if(op!="")
            {
                op ="";
            }
            stack.push(term);
        }
        else if ((term >= "0" && term <="9") || term ==".")
        {
            number.append(term);
        }
        else if(term == "+" || term =="-")
        {
            if(number != "")
            {
                res.push_back(number);
                number = "";
            }
            if(op!="")
            {
                op ="";
            }
            if(!stack.empty() && (stack.top() == "+" || stack.top() == "-" || stack.top() == "*" || stack.top() == "/"
               || stack.top() == "^"|| stack.top()=="sqrt" || stack.top()=="exp" || stack.top()=="log")){
                res.push_back(stack.top().c_str());
                stack.pop();
            }
            stack.push(term);
        }
        else if(term == "*" || term == "/")
        {
            if(number != "")
            {
                res.push_back(number);
                number = "";
            }
            if(op!="")
            {
                op ="";
            }
            if(!stack.empty() && (stack.top() == "*" || stack.top() == "/" || stack.top() == "^" || stack.top()=="sqrt" || stack.top()=="exp" || stack.top()=="log")){
                res.push_back(stack.top().c_str());
                stack.pop();
            }
            stack.push(term);
        }
        else if(term == "^")
        {
            if(number != "")
            {
                res.push_back(number);
                number = "";
            }
            if(op!="")
            {
                op ="";
            }
            stack.push(term);
        }
        else if(term == " ")
        {
            if(number != "")
            {
                res.push_back(number);
                number = "";
            }
            if(op!="")
            {
                op ="";
            }
        }
        else if((term >="a" && term<="z")||(term>="A" && term<="Z"))
        {
            op.append(term);
            if(op == "sqrt" || op=="exp" || op=="log"){
                stack.push(op);
            }
        }

    }
    while(!stack.empty()){
        if(stack.top() == "(" || stack.top() == ")")
        {
            std::cerr<< "Error, mismatch in parenthesis" << std::endl;
            exit(0);
        }
        if(number != "")
        {
            res.push_back(number);
            number = "";
        }
        res.push_back(stack.top().c_str());
        stack.pop();
    }
    return res;

}

float evaluateExpression(std::vector<std::string> postfixExpression){
    double res = 0;
    std::stack<std::string> stack;
    for(std::string &term : postfixExpression)
    {
        if(term == "+"){
            double op2 = strtod(stack.top().c_str(), NULL);
            stack.pop();
            if(!stack.empty()){
                double op1 = strtod(stack.top().c_str(), NULL);
                stack.pop();
                res = op1 + op2;
            } else{
                res = op2;
            }
            stack.push(std::to_string(res));
        }
        else if(term == "-"){
            double op2 = strtod(stack.top().c_str(), NULL);
            stack.pop();
            if(!stack.empty()){
                double op1 = strtod(stack.top().c_str(), NULL);
                stack.pop();
                res = op1 - op2;
            }
            else{
                res = op2;
            }
            stack.push(std::to_string(res));
        }
        else if(term == "*"){
            double op2 = atof(stack.top().c_str());
            stack.pop();
            if(!stack.empty()){
                double op1 = atof(stack.top().c_str());
                stack.pop();
                res = op1 * op2;
            }
            else{
                res = op2;
            }
            stack.push(std::to_string(res));
        }
        else if(term == "/"){
            double op2 = atof(stack.top().c_str());
            stack.pop();
            if(!stack.empty()){
                double op1 = atof(stack.top().c_str());
                stack.pop();
                res = op1 / op2;
            }
            else{
                res = op2;
            }
            stack.push(std::to_string(res));
        }
        else if(term == "^"){
            double op2 = atof(stack.top().c_str());
            stack.pop();
            if(!stack.empty()){
                double op1 = atof(stack.top().c_str());
                stack.pop();
                res = std::pow(op1,op2);
            }
            else{
                res = op2;
            }
            stack.push(std::to_string(res));
        }
        else if(term=="sqrt"){
            double op = atof(stack.top().c_str());
            stack.pop();
            res = std::sqrt(op);
            stack.push(std::to_string(res));
        }
        else if(term=="exp"){
            double op = atof(stack.top().c_str());
            stack.pop();
            res = std::exp(op);
            stack.push(std::to_string(res));
        }
        else if(term=="log"){
            double op = atof(stack.top().c_str());
            stack.pop();
            res = std::log10(op);
            stack.push(std::to_string(res));
        }
        else{
            stack.push(term);
        }
    }
    return res;
}

/*int main() {
    std::string expression;
    std::vector<std::string> postfixExpression;
    std::getline(std::cin, expression);
    postfixExpression = createPostfix(expression);
    std::cout << "Input Expression \n " << expression << std::endl;
    std::cout <<"PostFix expression" << std::endl;
    std::for_each(postfixExpression.begin(), postfixExpression.end(), [](std::string i)->void {std::cout << i << " ";});
    std::cout<<std::endl;
    float result = evaluateExpression(postfixExpression);
    std::cout << "The result is :   \n" << result <<std::endl;
    return 0;
}*/