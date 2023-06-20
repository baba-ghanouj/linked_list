#pragma once

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// Doubly-linked list
template <typename T>
class LinkedList
{
public:
    struct Node;                                                // Declaration of nested Node struct

// Construction / destruction
LinkedList();                                                   // Default constructor
LinkedList(const LinkedList<T>& list);                          // Copy constructor
~LinkedList();                                                  // Destructor

// Behaviors
void PrintForward() const;                                      // Print all linked list items in order
void PrintReverse() const;                                      // Print all linked list items in reverse
void PrintForwardRecursive(const Node* node) const; 
void PrintReverseRecursive(const Node* node) const;

// Accessors
unsigned int NodeCount() const;                                 // Returns _size
void FindAll(vector<Node*>& outData, const T& value) const;     // Returns a vector with all nodes containing value
const Node* Find(const T& data) const;                          // Returns pointer to first node with specified data
Node* Find(const T& data);                                      // Returns pointer to first node with specified data
const Node* GetNode(unsigned int index) const;                  // Returns the nth node in the list
Node* GetNode(unsigned int index);                              // Returns the nth node in the list
Node* Head();                                                   // Returns _head
const Node* Head() const;                                       // Returns _head
Node* Tail();                                                   // Returns _tail
const Node* Tail() const;                                       // Returns _tail

// Insertion 
void AddHead(const T& data);                                    // Create new node at front of list
void AddTail(const T& data);                                    // Create new node at end of list
void AddNodesHead(const T* data, unsigned int count);           // Given array, progressively link nodes
void AddNodesTail(const T* data, unsigned int count);           // Given array, regressively link nodes
void InsertAfter(Node* node, const T& data);                    // Insert node after specified node
void InsertBefore(Node* node, const T& data);                   // Insert node before specified node
void InsertAt(const T& data, unsigned int index);               // Insert node at given index

// Removal  
bool RemoveHead();                                              // Delete current head from list
bool RemoveTail();                                              // Delete current list from list
unsigned int Remove(const T&data);                              // Delete all nodes containing data
bool RemoveAt(unsigned int index);                              // Delete node at index
void Clear();                                                   // Delete all nodes in list

// Operators
const T& operator[](unsigned int index) const;                  // Subscript operator
T& operator[](unsigned int index);                              // Subscript operator
bool operator==(const LinkedList<T>& rhs) const;                // Equality operator
LinkedList<T>& operator=(const LinkedList<T>& rhs);             // Copy assignment operator

private:
// Member variables
Node* _head;                                                    // Pointer to first node in linked list
Node* _tail;                                                    // Pointer to last node in linked list
unsigned int _size;                                             // Number of nodes in linked list

// Private behaviors
void copy_from_object(const LinkedList<T>& object);             // Helper function for copy assignment and copy constructor
void remove_node(Node* node);                                   // Helper function for Remove and RemoveAAt
};

// Nested Node struct for LinkedList class
template <typename T>
struct LinkedList<T>::Node
{
    T data;                                                     // Data stored in the node
    Node* next;                                                 // Pointer to next node in linked list
    Node* prev;                                                 // Pointer to previous node in linked list

    // Constructors
    Node();                                                     // Default constructor
    Node(const T& data);                                        // Constructor with data assignment
};

template <typename T>
LinkedList<T>::LinkedList()
    {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
    copy_from_object(list);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node* current_node = _head;
    while (current_node != nullptr)         // next member variable of last pointer in a linked list should always be null
    {
        Node* next = current_node->next;    // Summon the next node before deallocating the current node
        delete current_node;
        current_node = next;
    }
}

template <typename T>
void LinkedList<T>::PrintForward() const
{
    Node* current_node = _head;                             // Use pointer to quickly iterate through list items
    for (unsigned int item = 0; item < _size; item++)
    {
        cout << current_node->data << endl;
        current_node = current_node->next;                 // Set the current node to the previous node for next loop
    }
}

