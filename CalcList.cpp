// Pair Programmers: Karthik Yechuri (U51358914) and Sri Sai Koushik Yaganti (U65258662)

/* Illustration: Calculator - using a doubly linked list, the calculator will perform addition, subtraction, multiplication, and
 division and keep a running total, number of operations completed, as well as what operations they were. It can also
 "undo" the last operation and can output a string of operations completed with fixed precision */

#include "CalcList.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

// Constructor w pointers for doubly linked list
CalcList::CalcList()
{
    header = new CalcNode;
    trailer = new CalcNode;
    header->next = trailer;
    trailer->prev = header;
}

// Deconstructor 
CalcList::~CalcList()
{
    while(!empty())
    {
        removeLastOperation();
    }
    delete header;
    delete trailer;
}

// checks if the list is empty
bool CalcList::empty() const
{
    return (header->next == trailer);
}

// adds new node for each new operation
void CalcList::addNode(double elem, FUNCTIONS operation, double num, double operand)
{
    CalcNode* newNode = new CalcNode;
    newNode->elem = elem;
    newNode->func = operation;
    newNode->num = num;
    newNode->operand = operand;

    // if linked list empty, pointer header to first node
    if(empty())
    {
        header->next = trailer->prev = newNode;
        newNode->prev = header;
        newNode->next = trailer;
    }

    // if not empty, add to the beginning of linked list
    else
    {
        newNode->next = header->next;
        newNode->prev = header;
        header->next->prev = newNode;
        header->next = newNode;
    } 
}

// return calculated total 
double CalcList::total() const
{
    return totalcalc;
}

// switch case to determine operation selected and calculate accordingly
// call addNode to add new node to linked list
// increase count
void CalcList::newOperation(const FUNCTIONS func, const double operand)
{
    double num = totalcalc;
    switch (func)
    {
        case 3:     if(operand == 0)
                    {
                        throw std::invalid_argument("Invalid: Division by 0 is not allowed!");
                    }

                    else
                    {
                        totalcalc = totalcalc/operand;
                    }
                    break;
        case 2:     totalcalc = totalcalc * operand;
                    break;
        case 1:     totalcalc -= operand;
                    break;
        default:    totalcalc += operand;
                    break;
    }

    addNode(totalcalc, func, num, operand);
    count++;
}

// if list empty, return message for invalid argument
// else, point pointers away, delete node
void CalcList::removeLastOperation()
{
    if(empty())
    {
        throw std::invalid_argument("Invalid: List is empty!");
    }
    
    else
    {
        CalcNode* remove = header->next;
        CalcNode* after = remove->next;
        after->prev = header;
        header->next = after;
        totalcalc = remove->num;
        count--;
        delete remove;
    }
}

// create string to be printed
// determine operator from user input func
// print out string with temp num, operand, and elem
std::string CalcList::toString(unsigned short precision) const
{
    CalcNode* temp = header->next;
    std::string op = "";
    std::string toret = "";
    int i = count;

    std::ostringstream ret;

    while(temp->next != trailer->next)
    {
        if(temp->func == 0)
        {
            op = "+";
        }
        else if(temp->func == 1)
        {
            op = "-";
        }
        else if(temp->func == 2)
        {
            op = "*";
        }
        else if(temp->func == 3)
        {
            op = "/";
        }

        ret.precision(precision);
        ret << std::fixed << i << ": " << temp->num << op << temp->operand << "=" << temp->elem << "\n";

        i--;
        temp = temp->next;
    }
    return ret.str();
}