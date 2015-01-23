//
//  main.cpp
//  Project 2
//
//  Created by Li-Wei Tseng on 4/17/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;


//#define TEST1
#ifdef TEST1
void test1(){
	Set s;
	Set a;
    
	assert(s.empty()); // check to see if s set is empty
	assert(a.empty()); // check to see if a set is empty
	
	unsigned long x = 9876543;
	assert(!s.get(42, x) && x == 9876543); // x unchanged by get failure
	s.insert(123456789);
	assert(s.size() == 1);
	assert(s.get(0, x));
	assert(x == 123456789);
	s.erase(123456789); // erase 123456789
	assert(!s.contains(123456789)); // check if it doesn't contain 123456789
	assert(s.empty()); // check to see if the set is empty
	s.insert(123);
	assert(s.size() == 1); // check size = 1
	s.insert(321);
	assert(s.size() == 2); // check size = 2
	s.insert(222);
	assert(s.size() == 3); // check size = 3
	assert(s.contains(123) && s.contains(222) && s.contains(321));
	// check to see if all numbers are in the set
	
	a.insert(987); // add 987
	a.insert(789); // add 789
    
	//check swap function
	s.swap(a);
    
	unsigned long temp = 0;
	a.get(0, temp);
	assert(temp == 123); //check to see if temp was correctly changed
    
	assert(!a.get(50, temp)); // get failure
    
	assert(a.contains(123) && a.contains(222) && a.contains(321));
	//check for correct swap
    
	assert(s.contains(789) && s.contains(987));//check for correct swap
	
	a.erase(321);
	assert(a.contains(123)); // check to see if the set still contains 123
	assert(!a.contains(321)); // check to see if the set doesn't contain 321
	assert(a.contains(222)); // check to see if the set still contains 222
	assert(a.size() == 2); // check the size = 2
	
	//copy constructor
	Set b(a);
	assert(a.contains(123)); // check to see if the set contains 123
	assert(!a.contains(321)); // check to see if the set doesn't contain 321
	assert(a.contains(222)); // check to see if the set contains 222
	assert(a.size() == 2); // check the size = 2
	
	//test equal operator
	b = s;
	assert(s.contains(789) && s.contains(987));//check for correct operator
    
	//test out unite function
	unite(s, a, b);
	assert(s.contains(789) && s.contains(987));//check for correct unite
	assert(a.contains(123)); // check to see if the set contains 123
	assert(!a.contains(321)); // check to see if the set doesn't contain 321
	assert(a.contains(222)); // check to see if the set contains 222
    
	Set c, d, e;
	//add 1,2,3,4
	c.insert(1);
	c.insert(2);
	c.insert(3);
	c.insert(4);
    
	//add 3,4,5,6
	d.insert(3);
	d.insert(4);
	d.insert(5);
	d.insert(6);
    
	//subtract the two and make sure 3,4 are gone
	subtract(c, d, e);
	assert(e.contains(1) && e.contains(2));
    
	//unite c and d and make sure it's only 1,2,5,6
	unite(c, d, e);
	assert(e.contains(1) && e.contains(2) && e.contains(5) && e.contains(6));
    
	//test out aliasing and make sure it's the same
	unite(e, d, e);
	assert(e.contains(1) && e.contains(2) && e.contains(5) && e.contains(6));
	subtract(e, e, e);
	assert(e.empty());
}
#endif
/*
void test()
{
    Set ss, ss2;
    ss.dump();
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss2.insert("david"));
    assert(ss2.insert("pita"));
    
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "focaccia";
    assert(ss.get(0, x)  &&  (x == "roti"  ||  x == "pita"));
    Set result = ss;
    ss.dump();
    subtract(ss, ss2, result);
    result.dump();
}*/


#define TESTCASE
#ifdef TESTCASE

void testEmpty()
{
    Set ss;
    assert(ss.empty());
    assert(ss.insert("abc"));
    assert(!ss.empty());
    assert(ss.erase("abc"));
    assert(ss.empty());
}

