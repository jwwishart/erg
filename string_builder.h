// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdlib.h> // calloc
#include <string.h> // strlen

#define prefix_length sizeof(int) * 2

// TODO call this a string builder sort of pattern...?
// TODO pull these string thingies out into util.h I think...
char * allocate_string_builder() 
{
    auto start = (char *)calloc(sizeof(char) * 16 + prefix_length, sizeof(char));
    auto result = start + prefix_length;

    auto location = (int *)(start);
    *location = 0;
    location = (int *)(start) + 1;
    *location = 16; 

    return result;
}

char * free_string_builder(char * string) {
    string -= prefix_length;
    free(string);
    return NULL;
}

char * append_character_array(char * str, char * append) {
    auto start = str - prefix_length;
    int capacity = (*(((int *)start)+1));
    int length   = (*(int *)start);
    int append_len = strlen(append);
    int required_capacity = length + append_len; 

    if (required_capacity > capacity) {
        auto new_buffer_size = required_capacity * 2;
         // TODO(jwwishart) not sure if this is ideal: new Capacity is just new capacity x 2
        start = (char *)realloc(start, sizeof(char) * new_buffer_size);
        str = start + prefix_length;

        auto location = (int *)(start) + 1;
        *location = new_buffer_size;
    }

    // TODO errors
    strcpy(str + length, append);

    // TODO(jwwishart) should set the next character to above a null \0 AND
    //  maybe might need to always allocate 1 extra character? to ensure it is always
    //  available to set!

    length += append_len;

    auto location = (int *)(start);
    *location = length;

    return str;
}


// Debugging Helper Function
// Prints the capacity, length etc of a string_builder
void dump_string_builder(char * str) {
    auto lengthAndCap = sizeof(int) * 2;

    printf("Value: %s\n", str);

    str -= lengthAndCap;

    printf("Length: %d\n", (*(int *)str));
    printf("Capacity: %d\n", (*(((int *)str)+1)));
}

#endif