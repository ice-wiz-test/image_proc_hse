#include <queue.h>
#include <iostream>

Node::Node(int32_t value, Node* next) : value(value), next(next) {
}

Queue::Queue() {
    size_ = 0;
    front_ = tail_ = nullptr;
}

void Queue::Push(int32_t value) {
    if (tail_ != nullptr) {
        tail_->next = new Node(value, nullptr);
        tail_ = tail_->next;
    } else {
        tail_ = new Node(value, nullptr);
        front_ = tail_;
    }
    size_++;
}

void Queue::Pop() {
    if (size_ == 0) {
        throw("Queue is empty!");
        return;
    }
    Node* s = front_;
    if (front_ != tail_) {
        front_ = front_->next;
        delete s;
    } else {
        front_ = front_->next;
        tail_ = front_;
        delete s;
    }
    size_--;
}

int32_t Queue::Front() const {
    if (size_ == 0) {
        throw("Queue is empty");
    }
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (front_ != nullptr) {
        Node* next_t = front_->next;
        delete front_;
        front_ = next_t;
    }
    tail_ = nullptr;
    size_ = 0;
}

bool Queue::Empty() const {
    return size_ == 0;
}

Queue::~Queue() {
    Clear();
}