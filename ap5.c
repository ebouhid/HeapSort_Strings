#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 32

void print_arr(char **arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s ", arr[i]);
    }
    printf("\n");

    return;
}

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

int greater_than(char *a, char *b, char *key, int key_len)
{
    int len_a = strlen(a);
    int len_b = strlen(b);
    int i = 0;

    while (i < len_a && i < len_b)
    {
        int rank_a = get_char_ranking(a[i], key, key_len);
        int rank_b = get_char_ranking(b[i], key, key_len);

        // printf("a = %c | rank_a = %d\n", a[i], rank_a);
        // printf("b = %c | rank_b = %d\n", b[i], rank_b);

        // if (rank_a == -1 || rank_b == -1)
        // {
        //     return -1;
        // }

        if (rank_a > rank_b)
            return 1;
        else if (rank_a < rank_b)
            return 0;
        // if rank_a == rank_b, loop keeps going
        i++;
    }

    // caso o laço acima acabe, definimos como menor a string de menor tamanho
    if (len_a < len_b)
        return 0;

    return 1;
}

void swap(char **arr, int pos_a, int pos_b)
{
    char *aux = arr[pos_a];
    arr[pos_a] = arr[pos_b];
    arr[pos_b] = aux;

    return;
}

void heapify(char **arr, int size_arr, int idx, char *key, int key_len)
{
    int largest_string_idx = idx;
    int left_idx = 2 * idx + 1;
    int right_idx = 2 * idx + 2;

    // printf("is %s > %s?\n", arr[left_idx], arr[idx]);

    if (left_idx < size_arr && greater_than(arr[left_idx], arr[idx], key, key_len))
        largest_string_idx = left_idx;

    if (right_idx < size_arr && greater_than(arr[right_idx], arr[idx], key, key_len))
        largest_string_idx = right_idx;

    // printf("largest_string_idx = %d | idx = %d\n", largest_string_idx, idx);

    if (largest_string_idx != idx)
    {
        swap(arr, idx, largest_string_idx);
        heapify(arr, size_arr, largest_string_idx, key, key_len);
    }

    return;
}

char *extract_max_from_heap(char **arr, int size_arr, char *key, int key_len)
{
    char *max = arr[0];
    size_arr--;
    char *last = arr[size_arr];
    arr[0] = last;

    heapify(arr, size_arr, 0, key, key_len);

    return max;
}

char **merge_sort(char **arr, int size_arr, char *key, int key_len)
{
    // building max heap
    for (int i = size_arr / 2 - 1; i >= 0; i--)
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

    return 0;
}