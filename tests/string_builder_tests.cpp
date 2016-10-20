// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

// clang++ --std=c++14 -g string_builder_tests.cpp -o bin/string_builder_tests && bin/string_builder_tests

#include "../erg.h"
#include "test.h"

int main() {
    print_test_heading();
    
    // Construct a new empty string builder
    StringBuilder *str = allocate_string_builder();

    expect(str != null);
    expect(get_string_builder_length(str) == 0);
    expect(get_string_builder_capacity(str) == 16);
    expect(str[0] == '\0');

    // Append within default 16 characters buffer size: no re-allocation
    auto message_part1 = "Hello World";

    str = append_string_buffer(str, (char *)message_part1);
    
    expect(str != null);
    expect(get_string_builder_length(str) == strlen(message_part1));
    expect(get_string_builder_capacity(str) == 16);
    expect(str[11] == '\0');
    expect(strcmp(str, "Hello World") == 0);
    
    // Append to entend capacity
    auto message_part2 = ". This is AMAZING!";
    auto expected_combined_length = strlen(message_part1) + strlen(message_part2);

    str = append_string_buffer(str, (char *)message_part2);
    
    expect(str != null);
    expect(get_string_builder_length(str) == expected_combined_length);
    expect(get_string_builder_capacity(str) > expected_combined_length);
    expect(str[29] == '\0');
    expect(strcmp(str, "Hello World. This is AMAZING!") == 0);

    // Append but don't extend capacity!
    auto current_capacity = get_string_builder_capacity(str);
    auto message_part3 = ". Reallocate? no!";
    expected_combined_length += strlen(message_part3);

    str = append_string_buffer(str, (char *)message_part3);
    
    expect(str != null);
    expect(get_string_builder_length(str) == expected_combined_length);
    expect(get_string_builder_capacity(str) == current_capacity);
    expect(str[46] == '\0');
    expect(strcmp(str, "Hello World. This is AMAZING!. Reallocate? no!") == 0);

    // Append a character
    str = append_string_buffer(str, 'Z');
    
    expect(str != null);
    expect(get_string_builder_length(str) == expected_combined_length + 1);
    expect(get_string_builder_capacity(str) == current_capacity); // Ought not change unless underlying algorithm changes;
    expect(str[46] == 'Z');
    expect(str[47] == '\0');
    expect(strcmp(str, "Hello World. This is AMAZING!. Reallocate? no!Z") == 0);

    // Printing the reference directly
    #ifndef SILENT
    printf("String Value Is: %s\n", str);
    #endif

    // Ensure we can clear the StringBuilder, retains capacity
    str = clear_string_builder(str);
    expect(str != null);
    expect(get_string_builder_length(str) == 0);
    expect(get_string_builder_capacity(str) == current_capacity);
    expect(str[0] == '\0');

    // Printing the reference directly
    #ifndef SILENT
    printf("String Value Is: %s\n", str);
    #endif

    // Be a good citizen and free out string builder
    str = free_string_builder(str);
}
