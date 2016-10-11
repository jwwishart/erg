// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

// clang++ --std=c++14 -g string_builder_tests.cpp -o bin/string_builder_tests && bin/string_builder_tests

#include <stdio.h>    // printf()

#include "../string_builder.h"

int main() {

// UPTO HERE vvv
// TODO(jwwishart) asserts to verify capacity etc...
// TODO(jwwishart) function to get length of string
// TODO(jwwishart) function to get capacity of string (use in other functions)
// TODO(jwwishart) cleanup the functions.. "location" and other oddities are not 
//  really easy to read...
//  - Maybe move stuff to some macros? or something? or maybe NOT!
// TODO(jwwishart) Final \0 character after string ... allocate extra byte!

    // Construct a new empty string builder
    auto str = allocate_string_builder();
    dump_string_builder(str);

    // Append within default 16 characters buffer size: no re-allocation
    str = append_character_array(str, (char *)"Hello World");
    dump_string_builder(str);

    // Append to entend capacity
    str = append_character_array(str, (char *)". This is AMAZING!");
    dump_string_builder(str);

    // Append but don't extend capacity
    str = append_character_array(str, (char *)". Reallocate? no!");
    dump_string_builder(str);

    // Printing the reference directly
    printf("String Value Is: %s\n", str);

    // Be a good citizen and free out string builder
    str = free_string_builder(str);
}