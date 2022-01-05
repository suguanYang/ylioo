#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// The KMP algorithm.
int *compute_prefix(char *pattern, int pattern_length)
{
    int *prefix_counts = (int*)malloc(sizeof(int) * pattern_length);
    prefix_counts[0] = 0;

    char k = 0;
    for(char q = 1; q < pattern_length; q++)
    {
        if (k > 0 && pattern[k] != pattern[q])
        {
            k = prefix_counts[q];
        }
        if (pattern[k] == pattern[q])
        {
            k++;
        }
        prefix_counts[q] = k;
    }

    return prefix_counts;
}

int kmp(char *P, char *T)
{
    int p_len = strlen(P);
    int t_len = strlen(T);

    int *prefix_counts = compute_prefix(P, p_len);

    int f_idx = -1;
    int k = 0;
    for (int i = 0; i < t_len; i++)
    {
        if (k > 0 && P[k] < T[i])
        {
            k = prefix_counts[k];
        }

        if (P[k] == T[i])
        {
            k++;
        }

        if (k == p_len)
        {
            f_idx = i - k + 1;
            return f_idx;
            // k = prefix_counts[k];    // continue to find next match
        }
    }

    return f_idx;
}

int main()
{
    char *exa = "ababaca";
    
    char *t = "abavcababaca";
    int idx = kmp(exa, t);
    return idx;
}