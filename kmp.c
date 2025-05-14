#include <stdio.h>
#include <string.h>

#define MAX 1000

void computePrefixFunction(char P[], int m, int pi[]) {
    pi[0] = 0;
    int k = 0;

    for (int q = 1; q < m; q++) {		//abacb
        while (k > 0 && P[k] != P[q])
            k = pi[k - 1];

        if (P[k] == P[q])
            k++;

        pi[q] = k;
    }
}

void KMPMatcher(char T[], char P[]) {   //T = abacabacbababacaabacba 	P= abacb 00100
    int n = strlen(T);
    int m = strlen(P);
    int pi[MAX];

    computePrefixFunction(P, m, pi);

    int q = 0; 
								         
    for (int i = 0; i < n; i++) {
        while (q > 0 && P[q] != T[i])
            q = pi[q - 1];

        if (P[q] == T[i])
            q++;

        if (q == m) {
            printf("Pattern occurs with shift %d\n", i - m + 1);
            q = pi[q - 1];
        }
    }
}

int main() {
    char T[MAX], P[MAX];
    printf("Enter text: ");
    scanf("%s", T);
    printf("Enter pattern: ");
    scanf("%s", P);

    KMPMatcher(T, P);
    return 0;
}
