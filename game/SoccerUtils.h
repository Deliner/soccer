//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_SOCCERUTILS_H
#define SOCCER_SOCCERUTILS_H

#include<sys/time.h>
#include <stdio.h>

namespace SoccerUtils {

    long long getCurrentTime() {
        struct timeval tv;

        gettimeofday(&tv, NULL);
        return (((long long) tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
    }
}


#endif //SOCCER_SOCCERUTILS_H
