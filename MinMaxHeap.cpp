/**
*	@file : MinMaxHeap.cpp
*	@author :  Haaris Chaudhry
*	@date : Mar 9, 2017
*	Purpose: The MinMaxHeap class will simulate the classical functions k-heap with k equal to 2
*/

#include "MinMaxHeap.h"
#include <cmath>
#include <iostream>

// Simple constructor that creates an empty array of size aSize
MinMaxHeap::MinMaxHeap( long aSize ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new long[aSize] )
{
}

// This constructor is used when reading values from a file
// Easier than using an array since we don't know how many numbers we'll read
// First insert values as they're given, then go to the first parent and begin
// trickleDown from the last parent to the first
MinMaxHeap::MinMaxHeap( long aSize, Queue<long>& aQueue ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new long[aSize] )
{
    while( !aQueue.isEmpty() )
    {
        bottomUpInsert( aQueue.peekFront() );
        aQueue.dequeue();
    }

    for( long i = lastParentIndex(); i >= 1; i-- )   //mNumNodes is the size of the array, the last used index is mNumNodes - 1
    {
        trickleDown( i );
    }
}

// This constructor uses an array to construct the heap
// First insert each value in the array in order, and then
// find the last parent and trickleDown for each parent
// starting from the last to the first
MinMaxHeap::MinMaxHeap( long aSize, long values[], long valuesSize ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new long[aSize] )
{
    for( long i = 1; i < valuesSize; i++ )
    {
        bottomUpInsert( values[i] );
    }

    for( long i = lastParentIndex(); i >= 1; i-- )
    {
        trickleDown( i );
    }
}

// The destructor, destroys the heap array
MinMaxHeap::~MinMaxHeap()
{
    delete[] mHeapArray;
}

// bottomUpInsert simply inserts values in the heap
// without heapifying
void MinMaxHeap::bottomUpInsert( const long aValue )
{
    mNumNodes++;
    mHeapArray[mNumNodes] = aValue;
}

// Inserts values into the heap, and then heapifies
void MinMaxHeap::insert( const long aValue )
{
    if( mNumNodes == mSIZE )
    {
        return;
    }
    bottomUpInsert( aValue );
    BubbleUp( mNumNodes );
}

void MinMaxHeap::levelOrderDisplay()                                  // Displays values in order
{
    long nodeCount = 1;

    for( long i = 0; i <= mNumNodes; i++ )
    {
        long valuesPerLevel = pow( i );                             // Each level contains (2 ^ level) values

        for( long j = 0; j < valuesPerLevel; j++ )
        {
            std::cout << mHeapArray[nodeCount] << " ";
            nodeCount++;

            if( ( ( j + 1 ) % 2 == 0 ) && ( j != 0 ) && ( j != valuesPerLevel - 1 ) && nodeCount != mNumNodes + 1 )
            {
                std::cout << "- ";
            }
            if( nodeCount == mNumNodes + 1 )                            // Stop displaying if we reach the end of the heap
            {
                std::cout << std::endl;
                return;
            }
        }

        std::cout << std::endl;
    }
}

// replaces the top value with the last value then heapifies
long MinMaxHeap::deleteMin()
{
    if( mNumNodes > 0 )
    {
        long minValue = mHeapArray[1];
        mHeapArray[1] = mHeapArray[mNumNodes];
        mHeapArray[mNumNodes] = -1;
        mNumNodes--;
        trickleDown( 1 );
        return minValue;
    }

    return -1;
}

// looks for the maximum value and then replaces it with the last value in the heap, then heapifies
long MinMaxHeap::deleteMax()
{
    long maxValue = -1;

    if( mNumNodes > 2 )
    {
        if( mHeapArray[2] > mHeapArray[3] )
        {
            // Swap 2nd array value with last one, "delete" last value, then tricklDown at index 2
            maxValue = mHeapArray[2];
            mHeapArray[2] = mHeapArray[mNumNodes];
            mHeapArray[mNumNodes] = -1;
            mNumNodes--;
            trickleDown( 2 );
        }
        else
        {
            // Swap 3rd array value with last one, "delete" last value, then tricklDown at index 3
            maxValue = mHeapArray[3];
            mHeapArray[3] = mHeapArray[mNumNodes];
            mHeapArray[mNumNodes] = -1;
            mNumNodes--;
            trickleDown( 3 );
        }
    }
    else if( mNumNodes == 2 )
    {
        // Only 2 nodes, therefore the second one has to be the max because it is the only one on a max level
        maxValue = mHeapArray[2];
        mHeapArray[2] = -1;
        mNumNodes--;
    }
    else if( mNumNodes == 1 )
    {
        // Only one value, delete it
        maxValue = mHeapArray[1];
        mHeapArray[1] = -1;
        mNumNodes--;
    }

    return maxValue;
}