template <typename T>
void LinkedList<T>::PrintReverse() const
{
    Node* current_node = _tail;                             // Use pointer to quickly iterate through list items
    for (unsigned int item = 0; item < _size; item++)
    {
        cout << current_node->data << endl;
        current_node = current_node->prev;             // Set the current node to the previous node for next loop
    }
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
    if(node != nullptr)
    {
        cout << node->data << endl;
        node = node->next;
        PrintForwardRecursive(node);
    }
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
    if(node != nullptr)
    {
        cout << node->data << endl;
        node = node->prev;
        PrintReverseRecursive(node);
    }
}

template <typename T>
void LinkedList<T>::AddHead(const T& data)
{
    Node* new_head = new Node(data);    // New node to be added to front of list
    if (_head == nullptr)               // Check to see if list is empty
    {
        // If list was previously empty, list now has a size of 1 and thus _head and _tail are the same node
        _head = new_head;
        _tail = new_head;
        _size = 1;
    }
    else 
    {
        _head->prev = new_head;         // Inform node currently at front of list that a new node will be inserted in front of it
        new_head->next = _head;         // Set new_head to point to current front of list
        _head = new_head;               // Set list to begin with new_head
        new_head->prev = nullptr;       // Since new_head is now at front of list, nothing comes before it
        _size++;                        // Increment size of linked list
    }
}

template <typename T>
void LinkedList<T>::AddTail(const T& data)
{
    Node* new_tail = new Node(data);    // New node to be added at end of list
    if (_head == nullptr)               // Check to see if list is empty
    {
        // If list was previously empty, list now has a size of 1 and thus _tail and _head are the same node
        _tail = new_tail;
        _head = new_tail;
        _size = 1;
    }
    else 
    {
        _tail->next = new_tail;         // Inform node currently at end of list that a new node will be inserted behind it
        new_tail->prev = _tail;         // Set new_tail to point to current end of list
        _tail = new_tail;               // Set list to end with new_tail
        new_tail->next = nullptr;       // Since new_tail is now at end of list, nothing comes before it
        _size++;                        // Increment size of linked list
    }
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
    {
        AddHead(data[count - i - 1]);   // To preserve the order of the array, start by adding the nth element and counting down
    }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
    {
        AddTail(data[i]);
    }
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data)
{  
    Node* new_node = new Node(data);
    new_node->prev = node;
    new_node->next = node->next;
    node->next->prev = new_node;
    node->next = new_node;
    
    _size++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
    Node* new_node = new Node(data);
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;

    _size++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
    if (index > _size or index < 0)
    {
        throw std::out_of_range("Error: Index out of range.");
    }
    else if (index == 0)
    {
        AddHead(data);
    }
    else if (index == _size)
    {
        AddTail(data);
    }
    else
    {
        Node* node = GetNode(index);
        InsertBefore(node, data);
    }
}

