// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

// NOTE where a flag has a ? to the left of it that means it is not implemented
// yet or is being considered for inclusion in the flags

// WARNING this is VERY simple approach currently... 

// TODO should look at a library at some point?


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
