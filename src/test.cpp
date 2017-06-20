/*
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;
int main() {
    int size=100000;
    unsigned long tmp=2<<10-1;

    float loadFactor=0.5;
    //
    for(int k=0;k<20;k++) {
        int sum=0;
        int max = 0;
        int zero=0;
        float mid=0;
        //каждый эксперимент повторяем 1000 раз, берём среднее
        for (int j = 0; j < 1000; j++) {
            /*
            С помощью "рандома" сымитируем заполнение хэш-таблицы. numbers[i] хранит длину цепочки от хэша i
            */
            /*
            int numbers[size] = {0};
            for (int i = 0; i < loadFactor * size; i++) {
                tmp = tmp * 13 + 37;
                numbers[tmp % size]++;
            }
            max = 0;
            zero=0;
            for (int i = 0; i < size; i++) {
                if (numbers[i] > max) {
                    max = numbers[i];
                }
                if(numbers[i]==0){
                    zero++;
                }
            }
             //в средней длине цепочке не будем учитывать нулевые ячейки.
             //Это логично - вряд ли мы будем искать запись, которой нет
            mid+=size*loadFactor/(size-zero);
            sum += max;
        }
        cout << "load factor: "<<loadFactor<<" average max: "<<1.0 * sum / 1000<<" middle: "<<mid/1000<<endl;
        loadFactor+=0.5;
    }

    return 0;
}*/
/*
 * С увеличением load factor средняя длина цепочки растёт линейно - даже при плохой хэш-функции
 * В отличие от открытой адресации, где длина пропорциональна 1/(1-alpha)
 * При этом средний максимум растёт явно быстрее - при LF=8 average max=30
 *
 */