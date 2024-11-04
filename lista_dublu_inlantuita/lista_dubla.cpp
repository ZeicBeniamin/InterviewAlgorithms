#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

ifstream fin("lista_dubla.in");
ofstream gout("lista_dubla.out");

class Node {
public:
  int id;
  Node *next;
  Node *prev;

  Node(int id) : id(id) {}

  static shared_ptr<Node> make_node(int id) {
    return make_shared<Node>(id);
  }
};

class List2 {
public:
  Node* first = NULL;
  Node* last = NULL;

  void insertAfter(Node* node, Node* newNode) {
    newNode -> prev = node; // 1
    newNode -> next = node -> next; // 2
    if (node -> next == NULL) {
      last = newNode;
    } else {
	    node -> next -> prev = newNode; // 3
    }
    node -> next = newNode; // 4
  }
  
  void insertBefore(Node* node, Node* newNode) {
    newNode -> next = node; // 1
    newNode -> prev = node -> prev; // 2
    if (node -> prev == NULL) {
      first = newNode;
    } else {
	    node -> prev -> next = newNode; // 3
    }
    node -> prev = newNode; // 4    
  }
  
  void insertFirst(Node* node) {
    first = node;
    last = node;
    node -> next = NULL;
    node -> prev = NULL;
  }

  void insert(Node* newNode) {
    if (first == NULL) {
     insertFirst(newNode);
    } else {
     insertBefore(first, newNode);
    }
  }

  void print_list() {
    Node* iter = first;
    while (iter != NULL) {
      gout << "Node " << iter -> id << "\n";
      iter = iter -> next;
    }
  }
 
  void push_back(Node* newNode) {
		if (last == NULL) {
      insertFirst(newNode);
    } else {
      insertAfter(last, newNode);
    }
  }

  void remove(Node* node) {
    if (node -> next == NULL) {
      last = node -> prev;
    } else {
      node -> next -> prev = node -> prev;
    }
    if (node -> prev == NULL) {
      first = node -> next;
    } else {
      node -> prev -> next = node -> next;
    }
  }
};

void read_input(List2* list) {
  int x;
  int y;


  while (!fin.eof()) {
    fin >> x >> y;
    if (fin.eof()) {
      break;
    }
    Node* node = new Node(y);

    switch(x) {
      case 1:
        list -> insert(node);
        break;
      case 2:
        list -> push_back(node);
        break;
      default:
        throw runtime_error("No such op");
    }
  }
}

int main() {
  List2 list;
  
  Node* node = new Node(3);

  read_input(&list);

  // list.insert(node);

  list.print_list();

  auto a = make_shared<Node>(3);
  // list.insert(a);
}