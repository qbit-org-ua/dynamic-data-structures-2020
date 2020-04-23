#include <iostream>

using namespace std;

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
    if (head == NULL) {
      head = new tree_node{key, NULL, NULL};
    } else {
      add_key(head, key);
    }
  }

  void add_key(tree_node *node, int key) {
    if (key == node->key) {
    } else if (key < node->key) {
      if (node->left == NULL) {
        node->left = new tree_node{key, NULL, NULL};
      } else {
        add_key(node->left, key);
      }
    } else if (key > node->key) {
      if (node->right == NULL) {
        node->right = new tree_node{key, NULL, NULL};
      } else {
        add_key(node->right, key);
      }
    }
  }

  void add_key_nonrec(tree_node *node, int key) {
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
  while (cin >> key, key != 0) {
    t.add_key(key);
  }
  t.pre_order();
  t.delete_tree();
  return 0;
}
