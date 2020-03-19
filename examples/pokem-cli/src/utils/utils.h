#ifndef UTILS_H
#define UTILS_H

/* a pretty name for an infinite loop */
#define forever for(;;)

/* Levenshtein distance: The minimum number of single-character edits required to change one word into the other. Strings do not have to be the same length. Taken from https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C */
int levenshtein(const char *s1, const char *s2);

/* Makes usage of the Levenshtein algorithm to find the index of the most similar string in an array. Return -1 if no result can be retrieved (because, for example, the array's lenght is zero or less) */
int findMostSimilarStringInArray(const char *str, const char **strArray, int arrayLenght);

#endif /* UTILS_H */