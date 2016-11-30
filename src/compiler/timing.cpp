#ifndef COMPILER_TIMING_CPP
#define COMPILER_TIMING_CPP


#include "timing.h"
#include <stdio.h>


void 
print_compiler_execution_time(
    std::chrono::system_clock::time_point start, 
    std::chrono::system_clock::time_point end) 
{
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    auto microseconds = total % 1000;
    total /= 1000;

    auto milliseconds = total % 1000;
    total /= 1000;

    auto seconds = total % 60;
    total /= 60;

    auto minutes = total % 60;
    total /= 60;

    auto hours = total % 24;
    total /= 24;

    auto days = total;

    if (days >= 1) {
        printf("%ld day", days);
        if (days > 1) printf("s");
        printf(" ");
    }
    if (hours >= 1) {
        printf("%ld hour", hours);
        if (hours > 1) printf("s");
        printf(" ");
    }
    if (minutes >= 1) {
        printf("%ld minute", minutes);
        if (minutes > 1) printf("s");
        printf(" ");
    }
    if (seconds >= 1) {
        printf("%ld second", seconds);
        if (seconds > 1) printf("s");
        printf(" ");
    }
    if (milliseconds >= 1) {
        printf("%ld millisecond", milliseconds);
        if (milliseconds > 1) printf("s");
        printf(" ");
    }
    if (microseconds >= 1) {
        printf("%ld microsecond", microseconds);
        if (microseconds > 1) printf("s");
    }
}

#endif /* COMPILER_TIMING_CPP */