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
//����Esc����
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
                cout << "����������" << endl;
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
    //�˴�result�������п��ޣ�result��һ���ַ������飬�����洢������ʽ�������ŵ����ݡ�
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