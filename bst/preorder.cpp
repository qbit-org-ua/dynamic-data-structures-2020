#include <iostream>

using namespace std;

// вершина двоичного дерева поиска
struct tree_node {
  int key; // в вершинах храним значения, будем называть их "ключами"
  tree_node *left; // в левом поддереве все ключи должны быть меньше key
  tree_node *right; // в правом поддереве все ключи должны быть больше key

};

// структура, хранящая указатель на вершину дерева,
// и предоставляющая операции для работы с деревом
struct tree {
  // вершина дерева, изначально она отсутствует
  tree_node *head = NULL;

  void delete_tree() {
    delete_node(head);
  }

  // метод для очистки памяти
  // рекурсивно удаляем левое и правое поддеревья,
  // и потом удаляем node.
  void delete_node(tree_node *node) {
    if (node != NULL) {
      delete_node(node->left);
      delete_node(node->right);
      delete node;
    }
  }

  // метод для добавления ключа в дерево
  void add_key(int key) {
    if (head == NULL) { // если в дереве нет вершин, то нужно создать первую вершину
      head = new tree_node{key, NULL, NULL};
      // такая конструкция работает начиная с C++11,
      // позволяет создать структуру и сразу проинициализировать её поля
      // в порядке объявления
      //
      // то есть, она эквивалентна следующим строчкам:
      // head = new tree_node;
      // head->key = key;
      // head->left = NULL;
      // head->right = NULL;
    } else { // иначе спустимся по дереву и ищем, куда добавить ключ
      add_key(head, key);
    }
  }

  // рекурсивный метод для добавления ключа в поддерево вершины node
  // будем считать, что node != NULL
  void add_key(tree_node *node, int key) {
    if (key == node->key) { // такой ключ уже имеется в дереве,
                            // значит, добавлять его не нужно
      // ничего не делаем
    } else if (key < node->key) { // добавляемый ключ меньше ключа в вершине,
                                  // значит, нужно его добавить в левое поддерево
      if (node->left == NULL) { // левого поддерева нет, его место может занять добавляемый ключ
        // добавляем
        node->left = new tree_node{key, NULL, NULL};
      } else { // левое поддерево есть, рекурсивно добавим ключ в него
        add_key(node->left, key);
      }
    } else if (key > node->key) { // добавляемый ключ больше ключа в вершине,
                                  // значит, нужно его добавить в правое поддерево
      if (node->right == NULL) { // правого поддерева нет, его место может занять добавляемый ключ
        // добавляем
        node->right = new tree_node{key, NULL, NULL};
      } else { // правое поддерево есть, рекурсивно добавим ключ в него
        add_key(node->right, key);
      }
    }
  }

  // то же самое можно реализовать и без рекурсии
  // будем считать, что node != NULL
  void add_key_nonrec(tree_node *node, int key) {
    // спускаемся по дереву,
    // на каждом шаге делаем то же самое, что и в рекурсивном варианте
    while (true) {
      if (key == node->key) {
        return;
      } else if (key < node->key) {
        if (node->left == NULL) {
          node->left = new tree_node{key, NULL, NULL};
          return;
        } else {
          node = node->left;
        }
      } else if (key > node->key) {
        if (node->right == NULL) {
          node->right = new tree_node{key, NULL, NULL};
          return;
        } else {
          node = node->right;
        }
      }
    }
  }

  // pre-order traversal - такой обход дерева, при котором мы
  // сначала выводим значение, хранящееся в вершине,
  // потом рекурсивно выводим левое поддерево,
  // потом рекурсивно выводим правое поддерево
  void pre_order() {
    pre_order(head);
  }

  void pre_order(tree_node *node) {
    if (node != NULL) {
      cout << node->key << " ";
      pre_order(node->left);
      pre_order(node->right);
    }
  }
};

int main() {
  tree t;
  int key;
  // считываем ключ, продолжаем выполнения цикла только если он не равен нулю
  while (cin >> key, key != 0) {
    t.add_key(key);
  }
  t.pre_order();
  t.delete_tree();
  return 0;
}
