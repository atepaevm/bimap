//
// Created by 12 on 18.06.2017.
//

#ifndef BIMAP_BIMAP_H
#define BIMAP_BIMAP_H

#include "HashMap.h"
/*
 * I used linked list in this bimap realization. Why not open addressing?
 * We can use test.cpp in src/ to confirm that list's better.
 * Some statistics:
 * load factor: 0.5 average max: 5.851 middle: 1.27055
 * load factor: 1 average max: 7.773 middle: 1.58173
 * load factor: 1.5 average max: 9.362 middle: 1.93057
 * load factor: 2 average max: 10.829 middle: 2.3128
 * load factor: 2.5 average max: 12.238 middle: 2.72316
 * load factor: 3 average max: 13.725 middle: 3.15674
 * load factor: 3.5 average max: 15.218 middle: 3.60859
 * load factor: 4 average max: 16.757 middle: 4.07435
 * load factor: 4.5 average max: 18.344 middle: 4.55035
 * load factor: 5 average max: 20.026 middle: 5.0337
 * load factor: 5.5 average max: 21.543 middle: 5.52241
 * load factor: 6 average max: 23.178 middle: 6.01481
 * load factor: 6.5 average max: 24.869 middle: 6.50971
 * details in src/test.cpp
 * For example, if LF=0.5, then middle length of list is just 1.27 (in open addressing it's 2)
 */
template <class K,class V>
class Bimap {
private:
    HashMap<K,V>* first;
    HashMap<V,K>* second;
public:
    Bimap(){
        first=new HashMap<K,V>();
        second=new HashMap<V,K>();
    }
    Bimap(int capacity,float loadFactor){
        first=new HashMap<K,V>(capacity,loadFactor);
        second=new HashMap<V,K>(capacity,loadFactor);
    }
    void put(K &key,V &value){
        first->put(key,value);
        second->put(value,key);
    }
    Node<K,V>* getByFirst(K &key){
        return first->get(key);
    }
    Node<V,K>* getBySecond(V &value){
        return second->get(value);
    }
    void removeByFirst(K &key){
        if(!first->get(key))
            return;
        V value=first->get(key)->getValue();
        first->remove(key);
        second->remove(value);
    }
    void removeBySecond(V &value){
        if(!second->get(value))
            return;
        K key=second->get(value)->getValue();
        second->remove(value);
        first->remove(key);
    }
    void removeAll(){
        first->removeAll();
        second->removeAll();
    }
};


#endif //BIMAP_BIMAP_H
