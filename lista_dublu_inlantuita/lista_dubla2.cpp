#include <iostream>
#include <fstream>
#include <memory> //shared_ptr

using namespace std;

ifstream fin("lista_dubla.in");
ofstream gout("lista_dubla.out");

// Node
class Node
{
private:
    int glob_id = 0;

public:
    int id;
    shared_ptr<Node> next;
    shared_ptr<Node> prev;

    Node() : id(++Node::glob_id) {}
    Node(int id) : id(id) {}

    static shared_ptr<Node> makeNode()
    {
        return make_shared<Node>();
    }

    static shared_ptr<Node> makeNode(int id)
    {
        return make_shared<Node>(id);
    }
};

// List (shared_ptr<Node>)
class List
{
public:
    shared_ptr<Node> last;
    shared_ptr<Node> first;

private:
    void insertAfter(shared_ptr<Node> ref_node, shared_ptr<Node> newNode)
    {
        newNode->prev = ref_node;
        newNode->next = ref_node->next;

        if (ref_node->next == NULL)
        {
            last = newNode;
        }
        else
        {
            ref_node->next->prev = newNode;
        }
        ref_node->next = newNode;
    }

    void insertBefore(shared_ptr<Node> ref_node, shared_ptr<Node> newNode)
    {
        newNode->next = ref_node;
        newNode->prev = ref_node->prev;

        if (ref_node->prev == NULL)
        {
            first = newNode;
        }
        else
        {
            ref_node->prev->next = newNode;
        }
        ref_node->prev = newNode;
    }

    inline void insertFirst(shared_ptr<Node> node)
    {
        first = node;
        last = node;
        node->next = NULL;
        node->prev = NULL;
    }

public:
    void push_front(shared_ptr<Node> node)
    {
        if (first == NULL)
        {
            insertFirst(node);
        }
        else
        {
            insertBefore(first, node);
        }
    }

    void push_back(shared_ptr<Node> node)
    {
        if (last == NULL)
        {
            insertFirst(node);
        }
        else
        {
            insertAfter(last, node);
        }
    }

    void remove(shared_ptr<Node> node)
    {
        if (node == first)
        {
            first = node->next;
        }
        else
        {
            node->prev->next = node->next;
        }
        if (node == last)
        {
            last = node->prev;
        }
        else
        {
            node->next->prev = node->prev;
        }
    }

    shared_ptr<Node> search(int id) {
        shared_ptr<Node> iterator = first;
        while (iterator != NULL)
        {
            if (iterator -> id == id) {
                return iterator;
            }
            iterator = iterator -> next;
        }
        return nullptr;
    }

    void print()
    {
        shared_ptr<Node> iterator = first;
        while (iterator != NULL)
        {
            gout << "Node " << iterator->id << "\n";
            iterator = iterator->next;
        }
    }
};

// Main func

int main()
{
    int op;
    int y;
    List list;

    while (!fin.eof())
    {
        fin >> op >> y;
        if (fin.eof()) {
            break;
        }
        gout << "Inserting node " << op << " " << y << "\n";
        auto node = Node::makeNode(y);
        switch (op)
        {
        case 1:
            list.push_front(node);
            break;
        case 2:
            list.push_back(node);
            break;
        default:
            cout << "Operation with code " << op << "does not exist.";
            throw runtime_error("No such operation");
            break;
        }
    }

    list.print();

    shared_ptr<Node> found = list.search(6);
    if (found != nullptr) {
        cout << "Found node with id " << found -> id << "at memory address " << found.get();
    }
}