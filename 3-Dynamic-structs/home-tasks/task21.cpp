#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

double calculatePostfix(const std::string& expression)
{
    std::stack<double> s;
    std::stringstream ss(expression);
    std::string temp;

    while (ss >> temp)
    {
        if (isdigit(temp[0]))
        {
            // Put numbers into stack
            s.push(stod(temp));
        }
        else {
            // Get two numbers from stack and use operator
            double b = s.top();
            s.pop();
            double a = s.top();
            s.pop();

            switch (temp[0])
            {
                case '+':
                    s.push(a + b);
                    break;
                case '-':
                    s.push(a - b);
                    break;
                case '*':
                    s.push(a * b);
                    break;
                case '/':
                    if (b != 0)
                    {
                        s.push(a / b);
                    }
                    else
                    {
                        std::cerr << "Division by zero" << std::endl;
                    }
                    break;
                default:
                    std::cerr << "Invalid operation." << std::endl;
            }
        }
    }

    return s.top();
}

int main() {
    std::string expression;
    std::cout << "Enter postfix expression: ";
    getline(std::cin, expression);

    double result = calculatePostfix(expression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

// Example 5 3 2 4 3 1 - * + 2 + 4 / + 1 + 4 * +

