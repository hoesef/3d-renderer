#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <iostream>

template <typename T> class Node {

    private:
        T m_data;
        Node<T>* m_next{nullptr};
        Node<T>* m_prev{nullptr};

    public:
        Node() = delete;
        Node(const Node<T>& other) = delete;
        Node(Node<T>&& other) = delete;
        Node<T>& operator=(const Node<T>& other) = delete;
        Node<T>& operator=(Node<T>&& other) = delete;

        // Constructors
        Node(const T& data) : m_data(data) {}                                   // Data only
        Node(const T& data, Node<T>* next, Node<T>* prev)                       // Data, nextm and previous
            : m_data(std::move(data)), m_next(next), m_prev(prev) {}
        Node(T&& data) : m_data(std::move(data)) {}                             // Data only (rvalue ref)
        Node(T&& data, Node<T>* next, Node<T>* prev)                            // Data (rvalue ref), next, and previous
            : m_data(std::move(data)), m_next(next), m_prev(prev) {}

        // Getters
        T& data() { return m_data; }
        Node<T>* next() { return m_next; }
        Node<T>* prev() { return m_prev; }

        // Setters
        void setNext(Node<T>* next) { m_next = next; }
        void setPrev(Node<T>* prev) { m_prev = prev; }

        ~Node() = default;
};

template <typename T> class Stack {

    private:
        Node<T>* m_head{nullptr};

    public:
        Stack() = default;
        Stack(const Stack& other) = delete;
        Stack(Stack&& other) = delete;
        Stack& operator=(const Stack& other) = delete;
        Stack& operator=(Stack&& other) = delete;

        // Add an element to the front of the stack
        void add(const T& data) {
            Node<T>* node = new Node<T>(data, m_head, nullptr);
            if (m_head) {
                m_head->setPrev(node);
            }
            m_head = node;
        }
        // Add an element to the front of the stack
        void add(T&& data) {
            Node<T>* node = new Node<T>(std::move(data), m_head, nullptr);
            if (m_head) {
                m_head->setPrev(node);
            }
            m_head = node;
        }
        // Pop the head off of the stack
        T pop() {
            if (!m_head) { throw std::runtime_error("Pop from an empty list.\n"); }
            T data = std::move(m_head->data());
            Node<T>* head = m_head->next();
            delete m_head;
            m_head = head;
            if (m_head)  { m_head->setPrev(nullptr); }
            return data;         
        }
        // friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
        //     os << "[";
        //     Node<T>* head = stack.m_head;
        //     while (head != nullptr) {
        //         os << head->data();
        //         head = head->next();
        //         if (head) { os << ", "; }
        //     }
        //     os << "]\n";
        //     return os;
        // }
        
        // Destructor
        ~Stack() {
            while (m_head != nullptr) {
                Node<T>* head = m_head->next();
                delete m_head;
                m_head = head;
            }
        }
};

#endif