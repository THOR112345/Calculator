// Pair: Karthik Yechuri (U51358914) and Sri Sai Koushik Yaganti (U65258662)

// This header file has CalcNode and CalcList classes
#ifndef CALCLIST_H
#define CALCLIST_H

// includes the CalcListInterface header file to add function declarations into CalcList class
#include "CalcListInterface.hpp"
#include <iostream>

// Calcnode class with doubly linked list elements
class CalcNode {
    private:
        double elem; // total after the operation is completed
        FUNCTIONS func; // what function to use
        double num; // number that adds into the operand
        double operand; // the operand that will be used in the calculation
        CalcNode* prev; // previous node in the list
        CalcNode* next; // next node in the list
        friend class CalcList; // allows CalcList access
};

// CalcList doubly linked list class
class CalcList {
    public:
        CalcList(); // constructor
        ~CalcList(); // destructor
        bool empty() const; // checks if list is empty
        double totalcalc = 0.0; // intializing total to 0
        int count = 0; // intializing counter to 0
        void addNode(double elem, FUNCTIONS operation, double num, double operand);
        virtual double total() const;
        virtual void newOperation(const FUNCTIONS func, const double operand);
        virtual void removeLastOperation();
        virtual std::string toString(unsigned short precision) const;
    private:
        // list sentinels
        CalcNode* header; // This node points to the beginning of the list
        CalcNode* trailer; // This node points to the end of the list
};

#endif