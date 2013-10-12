#ifndef ALGS_FILE_UTIL_H_
#define ALGS_FILE_UTIL_H_

#include<iostream>
#include<fstream>
#include<map>
#include<iterator>
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

    static vector<int> get_text_codeword(const string& textfile, const string& codefile, vector<int> &slave)
    {
        vector<pair<int, int> > prv = get_text_codeword(textfile, codefile);
        vector<int> master;
        slave.clear();
        for (int i = 0; i < (int) prv.size(); i++)
        {
            master.push_back(prv[i].first);
            slave.push_back(prv[i].second);
        }
        return master;
    }

    static vector<pair<int, int> > get_text_codeword(const string& textfile, const string& codefile)
    {
        vector<string> vecstr = segment_textfile(textfile);
        map<string, pair<int, int> > mp = get_codeword_map(codefile);
        vector<pair<int, int> > prv;
        for (int i = 0; i < (int) vecstr.size(); i++)
        {
            //            TODO 单独符号已被忽略
            if (mp[vecstr[i]].first != 0)
                prv.push_back(mp[vecstr[i]]);
        }
        return prv;
    }

    //    文本分词
    static vector<string> segment_textfile(const string& textfile)
    {
        vector<string> vec;
        ifstream infile;
        string sline;
        infile.open(textfile.c_str());
        if (!infile)
        {
            cout << "error:unable to open input file:" << textfile << endl;
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
    static map<string, pair<int, int> > get_codeword_map(const string& codefile)
    {
        map<string, pair<int, int> > mp;
        ifstream infile;
        string sline;
        infile.open(codefile.c_str());
        if (!infile)
        {
            cout << "error:unable to open input file:" << codefile << endl;
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
                int second = (right == -1 or left >= right) ? 1 : atoi(sline.substr(right + 1).c_str());
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

    template<typename T>
    static bool store_to_file(vector<T> v, const char* filename, bool add = false)
    {
        ofstream fout(filename, add ? ios::app : ios::out);
        if (!fout)
            return false;
        copy(v.begin(), v.end(), ostream_iterator<T>(fout, "\n"));
        fout.close();
        return true;
    }

    static void load_from_file(vector<int> &v, const char* filename)
    {
        v.clear();
        ifstream infile;
        string sline;
        infile.open(filename);
        if (!infile)
        {
            cout << "error:unable to open input file:" << filename << endl;
            return;
        }
        while (getline(infile, sline))
        {
            v.push_back(atoi(sline.c_str()));
        }
        infile.close();
    }

};
#endif
