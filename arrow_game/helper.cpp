#include "helper.h"

using std::string;
using std::vector;

// I have written two methods at the bottom to help with my input validation

Helper::Helper(){}

void Helper::printInvalidInput()
{
    std::cout << "Invalid input.\n" << std::endl;
}

bool Helper::isNumber(string s)
{
    string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;
    while (it != s.end()) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                break;
            }
        }   
        else if (!isdigit(*it))
        {
            break;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}

// loops through the input to see if there is a decimal point, the method will return true is there is a decimal
bool Helper::containsDecimalPoint(std::string input) {
    bool decimalFound = false;
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == '.') {
            decimalFound = true;
        }
        i++;
    }
    return decimalFound;
}


    
// compares the input to the string load to see if the user is intending to load a board
bool Helper::checkForLoad(string input){

    string load = "load";
    int compare_result = 0;

    compare_result = load.compare(input);
    bool same = true;

    if (compare_result != 0){
        same = false;

    }
    return same;

}