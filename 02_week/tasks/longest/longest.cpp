#include <stdexcept>
#include <iostream>

char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    if (begin == nullptr || end == nullptr || begin >= end) {
        count = 0;
        return nullptr;
    }

    const char* longest_start = begin;
    const char* current_start = begin;
    size_t max_length = 1;
    size_t current_length = 1;

    for (const char* ptr = begin + 1; ptr < end; ++ptr) {
        if (*ptr == *(ptr - 1)) {
            ++current_length;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
                longest_start = current_start;
            }
            current_start = ptr;
            current_length = 1;
        }
    }

    // Если все символы повторяются нужно отдельно проверить еще раз
    if (current_length > max_length) {
        max_length = current_length;
        longest_start = current_start;
    }

    count = max_length;
    return const_cast<char*>(longest_start);
}
