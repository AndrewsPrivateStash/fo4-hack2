/*
    FO4 term hack.
    Yet another Fallout4 Terminal hacker, but this time in C
    and hopefully it works, unlike the buggy bloated mess that was the Rust version

    Problem Overview:
    a selection of words are displayed on the "terminal" of equal char length
    and we have g guesses to find the correct word. Upon guessing, If incorrect,
    the terminal will display "x/y correct", where x is the number of correct chars in the correct position,
    and y is the word length.

    This allows for words to be removed if their characters do not match the accumuated knowledge of the guessed words.

    Algorithm
    given n remaining words, and having guessed m times, each with an x_m associated:
    for each remaning word_n:
        for each guess so far guess_m:
            if match(word_n, guess_m) != x_m -> remove word_n from answer-space


    exceptions:
    is it possible for the wrong word to have an equal x to a given guess. Yes.
    eg. corect is: aabbcc; guess is ddbbee (2); word is ffggcc (2)

    therefore we cannot know a word is correct, only that it is not correct, and by ellimination find the correct value,
    trusting that the game always provides an answer in the word set.

*/

#include <stdio.h>
#include <string.h>
#include "fo4.h"
#include "util.h"


#define BUFFER_SIZE 512



int main(void) {


    struct words *possible_words = NULL;
    short choice = 0;
    cls();

    while (1) {

        choice = menu();

        switch (choice) {
            case -1:    //quit
                return 0;
            case 1: {     //enter all possibilites
                if (possible_words != NULL) free_words(possible_words);
                puts("enter all possible words, seperated by commas");

                char input[BUFFER_SIZE];
                if (!fgets(input, BUFFER_SIZE, stdin)) {
                    fprintf(stderr, "couldn't read from stdin\n");
                    continue;
                };
                input[strcspn(input, "\n")] = '\0';     //remove trailing \n

                possible_words = parse_input_words(input);
                print_words(possible_words);
                break;
            }

            case 2: {     //enter a guess and return the remaining possibilities
                char guess[BUFFER_SIZE] = {0};
                int match_val = 0;

                int res = 0;
                while (res != 1) {
                    printf("enter the guessed word: ");
                    res = scanf("%s", guess);
                    while (getchar() != '\n');
                }

                res = 0;
                while (res != 1) {
                    printf("enter the match val #: ");
                    res = scanf("%d", &match_val);
                    while (getchar() != '\n');
                }

                add_guess(guess, (unsigned short) match_val, possible_words);
                update_possibilites(possible_words);
                print_possible(possible_words);

                break;
            }

            case 3:     //see remaining possibilites
                print_possible(possible_words);
                break;

            case 4:     //see all possibilities entered
                print_words(possible_words);
                break;

            default:
                printf("whoops, menu loop produced a choice of: %d, blergh\n", choice);
                break;

        }

    }

    free_words(possible_words);

    return 0;

}
