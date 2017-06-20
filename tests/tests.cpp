#include <iostream>
#include "tests.h"
using namespace std;

int main(){
    /**
     * this function tests bimap with using of database with 43k nodes
     * There are some tests of creation, getting, setting and removing
     */

    cout<<"test of count: ";
    if(testCount()){
        cout<<"yep"<<endl;
    }
    else{
        cout<<"nope"<<endl;
    }
    /**
     * It's similar test, but with class Person's using
     */

    cout<<"test of classes: ";
    if(testClasses()){
        cout<<"yep"<<endl;
    }
    else{
        cout<<"nope"<<endl;
    }
    /**
     * 100 iterations of filling and removing of the bimap
     * profiler said, that all's OK
     */

    cout<<"test of memory: ";
    if(testMem()){
        cout<<"yep"<<endl;
    }
    else{
        cout<<"nope"<<endl;
    }
}

