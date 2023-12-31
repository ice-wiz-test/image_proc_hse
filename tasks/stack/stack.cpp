#include "stack.h"

Node::Node(int32_t value, Node* prev) : value(value), previous(prev) {
}

Stack::Stack() {
    size_ = 0;
    head_ = nullptr;
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    size_++;
}

void Stack::Pop() {
    if (head_ == nullptr) {
        throw "Stack is empty!";
    }
    Node* next_head = head_->previous;
    delete head_;
    head_ = next_head;
    size_--;
}

int32_t Stack::Top() const {
    if (head_ == nullptr) {
        throw "Stack is empty!";
    }
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (head_ != nullptr) {
        Node* next_head = head_->previous;
        delete head_;
        size_--;
        head_ = next_head;
    }
}

bool Stack::Empty() const {
    return size_ == 0;
}

Stack::~Stack() {
    Clear();
}