void testSize()
{
    Set ss;
    assert(ss.size()==0);
    assert(ss.insert("abc"));
    assert(ss.size()!=0);
    assert(ss.size()==1);
    assert(ss.insert("bsd"));
    assert(ss.size()!=0);
    assert(ss.size()!=1);
    assert(ss.size()==2);
    assert(ss.insert("qwe"));
    assert(ss.size()==3);
    assert(!ss.insert("bsd"));//insert twice
    assert(ss.size()!=0);
    assert(ss.size()!=1);
    assert(ss.size()!=2);
    assert(ss.size()==3);
    assert(ss.erase("abc"));
    assert(ss.size()!=0);
    assert(ss.size()!=1);
    assert(ss.size()==2);
    assert(ss.size()!=3);
    assert(!ss.erase("abc"));//erase twice
    assert(ss.size()!=0);
    assert(ss.size()!=1);
    assert(ss.size()==2);
    assert(ss.size()!=3);
    assert(ss.erase("bsd"));
    assert(ss.size()!=0);
    assert(ss.size()==1);
    assert(ss.size()!=2);
    assert(ss.size()!=3);
    assert(ss.erase("qwe"));
    assert(ss.size()==0);
}

void testInsertErase()
{
    Set ss;
    assert(ss.size()==0);
    
    assert(!ss.erase(""));
    assert(ss.insert(""));//ss{""}
    assert(!ss.insert(""));//insert twice
    assert(ss.contains(""));
    
    assert(ss.insert("liweitseng"));//ss{"",liweitseng}
    assert(!ss.insert("liweitseng"));//ss{"",liweitseng}
    assert(ss.contains("liweitseng"));
    assert(ss.size()==2);
    
    assert(ss.insert("hellow"));//ss{"", liweisteng, hellow}
    assert(!ss.insert("hellow"));//ss{"", liweisteng, hellow}
    assert(ss.contains("hellow"));
    assert(ss.size()==3);
    
    assert(ss.insert("yea"));//ss{"", liweisteng, hellow, yea}
    assert(ss.contains("yea"));
    assert(!ss.insert("yea"));//ss{"", liweisteng, hellow, yea}
    
    assert(ss.insert("HELLOW"));//ss{"", liweisteng, hellow, yea, HELLOW}
    assert(!ss.insert("HELLOW"));//ss{"", liweisteng, hellow, yea, HELLOW}
    assert(ss.contains("HELLOW"));
    assert(ss.size() == 5);
    
    /////////////////////////erase/////////////////////////////
    
    assert(ss.erase(""));//ss{liweisteng, hellow, yea, HELLOW} erase first item
    assert(!ss.erase(""));//erase twice
    assert(!ss.contains(""));
    
    
    assert(ss.erase("hellow"));//ss{liweisteng, yea, HELLOW} erase middle item
    assert(!ss.erase("hellow"));//ss{liweisteng, yea, HELLOW} erase twice
    assert(!ss.contains("hellow"));
    assert(ss.size()==3);
    

    assert(ss.erase("HELLOW"));//ss{liweisteng, yea} erase last item
    assert(!ss.erase("HELLOW"));//ss{liweisteng, yea} erase twice
    assert(!ss.contains("HELLOW"));
    assert(ss.size() == 2);
    
    assert(ss.erase("yea"));//ss{liweisteng} erase last item
    assert(!ss.erase("yea"));//ss{liweisteng} erase twice
    assert(!ss.contains("yea"));
    assert(ss.size() == 1);
    
    
    assert(ss.erase("liweitseng"));//ss{} erase only one item
    assert(!ss.erase("liweitseng"));//ss{} erase twice
    assert(!ss.contains("liweitseng"));
    assert(ss.size() == 0);
}

void testContains()
{
    Set ss;
    assert(ss.size()==0);
    assert(ss.insert("abc"));
    assert(ss.size()!=0);
    assert(ss.size()==1);
    assert(ss.insert("bsd"));
    assert(ss.size()!=0);
    assert(ss.size()!=1);
    assert(ss.size()==2);
    assert(ss.insert("qwe"));
    assert(ss.contains("abc"));
    assert(ss.contains("bsd"));
    assert(ss.contains("qwe"));
    assert(!ss.contains("asdf"));
    assert(ss.erase("qwe"));
    assert(ss.erase("abc"));
    assert(ss.erase("bsd"));
    assert(!ss.contains("qwe"));
    assert(!ss.contains("abc"));
    assert(!ss.contains("bsd"));
    assert(!ss.contains("qwe"));
    assert(!ss.contains("qweradsf"));
}

