// Objective: Read a string from the user and extract a valid double-precision floating-point number from it

#include <iostream>
#include <cctype>
#include <iomanip> // fixed: force decimal notation, setprecision:  ensure display w/ specific number of digits after decimal point
#include <string>
// bring elements of the std namespace. allows for use without std:: prefix
using namespace std;

// declare prototype for extraction function
double extractNumeric(const string& str); // reference to string object

// declare main
int main() { 
    string input;

    while (true) { 
        // query user
        cout << "Enter a string (or 'end' to quit): ";
        cin >> input; 

        // iterate through each character and convert to lowercase
        for (char &c : input) { 
            c = tolower(c);
        }
        
        // check for break request
        if (input == "end") { 
            break;
        }    

        double number = extractNumeric(input);
        // handle return
        if (number != -999999.99) { 
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else { 
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}

// function to extract numeric value from an input string
double extractNumeric(const string& str) { 
    bool hasDecimal = false;
    bool hasSign = false;
    bool isValid = true;
    size_t length = str.length(); 

    // check input
    if (length == 0 || length > 20) { 
        // invalid input if the string is empty or too long
        return -999999.99;
    }

    // check if the string is a valid double
    for (size_t i = 0; i < length; i++) { 
        char c = str[i];
        // check for sign
        if (i == 0 && (c == '+' || c == '-')) { 
            hasSign = true;
        } else if (c == '.' && !hasDecimal) { // decimal check
            hasDecimal = true;
        } else if (!isdigit(c)) { // anything other than a digit here means structure is invalid
            isValid = false;
            break;
        }
    }

    // return error code if the string is invalid
    // check for a decimal at the end of the str (invalid)
    if (!isValid || (hasDecimal && str.find('.') == str.length() - 1)) { 
        return -999999.99;
    }

    // convert the string to a double
    double result = 0.0;
    double decimalMultiplier = 0.1;
    bool isNegative = (str[0] == '-');
    bool parsingDecimal = false; 

    // if str has a sign, start at second index
    for (size_t i = (hasSign ? 1 : 0); i < length; i++) { 
        char c = str[i];

        if (c == '.') { 
            parsingDecimal = true;
        } else if (isdigit(c)) { // treat rest as part of the decimal/fractional portion of number
            if (parsingDecimal) { // fractional part
                result += (c - '0') * decimalMultiplier; // convert char to int
                decimalMultiplier /= 10; // scale to place decimal in correct position
            } else { // integer part
                // shift existing number to the left to make space for new digit
                result = result * 10 + (c - '0'); // add numeric value of the current digit to result
            }
        }
    }

    return isNegative ? -result : result;
}