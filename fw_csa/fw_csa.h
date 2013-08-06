#ifndef ALGS_FW_CSA_H_
#define ALGS_FW_CSA_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sdsl/rrr_vector.hpp>
#include <sdsl/util.hpp>
#include "../utils/util.h"
#include "../utils/collection_util.h"
#include "../utils/file_util.h"

using namespace std;
using namespace sdsl;

template<typename bit_vector_class = bit_vector>
class BitVector
{
public:
    bit_vector_class bv;

private:

    int sample;
    bool dynamic;

    vector<int> sample_vec;

public:

    BitVector(bit_vector_class bv, int sample = 64, bool dynamic = false)
    {
        this->bv = bv;
        this->sample = sample;
        this->dynamic = dynamic;
    }

    BitVector(){

    }

    //   close
    void build(int begin, int end, int base = 0)
    {
        int sum = base;
        for (int i = begin; i <= end && i < bv.size(); i++)
        {
            sum = sum + bv[i];
            if (i % sample + 1 == sample)
            {
                sample_vec.push_back(sum);
            }
        }
    }

    int count(int idx)
    {
        int sum, start = (idx / sample) * sample;
        if (!dynamic)
        {
            if (sample_vec.size() != bv.size() / sample)
            {
                sample_vec.clear();
                build(0, bv.size() - 1);
            }
        }
        else
        {
            if (idx >= (sample_vec.size() + 1) * sample)
            {
                int base = sample_vec.size() > 1 ? sample_vec[sample_vec.size() - 1] : 0;
                build(sample_vec.size() * sample, start + sample, base);
            }
        }

        sum = idx / sample > 0 ? sample_vec[idx / sample - 1] : 0;
        for (int i = start; i <= start + idx % sample; i++)
        {
            sum += bv[i];
        }
        return sum;
    }
};

class CSA
{
public:
    static long tim, tim2;
    vector<int> sa;

    vector<int> psi;
    vector<int> sv;
//    vector<bool> bv;
    bit_vector bvv;
    BitVector<> bt;

public:
    CSA(const vector<int> &vec) :
            sa(cal_sa(vec)), psi(sa2psi()), bt(cal_ds2(vec, sv))
    {
        //        初始化列表会按成员声明的顺序来构造成员
        //        sa = cal_sa(vec);
        //        psi = sa2psi();
        //        bv = cal_ds(vec, sv);
        //        bvv = cal_ds2(vec, sv);
        //        bt = ?;
        bvv = bt.bv;
    }

    CSA() {

    }

    double get_csa_size()
    {
        return CollectionUtil::get_size_in_mega_bytes(psi) + CollectionUtil::get_size_in_mega_bytes(sv)
                + util::get_size_in_mega_bytes(bvv);
    }

    void load(const string filename)
    {
        FileUtil::load_from_file(psi, (filename + ".psi").c_str());
        FileUtil::load_from_file(sv, (filename + ".sv").c_str());
        util::load_from_file(bvv, (filename + ".bvv").c_str());
        BitVector<> tv = bvv;
        bt = tv;
    }

    void save(const string filename)
    {
        FileUtil::store_to_file(psi, (filename + ".psi").c_str());
        FileUtil::store_to_file(sv, (filename + ".sv").c_str());
        util::store_to_file(bvv, (filename + ".bvv").c_str());
    }

    vector<pair<int, int> > make_pair_vector(const vector<int> &vec)
    {
        vector<pair<int, int> > pair_vec;
        for (int i = 0; i < vec.size(); i++)
        {
            pair_vec.push_back(make_pair(vec[i], 0));
        }
        return pair_vec;
    }

    bool rank_of_level(vector<pair<int, int> > &vec_origin, int level)
    {
        int gap = 1 << level;
        cout << "gap: " << gap << endl;
        vector<pair<int, int> > vec = vec_origin;
        sort(vec.begin(), vec.end());

        vector<pair<int, int> >::iterator iter;
        iter = unique(vec.begin(), vec.end());
        if (iter != vec.end())
            vec.erase(iter, vec.end());

        map<pair<int, int>, int> mp;
        for (int i = 0; i < vec.size(); i++)
            mp.insert(make_pair(vec[i], i));

        for (int i = 0; i < vec_origin.size(); ++i)
        {
            if (i < vec_origin.size() - gap)
                vec_origin[i] = make_pair(mp[vec_origin[i]], mp[vec_origin[i + gap]]);
            else
                vec_origin[i] = make_pair(mp[vec_origin[i]], 0);
            //        cout << vec_origin[i].first << "_" << vec_origin[i].second << ", ";
        }

        return mp.size() == vec_origin.size();
    }

    vector<int> cal_rank(const vector<int> &vec)
    {
        vector<pair<int, int> > pair_vec = make_pair_vector(vec);

        int level = 0;
        while (!rank_of_level(pair_vec, level))
        {
            level += 1;
        }

        vector<pair<int, int> > pv;
        pv = pair_vec;
        sort(pv.begin(), pv.end());
        map<pair<int, int>, int> mp;
        for (int i = 0; i < pv.size(); i++)
            mp.insert(make_pair(pv[i], i));

        vector<int> rank_vec;
        for (int i = 0; i < pair_vec.size(); i++)
        {
            rank_vec.push_back(mp[pair_vec[i]]);
            //        cout << rank_vec[i] << " ";
        }

        return rank_vec;
    }

