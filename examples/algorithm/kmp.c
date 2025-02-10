#include <stdlib.h>
#include <stdio.h>


void printPrefix(int* prefix, int l) {
    for (int i = 0; i < l; i++) {
        printf("prefix: [%d]: %d\n", i, *(prefix + i));
    }
}

int len(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// copute the longest substring of pattern
// for each index
void compute_prefix(char *pattern, int pLen, int *prefix) {
    *(prefix + 0) = 0;

    int i = 1; int j = 0;
    while (i < pLen) {
        // 1. if j equals 0, means we can not match p[i] with the first char of the substring, just move to the next char of p
        // 2. if p[i] not equals p[j], assign j to the longest substring length that have matched for (j -1),
        //    and compare p[j] and p[i], this means we are ignore to compare the longest matched sub string of p
        // 3. if not match we continue this process untill j equals 0, which should go to scenario 1
        while (j != 0 && pattern[j] != pattern[i]) {
            j = *(prefix + j - 1);
        }

        // 4. if p[i] and p[j] matched, we add 1 to j, means we should increment the length of the matched substring of p[i]
        if (pattern[i] == pattern[j]) {
            j++;
        }
        // 5. the longer the substring matched, the bigger of j is
        *(prefix + i) = j;
        i++;
    }
}

void optimize_prefix(char *pattern, int pLen, int *prefix) {

    int i = 1; int j = 0;
    while (i < pLen) {
        while (j != 0 && pattern[j] != pattern[i]) {
            j = *(prefix + j - 1);
        }
        // 4. if p[i] and p[j] matched, we add 1 to j, means we should increment the length of the matched substring of p[i]
        if (pattern[i] == pattern[j]) {
            if (pattern[i] == pattern[pattern[j]]) {
                *(prefix + i) = *(prefix + pattern[j]);
            }
            j++;
        }

        i++;
    }
}

int kmp(char* target, char* pattern) {

    int pl = len(pattern); int tl = len(target);
    if (tl < pl) return -1;
    
    int* prefix = malloc(sizeof(int) * pl);
    compute_prefix(pattern, pl, prefix);

    // optimize_prefix(pattern, pl, prefix);

    printPrefix(prefix, pl);
    int i = 0;
    int j = 0;
    while (i < tl) {
        while (j > 0 && target[i] != pattern[j]) {
            j = *(prefix + (j - 1));
        }

        printf("ccc: %d: %c, %d: %c\n", i, target[i], j, pattern[j]);
        if (target[i] == pattern[j]) {
            j++;
        }

        if (j == pl) {
            return i - pl + 1;
        }

        i++;
    }

    return -1;

}

void main() {
    char* target = "aaaa";
    char* pattern = "bba";

    printf("%d", kmp(target, pattern));
}
