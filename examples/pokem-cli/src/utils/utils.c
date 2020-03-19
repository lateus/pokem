#include "utils.h"

#include <string.h>
#include <stdio.h>

/* Levenshtein distance: The minimum number of single-character edits required to change one word into the other. Strings do not have to be the same length. This is a modified version of the one published in https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C at the date Friday, December 20th, 2019 */
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int levenshtein(const char *s1, const char *s2)
{
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

/* Makes usage of the Levenshtein algorithm to find the index of the most similar string in an array. Return -1 if no result can be retrieved (because, for example, the array's lenght is zero or less) */
int findMostSimilarStringInArray(const char *str, const char **strArray, int arrayLenght)
{
    if (arrayLenght <= 0) {
        return -1;
    }

    /* assume that the most similar string is the first one */
    int index = 0;
    int currentDistance = levenshtein(str, strArray[0]);
    int minDistance = currentDistance;

    int i;
    for (i = 1; i < arrayLenght; ++i) {
        currentDistance = levenshtein(str, strArray[i]);
        if (currentDistance < minDistance) {
            index = i;
            minDistance = currentDistance;
        }
    }

    return index;
}