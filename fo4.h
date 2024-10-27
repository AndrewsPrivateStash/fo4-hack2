/*
    FO4 header
*/

#ifndef FO4_H_
#define FO4_H_

#include <stdbool.h>


// ####### WORD #######

/* struct to hold a word and associated data
    { char *chars, unsigned short int match_val, bool possible }
*/
struct word {
    char *chars;                        // array of chars making up the word
    unsigned short int match_val;       // the match value with the correct word {0..n-1}
    bool possible;                      // is the word a possible answer (true until guesses rendered)
};

short int match(const struct word*, const struct word*);
struct word* make_word(const char*, unsigned short int);
void free_word(struct word*);


// ####### WORDS #######

/* struct to hold a collection of words
    { struct word **words, unsigned short int cnt }
*/
struct words {
    struct word **words;        // array of word pointers
    unsigned short int cnt;     // count of array elements
};

struct words* parse_input_words(const char *input);
void free_words(struct words*);
void add_guess(char*, unsigned short, struct words*);

// update the possibilites based on the set of guesses (those words with val != 0)
void update_possibilites(struct words*);

// print the set of words with possible == true
void print_possible(struct words*);
void print_words(struct words*);


// ####### IO functions #######
int menu();


#endif