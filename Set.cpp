//
//  Set.cpp
//  Project 2
//
//  Created by Li-Wei Tseng on 4/17/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#include "Set.h"
#include <iostream>

using namespace std;

Set::Set()
{
    head = new Node; //head points to a dummy node

    //let next and prev pointers point to the dummy node
    head->m_next = head;
    head->m_prev = head;
    
    m_size = 0;
}//end constructor

Set::Set(const Set& src)
{
    //assign src's size to this
    m_size = src.m_size;
    
    //allocate new space for this's linked list
    head = new Node;
    head->m_next = head; //let next and prev pointers point to themselves
    head->m_prev = head;
    
    //create a temp ptr pointing to the newly added list
    Node* cur = head->m_next;
    //create a temp ptr pointing the src's lists
    Node* curSrc = src.head->m_next;
    for(; curSrc != src.head; curSrc = curSrc->m_next)
    {
        Node* newPtr = new Node;
        newPtr->m_item = curSrc->m_item; //assign src's item to the new one
        
        newPtr->m_next = cur->m_next; //points to the dummy node
        newPtr->m_prev = cur; //points to the previous node
        cur->m_next = newPtr; //connect prev node to the new node
        head->m_prev = newPtr; //complete the circle
        
        cur = newPtr;
    }//end for
}//end copy constructor

Set& Set::operator=(const Set& rhs)
{
    if(this != &rhs)
    {
        //create a temp Set to store the values of rhs
        //swap lhs and rhs
        Set temp(rhs);
        swap(temp);
    }//end if
    
    return *this;
}//end assignment operator

Set::~Set()
{
    //delete the linked list
    while(!empty())
    {
        Node* cur = head->m_next;//create a temp ptr points to a the position to be deleted(the first item)
        head->m_next = cur->m_next; //adjust the ptr so the head points to the later one. If there's only one item, then points to the head itself
        cur->m_next->m_prev = head; //complete the circle. If there's only one item, then points to the head itself
        
        //protection: make the deleted node's pointers NULL
        cur->m_next = nullptr;
        cur->m_prev = nullptr;

        delete cur; //delete the current item
        m_size--;//decrement the size
    }
    //delete the dummy node
    delete head;
}//end destructor

bool Set::empty() const
{
    return size() == 0;
}//end empty

int Set::size() const
{
    return m_size;
}//end size

bool Set::insert(const ItemType& value)
{
    if(contains(value))
    {
        //return false if the value is already in the list
        return false;
    }//end if
    
    //traverse to the last node
    Node *cur = head->m_next;
    while(cur->m_next != head)
    {
        cur = cur->m_next;
    }//end while
    
    //add the new value to the end
    Node *newPtr = new Node;//allocate a new space for a node
    newPtr->m_item = value; //assign a value to the node
    
    newPtr->m_next = head;//points to the dummy node
    newPtr->m_prev = cur; //make newPtr points to cur
    cur->m_next = newPtr;//make cur points to newPtr
    head->m_prev = newPtr;//complete the circle
    
    m_size++; //after the insertion is proceeded correctly, increment the size
    return true;
}//end insert

bool Set::erase(const ItemType& value)
{
    if(!contains(value))
    {
        //return false if the list doesn't have the value
        return false;
    }//end if
    
    //traverse to the position where the value is located
    Node* cur =head->m_next;
    while(cur != head && cur->m_item != value)
    {
        cur = cur->m_next;
    }//end while
    
    //delete the value
    (cur->m_prev)->m_next = cur->m_next;
    (cur->m_next)->m_prev = cur->m_prev;
    
    //protection: make the deleted node's pointers NULL
    cur->m_next = nullptr;
    cur->m_prev = nullptr;
    delete cur;
    cur = nullptr;
    
    m_size--;//after the insertion is proceeded correctly, decrement the size
    return true;
}//end erase

bool Set::contains(const ItemType& value) const
{
     return find(value) != m_size;
}//end contains

bool Set::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= m_size)
    {
        return false;
    }//end if
    
    //create a temp node ptr to find the position
    Node* cur = head->m_next;
    int curIndex = 0;
    for(; cur != head && curIndex < pos; cur = cur->m_next, curIndex++)
        ;//end for

    value = cur->m_item;
    return true;
}//end get

void Set::swap(Set& other)
{
    // Swap sizes
    int tempSize;
    tempSize = other.m_size;
    other.m_size = m_size;
    m_size = tempSize;
    
    // Swap pointers to the linked list
    Node* swapHead = head;
    head = other.head;
    other.head = swapHead;
}//end swap

int Set::find(const ItemType& value) const
{
    int index = 0;
    Node* cur = head->m_next;
    for(; cur != head && cur->m_item != value; cur = cur->m_next)
    {
        index++;
    }//end for
    return index;
}//end find

void Set::dump() const
{
    cerr << "The size of the Set is: " << m_size << endl;
    cerr << "The items in the Set are: " << endl;
    Node* cur = head->m_next;
    for(; cur != head; cur = cur->m_next)
    {
        cerr << cur->m_item << " ";
    }//end for
    
    cerr << endl;
}//end debugging function

void unite(const Set& s1, const Set& s2, Set& result)//using only public interface of Set;
{
    //create a "clean" temp set
    Set tempSet;
    
    //insert s1's list into tempSet
    for(int i = 0; i < s1.size(); i++)
    {
        ItemType item;
        s1.get(i, item);
        tempSet.insert(item);
    }//end for
    
    //insert s2's list into tempSet
    for(int i = 0; i < s2.size(); i++)
    {
        ItemType item;
        s2.get(i, item);
        tempSet.insert(item);
    }//end for

    // assign the temp set to the result
    result = tempSet;

}//end unite

void subtract(const Set& s1, const Set& s2, Set& result)//using only public interface of Set;
{
    //create a "clean" temp set
    Set tempSet;
    
    //unite s1 and s2 into tempSet
    unite(s1, s2, tempSet);
    
    //erase items of s2 in tempSet
    for(int i = 0; i < s2.size(); i++)
    {
        ItemType item;
        s2.get(i, item);
        tempSet.erase(item);
    }//end for
    
    //assign the temp set to the result
    result = tempSet;
}//end subtract