void testGet()
{
    Set ss;
    assert(ss.insert("abc"));
    assert(!ss.insert("abc"));//insert twice
    assert(ss.insert("hello"));
    assert(ss.insert("qqq"));
    ItemType x = "focaccia";
    assert(ss.get(0, x)  &&  (x == "abc"));
    assert(ss.get(1, x)  &&  (x == "hello"));
    assert(ss.get(2, x)  &&  (x == "qqq"));
    assert(ss.erase("abc"));
    assert(ss.get(0, x)  &&  (x == "hello"));
    assert(ss.get(1, x)  &&  (x == "qqq"));
    assert(ss.erase("hello"));
    assert(ss.get(0, x)  &&  (x == "qqq"));
    assert(!ss.get(-1, x));//extreme values
    assert(!ss.get(4, x));
    assert(!ss.get(100, x));
}

void testSwap()
{
    Set ss;
    assert(ss.insert("abc"));
    assert(ss.insert("bsd"));
    assert(ss.insert("qwe"));
    assert(ss.size() == 3);
    
    Set ss2;
    ss2.swap(ss);//now ss2 has ss1's value, while ss becomes empty
    assert(ss2.contains("abc"));
    assert(ss2.contains("bsd"));
    assert(ss2.contains("qwe"));
    assert(!ss2.contains("asdf"));
    assert(ss2.size() == 3);

    assert(!ss.contains("qwe"));
    assert(!ss.contains("abc"));
    assert(!ss.contains("bsd"));
    assert(ss.size() == 0);
    
    assert(ss.insert("lll"));//insert value to ss won't affect ss2
    assert(ss.contains("lll"));
    assert(ss.size() == 1);
    assert(!ss2.contains("lll"));
    assert(ss2.size() == 3);
    
    assert(!ss.erase("abc"));//ss doesn't contain ss2's value
    assert(!ss2.erase("lll"));//ss2 doesn't contain ss's value
    
    ss.swap(ss2);////now ss2 has one value, while ss has ss2's
    assert(ss.contains("abc"));
    assert(ss.contains("bsd"));
    assert(ss.contains("qwe"));
    assert(!ss.contains("lll"));
    assert(ss.size() == 3);

    assert(!ss2.contains("abc"));
    assert(!ss2.contains("bsd"));
    assert(!ss2.contains("qwe"));
    assert(ss2.contains("lll"));
    assert(ss2.size() == 1);
}

void testCopyAssign()
{
    Set ss;
    assert(ss.insert("abc"));
    assert(ss.insert("bsd"));
    assert(ss.insert("qwe"));
    assert(ss.size() == 3);
    
    Set ss2(ss);//test copy constructor
    assert(ss2.contains("abc"));
    assert(ss2.contains("bsd"));
    assert(ss2.contains("qwe"));
    assert(!ss2.contains("asdf"));
    assert(ss2.size() == 3);

    Set ss3;
    ss3 = ss2 = ss;//test assignment operator
    assert(ss3.contains("abc"));
    assert(ss3.contains("bsd"));
    assert(ss3.contains("qwe"));
    assert(!ss3.contains("asdf"));
    assert(ss3.size() == 3);

    assert(ss.erase("abc"));
    assert(ss2.contains("abc"));//ss2 not affected
    assert(ss3.contains("abc"));//ss3 not affected
    
    assert(ss3.insert("ss3"));//won't affect ss and ss2
    assert(ss3.contains("ss3"));
    assert(!ss.contains("ss3"));
    assert(!ss2.contains("ss3"));
    
    assert(ss.insert("disappear"));
    ss = ss3;//ss shoud now have ss3's value
    assert(ss3.size()== 4);
    assert(ss.size() == 4);
    assert(!ss.contains("disappear"));
    assert(ss.contains("ss3"));
    assert(ss.contains("abc"));
    assert(ss.contains("bsd"));
    assert(ss.contains("qwe"));
    
    assert(ss.erase("qwe"));//ss won't affect ss3
    assert(ss.erase("abc"));
    assert(ss.erase("bsd"));
    assert(ss.erase("ss3"));
    assert(!ss.contains("qwe"));
    assert(!ss.contains("abc"));
    assert(!ss.contains("bsd"));
    assert(!ss.contains("ss3"));
    assert(ss3.contains("ss3"));
    assert(ss3.contains("abc"));
    assert(ss3.contains("bsd"));
    assert(ss3.contains("qwe"));
    
    //////////////extreme cases//////////////
    
    //test empty list
    //copy constructor
    Set s1;
    assert(s1.size()==0);
    
    Set s2(s1);
    assert(s2.size()==0);
    
    Set sss2 = s1;
    assert(sss2.size()==0);
    
    //assignment operator
    Set s3;
    s3 = s1;
    assert(s3.size()==0);
    
    Set s4;
    s4 = s3 = s1;
    assert(s4.size()==0);
    
    //test only item list
    //copy constructor
    assert(s1.insert("apple"));//s1{apple}
    Set apple(s1);
    assert(apple.contains("apple"));//apple{apple}
    Set fruit = s1;
    assert(fruit.contains("apple"));//fruit{apple}
    
    //assignment operator
    Set apple2, apple3;
    apple2 = s1;
    assert(apple2.contains("apple"));
    apple3 = apple2 = s1;
    assert(apple3.contains("apple"));
    
}

