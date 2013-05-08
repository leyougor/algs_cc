#ifndef ALGS_UTILS_UTIL_H_
#define ALGS_UTILS_UTIL_H_

#include <string>
#include <iostream>
#include <sys/timeb.h>

class Util
{
public:
    static long get_system_time()
    {
        timeb t;
        ftime(&t);
        return 1000 * t.time + t.millitm;
    }
};


#endif
