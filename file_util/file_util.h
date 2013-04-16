//============================================================================
// Name        : ring-queue.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
#ifndef ALGS_FILE_UTIL_H_
#define ALGS_FILE_UTIL_H_

#include<iostream>
#include<fstream>
#include<map>
#include <stdlib.h>
#include "../utils/string_util.h"
#include "../utils/collection_util.h"
using namespace std;

class FileUtil
{
private:

public:
    FileUtil()
    {
    }

    static pair<vector<int> , vector<int> > get_file_vecint_pair(const string& filename, const string& codefile)
    {
        vector<string> vecstr = get_file_vecstr(filename, codefile);
        map<string, pair<int, int> > mp = get_codeword_map(codefile);
        vector<int> vec;
        vector<int> vec2;
        for (int i = 0; i < (int) vecstr.size(); i++)
        {
            //            TODO 单独符号已被忽略
            if (mp[vecstr[i]].first != 0)
            {
                vec.push_back(mp[vecstr[i]].first);
                vec2.push_back(mp[vecstr[i]].second);
                if (i < 20)
                    cout << vecstr[i] << ":" //NL
                            << mp[vecstr[i]].first << "," << mp[vecstr[i]].second << endl;
            }
        }
        return make_pair(vec, vec2);
    }
    static vector<string> get_file_vecstr(const string& filename, const string& codefile)
    {
        vector<string> vec;
        ifstream infile;
        string sline;
        infile.open(filename.c_str());
        if (!infile)
        {
            cout << "error:unable to open input file:" << filename << endl;
            return vec;
        }

        while (getline(infile, sline))
        {
            if (sline != "")
            {
                vector<string> vecstr = StringUtil::split(sline);
                //              忽略换行符
                //                vecstr.push_back("\n");

                CollectionUtil::merge_vector(vec, vecstr);
            }
        }
        return vec;
    }

    //    获取词表
    static map<string, pair<int, int> > get_codeword_map(const string& filename)
    {
        map<string, pair<int, int> > mp;
        ifstream infile;
        string sline;
        infile.open(filename.c_str());
        if (!infile)
        {
            cout << "error:unable to open input file:" << filename << endl;
            return mp;
        }

        while (getline(infile, sline))
        {
            if (sline != "")
            {
                int left = sline.find_last_of(":");
                int right = sline.find_last_of(",");
                string word = sline.substr(0, left);
                int first = atoi(sline.substr(left + 1, right - left - 1).c_str());
                int second;
                if (right == -1 or left >= right)
                    second = 1;
                else
                    second = atoi(sline.substr(right + 1).c_str());
                mp.insert(make_pair(word, make_pair(first, second)));
            }
            //            content.append(sline.c_str()).append("\n");
        }
        return mp;
    }

    static string get_file_content(const string& filename)
    {
        ifstream infile;
        string sline;
        string content;
        infile.open(filename.c_str());
        if (!infile)
        {
            cout << "error:unable to open input file:" << filename << endl;
            return "";
        }
        while (getline(infile, sline))
        {
            content.append(sline.c_str()).append("\n");
        }
        infile.close();
        return content;
    }

    static void write_file_content(const string& filename, const string& content)
    {
        write_file_content(filename, content, false);
    }

    static void append_file_content(const string& filename, const string& content)
    {
        write_file_content(filename, content, true);
    }

    static void write_file_content(const string& filename, const string& content, bool add)
    {
        ofstream outfile;
        outfile.open(filename.c_str(), add ? ofstream::app : ofstream::out);
        if (!outfile || !outfile.is_open())
        {
            cerr << "error:unable to open output file:" << filename << endl;
            return;
        }
        outfile << content << endl;
        outfile.flush();
        outfile.close();
    }

};
#endif
