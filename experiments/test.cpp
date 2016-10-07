// Linux: this was written and executed on Linux Mint
// clang++ --std=c++11 -g test.cpp -o bin/test && bin/test

#include <stdio.h>    // printf()
#include <unistd.h>   // getcwd()
#include <limits.h>   // PATH_MAX
#include <sys/stat.h> // mkdir()

#include "../os.h" // ERG_PATH_MAX, erg_getcwd()

int main() {
    // Operating System Defines
    //
    // Linux Mint 
    #ifdef ERG_OS_NIX
        printf("You are compiling this on Linux\n");
    #endif



    // Get the current working directory
    char buffer[ERG_PATH_MAX];
    erg_getcwd(buffer, ERG_PATH_MAX);
    printf("%s\n", buffer);
    // char buffer [PATH_MAX];
    // getcwd(buffer, PATH_MAX);
    // printf("%s\n", buffer);

    // Does a subdirectory exist?
// TODO check the directory exists first?

    // Create subdirectory
    //  Read and write permissions are given to the owner
    // 
    // Documentation: 
    //      mkdir function
    //      https://www.gnu.org/software/libc/manual/html_node/Creating-Directories.html
    //
    //      Permission Flag Information
    //      https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
    // 
    // Result:
    //  result is 0 for success -1 for failure
    auto result = mkdir("this_is_a_test", 
          // Owner: Do Anything
          S_IRUSR  
        | S_IWUSR
        | S_IXUSR
          // Group: Access Only
        | S_IRGRP
          // Others: Access Only
        | S_IROTH);

    printf("mkdir result: %d\n", result);
}