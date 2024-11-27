
#include "fo4.h"
#include "util.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// char matching function
// scan each word and count the number of match char positions
short int match(const struct word *wref, const struct word *wcomp) {
    short ref_len = strlen(wref->chars);

    // check that both strings are same length, if not return -1
    if ((size_t)ref_len != strlen(wcomp->chars)){
        return -1;
    }

    // scan the strings and count up matches
    short int match_cnt = 0;
    for (int i = 0; i < ref_len; i++) {
        if (wref->chars[i] == wcomp->chars[i]) {
            match_cnt++;
        }
    }

    return match_cnt;

}


// make a word object using passed values
struct word* make_word(const char* word, unsigned short int val) {
    short str_len = strlen(word);
    struct word* new_word = malloc(sizeof(struct word));

    new_word->chars = malloc(sizeof(char) * (str_len + 1));
    if(!strcpy(new_word->chars, word)) {
        return NULL;
    }
    new_word->match_val = val;
    new_word->possible = true;

    return new_word;
}


// free the memory for a word
void free_word(struct word* to_free) {
    free(to_free->chars);
    free(to_free);
}


// load a words struct from raw unparced comma seperated string
struct words* parse_input_words(const char *input) {

    // copy string for parsing
    char *in_str = malloc(sizeof(char)*(strlen(input)+1));
    in_str = strcpy(in_str, input);

    // make the words container
    struct words *out_words = malloc(sizeof(struct words));
    out_words->cnt = 0;
    out_words->words = malloc(sizeof(struct word*));

    char *tok;  // pointer that is shifted as strtok iterates
    tok = strtok(in_str, ",");


    // loop over string splitting on commas
    while(tok != NULL) {

        tok = trim(tok);    // trim tok
        to_upper_str(tok);  // upper case

        if (out_words->cnt > 0) {
            out_words->words = realloc(out_words->words, sizeof(struct word*) * (out_words->cnt +1));
        }

        struct word *tmp = make_word(tok,0);
        if (tmp) {
            out_words->words[out_words->cnt] = tmp;
            out_words->cnt++;
        }

        tok = strtok(NULL, ",");
    }

    free(in_str);

    return out_words;
}


// print words as list to stdout
void print_words(struct words* words) {
    printf("\nYour %d Words:\n", words->cnt);
    for (int i = 0; i < words->cnt -1; i++) {
        printf("%s (m%d,p%d), ", words->words[i]->chars, words->words[i]->match_val,words->words[i]->possible);
    }
    printf("%s (m%d,p%d)\n\n",
        words->words[words->cnt -1]->chars,
        words->words[words->cnt -1]->match_val,
        words->words[words->cnt -1]->possible
    );
}


void add_guess(char *guess, unsigned short match_val, struct words *words) {
    char str[128];
    strcpy(str, trim(guess));
    to_upper_str(str);

    //find word in words
    for (int i = 0; i < words->cnt; i++) {
        if( strcmp(str,words->words[i]->chars) == 0 ) {
            words->words[i]->match_val = match_val;
            words->words[i]->possible = false;  // a guess cannot be correct
        }
    }

}


// loop over the words and compare the match value of
// possible words against the guessed values; setting possibility accordingly
void update_possibilites(struct words *words) {
    for (int i = 0; i < words->cnt; i++) {
        if (words->words[i]->possible) {    // look for eligible words
            for ( int j = 0; j < words->cnt; j++) {
                if ( strcmp(words->words[i]->chars, words->words[j]->chars) != 0
                        && words->words[j]->match_val > 0) { // not the same word and a guess

                    if ( match(words->words[i], words->words[j]) != words->words[j]->match_val ) {
                        // possibility doesn't match guess so can be removed
                        words->words[i]->possible = false;
                        break;
                    }
                }
            }
        }
    }

}


void print_possible(struct words *words) {
    // scan the words and display the words with possible == true
    puts("\n");
    int pw_cnt = 0;
    for (int i = 0; i < words->cnt; i++) {
        if (words->words[i]->possible) {
            pw_cnt++;
            printf("%s\n", words->words[i]->chars);
        }
    }
    printf("%d possible words remaining\n\n", pw_cnt);
}


void free_words(struct words *words) {
    for (int i = 0; i < words->cnt; i++) {
        free_word(words->words[i]);
    }
    free(words->words);
    free(words);
}



// IO functions

// print the menu to the screen
// and grab user selection from stdin
int menu(void) {
    //cls();
    int input = -1;

    while (1) {
        puts("FO4 Terminal Hacker\n--------------------------------");
        puts("1) Enter Possible Words (overwrites)");
        puts("2) Enter Guess");
        puts("3) Show Remaing Possibilites");
        puts("4) Show All Words");
        puts("-1) Quit\n");

        int result = scanf("%d", &input);
        while(getchar() != '\n');   // flush newline

        if (result != 1 || input > 4 || input < -1 || input == 0) {
            puts("please enter a number between 1..4, or -1 to quit.\n\n");
            continue;
        }
        break;
    }

    return input;

}
