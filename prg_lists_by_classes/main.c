// http://informatics.mccme.ru/mod/statements/view.php?id=206

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct Item {
    char * s;
    struct Item * next;
};

struct List {
    struct Item * first, * last;
};

char * inttostr(int x) {
    int a[10];
    int n = 0;
    while (x > 0) {
        int v = x % 10;
        n++;
        a[n - 1] = v;
        x /= 10;
    }
    char * s = (char*)calloc((size_t) (n + 1), sizeof(char));
    for (int i = 0; i < n; i++) {
        s[i] = (char) ('0' + a[n - i - 1]);
    }
    s[n] = 0;
    return s;
}

int main() {
    int x;
    struct List list[3] = {};

    while (scanf("%d",&x) != -1) {
        //if (x == 0) break;
        char * surname = (char*)calloc(65, sizeof(char));
        scanf("%s", surname);
        char * number = inttostr(x);
        char * s = (char*)calloc(75, sizeof(char));
        strcat(s, number);
        strcat(s, " \0");
        strcat(s, surname);

        struct Item * item = (struct Item*)calloc(1, sizeof(struct Item));
        item->s = s;
        int k = x - 9;
        if (!list[k].first) {
            list[k].first = item;
            list[k].last = item;
        } else {
            list[k].last->next = item;
            list[k].last = item;
        }

        free(surname);
        free(number);
    }


    for (int i = 0; i < 3; i++) {
        for (struct Item * item = list[i].first; item; item = item->next) {
            printf("%s\n", item->s);
        }
    }

    for (int i = 0; i < 3; i++) {
        struct Item * item = list[i].first;
        while (item) {
            struct Item * next = item->next;
            free(item);
            item = next;
        }
    }
    return 0;
}
