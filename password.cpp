#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <conio.h>
#include <regex>

#pragma warning (disable:4996)

using namespace std;

class Esc : public exception {

};

#define MAX_PASSWORD_LENGTH 16
string getPassword()
{
    cout << "# ";
    string retstr;
    char ch = 0;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!retstr.empty()) {
                cout << "\b \b";
                retstr.pop_back();
            }
        } else if (retstr.length() >= MAX_PASSWORD_LENGTH) {
            continue;
        } else if (ch == 27) { //Esc
            cout << endl;
            throw Esc();
        } else {
            cout << "*";
            retstr.push_back(ch);
        }
    }

    cout << endl;
    return retstr;
}

#define MAX_STRING_LENGTH 16
//输入Esc结束
string getString() throw (Esc)
{
    cout << "# ";
    string retstr;
    char ch = 0;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!retstr.empty()) {
                cout << "\b \b";
                retstr.pop_back();
            }
        } else if (retstr.length() >= MAX_STRING_LENGTH) {
            continue;
        } else if (ch == 27) { //Esc
            cout << endl;
            throw Esc();
        } else {
            cout << ch;
            retstr.push_back(ch);
        }
    }

    cout << endl;
    return retstr;
}

int getNumber() throw (Esc)
{
    while (1) {
        try {
            string choose = getString();
            stringstream str(choose);
            int temp = INT_MIN;
            str >> temp;
            string remain;
            str >> remain;
            if (!remain.empty()) {
                cout << "请输入数字" << endl;
                continue;
            } else {
                return temp;
            }
        } catch (Esc) {
            throw Esc();
        }
    }
}

//regex
bool is_email_valid(const std::string& email)
{
    //const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    //const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    const std::regex pattern("(\\w+)@(\\w+)(\\.com)");
    //std:: match_results<std::string::const_iterator> result;
    bool valid = std::regex_match(email, pattern);
    //此处result参数可有可无，result是一个字符串数组，用来存储正则表达式里面括号的内容。
    return valid;
}

int main()
{
    string password;
    try {
        password = getPassword();
        cout << password << endl;
    } catch (Esc) {
        cout << "Esc" << endl;
    }
}