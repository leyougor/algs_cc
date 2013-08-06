#ifndef ALGS_FW_CSA_ENTRY_H_
#define ALGS_FW_CSA_ENTRY_H_

#include "fw_csa.h"
#include "../utils/file_util.h"
#include "../utils/collection_util.h"
#include "../utils/porter.h"

class CSAEntry
{
    //    TODO should be private
public:
    vector<int> slave;
    vector<int> master;
    map<string, pair<int, int> > mp;
    map<string, int> stem_mp;

    map<pair<int, int>, string> inv_mp;

    CSA csa;
public:
    CSAEntry(string textfile, string codefile) :
            master(FileUtil::get_text_codeword(textfile, codefile, slave)), csa(master)
    {
        mp = FileUtil::get_codeword_map(codefile);
        map<string, pair<int, int> >::iterator it;
        for (it = mp.begin(); it != mp.end(); ++it)
        {
            stem_mp[Porter::stem(it->first)] = it->second.first;
        }
        inv_mp = CollectionUtil::inverse_map(mp);

    }

    void save(string textfile)
    {
        csa.save(textfile);
    }

    void load(string textfile)
    {
        csa.load(textfile);
    }

    double get_csa_size()
    {
        return csa.get_csa_size();
    }

    int count(const string &str)
    {
        int code = stem_mp[str];
        return csa.count(code);
    }
    vector<int> locate(const string &str)
    {
        int code = stem_mp[str];
        return csa.locate(code);
    }

    string extract(int from, int to)
    {
        vector<int> ms = csa.extract(from, to);
        string ss = "";
        for (int i = from; i <= to; i++)
        {
            ss += inv_mp[make_pair(ms[i - from], slave[i])];
            ss += " ";
        }
        return ss;
    }

};

#endif