void testUnite()
{
    Set ss, ss2, ss3, ss4;
    assert(ss.insert("a"));
    assert(ss.insert("b"));
    assert(ss.insert("c"));
    assert(ss.size() == 3);//ss{a,b,c}
    
    assert(ss2.insert("b"));//ss2{b,c,d,e,f}
    assert(ss2.insert("c"));
    assert(ss2.insert("d"));
    assert(ss2.insert("e"));
    assert(ss2.insert("f"));
    assert(ss2.size() == 5);
    
    unite(ss, ss2, ss3);//test when result is empty ss3{}
    assert(ss3.contains("a"));
    assert(ss3.contains("b"));
    assert(ss3.contains("c"));
    assert(ss3.contains("d"));
    assert(ss3.contains("e"));
    assert(ss3.contains("f"));//ss3{a,b,c,d,e,f}
    assert(ss3.size() == 6);

    
    assert(ss4.insert("garbage"));//ss4{garbage}
    unite(ss, ss2, ss4);//test when result is not empty
    assert(ss4.contains("a"));
    assert(ss4.contains("b"));
    assert(ss4.contains("c"));
    assert(ss4.contains("d"));
    assert(ss4.contains("e"));
    assert(ss4.contains("f"));
    assert(!ss4.contains("garbage"));//ss4{a,b,c,d,e,f}
    assert(ss4.size() == 6);

    
    //test when the result is same as one of the parameter
    unite(ss,ss,ss);//ss{a,b,c}, ss, ss
    assert(ss.contains("a"));
    assert(ss.contains("b"));
    assert(ss.contains("c"));
    assert(ss.size() == 3);//result->ss{a,b,c}
    
    unite(ss, ss, ss2);//ss{a,b,c}, ss, ss2{b,c,d,e,f}
    assert(ss2.contains("a"));
    assert(ss2.contains("b"));
    assert(ss2.contains("c"));
    assert(ss2.size() == 3);//result->ss2{a,b,c}
    
    assert(ss2.insert("d"));
    assert(ss2.insert("e"));
    assert(ss2.insert("f"));//ss2{a,b,c,d,e,f}
    assert(ss2.size() == 6);
    unite(ss, ss2, ss);//ss{a,b,c}, ss2{a,b,c,d,e,f}, ss
    assert(ss.contains("a"));
    assert(ss.contains("b"));
    assert(ss.contains("c"));
    assert(ss.contains("d"));
    assert(ss.contains("e"));
    assert(ss.contains("f"));
    assert(ss.size() == 6);//result->ss{a,b,c,d,e,f}
    
    assert(ss2.erase("a"));
    assert(ss2.insert("yes"));//ss2{b,c,d,e,f,yes}
    assert(ss.erase("a"));
    assert(ss.insert("apple"));
    assert(ss.insert("banana"));
    assert(ss.insert("cow"));
    assert(ss.size() == 8);//ss{b,c,d,e,f,apple,banana,cow}
    
    assert(ss.insert("a"));//ss{a,b,c,d,e,f,apple,banana,cow}
    unite(ss, ss2, ss2);//ss, ss2, ss2
    assert(ss2.contains("a"));
    assert(ss2.contains("b"));
    assert(ss2.contains("c"));
    assert(ss2.contains("d"));
    assert(ss2.contains("e"));
    assert(ss2.contains("f"));
    assert(ss2.contains("apple"));
    assert(ss2.contains("banana"));
    assert(ss2.contains("cow"));
    assert(ss2.contains("yes"));
    assert(ss2.size() == 10);//ss2{a,b,c,d,e,f,apple,banana,cow,yes}
    
    
    Set s1, s2, s3, s4;
    assert(s1.size()==0);
    assert(s2.insert("a"));
    assert(s2.insert("b"));
    
    unite(s1, s2, s3);//s1 and s3 both empty
    assert(s3.contains("a"));
    assert(s3.contains("b"));
    
    assert(s4.insert("l"));
    assert(s4.insert("z"));
    
    unite(s1, s2, s4);//s4 is not empty
    assert(s4.contains("a"));
    assert(s4.contains("b"));
    assert(!s4.contains("l"));
    assert(!s4.contains("z"));
    
    

    Set sss, sss2, sss3, sss4;
    unite(sss, sss2, sss3);//all empty
    assert(sss.size()==0);
    assert(sss2.size()==0);
    assert(sss3.size()==0);
    
    assert(sss4.insert("a"));
    assert(sss4.insert("b"));
    unite(sss, sss2, sss4);//ss4 not empty
    assert(sss.size()==0);
    assert(sss2.size()==0);
    assert(sss4.size()==0);
}

