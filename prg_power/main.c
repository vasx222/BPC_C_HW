#include <stdio.h>

double power (double a, int n) {
    if (n == 0) {
        return 1;
    }
    return a * power(a, n - 1);
}

int main() {
    double a;
    int n;
    scanf("%lf%d", &a, &n);
    printf("%lf", power(a, n));

    return 0;
}