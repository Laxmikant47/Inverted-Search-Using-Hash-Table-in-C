#include"head.h"

int get_indexed_hash(const char *word) 
{
    char first_char = tolower(word[0]); // Convert to lowercase

    if (first_char >= 'a' && first_char <= 'z') 
    {
        return first_char - 'a'; // Index 0 to 25 for alphabets
    } else if (first_char >= '0' && first_char <= '9') 
    {
        return 26; // Index 26 for digits
    } else {
        return 27; // Index 27 for special characters
    }
}