#include <stdio.h>
#include <stdlib.h>

const int OK = 0, ERROR = 1, WRONG = 2;

struct arr {
    int * data;
    int len;
};

void change_elem(int * x) {
    *x += 3;
}

void map(struct arr * a, void (*func) (int*)) {
    for (int i = 0; i < a->len; i++) {
        func(a->data + i);
    }
}

void print_code(int code) {
    if (code == OK) {
        printf("OK\n");
        return;
    }
    if (code == ERROR) {
        printf("ERROR\n");
        return;
    }
    if (code == WRONG) {
        printf("WRONG\n");
        return;
    }
    printf("UNKNOWN\n");
}

int assert_equals(struct arr * a1, struct arr * a2) {
    if (!a1 || !a2 || !a1->data || !a2->data) {
        return ERROR;
    }
    if (a1->len != a2->len) {
        return WRONG;
    }
    for (int i = 0; i < a1->len; i++) {
        if (a1->data[i] != a2->data[i]) {
            return WRONG;
        }
    }
    return OK;
}

int assert_equals_ints(int a1, int a2) {
    return a1 == a2 ? OK : WRONG;
}

void test_OK() {
    struct arr a1, a2;
    a1.len = 10;
    a1.data = (int*)malloc(a1.len * sizeof(int));
    a2.len = 10;
    a2.data = (int*)malloc(a2.len * sizeof(int));
    for (int i = 0; i < a1.len; i++) {
        a1.data[i] = i;
        a2.data[i] = i + 3;
    }
    map(&a1, change_elem);
    int code = assert_equals(&a1, &a2);
    code = assert_equals_ints(code, OK);
    print_code(code);
}

void test_ERROR() {
    struct arr a;
    a.len = 10;
    a.data = (int*)malloc(a.len * sizeof(int));
    for (int i = 0; i < a.len; i++) {
        a.data[i] = i;
    }
    map(&a, change_elem);
    int code = assert_equals(0, &a);
    code = assert_equals_ints(code, ERROR);
    print_code(code);
}

void test_WRONG() {
    struct arr a1, a2;
    a1.len = 10;
    a1.data = (int*)malloc(a1.len * sizeof(int));
    a2.len = 10;
    a2.data = (int*)malloc(a2.len * sizeof(int));
    for (int i = 0; i < a1.len; i++) {
        a1.data[i] = i;
        a2.data[i] = i + 5;
    }
    map(&a1, change_elem);
    int code = assert_equals(&a1, &a2);
    code = assert_equals_ints(code, WRONG);
    print_code(code);
}

int main() {
    test_OK();
    test_ERROR();
    test_WRONG();
    return 0;
}