    vector<int> cal_sa(const vector<int> &vec)
    {
        vector<int> rank_vec = cal_rank(vec);
        return CollectionUtil::inverse_vector(rank_vec);
    }

    vector<int> sa2psi() const
    {
        vector<int> rank_vec = CollectionUtil::inverse_vector(sa);
        vector<int> psi;
        for (int i = 0; i < sa.size(); i++)
            psi.push_back(rank_vec[(sa[i] + 1) % sa.size()]);

        return psi;
    }

    vector<int> psi2sa() const
    {
        int length = psi.size();
        vector<int> sa(length);
        sa[0] = length - 1;
        int i, j = 0;
        for (i = 0; i < length; i++)
        {
            sa[psi[j]] = (sa[j] + 1) % length;
            j = psi[j];
        }
        return sa;
    }

    bit_vector cal_ds2(const vector<int> &vec, vector<int> &sv)
    {
        bit_vector bv(sa.size());
        sv.clear();

        for (int i = 0; i < sa.size(); i++)
        {
            if (i > 0 && vec[sa[i]] == vec[sa[i - 1]])
                bv[i] = false;
            else
            {
                bv[i] = true;
                sv.push_back(vec[sa[i]]);
            }
        }
        return bv;
    }

//    不再使用
    vector<bool> cal_ds(const vector<int> &vec, vector<int> &sv)
    {
        vector<bool> bv;
        sv.clear();

        for (int i = 0; i < sa.size(); i++)
        {
            if (i > 0 && vec[sa[i]] == vec[sa[i - 1]])
                bv.push_back(false);
            else
            {
                bv.push_back(true);
                sv.push_back(vec[sa[i]]);
            }

        }
        return bv;
    }

    int count(const int pat, vector<int> &loc)
    {
        int left = 0, right = sv.size() - 1, mid;
        loc.clear();
        //        二分查找
        bool found = false;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (sv[mid] > pat)
                right = mid - 1;
            else if (sv[mid] < pat)
                left = mid + 1;
            else
            {
                found = true;
                break;
            }
        }
        int sum = 0, cnt = 0;
        if (found)
        {
            //            注意条件i < bv.size()
            for (int i = 0; i < bvv.size() && sum <= mid + 1; i++)
            {
                sum += bvv[i];
                if (sum == mid + 1)
                {
                    cnt += 1;
                    loc.push_back(sa[i]);
                }
            }
        }
        return cnt;
    }

    int count(const vector<int> &pat, vector<int> &loc)
    {
        for (int i = 0; i < pat.size(); i++)
        {
            vector<int> curr;
            int cnt = count(pat[i], curr);
            if (cnt <= 0)
            {
                loc.clear();
                return 0;
            }
            if (i == 0)
                loc = curr;
            else
            {
                vector<int> res;
                sort(loc.begin(), loc.end());
                sort(curr.begin(), curr.end());
                set_intersection(loc.begin(), loc.end(), curr.begin(), curr.end(), inserter(res, res.begin()));
                if (res.size() <= 0)
                {
                    loc.clear();
                    return 0;
                }
                else
                    loc = res;
            }
            for (int j = 0; j < loc.size(); j++)
            {
                if (loc[j] == bvv.size() - 1 && i < pat.size() - 1)
                {
                    loc.clear();
                    return 0;
                }
                loc[j] = loc[j] + 1;
            }
        }
        for (int i = 0; i < loc.size(); i++)
            loc[i] = loc[i] - pat.size();
        sort(loc.begin(), loc.end());

        return loc.size();
    }

    int count(const int pat)
    {
        vector<int> loc;
        return count(pat, loc);
    }

    int count(const vector<int> &pat)
    {
        vector<int> vec;
        return count(pat, vec);
    }

    vector<int> locate(const int pat)
    {
        vector<int> loc;
        count(pat, loc);
        sort(loc.begin(), loc.end());
        return loc;
    }

    vector<int> locate(const vector<int> &pat)
    {
        vector<int> loc;
        count(pat, loc);
        return loc;
    }

    vector<int> extract()
    {
        return extract(0, sa.size() - 1);
    }
//    前闭后闭
    vector<int> extract(int start, int end)
    {
        vector<int> text;
        if (start > end || end < 0 || start < 0)
            return text;
        else if (end >= sa.size())
            end = sa.size() - 1;

        vector<int>::iterator iter = find(sa.begin(), sa.end(), start);
        int idx_sa = distance(sa.begin(), iter);

        for (int i = 0; i <= end - start; i++)
        {
            text.push_back(sv[(sum_of_bv(idx_sa) - 1)]);
            idx_sa = psi[idx_sa];
        }

        return text;
    }

    int extract(int index)
    {
        long tt = Util::get_system_time();
        vector<int>::iterator iter = find(sa.begin(), sa.end(), index);
        long tmp = Util::get_system_time() - tt;
        tim2 += tmp;
        int idx = sum_of_bv(distance(sa.begin(), iter)) - 1;
        return sv[idx];
    }

    int sum_of_bv(int index)
    {
        //        if (index >= bvv.size())
        //            index = bvv.size() - 1;
        //        int sum = 0;
        long tt = Util::get_system_time();
        //        for (int i = 0; i <= index; i++)
        //            sum += bvv[i];
        int sum = bt.count(index);
        long tmp = Util::get_system_time() - tt;
        tim += tmp;
        return sum;
    }

};

long CSA::tim = 0l;
long CSA::tim2 = 0l;

#endif
