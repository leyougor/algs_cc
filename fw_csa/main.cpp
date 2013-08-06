//============================================================================
// Name        : fw-csa.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "fw_csa.h"
#include "fw_csa_entry.h"

using namespace std;

const static string textfile = "/home/lau/corpus/english.50MB";
const static string codefile = "/home/lau/corpus/english.50MB_cw.txt";

void test_csa() {
	vector<int> vec;
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(5);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(5);

	for (int i = 0; i < 1000000; i++)
		vec.push_back(rand() % 5000);
	vec.push_back(0); // 作为结束符

	//    vector<int> sa = cal_sa(vec);
	//    vector<int> psi = sa2psi(sa);
	//    vector<int> sv;
	//    vector<bool> bv = cal_ds(vec, sa, sv);
	//    vector<int> resa = psi2sa(psi);

	CSA csa(vec);

	CollectionUtil::print_vec(vec, "orig");
	CollectionUtil::print_vec(csa.sa, "sa");
	CollectionUtil::print_vec(csa.psi, "psi");
	CollectionUtil::print_vec(csa.sv, "sv");
	CollectionUtil::print_vec(csa.bvv, "bvv");
	CollectionUtil::print_vec(csa.psi2sa(), "psi2sa");

	vector<int> pat, loc, text;
	pat.push_back(2);
	pat.push_back(3);
	//    pat.push_back(5);

	cout << "count: " << csa.count(pat, loc) << endl;
	CollectionUtil::print_vec(loc, "locate");

	int tt = time(0);
	//    for (int i = 0; i < 300; i++)
	//        csa.extract(rand() % 8000);
	//    text = csa.extract(8000, 8500);
	text = csa.extract(1, 12);
	CollectionUtil::print_vec(text, "text");

	cout << "\nextract cost time: " << time(0) - tt << "s" << endl;
	cout << "\nbitcount cost time: " << CSA::tim << "ms" << endl;
	cout << "\nfind cost time: " << CSA::tim2 << "ms" << endl;
}
void test_cse() {
	CSAEntry cse(textfile, codefile);

	CollectionUtil::print_vec(cse.master, "master");
	CollectionUtil::print_vec(cse.slave, "slave");

	cout << cse.count("said") << endl;
	CollectionUtil::print_vec(cse.locate("said"), "loc");

	cout << cse.extract(11000, 12000) << endl;
}

void test_paper() {
	vector<int> vec;
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.push_back(2);
	vec.push_back(0);

	CSA csa(vec);

	CollectionUtil::print_vec(vec, "orig");
	CollectionUtil::print_vec(csa.sa, "sa");
	CollectionUtil::print_vec(csa.psi, "psi");
	CollectionUtil::print_vec(csa.sv, "sv");
	CollectionUtil::print_vec(csa.bvv, "bvv");
	cin.get();
}

int main() {
	test_cse();
	return 0;
}