void testSubtract()
{
    Set ss, ss2, ss3, ss4;
    assert(ss.insert("a"));
    assert(ss.insert("b"));
    assert(ss.insert("c"));
    assert(ss.size() == 3);//ss{a,b,c}
    
    assert(ss2.insert("b"));//ss2{b,c,d,e,f}
    assert(ss2.insert("c"));
    assert(ss2.insert("d"));
    assert(ss2.insert("e"));
    assert(ss2.insert("f"));
    assert(ss2.size() == 5);
    
    subtract(ss, ss2, ss3);//test when result is empty ss3{}
    assert(ss3.contains("a"));
    assert(!ss3.contains("b"));
    assert(!ss3.contains("c"));
    assert(!ss3.contains("d"));
    assert(!ss3.contains("e"));
    assert(!ss3.contains("f"));//ss3{a}
    assert(ss3.size() == 1);
    
    
    assert(ss4.insert("garbage"));//ss4{garbage}
    subtract(ss, ss2, ss4);//test when result is not empty
    assert(ss4.contains("a"));
    assert(!ss4.contains("b"));
    assert(!ss4.contains("c"));
    assert(!ss4.contains("d"));
    assert(!ss4.contains("e"));
    assert(!ss4.contains("f"));
    assert(!ss4.contains("garbage"));//ss4{a}
    assert(ss4.size() == 1);
    
    
    //test when the result is same as one of the parameter
    subtract(ss,ss,ss);//ss{a,b,c}, ss, ss
    assert(!ss.contains("a"));
    assert(!ss.contains("b"));
    assert(!ss.contains("c"));
    assert(ss.size() == 0);//result->ss{}
    
    assert(ss.insert("a"));
    assert(ss.insert("b"));
    assert(ss.insert("c"));
    assert(ss.size() == 3);//ss{a,b,c}
    subtract(ss, ss, ss2);//ss{a,b,c}, ss, ss2{b,c,d,e,f}
    assert(!ss2.contains("a"));
    assert(!ss2.contains("b"));
    assert(!ss2.contains("c"));
    assert(ss2.size() == 0);//result->ss2{}
    
    assert(ss2.insert("a"));
    assert(ss2.insert("b"));
    assert(ss2.insert("c"));
    assert(ss2.insert("d"));
    assert(ss2.insert("e"));
    assert(ss2.insert("f"));//ss2{a,b,c,d,e,f}
    assert(ss2.size() == 6);
    subtract(ss, ss2, ss);//ss{a,b,c}, ss2{a,b,c,d,e,f}, ss
    assert(!ss.contains("a"));
    assert(!ss.contains("b"));
    assert(!ss.contains("c"));
    assert(!ss.contains("d"));
    assert(!ss.contains("e"));
    assert(!ss.contains("f"));
    assert(ss.size() == 0);//result->ss{}
    
    
    assert(ss2.erase("a"));
    assert(ss2.insert("yes"));//ss2{b,c,d,e,f,yes}
    assert(ss.insert("a"));
    assert(ss.insert("b"));
    assert(ss.insert("c"));
    assert(ss.size() == 3);//ss{a,b,c}
    assert(ss.erase("a"));
    assert(ss.insert("apple"));
    assert(ss.insert("banana"));
    assert(ss.insert("cow"));
    assert(ss.size() == 5);//ss{b,c,apple,banana,cow}
    
    assert(ss.insert("a"));//ss{a,b,c,apple,banana,cow}
    subtract(ss, ss2, ss2);//ss, ss2, ss2
    assert(ss2.contains("a"));
    assert(!ss2.contains("b"));
    assert(!ss2.contains("c"));
    assert(!ss2.contains("d"));
    assert(!ss2.contains("e"));
    assert(!ss2.contains("f"));
    assert(ss2.contains("apple"));
    assert(ss2.contains("banana"));
    assert(ss2.contains("cow"));
    assert(!ss2.contains("yes"));
    assert(ss2.size() == 4);//ss2{a,apple,banana,cow}
    
    
    Set s1, s2, s3, s4;
    assert(s1.insert("a"));
    assert(s1.insert("b"));//s1{a,b}
    assert(s2.size()==0);//s2{}
    
    
    subtract(s1, s2, s3);//s2 and s3 both empty
    assert(s3.contains("a"));
    assert(s3.contains("b"));//s3{a,b}
    assert(s3.size() == 2);
    
    assert(s4.insert("l"));
    assert(s4.insert("z"));//s4{l,z}
    
    subtract(s1, s2, s4);//s4 is not empty
    assert(s4.contains("a"));
    assert(s4.contains("b"));
    assert(!s4.contains("l"));
    assert(!s4.contains("z"));//s4{a,b}
    assert(s4.size() == 2);
    
    
    Set sss, sss2, sss3, sss4;
    subtract(sss, sss2, sss3);//all empty
    assert(sss.size()==0);
    assert(sss2.size()==0);
    assert(sss3.size()==0);
    
    assert(sss4.insert("a"));
    assert(sss4.insert("b"));
    subtract(sss, sss2, sss4);//ss4 not empty
    assert(sss.size()==0);
    assert(sss2.size()==0);
    assert(sss4.size()==0);

}

