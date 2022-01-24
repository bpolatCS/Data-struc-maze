#include "bpolat_hw1_Header.h"


template <class Object>
Stack<Object>::Stack( )
{
	topOfStack = NULL;
}



template <class Object>
Stack<Object>::Stack( const Stack<Object> & rhs )
{
	topOfStack = NULL;
	*this = rhs; // deep copy 
}


template <class Object>
Stack<Object>::~Stack( )
{
    makeEmpty( );
}


template <class Object>
bool Stack<Object>::isFull( ) const
{
	return false;
}


template <class Object>
bool Stack<Object>::isEmpty( ) const
{
    return topOfStack == NULL;
}

template <class Object>
const Object & Stack<Object>::top( ) const
{
   
    return topOfStack->element;
}

template <class Object>
void Stack<Object>::pop() 
{
	ListNode *oldTop = topOfStack;
	topOfStack = topOfStack->next;
	delete oldTop;
}
template <class Object>
void Stack<Object>::push( const Object & x )
{
	topOfStack = new ListNode( x, topOfStack);
}


template <class Object>
Object Stack<Object>::topAndPop( )
{
	Object topItem = top( );
	pop( );
	return topItem;
}


template <class Object>
void Stack<Object>::makeEmpty( )
{
	while ( ! isEmpty( ) )
		pop( );
}


template <class Object>
const Stack<Object> & Stack<Object>::
operator=( const Stack<Object> & rhs )
{
	if ( this != &rhs )
	{
		makeEmpty( );
		if ( rhs.isEmpty( ) )
			return *this;

		ListNode *rptr = rhs.topOfStack;
		ListNode *ptr  = new ListNode( rptr->element );
		topOfStack = ptr;

		for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
				ptr = ptr->next = new ListNode( rptr->element );
	}
	return *this;
}




