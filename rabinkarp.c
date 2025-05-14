#include <stdio.h>
#include <string.h>

int charValue(char ch) {
    return (ch - 'a' + 1);  
}

int computeHash(char *str, int len) {
    int hash = 0, power = 1;
    for (int i = len - 1; i >= 0; i--) {
        hash += charValue(str[i]) * power;
        power *= 10;
    }
    return hash;
}

void rabinKarp(char *text, char *pattern) {
    int n = strlen(text), m = strlen(pattern);

    int patHash = computeHash(pattern, m);
    int textHash = computeHash(text, m);
    int j =0;
    int power = 1;
    for (int i = 1; i < m; i++)
        power *= 10;  // 10^(m-1)

    for (int i = 0; i <= n - m; i++) {
        if (textHash == patHash) {
            for ( j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j==m)
                printf("Pattern found at index %d\n", i);
        }

        if (i < n - m) {
            textHash = (textHash - charValue(text[i]) * power) * 10 + charValue(text[i + m]);
        }
    }
}

int main() {
    char text[100], pattern[100];
    printf("Enter text:\n");
    scanf("%s", text);
    printf("Enter pattern:\n");
    scanf("%s", pattern);
    rabinKarp(text, pattern);
    return 0;
}
