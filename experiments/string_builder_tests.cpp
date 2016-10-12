// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

// clang++ --std=c++14 -g string_builder_tests.cpp -o bin/string_builder_tests && bin/string_builder_tests

#include "../erg.h"

int main() {

    // Construct a new empty string builder
    auto str = allocate_string_builder();

    expect(str != null);
    expect(get_string_builder_length(str) == 0);
    expect(get_string_builder_capacity(str) == 16);

    // Append within default 16 characters buffer size: no re-allocation
    auto message_part1 = "Hello World";

    str = append_character_array(str, (char *)message_part1);
    
    expect(str != null);
    expect(get_string_builder_length(str) == strlen(message_part1));
    expect(get_string_builder_capacity(str) == 16);

    // Append to entend capacity
    auto message_part2 = ". This is AMAZING!";
    auto expected_combined_length = strlen(message_part1) + strlen(message_part2);

    str = append_character_array(str, (char *)message_part2);
    
    expect(str != null);
    expect(get_string_builder_length(str) == expected_combined_length);
    expect(get_string_builder_capacity(str) > expected_combined_length);

    // Append but don't extend capacity!
    auto current_capacity = get_string_builder_capacity(str);
    auto message_part3 = ". Reallocate? no!";
    expected_combined_length += strlen(message_part3);

    str = append_character_array(str, (char *)message_part3);
    
    expect(str != null);
    expect(get_string_builder_length(str) == expected_combined_length);
    expect(get_string_builder_capacity(str) == current_capacity);

    // Printing the reference directly
    printf("String Value Is: %s\n", str);

    // Be a good citizen and free out string builder
    str = free_string_builder(str);
}