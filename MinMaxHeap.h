/**
*	@file : MinMaxHeap.h
*	@author :  Haaris Chaudhry
*	@date : Mar 9, 2017
*	Purpose: The MinMaxHeap class will simulate the classical functions k-heap with k equal to 2
*/

#ifndef MIN_MAX_HEAP_H
#define MIN_MAX_HEAP_H

#include "Queue.h"

class MinMaxHeap
{
public:
    /**
    * Constructor for the MinMaxHeap
    * @param aSize The size of the array that will contain the heap values
    * @return A Min 2-heap with a size of aSize
    */
    MinMaxHeap( long aSize );

    /**
    * Constructor for the MinMaxHeap
    * @param aSize The size of the array that will contain the heap values
    * @param aQueue This queue is used when values need to be read from a file
    * @return A Min 2-heap with a size of aSize containing the values in aQueue
    */
    MinMaxHeap( long aSize, Queue<long>& aQueue );

    /**
    * Constructor for the MinMaxHeap
    * @param aSize The size of the array that will contain the heap values
    * @param aQueue This queue is used when values need to be read from a file
    * @param values an array of values to be inserted into the heap
    * @param valuesSize the size of the array
    * @return A Min 2-heap with a size of aSize containing the values in values
    */
    MinMaxHeap( long aSize, long values[], long valuesSize );

    /**
    * The destructor
    */
    ~MinMaxHeap();

    /**
    * The insertion function, also heapifies the value
    * @param aValue The value to be inserted
    */
    void insert( const long aValue );

    /**
    * Displays the heap in a fancy level order using hyphens
    */
    void levelOrderDisplay();

    /**
    * Deletes the minimum value
    * @return The value that was deleted
    */
    long deleteMin();

    /**
    * Deletes the maximum value
    * @return The value that was deleted
    */
    long deleteMax();

private:
    /**
    * A function used to insert values without heapifying, used during bottom up construction
    * @param aValue The value to be inserted into the heap
    */
    void bottomUpInsert( const long aValue );

    /**
    * Finds the smallest child or grandchild of the given index
    * @param aValueToMove The value that we'll compare against
    * @param aIndex The index of the node that we'll compare against aValueToMove
    * @return The smallest child or grandchild of the given index, returns -1 if there are no smaller children
    */
    long indexSmallestCorGC( long aValueToMove, long aIndex ) const;

    /**
    * Finds the largest child or grandchild of the given index
    * @param aValueToMove The value that we'll compare against
    * @param aIndex The index of the node that we'll compare against aValueToMove
    * @return The largest child or grandchild of the given index, returns -1 if there are no smaller children
    */
    long indexLargestCorGC( long aValueToMove, long aIndex ) const;

    /**
    * Checks if the current node is a parent
    * @param aIndex The index of the current node
    * @return True if the node is a parent, false if otherwise
    */
    bool isParent( long aIndex ) const;

    /**
    * Gets the parent node index
    * @param aIndex The index of the current node
    * @return The index of the parent (-1 if there is no parent)
    */
    long getParentIndex( long aIndex ) const;

    /**
    * Gets the Grandparent node index
    * @param aIndex The index of the current node
    * @return The index of the grandparent (-1 if there is no parent)
    */
    long getGrandparentIndex( long aIndex ) const;

    /**
    * Checks if a particular child (either 0, or 1) exists
    * @param aIndex The index to check for children on
    * @param aNthChild The child index that we're searching for (either 0, or 1)
    * @return A flag indicating if a child does indeed exist (true if so, false if not)
    */
    bool nthChildExists( long aIndex, long aNthChild ) const;

    /**
    * Checks if a particular grandchild (either 0,1,2,3) exists
    * @param aIndex The index to check for grandchildren on
    * @param aNthGrandchild The grandchild index that we're searching for (either 0,1,2,3)
    * @return A flag indicating if a grandchild does indeed exist (true if so, false if not)
    */
    bool nthGrandchildExists( long aIndex, long aNthGrandchild ) const;

    /**
    * Retreives the index of the child
    * @param aIndex The index of the parent
    * @param aNthChild The child that we're searching for
    * @return The index of the child
    */
    long getNthChild( long aIndex, long aNthChild ) const;

    /**
    * Retreives the index of the grandchild
    * @param aIndex The index of the grandparent
    * @param aNthGrandchild The grandchild that we're searching for
    * @return The index of the grandchild
    */
    long getNthGrandchild( long aIndex, long aNthGrandchild ) const;

    /**
    * Determines if aPossibleGrandchildIndex is a grandchild of aIndex
    * @param aIndex The grandparent index
    * @param aPossibleGrandchildIndex The index that we'll check to see the grandchild status of
    * @return True if aPossibleGrandchildIndex is the grandchild index of aIndex, false otherwise
    */
    bool isGrandChildOfIndex( long aIndex, long aPossibleGrandchildIndex) const;

    /**
    * Helper function that computes powers of 2
    * @param exponent The power to raise 2 to
    * @return A power of 2
    */
    long pow( const long exponent ) const;

    /**
    * Function that indicates if the heap is empty
    * @return True if empty, false if not
    */
    bool isEmpty() const;

    /**
    * Finds the index of the last parent
    * @return The index of the last parent
    */
    long lastParentIndex();

    /**
    * Find out if the level that the index is on is a min level
    * @return True if a min level, false otherwise (which indicates max level)
    */
    bool isMinLevel( long aIndex );

    /**
    * Moves a value down through the heap to its proper spot
    * @param aIndex The index of the value to move
    */
    void trickleDown( long aIndex );

    /**
    * Moves a value up the heap
    * @param aIndex The index of the value to move up the heap
    */
    void BubbleUp( long aIndex );

    /**
    * Moves a value up the max portion of the heap
    * @param aIndex The index of the value to move up the heap
    */
    void BubbleUpMax( long aIndex );

    /**
    * Moves a value up the min portion of the heap
    * @param aIndex The index of the value to move up the heap
    */
    void BubbleUpMin( long aIndex );

    /**
    * Moves a value down through the heap to its proper spot, assuming it's at a min level
    * @param aIndex The index of the value to move
    */
    void trickleDownMin( long aIndex );

    /**
    * Moves a value down through the heap to its proper spot, assuming it's at a max level
    * @param aIndex The index of the value to move
    */
    void trickleDownMax( long aIndex );

    long mNumNodes;     //!< The number of nodes in the heap
    const long mSIZE;   //!< The size of the heapArray
    long* mHeapArray;   //!< The heapArray
};
#endif // !MIN_MAX_HEAP_H
