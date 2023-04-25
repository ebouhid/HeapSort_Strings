#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 32

/*
print_arr(char **arr, int len)
parameters:
- arr: string array to be printed (char**)
- len: size of arr (int)

returns:
none
*/
void print_arr(char **arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s ", arr[i]);
    }
    printf("\n");

    return;
}

/*
get_char_ranking(char character, char *key, int key_len)
parameters:
- character: character whose ranking is desired to know (char)
- key: array of characters in the desired lexicographic order (char*)
- key_len: lenght of "key" array

returns:
* character ranking
*/
int get_char_ranking(char character, char *key, int key_len)
{
    int i = 0;
    while (i < key_len)
    {
        if (character == key[i])
            return i;
        i++;
    }

    return -1;
}

/*
greater_than(char *a, char *b, char *key, int key_len)
parameters:
- a, b: strings to be compared(char*)
- key: array of characters in the desired lexicographic order (char*)
- key_len: length of "key" array

returns:
* 1 if a is considered greater than b according to the supplied lexicographic order or a equals b
* 0 otherwise
*/
int greater_than(char *a, char *b, char *key, int key_len)
{
    int len_a = strlen(a);
    int len_b = strlen(b);
    int i = 0;

    while (i < len_a && i < len_b)
    {
        int rank_a = get_char_ranking(a[i], key, key_len);
        int rank_b = get_char_ranking(b[i], key, key_len);

        if (rank_a > rank_b)
            return 1;
        else if (rank_a < rank_b)
            return 0;
        // if rank_a == rank_b, loop keeps going
        i++;
    }

    if (len_a < len_b)
        return 0;

    return 1;
}

/*
swap(char **arr, int pos_a, int pos_b)
parameters:
- arr: array of strings in which the swap will occur (char**)
- pos_a: index of first element (int)
- pos_b: index of second element (int)

returns:
none
*/
void swap(char **arr, int pos_a, int pos_b)
{
    char *aux = arr[pos_a];
    arr[pos_a] = arr[pos_b];
    arr[pos_b] = aux;

    return;
}

/*
heapify(char **arr, int size_arr, int idx, char *key, int key_len)
parameters:
- arr: array of strings to be heapified (char**)
- size_arr: size of arr (int)
- idx: index of arr to be heapified (int)
- key: array of characters in the desired lexicographic order (char*)
- key_len: length of "key" array (char*)

returns:
none
*/
void heapify(char **arr, int size_arr, int idx, char *key, int key_len)
{
    int largest_string_idx = idx;
    int left_idx = 2 * idx + 1;
    int right_idx = 2 * idx + 2;

    if (left_idx < size_arr && greater_than(arr[left_idx], arr[largest_string_idx], key, key_len))
        largest_string_idx = left_idx;

    if (right_idx < size_arr && greater_than(arr[right_idx], arr[largest_string_idx], key, key_len))
        largest_string_idx = right_idx;

    if (largest_string_idx != idx)
    {
        swap(arr, idx, largest_string_idx);
        heapify(arr, size_arr, largest_string_idx, key, key_len);
    }

    return;
}

/*
extract_max_from_heap(char **arr, int size_arr, char *key, int key_len)
parameters:
- arr: array of strings from which the maximum element will be extracted (char**)
- key: array of characters in the desired lexicographic order (char*)
- key_len: length of "key" array (char*)

returns:
* max element from arr (char)
*/
char *extract_max_from_heap(char **arr, int size_arr, char *key, int key_len)
{
    char *max = arr[0];
    char *last = arr[size_arr - 1];
    arr[0] = last;

    heapify(arr, size_arr - 1, 0, key, key_len);

    return max;
}

/*
extract_max_from_heap(char **arr, int size_arr, char *key, int key_len)
parameters:
- arr: array of strings from which the maximum element will be extracted (char**)
- key: array of characters in the desired lexicographic order (char*)
- key_len: length of "key" array (char*)

returns:
* sorted: pointer to sorted array
*/
char **merge_sort(char **arr, int size_arr, char *key, int key_len)
{
    // building max heap
    for (int i = size_arr / 2; i >= 0; i--)
    {
        heapify(arr, size_arr, i, key, key_len);
    }

    int builder = size_arr - 1;
    char **sorted = (char **)malloc(size_arr * sizeof(char *));

    while (builder >= 0)
    {
        sorted[builder] = extract_max_from_heap(arr, size_arr, key, key_len);
        builder--;
        size_arr--;
    }

    // free up arr
    free(arr);

    return sorted;
}

int main()
{
    int len_words, len_key;
    // get how many words
    scanf("%d", &len_words);

    // get key size
    scanf("%d", &len_key);

    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        // do nothing
    }

    char *key = (char *)malloc(len_key * sizeof(char));
    for (int i = 0; i < len_key; i++)
    {
        scanf("%c", &key[i]);
    }

    while ((c = getchar()) != '\n' && c != EOF)
    {
        // do nothing
    }
    // create string array
    char **words = (char **)malloc(len_words * sizeof(char *));

    // read string array
    for (int i = 0; i < len_words; i++)
    {
        char *bufword = (char *)malloc(WORDSIZE * sizeof(char));
        scanf("%s", bufword); // don't have to worry about whitespaces

        // check for illegal words
        for (int j = 0; j < strlen(bufword); j++)
        {
            if (get_char_ranking(bufword[j], key, len_key) == -1)
            {
                printf("A palavra %s eh invalida\n", bufword);
                return 0;
            }
        }
        words[i] = bufword;
    }

    words = merge_sort(words, len_words, key, len_key);

    print_arr(words, len_words);

    // free the memory for each string in words
    for (int i = 0; i < len_words; i++)
    {
        free(words[i]);
    }

    // free memory for words
    free(words);

    // free memory for key
    free(key);

    return 0;
}