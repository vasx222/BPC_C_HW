// http://informatics.mccme.ru/mod/statements/view.php?id=599

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value, height;
    struct Node * L, * R;
};

int add_node(struct Node ** root, struct Node * node,
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
            node->height = parent->height + 1;
        } else {
            node->height = 1;
            *root = node;
        }
        return node->height;
    }
    if (node->value == x) return 0;
    if (x < node->value) {
        return add_node(root, node->L, node, x);
    } else {
        return add_node(root, node->R, node, x);
    }
}

int max(int x, int y) {
    return x <= y ? y : x;
}

int count_height(struct Node * node) {
    if (!node) {
        return 0;
    }
    return 1 + max(count_height(node->L), count_height(node->R));
}

void clear_tree(struct Node * node) {
    if (!node) {
        return;
    }
    clear_tree(node->L);
    clear_tree(node->R);
    free(node);
}

int main() {
    struct Node * root = 0;
    int height = 0;
    while (1) {
        int x;
        scanf("%d", &x);
        if (x == 0) break;
        height = max(height, add_node(&root, root, 0, x));
    }
//    int height = count_height(root);
    printf("%d", height);//7 3 2 1 9 5 4 6 8 0
    clear_tree(root);
}