// Use k*i <= n to check for parent status, k=2
bool MinMaxHeap::isParent( long aIndex ) const
{
    return ( ( aIndex * 2 ) <= ( mNumNodes ) );
}

// Use i/k to get parent, k=2
long MinMaxHeap::getParentIndex( long aIndex ) const
{
    if( aIndex > 1 )
    {
        return ( ( aIndex ) / 2 );
    }
    else
    {
        return -1;
    }
}

// Finds the grandparent index, returns -1 if there is no grandparent
long MinMaxHeap::getGrandparentIndex( long aIndex ) const
{
    if( aIndex > 3 )
    {
        return ( ( aIndex ) / 4 );
    }
    else
    {
        return -1;
    }
}

// Check if the nth child exists
bool MinMaxHeap::nthChildExists( long aIndex, long aNthChild ) const
{
    return ( ( 2 * aIndex + aNthChild ) <= mNumNodes );
}

// Check if nth grandchild exists
bool MinMaxHeap::nthGrandchildExists( long aIndex, long aNthGrandchild ) const
{
    return ( ( 4 * aIndex + aNthGrandchild ) <= mNumNodes );
}

// Get the aNthChild
long MinMaxHeap::getNthChild( long aIndex, long aNthChild ) const
{
    if( nthChildExists( aIndex, aNthChild ) )
    {
        return 2 * aIndex + aNthChild;
    }
    else
    {
        return -1;
    }
}

// Gets the nth grandchildIndex
long MinMaxHeap::getNthGrandchild( long aIndex, long aNthGrandchild ) const
{
    if( nthGrandchildExists( aIndex, aNthGrandchild ) )
    {
        return 4 * aIndex + aNthGrandchild;
    }
    else
    {
        return -1;
    }
}

// Checks if aPossibleGrandchildIndex is a grandchild of aIndex
bool MinMaxHeap::isGrandChildOfIndex( long aIndex, long aPossibleGrandchildIndex ) const
{
    for( int i = 0; i < 4; i++ )    // Count 4 times because there is a max of four grandchildren
    {
        if( getNthGrandchild( aIndex, i ) == aPossibleGrandchildIndex )
        {
            return true;
        }
    }

    return false;
}

// Calculates powers of 2
long MinMaxHeap::pow( const long exponent ) const
{
    if( exponent == 0 )
    {
        return 1;
    }
    else
    {
        long returnValue = 1;

        for( long i = 0; i < exponent; i++ )
        {
            returnValue *= 2;
        }

        return returnValue;
    }
}

// Check if the heap is empty
bool MinMaxHeap::isEmpty() const
{
    return ( mNumNodes > 0 );
}

// Find the index of the last parent
long MinMaxHeap::lastParentIndex()
{
    return ( ( mNumNodes ) / 2 );
}

