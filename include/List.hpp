#pragma once
#include <cstddef>
#include <utility>
#include "Forward.hpp"

template <typename T>
class List {
    private:
        struct Node {
            T data;
            Node* next = nullptr;
            Node* prev = nullptr;
            Node() = default;

            template<typename ...Args>
            Node(Args&&... values)
            : data(forward<Args>(values)...), next{nullptr}, prev{nullptr} {}

            Node(const T& value)
            : data(value), next(nullptr), prev(nullptr) {}
            Node(T&& value)
            : data(std::move(value)), next(nullptr), prev(nullptr) {}
        };

        Node* head = nullptr;
        Node* tail = nullptr;
        size_t Size = 0;

    public: 
        List() = default;
        List(size_t size, const T& value = T());
        List(const List& other );
        List( List&& other );
        List(std::initializer_list<T> list);
        List& operator=(const List& other);
    	List& operator=(List&& other);
        List& operator=( std::initializer_list<T> ilist );
        ~List();

        void assign(size_t count, const T& value);
        void assign(std::initializer_list<T> ilist );
        T& front() ;
        const T& front() const;
        T& back() ;
        const T& back() const;

        bool empty() const;
        size_t size() const;
        size_t max_size() const ;
        void push_back( const T& value );
        void push_back( T&& value );
        void push_back();
        void push_front( const T& value );
        void push_front( T&& value );
        void pop_back();
        void pop_front();
        void insert( size_t position, const T& value );
        void insert( size_t position, T&& value );
        void insert( size_t position, size_t count, const T& value );
        void insert( size_t position, std::initializer_list<T> ilist );
        template<typename... Args>
        void emplace(const size_t position, Args&&... values);   
        template<typename... Args>
        void emplace_back(Args&&... values);
        template<typename... Args>
        void emplace_front(Args&&... values);
        void erase( size_t pos );
        void resize( size_t count );
        void resize( size_t count,const T& value);
        void swap( List& other );
        void unique();
        void merge( List& other ); 
        void clear();
        
           
};

