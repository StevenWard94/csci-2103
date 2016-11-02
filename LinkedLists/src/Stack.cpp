/***********************************************************************************//**
 * Author:       Steven Ward <stevenward94@gmail.com>
 * File:         csci-2103/LinkedLists/src/Stack.cpp
 * URL:          https://github.com/StevenWard94/csci-2103
 * Last Change:  2016 Oct 26
 ***********************************************************************************/

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include <stdlib.h>

template<typename T>
class Stack {
    typedef T value_t;
    struct Node;

  public:
    value_t&& top( ) const;
    inline size_t size( ) const { return size_; }

    inline bool isEmpty( ) const { return static_cast<bool>(top_); }
    inline bool isFull( ) const { return false; }

    Stack& push(value_t const& item);
    Stack& push(value_t&& item);

    Stack& pop( );
    value_t&& pop_get( );

    Stack& clear( );
    Stack& clone( ) const;

    Stack& operator= (Stack const& rhs);
    Stack& operator= (Stack&& rhs);

    inline Stack( ) : top_{ nullptr }, size_(0) { }
    inline Stack(Node const* top, size_t size)
            : top_{ new Node(*top) }, size_(size) { }
    Stack(Stack const& other);
    Stack(Stack&& other);

    virtual ~Stack( );

  private:
    Node* top_;
    size_t size_;

    struct Node {
        value_t data;
        Node* next;

        Node( ) : data{ value_t() }, next{ nullptr } { }
        Node(value_t const& val, Node const* node = nullptr)
                : data{ val }, next{ node } { }

        Node(value_t&& val, Node const* node = nullptr)
                : data{ std::move(val) }, next{ node } { }

        Node(Node const& other)
                : data{ other.data }, next{ other.next } { }

        Node(Node&& other)
                : data{ std::move(other.data) }, next{ std::move(other.next) }
        { other.next = nullptr; }

        Node& operator= (Node const& rhs) = default;
        Node& operator= (Node&& rhs) = default;
    };
};


template<typename T>
inline T&& Stack<T>::top( ) const {
    if (this->isEmpty()) {
        throw std::domain_error("Stack<T>::top() : cannot access top of empty stack");
    }
    else {
        return std::forward<T>(this->top_->data);
    }
}


template<typename T>
inline Stack<T>& Stack<T>::push(T const& item) {
    Node* const stacked = new Node(item, this->top_);
    this->top_ = stacked;
    this->size_++;
    return *this;
}


template<typename T>
inline Stack<T>& Stack<T>::push(T&& item) {
    Node* const stacked = new Node(std::forward<T>(item), this->top_);
    this->top_ = stacked;
    this->size_++;
    return *this;
}


template<typename T>
inline Stack<T>& Stack<T>::pop( ) {
    if (!this->isEmpty()) {
        Node* const tmp = this->top_;
        this->top_ = tmp->next;
        this->size_--;
        delete tmp;
        return *this;
    }
    else {
        throw std::domain_error("Stack<T>::pop() : cannot remove element from empty stack");
    }
}


template<typename T>
inline T&& Stack<T>::pop_get( ) {
    if (!this->isEmpty()) {
        T* popped = new T(std::move(this->top_->data));
        this->pop;
        return std::forward<T>(*popped);
    }
    else {
        throw std::domain_error("Stack<T>::pop_get() : cannot remove element from empty stack");
    }
}


template<typename T>
inline Stack<T>& Stack<T>::clear( ) {
    Node* destructor = this->top_;
    while (destructor != nullptr) {
        Node* const tmp = destructor;
        destructor = tmp->next;
        delete tmp;
        tmp = nullptr;
    }
    this->top_ = nullptr;
    this->size_ = 0;
    return *this;
}


template<typename T>
inline Stack<T>& Stack<T>::clone( ) const {
    return new Stack<T>(*this);
}


template<typename T>
inline Stack<T>& Stack<T>::operator= (Stack<T> const& rhs) {
    if (this != &rhs) {

        if (!this->isEmpty()) {
            this->clear();
        }

        Node const* inputIt = rhs.top_;
        Node* outputIt = this->top_;

        while (inputIt != nullptr) {
            outputIt = new Node(inputIt->data);
            this->size_++;
            inputIt = inputIt->next;
            outputIt = outputIt->next;
        }
    }
    return *this;
}


template<typename T>
inline Stack<T>& Stack<T>::operator= (Stack<T>&& rhs) {
    if (this != &rhs) {

        if (!this->isEmpty()) {
            this->clear();
        }

        Node* inputIt = rhs.top_;
        Node* outputIt = this->top_;

        while (inputIt != nullptr) {
            outputIt = new Node(std::forward<T>(inputIt->data));
            this->size_++;
            inputIt = inputIt->next;
            outputIt = outputIt->next;
        }
    }
    return *this;
}


template<typename T>
inline Stack<T>::Stack(Stack<T> const& other) : Stack() {
    if (!other.isEmpty()) {
        Node const* inputIt = other.top_;
        Node* outputIt = this->top_;

        while (inputIt != nullptr) {
            outputIt = new Node(inputIt->data);
            this->size_++;
            inputIt = inputIt->next;
            outputIt = outputIt->next;
        }
    }
}


template<typename T>
inline Stack<T>::Stack(Stack<T>&& other) : Stack() {
    if (!other.isEmpty()) {
        Node* inputIt = other.top_;
        Node* outputIt = this->top_;

        while (inputIt != nullptr) {
            outputIt = new Node(std::forward<T>(inputIt->data));
            this->size_++;
            inputIt = inputIt->next;
            outputIt = outputIt->next;
        }
    }
}


template<typename T>
inline Stack<T>::~Stack<T>( ) {
    this->clear();
}
