#include <iostream>

using namespace std;

// Запись "tree_node *&node" означает "ссылка на tree_node*",
// то есть "ссылка на указатель на tree_node".
//
// Если вы хотите написать функцию swap, то вы ей аргументы передаёте по ссылке:
// void swap(int &a, int &b);
// и если вы в такой функции меняете a,
// то меняется та переменная, которую передали в функцию swap
// а не её копия, как было бы в случае просто "int a".
//
// Если заменить int на "tree_node*", то получится то же самое,
// только с переменными типа "tree_node*".

struct tree_node {
  int key;
  tree_node *left;
  tree_node *right;
};

struct tree {
  tree_node *head = NULL;

  void delete_tree() {
    delete_node(head);
  }

  void delete_node(tree_node *node) {
    if (node != NULL) {
      delete_node(node->left);
      delete_node(node->right);
      delete node;
    }
  }

  void add_key(int key) {
    add_key(head, key);
  }

  // Благодаря тому, что мы передаём "tree_node*" по ссылке,
  // мы можем не предполагать, что node != NULL, а обработать этот случай.
  void add_key(tree_node *&node, int key) {
    if (node == NULL) {
      node = new tree_node{key, NULL, NULL};
    } else if (key < node->key) {
      add_key(node->left, key);
    } else if (key > node->key) {
      add_key(node->right, key);
    } else if (key == node->key) {
      // ничего не делаем
    }
  }

  void pre_order() {
    pre_order(head);
  }

  void pre_order(tree_node *node) {
    if (node != NULL) {
      pre_order(node->left);
      cout << node->key << " ";
      pre_order(node->right);
    }
  }
};

int main() {
  tree t;
  int key;
  while (cin >> key, key != 0) {
    t.add_key(key);
  }
  t.pre_order();
  t.delete_tree();
  return 0;
}