template<typename T>
List<T>::List( size_t size, const T& value ): head(new Node(value)), Size{size} {

    --size;
    Node* tmp = head;
    for(size_t i{}; i < size; ++i) {
        tmp->next = new Node(value);
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    tail = tmp;
}

template<typename T>
List<T>::List(const List& other): head(nullptr), tail(nullptr), Size(0) {
    Node* tmp = other.head;

    while (tmp) {
        push_back(tmp->data);
        tmp = tmp->next;
    }
}

template<typename T>
List<T>::List( List&& other ): head(other.head), tail(other.tail), Size(other.Size)  {
    other.head = nullptr;
    other.tail = nullptr;
    other.Size = 0;
}

template<typename T>
List<T>::List(std::initializer_list<T> list): head{nullptr}, tail(nullptr), Size{0} {
	for( T val : list) {
		push_back(val);
	}
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if(this == &other) return *this;
    clear();
    
    Node* tmp = other.head;
    while (tmp) {
        push_back(tmp->data);
        tmp = tmp->next;
    }
	return *this;	
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other) {
	if(this == &other) return *this;
    clear();
	head = other.head;
    tail = other.tail;
    Size = other.Size;

    other.head = nullptr;
    other.tail = nullptr;
    other.Size= 0;
    
    return *this;
}

template<typename T>
List<T>& List<T>::operator=( std::initializer_list<T> ilist ){
    assign(ilist);
    return *this;
}

template<typename T>
List<T>::~List() { clear(); }

template<typename T>
void List<T>::clear() {
    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    Size = 0;
}


template<typename T>
void List<T>::assign(size_t count, const T& value) {
    clear();
    // Size = count;
    for(size_t i {}; i < count; ++i){
        push_back(value);
    }

}

template<typename T>
void List<T>::assign(std::initializer_list<T> ilist) {
    clear();
	for( T val : ilist) {
		push_back(val);
        
	}
}



template<typename T>
T& List<T>::front() { return head->data; }

template<typename T>
const T& List<T>::front() const { return head->data; }

template<typename T>
T& List<T>::back() {return tail->data; }

template<typename T>
const T& List<T>::back() const{ return tail->data; }

template<typename T>
bool List<T>::empty() const { return !head; }

template<typename T>
size_t List<T>::size() const { return Size; } 
template<typename T>
size_t List<T>::max_size() const {  return 768614336404564650; }

template<typename T>
void List<T>::push_back(){
    Node* node = new Node();

    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++Size;
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* node = new Node(value);

    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++Size;
}

template<typename T>
void List<T>::push_back( T&& value ) {
    Node* node = new Node(std::move(value));

    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++Size;
}

template<typename T>
void List<T>::insert(size_t position, const T& value) {
    if (position < 0 || position > Size) {
        throw std::out_of_range("Position out of range");
    }
    Node* node = new Node(value);
    if (position == 0) {
        node->next = head;
        if (head) {
            head->prev = node;
        }
        head = node;
        if (!tail) {
            tail = node;
        }
    } else if (position == Size) {
        tail->next = node;
        node->prev = tail;
        tail = node;
    } else {
        Node* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;
    }
    ++Size;
}

template<typename T>
void  List<T>::insert( size_t position, size_t count, const T& value ) {
    if (position < 0 || position > Size) {
        throw std::out_of_range("Position out of range");
    }

    for(size_t i{}; i < count ; ++i){
        insert(position, value);
    }
}

template<typename T>
void  List<T>::insert( size_t position,  std::initializer_list<T> ilist) {
    if (position < 0 || position > Size) {
        throw std::out_of_range("Position out of range");
    }
    
    for( T val : ilist) {
		insert( ++position, val);
	}

}

template<typename T>
void List<T>::erase( size_t position ){
    if ( position > Size) {
        std::cout<< "Position out of range" << std::endl;
        return;
    }
    std::cout<<"1"<<std::endl;
    if(position == 0){
        pop_front();
        std::cout<<"0"<<std::endl;
    } else if(position == Size){
        pop_back();
        std::cout<<"size"<<std::endl;
    }else {
    Node* current = head;
    for (size_t i = 0; i < position; ++i) {
        current = current->next;
    }
    current->prev->next = current->next;
    current =nullptr;
    }   
}

template<typename T>
void List<T>::push_front( const T& value ) {
    Node* node = new Node(value);
    node->next = head;
    head = node;
    ++Size;
}

template<typename T>
void List<T>::push_front( T&& value ) {
    Node* node = new Node(std::move(value));
    node->next = head;
    head = node;
    ++Size;
}

template<typename T>
void List<T>::pop_back() {
    Node* oldTail = tail;
    if(tail->prev){
        tail->prev->next =nullptr;
        tail = tail->prev;
        --Size;
    } else {
        head = nullptr;
        tail = nullptr;
        --Size;
    }
    delete oldTail;  
}    
template<typename T>
void List<T>::pop_front() {
    Node* oldhead = head;
    if(empty()) return;

    if(head->next){
        head->next->prev = nullptr;
        head = head->next;
        --Size;
    } else {
        head =nullptr;
        tail = nullptr;
        --Size;
    }
    
    delete oldhead;
}



template<typename T>
void List<T>::resize(size_t count) {
    if(count == Size ){ return;
    } else if(count < Size){
        for(size_t i{Size}; i > count; --i) {
            pop_back();
        }
    }else if(count > Size){
        for(size_t i{count}; i < Size; ++i){
            push_back();
        }
    }    
}
template<typename T>
void List<T>::resize(size_t count, const T& value){
    if (count == Size )  return;
    else if (count < Size) {
        for(size_t i{Size}; i > count; --i) {
            pop_back();
        }
    }else if(count > Size){
        for(size_t i{count}; i < Size; ++i){
            push_back(value);
        }
    }    
}

template<typename T>
void List<T>::swap(List<T>& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(Size, other.Size);
}


template<typename T>
void List<T>::unique() {
    if (!head) return; 
    Node* current = head;
    while (current && current->next) {
        if (current->data == current->next->data) {
            Node* duplicate = current->next;
            current->next = duplicate->next;

            if (duplicate->next)
                duplicate->next->prev = current;
            else
                tail = current;   
            delete duplicate;
            --Size;
        }
        else {
            current = current->next;
        }
    }

}



template<typename T>
void List<T>::merge(List& other) {

    if (this == &other) return;
    Node* r = head;
    Node* l = other.head;

    List result;   

    while (r && l) {
        if (r->data <= l->data) {
            result.push_back(r->data);
            r = r->next;
        } else {
            result.push_back(l->data);
            l = l->next;
        }
    }
    while (r) {
        result.push_back(r->data);
        r = r->next;
    }

    
    while (l) {
        result.push_back(l->data);
        l = l->next;
    clear();
    other.clear();
    *this = std::move(result);
    }
    
}
template<typename T>
template<typename... Args>  
void List<T>::emplace(const size_t position, Args&&... values){
    if (position > Size) {
        throw std::out_of_range("Position out of range");
    }
    
    Node* node = new Node(forward<Args>(values)...);

    if (position == 0) {
        emplace_front(forward<Args>(values)...);
    } else if (position == Size) {
        emplace_back(forward<Args>(values)...);
    } else {
        Node* current = head;
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;
    }
    ++Size;
}


template<typename T>
template<typename... Args>
void List<T>::emplace_back(Args&&... values){
    Node* node = new Node(forward<Args>(values)...);

    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++Size;
}


template<typename T>
template<typename... Args>
void List<T>::emplace_front(Args&&... values){
    Node* node = new Node(forward<Args>(values)...);
    node->next = head;
    head = node;
    ++Size;
}



template<typename T>
void  List<T>::insert( size_t  position, T&& value ) {
    if ( position > Size) {
        throw std::out_of_range("Position out of range");
    }

    Node* node = new Node(std::move(value));

    if (position == 0) {
        push_front(value);
    } else if (position == Size) {
        push_back(value);
    } else {
        Node* current = head;
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;
    }
    ++Size;
}
