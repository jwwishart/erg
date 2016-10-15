// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

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
        OS Indicator Defines
            https://sourceforge.net/p/predef/wiki/OperatingSystems/

        PATH_MAX
            https://www.gnu.org/software/libc/manual/html_node/Limits-for-Files.html
            
        getcwd()
            https://www.gnu.org/software/libc/manual/html_node/Working-Directory.html

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

extern void
erg_printcwd() 
{
    char buffer[1000];
    erg_getcwd(buffer, 1000);
    printf("%s\n", buffer);
}

// WARNING: Caller must free the memory when you are done with it!
extern char *
erg_get_file_contents(const char *path) 
{
    // TODO(jwwishart) what if the path is a directory?
    FILE * file;
    file = fopen(path, "r");
    if (file == null) return null;

    fseek(file, 0L, SEEK_END);
    int file_size = ftell(file);
    rewind(file);

    auto buffer = (char *)malloc(sizeof(char) * file_size + 1);
    buffer[file_size] = '\0';
    fread(buffer, sizeof(buffer), file_size, file);

    return buffer;
}
