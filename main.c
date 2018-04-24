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

void test_map_OK() {
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
    free(a1.data);
    free(a2.data);
}

void test_map_ERROR() {
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
    free(a.data);
}

void test_map_WRONG() {
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
    free(a1.data);
    free(a2.data);
}

int condition(int * x) {
    return *x > 7 ? OK : WRONG;
}

struct arr * where(struct arr * a, int (*func) (int*)) {
    struct arr * res = (struct arr*)malloc(sizeof(struct arr));
    res->len = a->len;
    res->data = (int*)calloc((size_t) a->len, sizeof(int));

    int len = 0;
    for (int i = 0; i < a->len; i++) {
        if (condition(&a->data[i]) == OK) {
            res->data[len++] = a->data[i];
        }
    }
    res->len = len;
    if (len < a->len) {
        res->data = (int*)realloc(res->data, len * sizeof(int));
    }
    return res;
}

void test_where_OK() {
    struct arr a1, a2;
    a1.len = 10;
    a1.data = (int*)malloc(a1.len * sizeof(int));
    a2.len = 3;
    a2.data = (int*)malloc(a2.len * sizeof(int));
    for (int i = 1; i <= a1.len; i++) {
        a1.data[i - 1] = i;
    }
    a2.data[0] = 8;
    a2.data[1] = 9;
    a2.data[2] = 10;
    struct arr * res = where(&a1, condition);
    int code = assert_equals(res, &a2);
    code = assert_equals_ints(code, OK);
    print_code(code);
    free(res);
    free(a1.data);
    free(a2.data);
}

int condition2(int * x) {
    return *x % 2 == 0 ? OK : WRONG;
}

void test_where_WRONG() {
    struct arr a1, a2;
    a1.len = 10;
    a1.data = (int*)malloc(a1.len * sizeof(int));
    a2.len = 10;
    a2.data = (int*)malloc(a2.len * sizeof(int));
    for (int i = 1; i <= a1.len; i++) {
        a1.data[i - 1] = i;
        a2.data[i - 1] = i * 2;
    }
    struct arr * res = where(&a1, condition2);
    int code = assert_equals(res, &a2);
    code = assert_equals_ints(code, WRONG);
    print_code(code);
    free(res);
    free(a1.data);
    free(a2.data);
}

int main() {
    test_map_OK();
    test_map_ERROR();
    test_map_WRONG();

    test_where_OK();
    test_where_WRONG();
    return 0;
}