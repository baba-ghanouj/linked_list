#pragma once

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

template <typename T>
class LinkedList
{
private:

    struct Node
    {
        T* _data;                                               // Data stored in the node
        Node* _next;                                            // Pointer to next node in linked list
        Node* _previous;                                        // Pointer to previous node in linked list
    };

Node* _head;                                                    // Pointer to first node in list
Node* _tail;                                                    // Pointer to last node in list

public:


/*==== Construction / Destruction ====*/ 
LinkedList();                                                   // Default constructor
LinkedList(const LinkedList<T>& list);                          // Copy constructor
~LinkedList();                                                  // Destructor

/*==== Behaviors ====*/ 
void PrintForward() const;
void PrintReverse() const;
void PrintForwardRecursive(const Node* node) const; 
void PrintReverseRecursive(const Node* node) const;

/*==== Accessors ====*/
unsigned int NodeCount () const;
void FindAll (vector<Node*>& outData, const T& value) const;
const Node* Find(const T& data) const;
Node* Find(const T& data);
const Node* GetNode (unsigned int index) const;
Node* GetNode (unsigned int index);
Node* Head();
const Node* Head() const;
Node* Tail();
const Node* Tail() const;

/*==== Insertion ====*/ 
void AddHead (const T& data); void AddTail(const T& data);
void AddNodesHead (const T* data, unsigned int count); 
void AddNodesTail(const T* data, unsigned int count);
void InsertAfter (Node* node, const T& data); 
void InsertBefore (Node* node, const T& data);
void InsertAt (const T& data, unsigned int index);

/*==== Removal ====*/ 
bool RemoveHead();
bool RemoveTail();
unsigned int Remove (const T&data);
bool RemoveAt (unsigned int index);
void Clear();

/*==== Operators ====*/
const T& operator[](unsigned int index) const;
T& operator[](unsigned int index);
bool operator==(const LinkedList<T>& rhs) const;
LinkedList<T>& operator=(const LinkedList<T>& rhs);             // Copy assignment operator
};
