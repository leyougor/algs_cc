#ifndef ALGS_UTILS_COLLECTION_UTIL_H_
#define ALGS_UTILS_COLLECTION_UTIL_H_

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class CollectionUtil
{
public:

    template<typename K, typename V>
    static map<V, K> inverse_map(const map<K, V> &mp)
    {
        map<V, K> inv_mp;

        for (typename map<K, V>::const_iterator it = mp.begin(); it != mp.end(); ++it)
        {
            inv_mp[it->second] = it->first;
        }

        return inv_mp;
    }

    static vector<int> inverse_vector(const vector<int> &vec)
    {
        int length = vec.size();
        vector<int> inv_vec(length);
        for (int i = 0; i < length; i++)
        {
            inv_vec[vec[i]] = i;
        }
        return inv_vec;
    }

    template<typename vector_class>
    static void print_vec(const vector_class &vec, string name, int limit = 50)
    {
        cout << name << ":[ ";
        for (int i = 0; i < (int) vec.size(); i++)
        {
            if (i < limit)
                cout << vec[i] << " ";
            else if (i == limit)
                cout << "(more than " << limit << " items)..";
        }
        cout << "]" << endl;
    }

    template<typename A>
    static A* vector_to_array(const vector<A> &vec, int &length)
    {
        length = vec.size();
        A* pa = new A[length];
        if (length > 0)
        {
            for (int i = 0; i < length; i++)
            {
                pa[i] = vec[i];
            }
        }
        return pa;
    }

    template<typename A>
    static vector<A> array_to_vector(const A* pa, const int length)
    {
        vector<A> vec;
        if (pa != NULL)
        {
            for (int i = 0; i < length; i++)
            {
                vec.push_back(pa[i]);
            }
        }
        return vec;

    }

    template<typename A>
    static void merge_vector(vector<A> &master, const vector<A> &slave)
    {
        for (int i = 0; i < (int) slave.size(); i++)
        {
            master.push_back(slave[i]);
        }
    }

    template<typename A>
    static void add_vector_to_array(const vector<A> &vec, A* &arr, int &length)
    {
        int new_length = length + vec.size();
        A* new_arr = new A[new_length];
        for (int i = 0; i < new_length; i++)
        {
            if (i < length)
                new_arr[i] = arr[i];
            else
                new_arr[i] = vec[i - length];
        }
        arr = new_arr;
        length = new_length;
    }

};

#endif
