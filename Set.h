//
//  Set.h
//  Project 2
//
//  Created by Li-Wei Tseng on 4/17/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#ifndef __Project_2__Set__
#define __Project_2__Set__

#include <iostream>
#include <string>

typedef std::string ItemType;
//typedef unsigned long ItemType;

class Set
{
public:
    Set(); //constructor
    Set(const Set& src); //copy constructor
    Set& operator=(const Set& rhs); //assignment operator
    ~Set(); //destructor
    
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    
    void dump() const;//debugging function
    
private:
    
    struct Node //circular doubly-linked list with a dummy node
    {
        ItemType m_item;
        Node* m_next;
        Node* m_prev;
    };
    
    Node* head;
    int m_size;
    int find(const ItemType& value) const;
    // Return the position of value in the m_data array, or m_size if
    // it is not in the array.
};

//two non-member functions
void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* defined(__Project_2__Set__) */
