
#ifndef _BPOLAT_HW1_HEADER_H
#define _BPOLAT_HW1_HEADER_H

#include <iostream>

using namespace std;

template <class Object>
class Stack
{
	public:
		Stack( );
		Stack( const Stack & rhs );
		~Stack( );

		bool isEmpty( ) const;
		bool isFull( ) const;
		void makeEmpty( );

		void pop() ;
		void push( const Object & x );
		Object topAndPop( );
		const Object & top( ) const;

		const Stack & operator=( const Stack & rhs );

	private:
		struct ListNode
		{
			Object element;
			ListNode *next;

			ListNode( const Object & theElement, ListNode * n = NULL )
				: element( theElement ), next( n ) { }
		};
		ListNode *topOfStack;  // list itself is the stack
  };
#include "bpolat_hw1_Class.cpp"
#endif

