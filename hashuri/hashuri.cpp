#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
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

#define M 217
#define A 0.618

using namespace std;

ifstream fin("hashuri.in");
ofstream gout("hashuri.out");

List list[M + 2];

// [{A * x} * M], where
// {} - fractional part of number
// [] - integer part of number
// A belongs to (0,1)
// M randomly chosen
inline int h(int x)
{
    return (int)(((A * x) - (int)(A * x)) * M);
}

inline void check_hash(int hash)
{
    if (hash > M)
    {
        cout << "List index " << hash << "out of bounds";
        throw runtime_error("List index out of bounds");
    }
}

void add(int elem)
{
    int hash = h(elem);
    check_hash(hash);

    list[hash].push_back(elem);
}

void del(int elem)
{
    int hash = h(elem);
    check_hash(hash);

    list[hash].search_and_remove(elem);
}

bool search(int elem)
{
    int hash = h(elem);
    check_hash(hash);

    auto node = list[hash].search(elem);

    if (node == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    int ops_nr;
    int op;
    int elem;

    fin >> ops_nr;
    cout << ops_nr << "\n";

    for (int i = 0; i < ops_nr; ++i)
    {
        fin >> op >> elem;
        switch (op)
        {
        case 1:
            add(elem);
            break;
        case 2:
            del(elem);
            break;
        case 3:
            {
                bool found = search(elem);
                if (found)
                {
                    gout << 1 << "\n";
                }
                else
                {
                    gout << 0 << "\n";
                }
                break;
            }
        default:
            throw runtime_error("Wrong op");
        }
    }

    fin.close();
    gout.close();
    return 0;
}