#endif

int main()
{
    
    testEmpty();
    testSize();
    testContains();
    testGet();
    testSwap();
    testCopyAssign();
    testUnite();
    testSubtract();
    testInsertErase();
    
    //test();
    cout << "Passed all tests" << endl;
}

// tester.cpp
// To test HW 1 Problem 1, uncomment the following line:

#ifdef HW1TEST
// #define TESTNEW

#ifdef TESTNEW
#include "newSet.h"
#else
#include "Set.h"
#endif

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <type_traits>

using namespace std;

static ItemType DUMMY = 123;
static ItemType DEFAULT = 0;
static ItemType ARRAY[6] = { 10, 20, 30, 40, 50, 60 };

bool isPermutation(ItemType a[], const ItemType b[], int n)
{
	for (size_t k = 0; k < n; k++)
	{
		size_t j;
		for (j = k; j < n; j++)
		{
			if (b[k] == a[j])
			{
				ItemType t = a[k];
				a[k] = a[j];
				a[j] = t;
				break;
			}
		}
		if (j == n)
			return false;
	}
	return true;
}

const int SPEC_MAX = 200;

void testone(int n)
{
	Set s;
	switch (n)
	{
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&Set::empty), bool (Set::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&Set::size), int (Set::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&Set::contains),
					bool (Set::*)(const ItemType&) const>::value));
        } break; case  4: {
            assert((is_same<decltype(&Set::get),
					bool (Set::*)(int, ItemType&) const>::value));
        } break; case  5: {
            assert(s.empty());
        } break; case  6: {
            assert(s.size() == 0);
        } break; case  7: {
            assert(!s.erase(DEFAULT)  &&  s.size() == 0);
        } break; case  8: {
            assert(!s.contains(DEFAULT));
        } break; case  9: {
            ItemType x = DUMMY;
            assert(!s.get(0, x));
        } break; case 10: {
            ItemType x = DUMMY;
            s.get(0, x);
            assert(x == DUMMY);
        } break; case 11: {
            assert(s.insert(DUMMY));
        } break; case 12: {
            s.insert(DUMMY);
            assert(!s.empty());
        } break; case 13: {
            s.insert(DUMMY);
            assert(s.size() == 1);
        } break; case 14: {
            s.insert(DUMMY);
            assert(s.contains(DUMMY));
        } break; case 15: {
            s.insert(DUMMY);
            ItemType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 16: {
            s.insert(DUMMY);
            ItemType x = DEFAULT;
            s.get(0, x);
            assert(x == DUMMY);
        } break; case 17: {
            assert(s.insert(DUMMY)  &&  !s.insert(DUMMY));
        } break; case 18: {
            s.insert(DUMMY);
            s.insert(DUMMY);
            assert(s.size() == 1);
        } break; case 19: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            assert(!s.empty()   &&  s.size() == 2);
        } break; case 20: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = DUMMY;
            s.get(0,x);
            assert(x == ARRAY[0]  ||  x == ARRAY[1]);
        } break; case 21: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = DUMMY;
            s.get(0,x);
            ItemType y = DUMMY;
            s.get(0,y);
            assert(x == y);
        } break; case 22: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = DUMMY;
            s.get(0,x);
            ItemType y = DUMMY;
            s.get(1,y);
            assert((x == ARRAY[0]  &&  y == ARRAY[1])  ||
                   (x == ARRAY[1]  &&  y == ARRAY[0]));
        } break; case 23: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            assert(s.size() == 5);
        } break; case 24: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            ItemType a[5] = { DUMMY, DUMMY, DUMMY, DUMMY, DUMMY };
            for (size_t k = 0; k < 5; k++)
                s.get(k, a[k]);
            assert(isPermutation(a, ARRAY, 5));
        } break; case 25: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            assert(s.size() == 2);
        } break; case 26: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType a[2] = { DUMMY, DUMMY };
            for (size_t k = 0; k < 2; k++)
                s.get(k, a[k]);
            assert(isPermutation(a, ARRAY, 2));
        } break; case 27: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[3]));
        } break; case 28: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            s.erase(ARRAY[3]);
            assert(s.size() == 4);
        } break; case 29: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[0])  &&  s.size() == 4);
        } break; case 30: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[4])  &&  s.size() == 4);
        } break; case 31: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[1]);
            assert(s.erase(ARRAY[1])  &&  s.size() == 2);
        } break; case 32: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.erase(ARRAY[3]);
            ItemType a[3] = { DUMMY, DUMMY, DUMMY };
            for (size_t k = 0; k < 3; k++)
                s.get(k, a[k]);
            assert(s.size() == 3  &&  isPermutation(a, ARRAY, 3));
        } break; case 33: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[3]);
            s.erase(ARRAY[3]);
            ItemType a[3] = { DUMMY, DUMMY, DUMMY };
            for (size_t k = 0; k < 3; k++)
                s.get(k, a[k]);
            assert(s.size() == 3  &&  isPermutation(a, ARRAY, 3));
        } break; case 34: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            assert(!s.erase(ARRAY[4]));
        } break; case 35: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.erase(ARRAY[4]);
            assert(s.size() == 4);
        } break; case 36: {
            s.insert(DUMMY);
            s.erase(DUMMY);
            assert(s.size() == 0);
        } break; case 37: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x;
            assert(!s.get(-1, x));
        } break; case 38: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x = DUMMY;
            s.get(-1, x);
            assert(x == DUMMY);
        } break; case 39: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x;
            assert(! s.get(3, x));
        } break; case 40: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x = DUMMY;
            s.get(3, x);
            assert(x == DUMMY);
        } break; case 41: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            assert(!s.contains(DEFAULT));
        } break; case 42: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            assert(s.contains(ARRAY[2]));
        } break; case 43: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[2]);
            assert(s.size() == 2  &&  !s.contains(ARRAY[2]));
        } break; case 44: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            assert(s.size() == 3  &&  s.contains(ARRAY[2])  &&
                   s.contains(ARRAY[3]));
        } break; case 45: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s.swap(s2);
                assert(s.size() == 2  &&  s2.size() == 3);
            }
        } break; case 46: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s.swap(s2);
                assert(s.contains(ARRAY[3])  &&  s.contains(ARRAY[4]));
                assert(!s2.contains(ARRAY[3])  &&  !s2.contains(ARRAY[4]));
                for (size_t k = 0; k < 3; k++)
                {
                    assert(!s.contains(ARRAY[k]));
                    assert(s2.contains(ARRAY[k]));
                }
            }
        } break; case 47: {
            for (size_t k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            assert(s.size() == SPEC_MAX);
        } break; case 48: {
            for (size_t k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            ItemType x = SPEC_MAX;
            assert(s.insert(x)  &&  s.size() == SPEC_MAX+1  &&  s.contains(x));
        } break; case 49: {
            assert(s.insert(DUMMY));
            for (size_t k = 0; k < 10*SPEC_MAX; k++)
                assert(!s.insert(DUMMY));
        } break; case 50: {
            for (size_t k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            assert(s.insert(SPEC_MAX));
            s.erase(0);
            assert(s.insert(SPEC_MAX+1));
            assert(s.insert(SPEC_MAX+2));
#if TESTNEW
        } break; case 51: {
            const size_t CAPACITY = 2;
            Set s2(CAPACITY);
            for (size_t k = 0; k < CAPACITY; k++)
                assert(s2.insert(k));
            assert(! s2.insert(CAPACITY));
        } break; case 52: {
            const size_t CAPACITY = SPEC_MAX*2;
            Set s2(CAPACITY);
            for (size_t k = 0; k < CAPACITY; k++)
                assert(s2.insert(k));
            assert(! s2.insert(CAPACITY));
        } break; case 53: {
            // This test checked that the destructor deletes the array of items.
        } break; case 54: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 55: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                ItemType a[4] = { DUMMY, DUMMY, DUMMY, DUMMY };
                for (size_t k = 0; k < 4; k++)
                    s2.get(k, a[k]);
                assert(s2.size() == 4  &&  isPermutation(a, ARRAY, 4));
            }
        } break; case 56: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                ItemType a[3] = { DUMMY, DUMMY, DUMMY };
                for (size_t k = 0; k < 3; k++)
                    s.get(k, a[k]);
                assert(s.size() == 3  &&  isPermutation(a, ARRAY, 3));
            }
        } break; case 57: {
            {
                Set s2(2);
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                Set s3(s2);
                assert(! s3.insert(ARRAY[2]));
            }
        } break; case 58: {
            // This test checked that the assignment operator doesn't just
            // copy a pointer.
        } break; case 59: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[2]);
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2 = s;
                s2.insert(ARRAY[5]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 60: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2.insert(ARRAY[5]);
                s2 = s;
                s2.insert(ARRAY[2]);
                ItemType a[3] = { DUMMY, DUMMY, DUMMY };
                for (size_t k = 0; k < 3; k++)
                    s2.get(k, a[k]);
                assert(s2.size() == 3  &&  isPermutation(a, ARRAY, 3));
            }
        } break; case 61: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2.insert(ARRAY[5]);
                s2 = s;
                s2.insert(ARRAY[2]);
                ItemType a[2] = { DUMMY, DUMMY };
                for (size_t k = 0; k < 2; k++)
                    s.get(k, a[k]);
                assert(s.size() == 2  &&  isPermutation(a, ARRAY, 2));
            }
        } break; case 62: {
            // This test checked that swap doesn't take a length of time
            // proportional to the number of items in the Sets.
        }
	}
}

int main()
{
	//cout << "Enter test number: ";
	int n;
    for(int n = 1; n < 51; n++ )
	{
        //cin >> n;
        testone(n);
        cout << n << " Passed" << endl;
    }
}
#endif //newSet
#endif //HW1

