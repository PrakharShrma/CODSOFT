#include <iostream>

int main() {
    double num1, num2;
    char op;

    std::cout << "Welcome to the Amazing Calculator!\n";
    std::cout << "Enter your first number: ";
    std::cin >> num1;
    std::cout << "Enter your second number: ";
    std::cin >> num2;
    std::cout << "Enter the operator (+, -, *, /): ";
    std::cin >> op;

    double result;
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                std::cout << "Oops! You cannot divide by zero. The universe might implode if you try that.\n";
                return 1;
            }
            break;
        default:
            std::cout << "Oh no! The operator you entered is as mysterious as the dark side of the moon.\n";
            return 1;
    }

    std::cout << "Voila! The result of your calculation is: " << result << std::endl;

    return 0;
}
