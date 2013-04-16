//============================================================================
// Name        : ring-queue.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include "file_util.h"

using namespace std;

int main(void)
{

    string file = "/host/tmp/whitman-leaves.txt";
    string codefile = "/host/tmp/whitman-leaves_cw.txt";
    map<string, pair<int, int> > mp = FileUtil::get_codeword_map(codefile);
    // watch out for ./->
    // cout << mp.begin()->first << ":" << mp.begin()->second.first << "," << mp.begin()->second.second << endl;

    //    vector<string> vec = FileUtil::get_file_to_vecstr(file, codefile);
    //    for(int i = 0 ;i < 100; i++)
    //        cout << vec[i] << " ";
    //    map<string, pair<int, int> >::iterator it;
    //
    //    int i = 0;
    //    for (it = mp.begin(); it != mp.end(); it++, i++)
    //    {
    //        cout << it->first << ":" << it->second.first << "," << it->second.second << endl;
    //    }
    vector<int> vec = FileUtil::get_file_vecint_pair(file, codefile).first;
    vector<int> vec2 = FileUtil::get_file_vecint_pair(file, codefile).second;
    for (int i = 0; i < (int)vec.size(); i++)
    {
        if (i < 50)
            cout << vec[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < (int)vec2.size(); i++)
    {
        if (i < 50)
            cout << vec2[i] << " ";
    }
    cout << endl;

    cout << "\nfinish!" << endl;
    return 0;
}
