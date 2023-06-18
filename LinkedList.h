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
void FindAll(vector<Node*>& outData, const T& value) const;
const Node* Find(const T& data) const;
Node* Find(const T& data);
const Node* GetNode (unsigned int index) const;
Node* GetNode(unsigned int index);
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
};

// Definition of nested Node struct
template <typename T>
struct LinkedList<T>::Node
{
    T _data;                                                    // Data stored in the node
    Node* _next;                                                // Pointer to next node in linked list
    Node* _previous;                                            // Pointer to previous node in linked list

    // Constructors
    Node();                                                     // Default constructor
    Node(const T& data);                                        // Constructor with _data assignment
};

template <typename T>
LinkedList<T>::LinkedList()
    {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node* current_node = _head;
    while (current_node != nullptr)         // _next member variable of last pointer in a linked list should always be null
    {
        Node* next = current_node->_next;   // Summon the next node before deallocating the current node
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
        cout << current_node->_data << endl;
        current_node = current_node->_next;                 // Set the current node to the previous node for next loop
    }
}

template <typename T>
void LinkedList<T>::PrintReverse() const
{
    Node* current_node = _tail;                             // Use pointer to quickly iterate through list items
    for (unsigned int item = 0; item < _size; item++)
    {
        cout << current_node->_data << endl;
        current_node = current_node->_previous;             // Set the current node to the previous node for next loop
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
        _head->_previous = new_head;    // Inform node currently at front of list that a new node will be inserted in front of it
        new_head->_next = _head;        // Set new_head to point to current front of list
        _head = new_head;               // Set list to begin with new_head
        new_head->_previous = nullptr;  // Since new_head is now at front of list, nothing comes before it
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
        _tail->_next = new_tail;        // Inform node currently at end of list that a new node will be inserted behind it
        new_tail->_previous = _tail;    // Set new_tail to point to current end of list
        _tail = new_tail;               // Set list to end with new_tail
        new_tail->_next = nullptr;      // Since new_tail is now at end of list, nothing comes before it
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
unsigned int LinkedList<T>::NodeCount() const
{
    return _size;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
    for (unsigned int node_num = 0; node_num < _size; node_num++)
        {
            Node* current_node = GetNode(node_num);
            T node_data = current_node->_data;
            if (node_data == data)
            {
                return current_node;
            }
        }
    return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
    for (unsigned int node_num = 0; node_num < _size; node_num++)
        {
            Node* current_node = GetNode(node_num);
            T node_data = current_node->_data;
            if (node_data == data)
            {
                return current_node;
            }
        }
    return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode (unsigned int index) const
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
        current_node = current_node->_next;
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
        current_node = current_node->_next;
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
    return GetNode(index);
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
    return GetNode(index);
}



template <typename T>
LinkedList<T>::Node::Node()
{
    _next = nullptr;
    _previous = nullptr;
    _data = T();
}

template <typename T>
LinkedList<T>::Node::Node(const T& data)
{
    _next = nullptr;
    _previous = nullptr;
    _data = data;
}




