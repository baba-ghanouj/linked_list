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
private:
    struct Node;                                                // Declaration of nested Node struct

// Member variables
Node* _head;                                                    // Pointer to first node in linked list
Node* _tail;                                                    // Pointer to last node in linked list
unsigned int _size;                                             // Number of nodes in linked list

public:
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
unsigned int NodeCount() const;
void FindAll(vector<Node*>& outData, const T& value) const;
const Node* Find(const T& data) const;
Node* Find(const T& data);
const Node* GetNode (unsigned int index) const;
Node* GetNode(unsigned int index);
Node* Head();
const Node* Head() const;
Node* Tail();
const Node* Tail() const;

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
const T& operator[](unsigned int index) const;
T& operator[](unsigned int index);
bool operator==(const LinkedList<T>& rhs) const;
LinkedList<T>& operator=(const LinkedList<T>& rhs);             // Copy assignment operator
};

// Definition of nested Node struct
template <typename T>
struct LinkedList<T>::Node
{
    T _data;                                                   // Data stored in the node
    Node* _next;                                                // Pointer to next node in linked list
    Node* _previous;                                            // Pointer to previous node in linked list
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

    while (current_node != nullptr)
    {
        Node* next = current_node->_next;
        delete current_node;
        current_node = next;
    }
}

template <typename T>
void LinkedList<T>::PrintForward() const
{
    Node* current_item = _head;
    for (unsigned int item = 0; item < _size; item++)
    {
        cout << current_item->_data << endl;
        current_item = current_item->_next;
    }
}

template <typename T>
void LinkedList<T>::PrintReverse() const
{
    Node* current_item = _tail;
    for (unsigned int item = 0; item < _size; item++)
    {
        cout << current_item->_data << endl;
        current_item = current_item->_previous;
    }
}

template <typename T>
void LinkedList<T>::AddHead(const T& data)
{
    Node* new_head = new Node();          // New node to be added to front of list
    new_head->_data = data;

    // Check to see if list is empty
    if (_head == nullptr)
    {
        // If list was previously empty, list now has a size of 1 and thus _head and _tail are the same
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
    Node* new_tail = new Node();          // New node to be added to end of list
    new_tail->_data = data;

    // Check to see if list is empty
    if (_head == nullptr)
    {
        // If list was previously empty, list now has a size of 1 and thus _tail and _head are the same
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
        AddHead(data[count - i - 1]);
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