bool MinMaxHeap::isMinLevel( long aIndex )
{
    if( static_cast<long>( floor( log2l( aIndex ) ) ) % 2 == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// TrickleDown checks to see whether we should use the min trees or max trees
void MinMaxHeap::trickleDown( long aIndex )
{
    if( isMinLevel( aIndex ) )
    {
        trickleDownMin( aIndex );
    }
    else
    {
        trickleDownMax( aIndex );
    }
}

// Bubble up moves the value up while maintaining the min-max heap ordered structure
void MinMaxHeap::BubbleUp( long aIndex )
{
    long parentIndex = getParentIndex( aIndex );    // There is no parent if getParentIndex returns -1

    if( isMinLevel( aIndex ) )
    {

        if( parentIndex > -1 && mHeapArray[aIndex] > mHeapArray[parentIndex] )
        {
            // Swap
            long temp = mHeapArray[aIndex];
            mHeapArray[aIndex] = mHeapArray[parentIndex];
            mHeapArray[parentIndex] = temp;

            BubbleUpMax( parentIndex );
        }
        else
        {
            BubbleUpMin( aIndex );
        }
    }
    else
    {
        if( parentIndex > -1 && mHeapArray[aIndex] < mHeapArray[parentIndex] )
        {
            // Swap
            long temp = mHeapArray[aIndex];
            mHeapArray[aIndex] = mHeapArray[parentIndex];
            mHeapArray[parentIndex] = temp;

            BubbleUpMin( parentIndex );
        }
        else
        {
            BubbleUpMax( aIndex );
        }
    }
}

// Bubble up a value through a max tree
void MinMaxHeap::BubbleUpMax( long aIndex )
{
    long grandparentIndex = getGrandparentIndex( aIndex );

    if( grandparentIndex > -1 )     // Did we actually get a grandparent?
    {
        if( mHeapArray[aIndex] > mHeapArray[grandparentIndex] )
        {
            // Swap
            long temp = mHeapArray[aIndex];
            mHeapArray[aIndex] = mHeapArray[grandparentIndex];
            mHeapArray[grandparentIndex] = temp;

            BubbleUpMin( grandparentIndex );
        }
    }
}

// Bubble up a value through a min tree
void MinMaxHeap::BubbleUpMin( long aIndex )
{
    long grandparentIndex = getGrandparentIndex( aIndex );

    if( grandparentIndex > -1 )     // Did we actually get a grandparent?
    {
        if( mHeapArray[aIndex] < mHeapArray[grandparentIndex] )
        {
            // Swap
            long temp = mHeapArray[aIndex];
            mHeapArray[aIndex] = mHeapArray[grandparentIndex];
            mHeapArray[grandparentIndex] = temp;

            BubbleUpMin( grandparentIndex );
        }
    }
}

// Trickle down through a min tree
void MinMaxHeap::trickleDownMin( long aIndex )
{
    if( isParent( aIndex ) )
    {
        long m = indexSmallestCorGC( mHeapArray[aIndex], aIndex );      // If no child/grandchild is larger than the value at aIndex, then we get -1

        if( m > -1 )
        {
            if( isGrandChildOfIndex( aIndex, m ) )
            {
                if( mHeapArray[m] < mHeapArray[aIndex] )
                {
                    // Swap
                    long temp = mHeapArray[m];
                    mHeapArray[m] = mHeapArray[aIndex];
                    mHeapArray[aIndex] = temp;

                    long parentIndexOfM = getParentIndex( m );
                    if( mHeapArray[m] > mHeapArray[parentIndexOfM] )
                    {
                        // Swap (probably should've used a function for this...)
                        long anotherTemp = mHeapArray[m];
                        mHeapArray[m] = mHeapArray[parentIndexOfM];
                        mHeapArray[parentIndexOfM] = anotherTemp;
                    }

                    trickleDownMin( m );
                }
            }
            else
            {
                if( mHeapArray[m] < mHeapArray[aIndex] )
                {
                    // Swap
                    long temp = mHeapArray[m];
                    mHeapArray[m] = mHeapArray[aIndex];
                    mHeapArray[aIndex] = temp;
                }
            }
        }
    }
}

// Trickle down through a max tree
void MinMaxHeap::trickleDownMax( long aIndex )
{
    if( isParent( aIndex ) )
    {
        long m = indexLargestCorGC( mHeapArray[aIndex], aIndex );   // If no child/grandchild is larger than the value at aIndex, then we get -1

        if( m > -1 )
        {
            if( isGrandChildOfIndex( aIndex, m ) )
            {
                if( mHeapArray[m] > mHeapArray[aIndex] )
                {
                    // Swap
                    long temp = mHeapArray[m];
                    mHeapArray[m] = mHeapArray[aIndex];
                    mHeapArray[aIndex] = temp;

                    long parentIndexOfM = getParentIndex( m );
                    if( mHeapArray[m] < mHeapArray[parentIndexOfM] )
                    {
                        // Swap
                        long anotherTemp = mHeapArray[m];
                        mHeapArray[m] = mHeapArray[parentIndexOfM];
                        mHeapArray[parentIndexOfM] = anotherTemp;
                    }

                    trickleDownMax( m );
                }
            }
            else
            {
                if( mHeapArray[m] > mHeapArray[aIndex] )
                {
                    // Swap
                    long temp = mHeapArray[m];
                    mHeapArray[m] = mHeapArray[aIndex];
                    mHeapArray[aIndex] = temp;
                }
            }
        }
    }
}

// Find the index of the smallest child
long MinMaxHeap::indexSmallestCorGC( long aValueToMove, long aIndex ) const
{
    if( isParent( aIndex ) )
    {
        long childIndices[6];

        for( long i = 0; i < 6; i++ )   // This for loop will fill an array with children and grandchildren
        {
            long ithChildIndex;

            if( i < 2 )                 // The first two slots are for children
            {
                ithChildIndex = getNthChild( aIndex, i );
            }
            else
            {
                ithChildIndex = getNthGrandchild( aIndex, i - 2 );
            }


            if( ithChildIndex > -1 )
            {
                childIndices[i] = mHeapArray[ithChildIndex];
            }
            else
            {
                childIndices[i] = -1;
            }
        }

        long minValueIndex = -1;

        for( long i = 0; i < 6; i++ )
        {
            if( aValueToMove > childIndices[i] && childIndices[i] != -1 )
            {
                if( minValueIndex == -1 || ( childIndices[i] < childIndices[minValueIndex] ) )
                {
                    minValueIndex = i;      // minValueIndex has the potential to stay at -1 here, indicating no smaller children
                }
            }
        }

        if( minValueIndex > -1 )
        {
            // Since minValueIndex was taken from childIndices and we know that childIndices carries child values in 
            // indexes 1 and 2, and grandchildren in indexes 3-5, we can determine whether we should get 
            // children or grandchildren
            if( minValueIndex < 2 )
            {
                return ( getNthChild( aIndex, minValueIndex ) );
            }
            else
            {
                return ( getNthGrandchild( aIndex, minValueIndex - 2 ) );   // Need to subtract two because we're getting the (0th, 1st, 2nd, or 3rd) grandchild
            }                                                               // Not the 2nd, 3rd, 4th, or 5th

        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
long MinMaxHeap::indexLargestCorGC( long aValueToMove, long aIndex ) const
{
    if( isParent( aIndex ) )
    {
        long childIndices[6];

        for( long i = 0; i < 6; i++ )   // This for loop will fill an array with children and grandchildren
        {
            long ithChildIndex;

            if( i < 2 )                 // The first two slots are for children
            {
                ithChildIndex = getNthChild( aIndex, i );
            }
            else
            {
                ithChildIndex = getNthGrandchild( aIndex, i - 2 );
            }


            if( ithChildIndex > -1 )
            {
                childIndices[i] = mHeapArray[ithChildIndex];
            }
            else
            {
                childIndices[i] = -1;
            }
        }

        long maxValueIndex = -1;

        for( long i = 0; i < 6; i++ )
        {
            if( aValueToMove < childIndices[i] && childIndices[i] != -1 )
            {
                if( maxValueIndex == -1 || ( childIndices[i] > childIndices[maxValueIndex] ) )
                {
                    maxValueIndex = i;      // minValueIndex has the potential to stay at -1 here, indicating no smaller children
                }
            }
        }

        if( maxValueIndex > -1 )
        {
            // Since minValueIndex was taken from childIndices and we know that childIndices carries child values in 
            // indexes 1 and 2, and grandchildren in indexes 3-5, we can determine whether we should get 
            // children or grandchildren
            if( maxValueIndex < 2 )
            {
                return ( getNthChild( aIndex, maxValueIndex ) );
            }
            else
            {
                return ( getNthGrandchild( aIndex, maxValueIndex - 2 ) );       // Need to subtract two because we're getting the (0th, 1st, 2nd, or 3rd) grandchild
            }                                                                   // Not the 2nd, 3rd, 4th, or 5th
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
