// http://informatics.mccme.ru/mod/statements/view3.php?id=599&chapterid=759#1

#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node * L, * R;
};

void add_node(struct Node ** root, struct Node * node,
             struct Node * parent, int x) {
    if (!node) {
        node = (struct Node*)malloc(sizeof(struct Node));
        node->value = x;
        node->L = 0;
        node->R = 0;
        if (parent) {
            if (x < parent->value) {
                parent->L = node;
            } else {
                parent->R = node;
            }
        } else {
            *root = node;
        }
    }
    if (node->value == x) return;
    if (x < node->value) {
        add_node(root, node->L, node, x);
    } else {
        add_node(root, node->R, node, x);
    }
}

int max(int x, int y) {
    return x <= y ? y : x;
}

void clear_tree(struct Node * node) {
    if (!node) {
        return;
    }
    clear_tree(node->L);
    clear_tree(node->R);
    free(node);
}

int get_max(struct Node * node) {
    if (!node->R) {
        return node->value;
    }
    return get_max(node->R);
}

int get_second_max(struct Node * node, struct Node * parent) {
    if (!node->R) {
        if (node->L) {
            return get_max(node->L);
        } else {
            return parent->value;
        }
    } else {
        return get_second_max(node->R, node);
    }
}

int main() {
    struct Node * root = 0;
    while (1) {
        int x;
        scanf("%d", &x);
        if (x == 0) break;
        add_node(&root, root, 0, x);
    }
    printf("%d\n", get_second_max(root, 0));
    // 7 3 2 1 9 5 4 6 8 0
    clear_tree(root);
}