#ifndef COMPILER_TIMING_H
#define COMPILER_TIMING_H


#include <chrono>   // high_resolution_clock

void 
print_compiler_execution_time(std::chrono::system_clock::time_point start, 
                              std::chrono::system_clock::time_point end);


#endif /* COMPILER_TIMING_H */