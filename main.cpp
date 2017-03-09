#include <iostream>
#include <fstream>
#include "MinMaxHeap.h"

long getChoice();
void menuLoop( MinMaxHeap& minMaxHeap );
void insertItem( MinMaxHeap& minMaxHeap );
void deletemax( MinMaxHeap& minMaxHeap );
void deletemin( MinMaxHeap& minMaxHeap );
void printLevelOrder( MinMaxHeap& minMaxHeap );

int main()
{
    long anInteger;
    std::ifstream fileReader( "data.txt" );

    if( fileReader.is_open() )
    {
        Queue<long> readValues;

        while( fileReader >> anInteger )
        {
            readValues.enqueue( anInteger );
        }

        MinMaxHeap minMaxHeap( 200, readValues );

        menuLoop( minMaxHeap );
        fileReader.close();
    }
    else
    {
        std::cout << "Error reading file\n";
    }

    return 0;
}

void menuLoop( MinMaxHeap& minMaxHeap )
{
    long choice = 0;

    while( choice != 5 )
    {
        choice = getChoice();

        switch( choice )
        {
        case 1:
            insertItem( minMaxHeap );
            break;
        case 2:
            deletemin( minMaxHeap );
            break;
        case 3:
            deletemax( minMaxHeap );
            break;
        case 4:
            printLevelOrder( minMaxHeap );
            break;
        case 5:
        default:
            if( choice != 5 )
            {
                std::cout << "Enter a valid choice (1-5)\n";
            }
            break;
        }
    }
}

long getChoice()
{
    long choice = 0;

    std::cout << "..........................................................\n";
    std::cout << "Please choose one of the folowing commands:\n";
    std::cout << "1 - insert\n"
        << "2 - deletemin\n"
        << "3 - deletemax\n"
        << "4 - levelorder\n"
        << "5 - exit\n"
        << "\n";

    std::cin >> choice;

    return choice;
}

void insertItem( MinMaxHeap& minMaxHeap )
{
    std::cout << "Choose a number to be added to the heap\n";
    long number;
    std::cin >> number;
    minMaxHeap.insert( number );
}

void deletemin( MinMaxHeap& minMaxHeap )
{
    if( minMaxHeap.deleteMin() == -1 )
    {
        std::cout << "The heap is empty\n";
    }
}

void deletemax( MinMaxHeap& minMaxHeap )
{
    if( minMaxHeap.deleteMax() == -1 )
    {
        std::cout << "The heap is empty\n";
    }
}

void printLevelOrder( MinMaxHeap& minMaxHeap )
{
    std::cout << "Level Order:\n";
    minMaxHeap.levelOrderDisplay();
    std::cout << std::endl;
}