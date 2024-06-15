#include <stdio.h>
#include <stdlib.h>

// Структура для представления узла двоичного дерева
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция для создания нового узла с заданным значением
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для вставки нового значения в двоичное дерево
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Функция для вычисления суммы всех элементов в двоичном дереве
int sum(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->data + sum(root->left) + sum(root->right);
}

int main() {
    struct Node* root = NULL;
    int values[] = {1, 3, 5, 6, 7, 10, 13, 15, 18};

    for (int i = 0; i < 9; i++) {
        root = insert(root, values[i]);
    }

    printf("Сумма всех элементов в дереве: %d\n", sum(root));

    return 0;
}