template <typename T>
bool LinkedList<T>::RemoveHead()
{
    if (_head == nullptr)
    {
        // cout << "Could not remove size: " << _size << endl;
        return false;
    }
    else if (_head->next == nullptr)
    {
        delete _head;
        _head = nullptr;
    }
    else
    {    
    Node* new_head = _head->next;
    new_head->prev = nullptr;
    delete _head;
    _head = new_head;
    }
    _size--;
    // cout << "Head removed!" << endl;
    // cout << "New size:" << _size << endl;
    return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail()
{
    // cout << "Starting tail location in memory: " << _tail << endl;
    if (_tail == nullptr)
    {
        // cout << "Could not remove size: " << _size << endl;
        return false;
    }
    else if (_tail->prev == nullptr)
    {
        // cout << "_tail: " << _tail << " ->prev " << _tail->prev << " ->prev->prev " << _tail->prev->prev << endl;
        // cout << "Deleted tail at: " << _tail << endl;
        _tail = nullptr;
    }
    else
    {
    Node* new_tail = _tail->prev;
    new_tail->next = nullptr;
    // cout << "new_tail: " << new_tail << " ->prev: " << new_tail->prev << " ->next: " << new_tail->next << endl;
    // cout << "_tail: " << _tail << " ->prev " << _tail->prev << " ->prev->prev " << _tail->prev->prev << endl;
    delete _tail;
    _tail = new_tail;
    }
    _size--;
    // cout << "Tail removed!" << endl;
    // cout << "New size:" << _size << endl;
    return true;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T&data)
{
    vector<LinkedList<T>::Node*> nodes;
    FindAll(nodes, data);

    for (unsigned int node = 0; node < nodes.size(); node++)
    {
        Node* current_node = nodes[node];
        if (current_node->prev == nullptr)
        {
            RemoveHead();
        }
        else if (current_node->next == nullptr)
        {
            RemoveTail();
        }
        else
        {
            remove_node(current_node);
        }
    }
    return nodes.size();
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
    try
    {
        Node* node = GetNode(index);
        remove_node(node);
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

template <typename T> void 
LinkedList<T>::Clear()
{
    _size = 0;
    this->~LinkedList();
    _head = nullptr;
    _tail = nullptr;
}


template <typename T>
unsigned int LinkedList<T>::NodeCount() const
{
    return _size;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
    Node* current_node = _head;
    for (unsigned int node_num = 0; node_num < _size; node_num++)
        {
            T node_data = current_node->data;
            if (node_data == value)
            {
                outData.push_back(current_node);
            }
            current_node = current_node->next;
        }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
    Node* current_node = _head;
    while (current_node != nullptr)
    {
        if (current_node->data == data)
        {
            return current_node;
        }
        current_node = current_node->next;
    }
    return current_node;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
    Node* current_node = _head;
    while (current_node != nullptr)
    {
        if (current_node->data == data)
        {
            return current_node;
        }
        current_node = current_node->next;
    }
    return current_node;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
    if (index == 0)
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _head;
    }
    Node* current_node = _head;
    for (unsigned int node = 0; node < index; node++)
    {
        current_node = current_node->next;
        if (current_node == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
    }

    return current_node;    
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
    if (index == 0)
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _head;
    }
    Node* current_node = _head;
    for (unsigned int node = 0; node < index; node++)
    {
        current_node = current_node->next;
        if (current_node == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
    }

    return current_node;    
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
    return _head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
    return _head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
    return _tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
    return _tail;
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
    if (index == 0)
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _head->data;
    }
    Node* current_node = _head;
    for (unsigned int node = 0; node < index; node++)
    {
        current_node = current_node->next;
        if (current_node == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
    }

    return current_node->data;    
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
    if (index == 0)
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _head->data;
    }
    Node* current_node = _head;
    for (unsigned int node = 0; node < index; node++)
    {
        current_node = current_node->next;
        if (current_node == nullptr)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
    }

    return current_node->data;    
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
    if (_size != rhs._size)
    {
        return false;
    }

    Node* lhs_node = _head;
    Node* rhs_node = rhs._head;
    for (unsigned int node = 0; node < _size; node++)
    {
        if (lhs_node->data != rhs_node->data)
        {
            return false;
        }
        lhs_node = lhs_node->next;
        rhs_node = rhs_node->next;

    }
    return true;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    this->~LinkedList();
    copy_from_object(rhs);

    return *this;
}

template <typename T>
LinkedList<T>::Node::Node()
{
    next = nullptr;
    prev = nullptr;
    data = T();
}

template <typename T>
LinkedList<T>::Node::Node(const T& data)
{
    next = nullptr;
    prev = nullptr;
    this->data = data;
}

template <typename T>
void LinkedList<T>::copy_from_object(const LinkedList<T>& object)
{    
    Node* current_node = object._head;
    T new_data = current_node->data;
    _head = nullptr;
    _tail = nullptr;
    while (current_node != nullptr)
    {
        new_data = current_node->data;
        AddTail(new_data);
        current_node = current_node->next;
    }
}

template <typename T>
void LinkedList<T>::remove_node(Node* node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    _size--;
}