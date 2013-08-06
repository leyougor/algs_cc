#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sdsl/rrr_vector.hpp>
#include <sdsl/util.hpp>
#include "file_util.h"

using namespace std;
using namespace sdsl;

struct person
{
//	char name[20];
    string name;
    int math;
    int eng;
    int total;
};

void test_cfile()
{
    FILE *fp;

    person cc =
    { "lay", 53, 87, 128 };

    if ((fp = fopen("test.txt", "w+")) == NULL)
    {
        cout << "error in open file" << endl;
    }
//    fseek(fp, 10 * sizeof(st), 0);
    fwrite(&cc, sizeof(cc), 2, fp);
    fseek(fp, 0, SEEK_SET);
    fread(&cc, sizeof(cc), 1, fp);
    cout << cc.name << ":" << cc.math << "," << cc.eng << "," << cc.total << endl;

    fclose(fp);
}

struct student
{
//	char name[20];
    string name;
    int num;
    int age;
    char sex;
};

void test_file_w()
{
    person bb[2] =
    { "lay", 53, 87, 128, "lay", 53, 87, 128 };
    ofstream fout("test.txt", ios::binary);
    if (!fout)
    {
        cerr << "open error!" << endl;
    }
    fout.write((char*) &bb, sizeof(bb));
    fout.close();

    person cc[2];
    ifstream fin("test.txt", ios::binary);
    if (!fin)
    {
        cerr << "open error!" << endl;
    }
    for (int i = 0; i < 1; i++)
        fin.read((char*) &cc[i], sizeof(cc[i]));
    fin.close();
    cout << cc[0].name << ":" << cc[0].math << "," << cc[0].eng << "," << cc[0].total << endl;
}

void test_file_r()
{
    person cc[3];
    ifstream fin("test.txt", ios::binary);
    if (!fin)
    {
        cerr << "open error!" << endl;
    }
    for (int i = 0; i < 1; i++)
        fin.read((char*) &cc[i], sizeof(cc[i]));
    fin.close();
    cout << cc[0].name << ":" << cc[0].math << "," << cc[0].eng << "," << cc[0].total << endl;
}

void test_write()
{
    student stud[3] =
    {
    { "Lisdfasdasdasdasdasdadssadas", 1001, 18, 'f' },
      { "Fun", 1002, 19, 'm' },
      { "Wang", 1004, 17, 'f' } };
    ofstream outfile("test.txt", ios::binary);
    if (!outfile)
    {
        cerr << "open error!" << endl;
    }
    for (int i = 0; i < 3; i++)
    {
        cout << "size of student :" << sizeof(stud[i]) << endl;
        outfile.write((char*) &stud[i], sizeof(stud[i]) * 2);
    }
    outfile.close();

    student stud2[3];
    int i;
    ifstream infile("test.txt", ios::binary);
    if (!infile)
    {
        cerr << "open error!" << endl;
    }
    for (i = 0; i < 3; i++)
    {
        infile.read((char*) &stud2[i], sizeof(stud[i]));
    }
    infile.close();
    for (i = 0; i < 3; i++)
    {
        cout << "NO." << i + 1 << endl;
        cout << "name:" << stud2[i].name << endl;
        cout << "num:" << stud2[i].num << endl;
        cout << "age:" << stud2[i].age << endl;
        cout << "sex:" << stud2[i].sex << endl << endl;
    }
}

void test_read()
{
    student stud[3];
    int i;
    ifstream infile("test.txt", ios::binary);
    if (!infile)
    {
        cerr << "open error!" << endl;
    }
    for (i = 0; i < 3; i++)
        infile.read((char*) &stud[i], sizeof(stud[i]));
    infile.close();
    for (i = 0; i < 3; i++)
    {
        cout << "NO." << i + 1 << endl;
        cout << "name:" << stud[i].name << endl;
        cout << "num:" << stud[i].num << endl;
        cout << "age:" << stud[i].age << endl;
        cout << "sex:" << stud[i].sex << endl << endl;
    }
}
int main()
{
    string ss = "nihao";
//	test_file_w();
//	test_file_r();

    vector<bool> v;
    v.push_back(false);
    v.push_back(false);
    v.push_back(true);
//    ofstream fout("test.txt", ios::app);

    bit_vector bv(10);
    for (int i = 0; i < 10; i++)
        bv[i] = i;
    util::store_to_file(bv, "test.txt");
    cout << util::get_size_in_mega_bytes(bv) << endl;

    bit_vector cv;
    util::load_from_file(cv, "test.txt");

    for (int i = 0; i < cv.size(); i++)
        cout << cv[i] << endl;

//ostream_iterator<string>(cout," ");
//    copy(v.begin(), v.end(), ostream_iterator<bool>(fout, ","));
    FileUtil::store_to_file(v, "test.txt");

//    vector<int> cv;
//
//    FileUtil::load_from_file(cv, "test.txt");
//
    CollectionUtil::print_vec(cv,"cv");
//    cout << CollectionUtil::get_size_in_mega_bytes(cv) << endl;

    return 0;
}
