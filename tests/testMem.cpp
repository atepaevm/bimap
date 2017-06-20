#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include "../src/Bimap.h"
/*
using namespace std;
bool testMem() {
    //true if all's OK
    bool ret=true;
    const int size=43394;
    const int countOfIter=1000;
    vector<pair<string,int>> db;
    vector<pair<string,int>> removed;
    unsigned int pseudoRandom=1812;
    ifstream fin("C:\\Users\\12\\ClionProjects\\BiMap\\tests\\db.txt");
    string s;
    int tmp;
    if(fin.is_open()){
        cout<<"OK!\n";
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
        cout<<i<<endl;
    }
return true;

}
*/
/*
     * Memory consumption is constant - even after 10000 iterations
     *
     *
     * */