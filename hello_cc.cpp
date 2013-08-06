/*
 * hello_cc.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: lau
 */

#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	vector<int> vec;
	for (int i = 0; i < 100; i++)
		vec.push_back(i * i);
	cout <<"vec size :" <<vec.size()*sizeof(int)/1024/1024 <<"mb"<< endl;
	cout << "hello,worl!" << endl;
	cout << "\nfinish!" << endl;
	return 0;
}

