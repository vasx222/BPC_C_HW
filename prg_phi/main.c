#include <stdio.h>


int phi(int n) {
    if (n < 2) {
        return 1;
    }
    return phi(n - 1) + phi(n - 2);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", phi(n));
    return 0;
}