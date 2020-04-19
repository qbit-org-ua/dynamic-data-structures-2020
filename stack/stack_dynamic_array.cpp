// Стек на динамическом саморасширяющемся массиве

#include <iostream>
#include <string>
#include <set>

using namespace std;

int const DEFAULT_CAPACITY = 2;

struct stack {
  int capacity = DEFAULT_CAPACITY;
  int *stack = new int[capacity];
  int size_ = 0;

  void delete_stack() {
    delete[] stack;
  }

  void change_capacity(int new_capacity) {
    int *new_stack = new int[new_capacity];
    for (int i = 0; i < size_; ++i) {
      new_stack[i] = stack[i];
    }
    delete[] stack;
    stack = new_stack;
    capacity = new_capacity;
  }

  void ensure_capacity(int new_size) {
    if (new_size < capacity / 4) {
      change_capacity(capacity / 2);
    }
    if (new_size > capacity) {
      change_capacity(capacity * 2);
    }
  }

  void push(int value) {
    ensure_capacity(size_ + 1);
    stack[size_++] = value;
  }

  int pop() {
    int result = stack[--size_];
    ensure_capacity(size_);
    return result;
  }

  int back() {
    return stack[size_ - 1];
  }

  int size() {
    return size_;
  }

  void clear() {
    size_ = 0;
    change_capacity(DEFAULT_CAPACITY);
  }
};

int main() {
  string cmd;
  stack st;
  while (cin >> cmd) {
    if (cmd == "push") {
      int arg;
      cin >> arg;
      st.push(arg);
      cout << "ok";
    } else if (cmd == "pop") {
      if (st.size() == 0) {
        cout << "error";
      } else {
        cout << st.pop();
      }
    } else if (cmd == "back") {
      if (st.size() == 0) {
        cout << "error";
      } else {
        cout << st.back();
      }
    } else if (cmd == "size") {
      cout << st.size();
    } else if (cmd == "clear") {
      st.clear();
      cout << "ok";
    } else if (cmd == "exit") {
      cout << "bye";
    }
    cout << "\n";
  }
  st.delete_stack();
  return 0;
}
