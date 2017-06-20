//
// Created by 12 on 19.06.2017.
//

#ifndef BIMAP_TESTS_H
#define BIMAP_TESTS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include "../src/Bimap.h"
bool static testCount() {
    //true if all's OK
    bool ret=true;
    //db's size
    const int size = 43394;
    //program maping of db
    vector<pair<string, int>> db;
    //removed nodes
    vector<pair<string, int>> removed;
    unsigned int pseudoRandom = 1;
    ifstream fin("C:\\Users\\12\\ClionProjects\\BiMap\\tests\\db.txt");
    string s;
    int cur;
    if (fin.is_open()) {
        //cout << "OK!\n";
    }
    Bimap<string, int> map(128, 128);
    for (int i = 0; i < size; i++) {
        fin >> cur;
        fin >> s;
        db.push_back({s, cur});
        map.put(s, cur);
    }
    //yes, it's no true random, but why not?
    while (pseudoRandom < size) {
        removed.push_back(db[pseudoRandom]);
        db.erase(db.begin() + pseudoRandom);
        pseudoRandom += 31;
    }
    //checking of existing nodes
    for (int i = 0; i < db.size(); i++) {
        Node<string, int> *tmp = map.getByFirst(db[i].first);
        Node<int, string> *cur = map.getBySecond(db[i].second);
        if (tmp) {
            if (tmp->getValue() != db[i].second) {
                cout << "mismatch for key " << db[i].first << " and value " << db[i].second << endl;
                ret=false;
            }
        }
        else {
            cout << "Error: key \"" << db[i].first << "\" not found" << endl;
            ret=false;
        }
        if (cur) {
            if (cur->getValue() != db[i].first) {
                cout << "mismatch for key " << db[i].second << " and value " << db[i].first << endl;
                ret=false;
            }
        }
        else {
            cout << "Error: key \"" << db[i].second << "\" not found" << endl;
            ret=false;
        }

    }
    //remove pseudorandom nodes
    for (int i = 0; i < removed.size(); i++) {
        if (i % 2 == 0) {
            map.removeByFirst(removed[i].first);
        }
        else {
            map.removeBySecond(removed[i].second);
        }
    }
    //checking of removed nodes
    for (int i = 0; i < removed.size(); i++) {
        Node<string, int> *tmp = map.getByFirst(removed[i].first);
        Node<int, string> *cur = map.getBySecond(removed[i].second);
        if (tmp) {
            cout << i + 1 << ") Error: key \"" << removed[i].first << "\" doesn't exist, but was found" << endl;
            ret=false;
        }
        if (cur) {
            cout << i + 1 << ") !!!Error: key \"" << removed[i].second << "\" doesn't exist, but was found" << endl;
            ret=false;
        }
    }
    return ret;
}
class Person{
public:
    string city;
    string surname;
    int id;
    float money;
    Person(string city,string surname, int id,float money):city(city),surname(surname),id(id),money(money){}
    bool operator!=(Person person) const{
        return !((this->city==person.city)&&
                 (this->surname==person.surname)&&
                 (this->id==person.id)&&
                 (abs(this->money-person.money)<0.01));
    }
    bool operator==(const Person person) const{
        return (this->city==person.city)&&
               (this->surname==person.surname)&&
               (this->id==person.id)&&
               (abs(this->money-person.money)<0.01);
    }
};
namespace std{
    template<>
    class hash<Person>{
    public:
        size_t operator()(const Person &person) const{
            return std::hash<std::string>()(person.city)^
                   std::hash<std::string>()(person.surname)^
                   std::hash<int>()(person.id)^
                   std::hash<float>()(person.money);
        }
    };
}

bool testClasses() {
    //true if all's OK
    bool ret=true;
    vector<pair<int,Person>> persons;
    vector<pair<int,Person>> removed;
    ifstream fin("C:\\Users\\12\\ClionProjects\\BiMap\\tests\\persons.txt");
    int size=4365;
    int pseudoRandom=1;
    string city;
    string surname;
    int id;
    float money;
    if(fin.is_open()){
        //cout<<"OK!\n";
    }
    Person person("default","default",-1,-1);
    Bimap<int,Person> map(16,0.5);
    for(int i=0;i<size;i++){
        fin>>person.city;
        fin>>person.surname;
        fin>>person.id;
        fin>>person.money;
        persons.push_back({person.id,person});
        map.put(person.id,person);
    }
    while(pseudoRandom<size){
        removed.push_back(persons[pseudoRandom]);
        persons.erase(persons.begin()+pseudoRandom);
        pseudoRandom+=31;
    }
//checking of existing nodes
    for(int i=0;i<persons.size();i++){
        Node<int,Person>* tmp=map.getByFirst(persons[i].first);
        Node<Person,int>* cur=map.getBySecond(persons[i].second);
        if(tmp){
            if(tmp->getValue()!=persons[i].second){
                cout<<"mismatch for key "<<persons[i].first<<" and value "<<persons[i].second.city<<endl;
                ret=false;
            }
        }
        else{
            cout<<"Error: key \""<<persons[i].first<<"\" not found"<<endl;
            ret=false;
        }
        if(cur){
            if(cur->getValue()!=persons[i].first){
                cout<<"mismatch for key "<<persons[i].second.city<<" and value "<<persons[i].first<<endl;
                ret=false;
            }
        }
        else{
            cout<<"Error: key \""<<persons[i].second.city<<"\" not found"<<endl;
            ret=false;
        }

    }
    //remove pseudorandom nodes
    for(int i=0;i<removed.size();i++){
        if(i%2==0){
            map.removeByFirst(removed[i].first);
        }
        else{
            map.removeBySecond(removed[i].second);
        }
    }
    //checking of removed nodes
    for(int i=0;i<removed.size();i++){
        Node<int,Person>* tmp=map.getByFirst(removed[i].first);
        Node<Person,int>* cur=map.getBySecond(removed[i].second);
        if(tmp){
            cout<<i+1<<") Error: key \""<<removed[i].first<<"\" doesn't exist, but was found"<<endl;
            ret=false;
        }
        if(cur){
            cout<<i+1<<") !!!Error: key \""<<removed[i].second.city<<"\" doesn't exist, but was found"<<endl;
            ret=false;
        }
    }
    return ret;
}

bool testMem() {
    //true if all's OK
    bool ret=true;
    const int size=43394;
    const int countOfIter=100;
    vector<pair<string,int>> db;
    vector<pair<string,int>> removed;
    unsigned int pseudoRandom=1812;
    ifstream fin("C:\\Users\\12\\ClionProjects\\BiMap\\tests\\db.txt");
    string s;
    int tmp;
    if(fin.is_open()){
        //cout<<"OK!\n";
    }

    Bimap<string,int> map(16,0.2);
    for(int i=0;i<size;i++){
        fin>>tmp;
        fin>>s;
        db.push_back({s,tmp});
    }
    for(int i=0;i<countOfIter;i++){
        for(int j=0;j<db.size();j++){
            map.put(db[i].first,db[i].second);
        }
        map.removeAll();
        //cout<<i<<endl;
    }
    return true;

}

/*
     * Memory consumption is constant - even after 10000 iterations
     * But it's so long!
     *
     * */

#endif //BIMAP_TESTS_H
