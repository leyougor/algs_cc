#ifndef ALGS_UTILS_STRING_UTIL_H_
#define ALGS_UTILS_STRING_UTIL_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class StringUtil
{
public:
    static vector<string> split(const string &str)
    {
        vector<string> strvec;
        string strtemp;

        string::size_type pos1, pos2;
        pos2 = str.find(' ');
        pos1 = 0;
        while (string::npos != pos2)
        {
            strvec.push_back(str.substr(pos1, pos2 - pos1));

            pos1 = pos2 + 1;
            pos2 = str.find(' ', pos1);
        }
        strvec.push_back(str.substr(pos1));
        return strvec;
    }
};


#endif
