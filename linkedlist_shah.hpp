/*
Name: Karina Shah
Date: 4/27/23
Description: Template classes for a node and linked lists
*/

#pragma once
#ifndef linkedlist_shah_hpp
#define linkedlist_shah_hpp
#include <iostream>
using namespace std;

// Node class (function declarations)
template <class T>
class Node{
    public:
    Node();
    Node(T d);
    Node(T d, Node<T>* front, Node<T>* back);
    T getData();
    void setData(T d);
    Node<T>* getNext();
    void setNext(Node <T>* n);
    Node<T>* getPrevious();
    void setPrevious(Node<T>* p);
    // Node Attributes
    private:
    T data;
    Node <T>* next;
    Node <T>* previous;
};

// Empty Constructor: Sets next and previous to null
template <class T> Node<T>::Node(){
    next = nullptr;
    previous = nullptr;
}
// Constructor: Takes in d and stores in into data and sets next and previous to null
template<class T> Node<T>::Node(T d){
    data = d;
    next = nullptr;
    previous = nullptr;
}
// Constructor: Takes in d and stores it into data and sets next to front and previous and back
template<class T> Node<T>::Node(T d, Node<T>* front, Node<T>* back){
    data = d;
    next = front;
    previous = back;
}
// Getters and setters
template<class T> T Node<T>::getData(){
    return data;
}
template<class T> void Node<T>::setData(T d){
    data = d;
}
template<class T> Node<T>* Node<T>::getNext(){
    return next;
}
template<class T> void Node<T>::setNext(Node<T>* n){
    next = n;
}
template<class T> Node<T>* Node<T>::getPrevious(){
    return previous;
}
template<class T> void Node<T>::setPrevious(Node<T>* p){
    previous = p;
}
// LinkedList Class
template <class T>
class LinkedList{
    public:
    // Empty Constructor: Sets head to null
    LinkedList(){
        head = NULL;
    }
    // Constructor: Sets h to head
    LinkedList(Node <T>* h){
        head = h;
    }
    // Getter
    Node <T>* getHead(){
        return head;
    }
    // Destructor
    ~LinkedList(){
        if(head != nullptr){
            Node <T>* current = head;
            while(current != nullptr){
                Node <T>* del = current;
                current = current->getNext();
                delete del;
            }
        }
    }
    // Creates node from data and adds it to the front of the list
    void AddToFront(T data){
        Node <T>* newLink = new Node(data);
        if(head == nullptr){
            head = newLink;
        }
        else{
            head->setPrevious(newLink);
            newLink->setNext(head);
            head = newLink;
        }
    }
    // Creates node from data and adds it to the end of the list
    void AddToEnd(T data){
        if(head == nullptr){
            AddToFront(data);
        }
        else{
            Node <T>* newLink = new Node(data);
            Node <T>* temp = head;
            while(temp->getNext() != nullptr){
                temp = temp->getNext();
            }
            temp->setNext(newLink);
            newLink->setPrevious(temp);
        }
    }
    // Creates node from data and adds it to the list at the index given
    void AddAtIndex(T data, int index){
        if(index < 0){
            throw out_of_range("Add at Index: Less than length");
        }
        else if(index == 0){
            AddToFront(data);
        }
        else{
            Node <T>* newLink = new Node(data);
            Node <T>* temp = head;
            int i = 0;
            while(i < index - 1){
                if(temp != nullptr){
                    temp = temp->getNext();
                    i++;
                }
                else{
                    throw out_of_range("Add at Index: Greater than length");
                    break;
                }
            }
            if(temp != nullptr){
                newLink->setNext(temp->getNext());
                newLink->setPrevious(temp);
                temp->setNext(newLink);
                if(newLink->getNext() != nullptr){
                    newLink->getNext()->setPrevious(newLink);
                }
            }
        }
    }
    // Creates node from data and adds it before n
    void AddBefore(Node <T>* n, T data){
        Node <T>* newLink = new Node(data);
        newLink->setNext(n);
        if(n->getPrevious() == nullptr){
            n->setPrevious(newLink);
            head = newLink;
        }
        else{
            Node <T>* temp = n->getPrevious();
            temp->setNext(newLink);
            n->setPrevious(newLink);
            newLink->setPrevious(temp);
        }
    }
    // Creates node from data and adds it after n
    void AddAfter(Node<T>* n, T data){
        Node <T>* newLink = new Node(data);
        newLink->setPrevious(n);
        if(n->getNext() == nullptr){
            n->setNext(newLink);
        }
        else{
            Node <T>* temp = n->getNext();
            n->setNext(newLink);
            temp->setPrevious(newLink);
            newLink->setNext(temp);
        }
    }
    // Removes the node at the front of the list and returns it data
    T RemoveFromFront(){
        T rv;
        if(head != nullptr){
            if(head->getNext() != nullptr){
                Node <T>* del = head;
                head = head->getNext();
                rv = del->getData();
                if(head != nullptr){
                    head->setPrevious(nullptr);
                }
                delete del;
                return rv;
            }
            else{
                head = nullptr;
            }
            return rv;
            //delete del;
        }
        else{
            throw invalid_argument("Remove from Front: No list");
        }
    }
    // Removes the node at the end of the list and returns its data
    T RemoveFromEnd(){
        if(head != nullptr){
            if(head->getNext() == nullptr){
                T rv = head->getData();
                head = nullptr;
                return rv;
            }
            else{
                Node <T>* temp = head;
                while(temp->getNext()->getNext() != nullptr){
                    temp = temp->getNext();
                }
                Node <T>* last = temp->getNext();
                T rv = last->getData();
                temp->setNext(nullptr);
                delete last;
                return rv;
            }
        }
        else{
            throw invalid_argument("Remove from End: No list");
        }
        
    }
    // Removes the first node with the given data
    void RemoveTheFirst(T data){
        Node <T>* temp = head;
        if(temp != nullptr){
            if(temp->getData() == data){
                head = head->getNext();
                head->setPrevious(nullptr);
                delete(temp);
            }
            else{
                while(temp->getNext() != nullptr){
                    if(temp->getNext()->getData() == data){
                        Node <T>* del = temp->getNext();
                        if(temp->getNext()->getNext() != nullptr){
                            temp->getNext()->getNext()->setPrevious(temp);
                            temp->setNext(temp->getNext()->getNext());
                        }
                        else{
                            temp->setNext(nullptr);
                        }
                        delete del;
                        break;
                    }
                    else{
                        temp = temp->getNext();
                    }

                }
            }
        }
        else{
            throw invalid_argument("RemoveFromFirst: No List");
        }
    }
    // Removes node given
    void RemoveNode(Node<T>* del){
        if(head == nullptr || del == nullptr){
            throw invalid_argument("Remove Node: No list or nothing to remove");
            return;
        }
        else if(head->getData() == del->getData()){
            Node <T>* del = head;
            head = head->getNext();
            head->setPrevious(nullptr);
            delete(del);
            return;
        }
        if(del->getNext() != nullptr){
            del->getNext()->setPrevious(del->getPrevious());
        }
        if(del->getPrevious() != nullptr){
            del->getPrevious()->setNext(del->getNext());
        }
        delete(del);
    }
    // Removes all nodes in the list with the matching data
    void RemoveAllOf(T data){
        Node <T>* temp = head;
        if(head == nullptr){
            throw invalid_argument("Nothing to remove");
        }
        else{
            while(head != nullptr && head->getData() == data){
                Node <T>* del = head;
                head = head->getNext();
                head->setPrevious(nullptr);
                delete(del);
            }
            if(head == nullptr){
                return;
            }
            temp = head;
            while(temp->getNext() != nullptr){
                while(temp->getNext()->getData() == data){
                    Node <T>* del = temp->getNext();
                    if(temp->getNext()->getNext() != nullptr){
                        temp->getNext()->getNext()->setPrevious(temp);
                        temp->setNext(temp->getNext()->getNext());
                    }
                    else{
                        temp->setNext(nullptr);
                        delete del;
                        return;
                    }
                    delete del;
                }
                temp = temp->getNext();
            }
        }
    }
    // Removes the node before n and returns its data
    T RemoveBefore(Node <T>* n){
        if(n->getPrevious() == nullptr){
            throw invalid_argument("Nothing to remove");
        }
        else{
            T rv;
            if(n->getPrevious()->getPrevious() == nullptr){
                rv = RemoveFromFront();
            }
            else{
                Node <T>* del = n->getPrevious();
                rv = del->getData();
                n->getPrevious()->getPrevious()->setNext(n);
                n->setPrevious(n->getPrevious()->getPrevious());
                delete(del);
            }
            return rv;
        }
    }
    // Removes the node after n and returns its data
    T RemoveAfter(Node <T>* n){
        if(n->getNext() == nullptr || n == nullptr){
            throw invalid_argument("Nothing to remove");
        }
        else{
            T rv;
            if(n->getNext()->getNext() == nullptr){
                rv = RemoveFromEnd();
            }
            else{
                Node <T>* del = n->getNext();
                rv = del->getData();
                n->getNext()->getNext()->setPrevious(n);
                n->setNext(n->getNext()->getNext());
                delete(del);
            }
            return rv;
        }
    }
    // Iterates through the list and checks if a node with the given data exists. Returns true if element is found and false otherwise
    bool ElementExists(T data){
        Node <T>* temp = head;
        while(temp != nullptr){
            if(temp->getData() == data){
                return true;
            }
            temp = temp->getNext();
        }
        return false;
    }
    // Finds the first instance of a node with given data and returns the node
    Node <T>* Find(T data){
        if(!ElementExists(data)){
            throw invalid_argument("Doesn't exist");
            return nullptr;
        }
        Node <T>* temp = head;
        while(temp != nullptr){
            if(temp->getData() == data){
                return temp;
            }
            temp = temp->getNext();
        }
        return nullptr;
    }
    // Finds the index of the first node with the given data
    int IndexOf(T data){
        Node <T>* temp = head;
        int count = 0;
        while(temp != nullptr){
            if(temp->getData() == data){
                return count;
            }
            temp = temp->getNext();
            count++;
        }
        return -1;
    }
    // Retrieves the data of the first element of the list
    T RetrieveFront(){
        if(head != nullptr){
            return head->getData();
        }
        throw out_of_range("Retrieve Front: No list");
    }
    // Retrieves the data of the last element of the list
    T RetrieveEnd(){
        if(head == nullptr){
            throw out_of_range("Retrieve End: No list");
        }
        Node <T>* temp = head;
        while(temp->getNext() != nullptr){
            temp = temp->getNext();
        }
        return temp->getData();
    }
    // Retrieves the element of the node at the index given
    T Retrieve(int index){
        if(index < 0){
            throw out_of_range("Index is negative");
        }
        int count = 0;
        Node <T>* temp = head;
        while(count < index && temp != nullptr){
            temp = temp->getNext();
            count++;
        }
        if(temp == NULL){
            throw out_of_range("Doesn't exist");
        }
        return temp->getData();
    }
    // Prints the list
    void PrintList(){
        if(head != nullptr){
            Node <T>* temp = head;
            while(temp->getNext() != nullptr){
                cout << temp->getData() << "=";
                temp = temp->getNext();
            }
            cout << temp->getData() << endl;
        }
    }
    // Empties the list
    void Empty(){
        if(head != nullptr){
            Node <T>* current = head;
            while(current != nullptr){
                Node <T>* del = current;
                current = current->getNext();
                delete del;
            }
            head = nullptr;
        }
        else{
            throw out_of_range("Empty: No list");
        }
    }
    // Finds the length of the list
    int Length(){
        int count = 0;
        Node <T>* temp = head;
        while(temp != nullptr){
            count++;
            temp = temp->getNext();
        }
        return count;
    }
    // Attributes
    private:
    Node <T>* head;
};
#endif 