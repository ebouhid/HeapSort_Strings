#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 32

void print_arr(char **arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s\n", arr[i]);
    }

    return;
}

int get_char_ranking(char character, char *key, int key_len)
{
    int i = 0;
    while (i < key_len)
    {
        if (character == key[i])
            return key_len - i;
    }

    return -1;
}

int compare_strings(char *a, char *b, char *key, int key_len)
{
    int len_a = strlen(a);
    int len_b = strlen(b);
    int i = 0;

    while (i < len_a && i < len_b)
    {
        int rank_a = get_char_ranking(a[i], key, key_len);
        int rank_b = get_char_ranking(b[i], key, key_len);

        if (rank_a == -1 || rank_b == -1)
        {
            return 0;
        }

        if (rank_a > rank_b)
            return 1;
        else if (rank_a < rank_b)
            return -1;
        // caso igual, continua rodando
    }

    // caso o laço acima acabe, definimos como menor a string de menor tamanho
    if (len_a < len_b)
        return len_a;

    return len_b;
}

void build_max_heap()

    int main()
{
    int len_words, len_key;
    // ler quantidade de palavras
    scanf("%d", &len_words);

    // ler tamanho da ordem
    scanf("%d", &len_key);
    char key[] = (char *)malloc(len_key * sizeof(char));
    for (int i = 0; i < len_key; i++)
    {
        scanf("%c", &key[i]);
    }

    // criar lista de palavras
    char **words = (char **)malloc(len_words * sizeof(char *));

    // ler lista de palavras
    for (int i = 0; i < len_words; i++)
    {
        char *bufword = (char *)malloc(WORDSIZE * sizeof(char));
        scanf("%s", bufword); // não nos preocupamos com espaços
        words[i] = bufword;
    }

    // sanity check

    return 0;
}