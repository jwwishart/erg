// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdlib.h> // calloc
#include <string.h> // strlen

typedef char StringBuilder;

// Capacity & Length
#define prefix_length sizeof(int) * 2

// TODO call this a string builder sort of pattern...?
// TODO pull these string thingies out into util.h I think...
StringBuilder * allocate_string_builder() 
{
    auto start = (char *)malloc(sizeof(char) * 16 + prefix_length);
    auto result = start + prefix_length;

    auto location = (int *)(start);
    *location = 0;
    location = (int *)(start) + 1;
    *location = 16;

    result[0] = '\0';

    return result;
}

char * free_string_builder(StringBuilder * string) {
    string -= prefix_length;
    free(string);
    return NULL;
}

int get_string_builder_length(StringBuilder * str) {
    auto start = str - prefix_length;
    return (*(int *)start);
}

int get_string_builder_capacity(StringBuilder * str) {
    auto start = str - prefix_length;
    return (*(((int *)start)+1));
}

StringBuilder * append_string_buffer(StringBuilder * str, char * append) 
{
    auto start = str - prefix_length;
    int capacity = (*(((int *)start)+1));
    int length   = (*(int *)start);
    int append_len = strlen(append);
    int required_capacity = length + append_len + 1; // + 1 is null terminating character  

    if (required_capacity > capacity) {
        auto new_buffer_size = required_capacity * 2;
        
        start = (char *)realloc(start, sizeof(char) * new_buffer_size);
        str = start + prefix_length;

        auto location = (int *)(start) + 1;
        *location = new_buffer_size;
    }

    // TODO errors
    strcpy(str + length, append);

    // Ensure char after last char is null
    str[required_capacity] = '\0';

    // TODO(jwwishart) should set the next character to above a null \0 AND
    //  maybe might need to always allocate 1 extra character? to ensure it is always
    //  available to set!

    length += append_len;

    auto location = (int *)(start);
    *location = length;

    return str;
}

StringBuilder * append_string_buffer(StringBuilder * str, char c) 
{
    char buffer[2];
    buffer[0] = c;
    buffer[1] = '\0';

    auto result = append_string_buffer(str, buffer);
    return result;
}

StringBuilder * clear_string_builder(StringBuilder * str) 
{
    auto start = str - prefix_length;
    auto location = (int *)(start);
    *location = 0;
    str[0] = '\0';
    return str;
}

// Debugging Helper Function
// Prints the capacity, length etc of a string_builder
void dump_string_builder(StringBuilder * str) {
    auto lengthAndCap = sizeof(int) * 2;

    printf("Value: %s\n", str);

    str -= lengthAndCap;

    printf("Length: %d\n", (*(int *)str));
    printf("Capacity: %d\n", (*(((int *)str)+1)));
}

#endif