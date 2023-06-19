#pragma once

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// Definition of doubly-linked list class
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
const Node* GetNode (unsigned int index) const;                 // Returns the nth node in the list
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
void InsertAfter(Node* node, const T& data); 
void InsertBefore(Node* node, const T& data);
void InsertAt(const T& data, unsigned int index);

// Removal  
bool RemoveHead();
bool RemoveTail();
unsigned int Remove (const T&data);
bool RemoveAt (unsigned int index);
void Clear();

// Operators
const T& operator[](unsigned int index) const;                  // Subscript operator
T& operator[](unsigned int index);                              // Subscript operator
bool operator==(const LinkedList<T>& rhs) const;
LinkedList<T>& operator=(const LinkedList<T>& rhs);             // Copy assignment operator

private:
// Member variables
Node* _head;                                                    // Pointer to first node in linked list
Node* _tail;                                                    // Pointer to last node in linked list
unsigned int _size;                                             // Number of nodes in linked list

// Private behaviors
void copy_from_object(const LinkedList<T>& object);             // Helper function for copy assignment and copy constructor
};

// Definition of nested Node struct
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
        _head->prev = new_head;    // Inform node currently at front of list that a new node will be inserted in front of it
        new_head->next = _head;        // Set new_head to point to current front of list
        _head = new_head;               // Set list to begin with new_head
        new_head->prev = nullptr;  // Since new_head is now at front of list, nothing comes before it
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
        _tail->next = new_tail;        // Inform node currently at end of list that a new node will be inserted behind it
        new_tail->prev = _tail;    // Set new_tail to point to current end of list
        _tail = new_tail;               // Set list to end with new_tail
        new_tail->next = nullptr;      // Since new_tail is now at end of list, nothing comes before it
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
    Node* node = GetNode(index);
    cout << "data at current node: " << node->data << endl;
    InsertAfter(node, data);
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

