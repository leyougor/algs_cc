#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "file_util.h"
#include "string_util.h"
#include "collection_util.h"
#include "porter.h"

using namespace std;
const static string file = "/host/tmp/whitman-leaves.txt";
const static string codefile = "/host/tmp/whitman-leaves_cw.txt";

void test_file()
{

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
    vector<int> slave;
    vector<int> master = FileUtil::get_text_codeword(file, codefile, slave);

    CollectionUtil::print_vec(master, "master");
    CollectionUtil::print_vec(slave, "slave");

}

void test_string()
{
    string test = "aa a2 bbc cccd";

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

    vector<string> vec = CollectionUtil::array_to_vector(ss, 2);
    for (int i = 0; i < 2; i++)
    {
        cout << vec[i] << endl;
    }

}

void test_extract_text()
{
    vector<int> slave;

    vector<int> master = FileUtil::get_text_codeword(file, codefile, slave);

    map<pair<int, int> , string> mp = CollectionUtil::inverse_map(FileUtil::get_codeword_map(codefile));

    string ss;
    for (int i = 0; i < 100; i++)
    {
        ss += mp[make_pair(master[i], slave[i])];
        ss += " ";
    }

    cout << ss << endl;
}

int main()
{
    string ss = "{{{;apple}}";
    cout << Porter::stem(ss) << endl;

    cout << "finish!" << endl;
    return 0;
}
