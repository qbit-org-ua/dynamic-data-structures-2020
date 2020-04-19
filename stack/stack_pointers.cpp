// Стек на односвязном списке

#include <iostream>
#include <string>
#include <set>

using namespace std;

struct stack_node {
  int element;
  stack_node *prev;
};

struct stack {
  stack_node *top = NULL;
  int size_ = 0;

  void delete_stack() {
    clear();
  }

  void push(int value) {
    // Можно записать так
    //stack_node *new_top = new stack_node;
    //(*new_top).element = value;
    //(*new_top).prev = top;

    // Вместо разыменовывания в скобках и обращения к полю можно использовать
    // "оператор стрелочка"
    //stack_node *new_top = new stack_node;
    //new_top->element = value;
    //new_top->prev = top;

    // Начиная с C++11 можно писать так
    stack_node *new_top = new stack_node{value, top};

    top = new_top;
    ++size_;
  }

  int pop() {
    //int result = (*top).element;
    //stack_node *new_top = (*top).prev;

    //int result = top->element;
    //stack_node *new_top = top->prev;

    // Начиная с C++17 можно писать так
    auto [result, new_top] = *top;

    delete top;
    top = new_top;
    --size_;
    return result;
  }

  int back() {
    return top->element;
  }

  int size() {
    return size_;
  }

  void clear() {
    while (size_ != 0) {
      pop();
    }
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
  st.clear();
  return 0;
}
