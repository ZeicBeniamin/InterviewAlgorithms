#include <iostream>
#include <fstream>
#include <memory> //shared_ptr

using namespace std;

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

    void push_front(int node_id)
    {
        shared_ptr<Node> node = Node::makeNode(node_id);
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


    void push_back(int node_id)
    {
        shared_ptr<Node> node = Node::makeNode(node_id);
        if (last == NULL)
        {
            insertFirst(node);
        }
        else
        {
            insertAfter(last, node);
        }
    }

    // Assumes node is in list
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

    shared_ptr<Node> search_and_remove(int id) {
        shared_ptr<Node> iterator = first;
        while (iterator != NULL)
        {
            if (iterator -> id == id) {
                remove(iterator);
            }
            iterator = iterator -> next;
        }
        return nullptr;
    }

    void print(ostream out)
    {
        shared_ptr<Node> iterator = first;
        while (iterator != NULL)
        {
            out << "Node " << iterator->id << "\n";
            iterator = iterator->next;
        }
    }
};