#pragma once
//*************************************************************
// Author: D.S. Malik
//
// This class specifies the basic operations on a queue as a
// linked list.
//*************************************************************
//Definition of the node
template < class Type>
struct nodeType
{

    Type info;

    nodeType <Type>* link;

};

template <class Type>
class queueADT
{
public:
    virtual bool isEmptyQueue() const = 0;
    //Function to determine whether the queue is empty.
    //Postcondition: Returns true if the queue is empty,
    // otherwise returns false.
    virtual bool isFullQueue() const = 0;
    //Function to determine whether the queue is full.
    //Postcondition: Returns true if the queue is full,
    // otherwise returns false.
    virtual void initializeQueue() = 0;
    //Function to initialize the queue to an empty state.
    //Postcondition: The queue is empty.
    virtual Type front() const = 0;
    //Function to return the first element of the queue.
    //Precondition: The queue exists and is not empty.
    //Postcondition: If the queue is empty, the program
    // terminates; otherwise, the first element of the queue
    // is returned.

    virtual Type back() const = 0;
    //Function to return the last element of the queue.
    //Precondition: The queue exists and is not empty.
    //Postcondition: If the queue is empty, the program
    // terminates; otherwise, the last element of the queue
    // is returned.
    virtual void addQueue(const Type& queueElement) = 0;
    //Function to add queueElement to the queue.
    //Precondition: The queue exists and is not full.
    //Postcondition: The queue is changed and queueElement is
    // added to the queue.
    virtual void deleteQueue() = 0;
    //Function to remove the first element of the queue.
    //Precondition: The queue exists and is not empty.
    //Postcondition: The queue is changed and the first element
    // is removed from the queue.
};


template < class Type >
class linkedQueueType :public queueADT < Type >
{

public:
    const linkedQueueType < Type >& operator=
        (const linkedQueueType < Type >&);

    //Overload the assignment operator.
    bool isEmptyQueue()const;

    //Function to determine whether the queue is empty.
    //Postcondition: Returns true if the queue is empty,
    // otherwise returns false.
    bool isFullQueue()const;

    //Function to determine whether the queue is full.
    //Postcondition: Returns true if the queue is full,
    // otherwise returns false.
    void initializeQueue();

    //Function to initialize the queue to an empty state.
    //Postcondition: queueFront = NULL; queueRear = NULL
    Type front()const;

    //Function to return the first element of the queue.
    //Precondition: The queue exists and is not empty.
    //Postcondition: If the queue is empty, the program
    // terminates; otherwise, the first element of the
    // queue is returned.
    Type back()const;

    //Function to return the last element of the queue.
    //Precondition: The queue exists and is not empty.
    /*464 | Chapter 8: Queues
    8*/
    //Postcondition: If the queue is empty, the program
    // terminates; otherwise, the last element of the
    // queue is returned.
    void addQueue(const Type& queueElement);

    //Function to add queueElement to the queue.
    //Precondition: The queue exists and is not full.
    //Postcondition: The queue is changed and queueElement is
    // added to the queue.
    void deleteQueue();

    //Function to remove the first element of the queue.
    //Precondition: The queue exists and is not empty.
    //Postcondition: The queue is changed and the first element
    // is removed from the queue.
    linkedQueueType();

    //Default constructor
    linkedQueueType(const linkedQueueType < Type >& otherQueue);

    //Copy constructor
    ~linkedQueueType();


    template <class Type>
    bool linkedQueueType<Type>::isEmptyQueue() const
    {
        return(queueFront == NULL);
    } //end
    template <class Type>
    bool linkedQueueType<Type>::isFullQueue() const
    {
        return false;
    } //end isFullQueue

    template <class Type>
    void linkedQueueType<Type>::initializeQueue()
    {
        nodeType<Type>* temp;
        while (queueFront != NULL) //while there are elements left
        //in the queue
        {
            temp = queueFront; //set temp to point to the current node
            queueFront = queueFront->link; //advance first to
            //the next node
            delete temp; //deallocate memory occupied by temp
        }
        queueRear = NULL; //set rear to NULL
    } //end initializeQueue

    template <class Type>
    void linkedQueueType<Type>::addQueue(const Type& newElement)

    {
        nodeType<Type>* newNode;
        newNode = new nodeType<Type>; //create the node
        newNode->info = newElement; //store the info
        newNode->link = NULL; //initialize the link field to NULL
        if (queueFront == NULL) //if initially the queue is empty
        {
            queueFront = newNode;
            queueRear = newNode;
        }
        else //add newNode at the end
        {
            queueRear->link = newNode;
            queueRear = queueRear->link;
        }
    }//end addQueue
    template <class Type>
    Type linkedQueueType<Type>::front() const
    {
        assert(queueFront != NULL);
        return queueFront->info;
    } //end front
    template <class Type>
    Type linkedQueueType<Type>::back() const
    {
        assert(queueRear != NULL);
        return queueRear->info;
    } //end back
    template <class Type>
    void linkedQueueType<Type>::deleteQueue()
    {
        nodeType<Type>* temp;
        if (!isEmptyQueue())
        {
            temp = queueFront; //make temp point to the first node
            queueFront = queueFront->link; //advance queueFront
            delete temp; //delete the first node
            if (queueFront == NULL) //if after deletion the
            //queue is empty
                queueRear = NULL; //set queueRear to NULL
        }
        else
            cout << "Cannot remove from an empty queue" << endl;
    }//end deleteQueue

    template<class Type>
    linkedQueueType<Type>::linkedQueueType()
    {
        queueFront = NULL; //set front to null
        queueRear = NULL; //set rear to null
    } //end default constructor
    //Destructor
private:
    nodeType < Type >* queueFront;//pointer to the front of the queue
    nodeType < Type >* queueRear;	//pointer to the rear of the queue
};
