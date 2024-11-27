#include <string.h>
#include <ctype.h>
#include <stdio.h>


// trim whitespace inplace
char *trim(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

//clear screen
void cls(void) {
    printf("\e[1;1H\e[2J"); // only for unix
}

//convert a string to uppercase (ASCII)
void to_upper_str(char *str) {
    char *s = str;
    while (*s) {
        *s = toupper((unsigned char) *s);
        s++;
    }
}
