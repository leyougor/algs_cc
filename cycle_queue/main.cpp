//============================================================================
// Name        : ring-queue.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "cycle_queue.h"

using namespace std;

int main(void)
{
    CycleQueue<int> rq;
    rq.in_queue(0);
    rq.in_queue(0);
    rq.in_queue(0);
    rq.in_queue(1);
    rq.print_queue();

    int sum = rq.sum();
    while(sum <= 200){
        rq.in_queue(sum);
        cout << sum << " ";
        sum = rq.sum();
    }

    cout << "\nfinish!" << endl;
    return 0;
}
