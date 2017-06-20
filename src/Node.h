#ifndef BIMAP_NODE_H
#define BIMAP_NODE_H
#include <iostream>
template<class K,class V>
    class Node{
        //TODO: disallow copy and assignment
    public:
        Node(const K &key,const V &value,Node* &prev):key(key),value(value),next(NULL),prev(prev){}
        Node():key(NULL),value(NULL),next(NULL),prev(NULL){}
        Node(const K &key,const V &value):key(key),value(value),next(NULL),prev(NULL){}
        //all getters:
        K getKey() const {
            return this->key;
        }
        V getValue() const {
            return this->value;
        }
        Node* getNext() const {
            return this->next;
        }
        Node* getPrev() const {
            return this->prev;
        }
        void setValue(const V &value){
            this->value=value;
        }
        void setNext(const Node* next){
            this->next=(Node*)next;
        }
        void setPrev(const Node* prev){
            this->prev= (Node *) prev;
        }
        /*
         * we will use linked list, so we need pointers to next and previous values
         */
    private:
        K key;
        V value;
        Node* next;
        Node* prev;
    };
#endif //BIMAP_NODE_H
