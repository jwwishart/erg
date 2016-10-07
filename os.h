// Copyright (c) 2016 Justin William Wishart
// Full Licence is found in the LICENSE.txt file

/*
    // This file contains operating system functionality
    // No other file ought ever contain operating system specific system calls

    Supported Operating Systems + Compiler Symbol Flag Name
    - *nix      = ERG_OS_NIX
    - Windows   = ERG_OS_WIN
    - Mac       = ERG_OS_MAC
*/

/*
    Documentation:
    PATH_MAX - https://www.gnu.org/software/libc/manual/html_node/Limits-for-Files.html
    getcwd() - https://www.gnu.org/software/libc/manual/html_node/Working-Directory.html
*/

 
#ifdef __gnu_linux__
    #define ERG_OS_NIX
#endif
// TODO do other system defines



#ifdef ERG_OS_NIX 
    #include <limits.h> // PATH_MAX
    #include <unistd.h> // getcwd

    #define ERG_PATH_MAX PATH_MAX 
#endif



// TESTED: 
// - ERG_OS_NIX
extern char *
erg_getcwd(char *buffer, size_t max_length) 
{
    #ifdef ERG_OS_NIX
        return getcwd(buffer, max_length);
    #endif

    // TODO error situation... ?
}