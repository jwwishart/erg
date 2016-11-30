// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#ifndef COMPILER_ARGUMENTS_H
#define COMPILER_ARGUMENTS_H

#ifdef __cplusplus
extern "C" {
#endif


// WARNING this is VERY simple approach currently...

// TODO(jwwishart) loko at this for options parsing...
// https://github.com/nothings/stb/blob/master/stb.h#L5819

struct CompilerArgumentFlags {
    // Flags
    
    // Name:    enableSilentMode
    // Default: false
    // Details: Specifies whether a successfull compilation should not show ANY output
    //          Errors will still show. Warnings will be suppressed
    // Flags: ? -q
    //        ? --silent
    //        ? --quiet
    bool enableSilentMode;


    // Debugging Specific Flags
    #ifdef DEBUG

    bool runCompilerTests;

    #endif
};



static bool is_flag_set(int argc, char *argv[], const char *flagString) {
    for (auto i = 0; i < argc; i++) {
        auto a = argv[i];
        auto f = flagString;

        while (*a == *f || (*a == '\0' && *f == '\0')) {
            if (*a == '\0') return true;
            a++;
            f++;
        }
    }

    return false;
}



// Parses the arguments and fills in the supplied argument flags object appropriately
// it will also set defaults
void parse_flags(int argc, char *argv[], CompilerArgumentFlags* flags) {
    // Set Defaults: Anything that is true by default needs to be set.

    // Parse arguments and extract flag only options
    flags->enableSilentMode = is_flag_set(argc, argv, "-q");

    #ifdef DEBUG
    flags->runCompilerTests = is_flag_set(argc, argv, "--run-compiler-tests");
    #endif
}


#ifdef __cplusplus
}
#endif

#endif /* COMPILER_ARGUMENTS_H */
