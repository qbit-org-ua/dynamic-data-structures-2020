// Стек на статическом массиве

#include <iostream>
#include <string>
#include <set>

using namespace std;

int const MAX_SIZE = 100;

struct stack {
  int stack[MAX_SIZE];
  int size_ = 0;

  void push(int value) {
    stack[size_++] = value;
  }

  int pop() {
    return stack[--size_];
  }

  int back() {
    return stack[size_ - 1];
  }

  int size() {
    return size_;
  }

  void clear() {
    size_ = 0;
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
  return 0;
}
