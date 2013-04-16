#include <string>
#include <iostream>
#include <vector>
#include "string_util.h"
#include "collection_util.h"

using namespace std;

int main()
{
    string test = "aa a2 bbc cccd";
    //        vector<string> strvec;
    //        string strtemp;
    //
    //        string::size_type pos1, pos2;
    //        pos2 = test.find(' ');
    //        pos1 = 0;
    //        while (string::npos != pos2)
    //        {
    //                strvec.push_back(test.substr(pos1, pos2 - pos1));
    //
    //                pos1 = pos2 + 1;
    //                pos2 = test.find(' ', pos1);
    //        }
    //        strvec.push_back(test.substr(pos1));


    vector<string> strvec = StringUtil::split(test);
    vector<string>::iterator iter1 = strvec.begin(), iter2 = strvec.end();
    while (iter1 != iter2)
    {
        cout << *iter1 << endl;
        ++iter1;
    }
//    string ss[2] = {"sd","Bs"};
    string* ss = new string[2];
    ss[0] = "ew";
    ss[1] = "er";
//    int len = 2;
//    StringUtil::add_vector_to_array(ss,len,strvec);
//    for(int i = 0 ;i < len;i++){
//        cout << ss[i] << " ";
//    }
//    cout << endl;

    vector<string> vec = CollectionUtil::array_to_vector(ss,2);
    for(int i = 0; i<2;i++){
        cout << vec[i]<< endl;
    }


    return 0;
}
