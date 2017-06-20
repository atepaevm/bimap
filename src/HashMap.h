#ifndef BIMAP_HASHMAP_H
#define BIMAP_HASHMAP_H

#include "Node.h"

using namespace std;
template <class K,class V>
    class HashMap {
    private:
        //The default initial capacity
        constexpr static int DEFAULT_INITIAL_CAPACITY = 16;
        //The default maximum capacity
        constexpr static int MAXIMUM_CAPACITY = 1 << 20;
        //The load factor used when none specified in constructor
        constexpr static float DEFAULT_LOAD_FACTOR = 0.5f;

        //The current capacity of hashmap
        int capacity;
        //The current count of hashmap
        int count;
        //load factor of this hashmap
        float loadFactor;
        //The next count value at which to recount (capacity * load factor)
        int limit;
        Node<K,V> **table;
    public:
        HashMap() {
            table=new Node<K,V> *[DEFAULT_INITIAL_CAPACITY];
            this->count=0;
            this->loadFactor=DEFAULT_LOAD_FACTOR;
            this->capacity==DEFAULT_INITIAL_CAPACITY;
            this->limit=capacity*loadFactor;
            for(int i=0;i<capacity;i++){
                table[i]=NULL;
            }
        }
        HashMap(int capacity,float loadFactor) {
            if (capacity < 0.25 || capacity > 1 << 20 || loadFactor < 0 || loadFactor*capacity<1) {
                capacity=16;
                loadFactor=0.75;
            }

                table = new Node<K, V> *[capacity];
                this->count = 0;
                this->loadFactor = loadFactor;
                this->capacity = capacity;
                this->limit = capacity * loadFactor;
                for(int i=0;i<capacity;i++){
                    table[i]=NULL;
                }

        }
        ~HashMap(){
            for(int i=0;i<this->capacity;i++){
                Node<K,V>* tmp=table[i];
                while(tmp!=NULL){
                    Node<K,V>* cur=tmp->getNext();
                    delete tmp;
                    tmp=cur;
                }
                table[i]=NULL;
            }
        }
        void showAll(){
            Node<K,V>* entry;
            for(int i=0;i<this->capacity;i++){
                if(table[i]==NULL){
                    cout<<i<<") NULL\n";
                }
                else{
                    cout<<i<<")\n";
                    entry=table[i];
                    while(entry){
                        cout<<"\tkey: "<<entry->getKey()<<" value: "<<entry->getValue()<<endl;
                        entry=entry->getNext();
                    }
                }
            }
        }
        /*
         * when limit exceeded, it's necessary to recount all hashes and make new table
         * old pointers' table will be removed
         */
        void rehash(){
            int newCapacity=MAXIMUM_CAPACITY>capacity<<1?this->capacity<<1:MAXIMUM_CAPACITY; /* *2 */
            Node<K,V>** newTable=new Node<K, V> *[newCapacity];
            for(int i=0;i<newCapacity;i++){
                newTable[i]=NULL;
            }
            this->count=0;
            for(int i=0;i<this->capacity;i++){
                Node<K,V>* tmp=table[i];
                while(tmp){
                    putInTable(tmp->getKey(),tmp->getValue(),newTable,newCapacity);
                    tmp=tmp->getNext();
                }
            }
            //cout<<"!!!\n";
           //showAll();
            //remove just pointers, not data
            delete[] table;
            table=newTable;
            this->capacity=newCapacity;
            this->limit=newCapacity*this->loadFactor;
            /*cout<<"New size is "<<capacity<<endl;*/
            //showAll();
        }
        /*
         * &table - table that's used to put node
         * @capacity - capacity that's used to count hash
         */
        void putInTable(const K &key, const V &value,Node<K,V>** table,int capacity){
            std::hash<K> hash_func;
            unsigned long hash=hash_func(key);
            Node<K,V>* entry=table[hash%capacity];
            Node<K,V>* prev=NULL;
            while(entry!=NULL&&entry->getKey()!=key){
                prev=entry;
                entry=entry->getNext();
            }
            //table hasn't this value
            if(entry==NULL){
                entry=new Node<K,V>(key,value,prev);
                if(prev==NULL){
                    table[hash%capacity]=entry;
                    /*prev->next=entry;*/
                }
                else{
                    prev->setNext(entry);
                }
                count++;

            }
                //table has this value, value will be updated
            else{
                entry->setValue(value);
            }
        }
        void put (const K &key, const V &value){
            if(this->limit==count){
                rehash();
            }
            putInTable(key,value,table,this->capacity);
            //showAll();
        }
        Node<K,V>* get(const K &key){
            std::hash<K> hash_func;
            unsigned long hash=hash_func(key);
            Node<K,V>* entry=table[hash%this->capacity];
            while(entry){
                if(entry->getKey()==key){
                    return new Node<K,V>(key,entry->getValue());
                }
                entry=entry->getNext();
            }
            return NULL;
        }
        void remove(const K &key){
            std::hash<K> hash_func;
            unsigned long hash=hash_func(key);
            Node<K,V>* entry=table[hash%this->capacity];
            while(entry&&entry->getKey()!=key){
                entry=entry->getNext();
            }
            //table hasn't this key
            if(!entry){
                return;
            }
            //node's in the middle of list
            if(entry->getNext()&&entry->getPrev()){
                entry->getPrev()->setNext(entry->getNext());
                entry->getNext()->setPrev(entry->getPrev());
                delete entry;
                count--;
                return;
            }
            //node's in the end of list
            if(!entry->getNext()&&entry->getPrev()){
                entry->getPrev()->setNext(NULL);
                delete entry;
                count--;
                return;
            }
            //node's in the begin of list
            if(entry->getNext()&&!entry->getPrev()){
                entry->getNext()->setPrev(NULL);
                table[hash%this->capacity]=entry->getNext();
                delete entry;
                count--;
                return;
            }
            //node's only one
            delete entry;
            table[hash%this->capacity]=NULL;
            count--;
        }
        void removeAll(){
            Node<K,V>* entry;
            Node<K,V>* tmp;
            for(int i=0;i<this->capacity;i++){
                entry=table[i];
                    while(entry){
                        tmp=entry->getNext();
                        delete entry;
                        entry=tmp;
                    }
                }
            delete[] table;
            //init table by defualt values
            table=new Node<K,V> *[DEFAULT_INITIAL_CAPACITY];
            this->count=0;
            this->loadFactor=DEFAULT_LOAD_FACTOR;
            this->capacity==DEFAULT_INITIAL_CAPACITY;
            this->limit=capacity*loadFactor;
            for(int i=0;i<capacity;i++){
                table[i]=NULL;
            }
            }
    };

#endif //BIMAP_HASHMAP_H
