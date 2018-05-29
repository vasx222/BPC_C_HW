// http://informatics.mccme.ru/mod/statements/view3.php?id=253&chapterid=156

#include <stdio.h>

void f(int n) {
    int x;
    scanf("%d", &x);
    if (n - 1 > 0) {
        f(n - 1);
    }
    printf("%d ", x);
}

int main() {
    int n;
    scanf("%d", &n);
    f(n);
    return 0;
}
