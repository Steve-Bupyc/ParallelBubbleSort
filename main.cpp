#include "func.h"

int main(int argc, char* argv[]) {
    time_t timer;
    vector<int> values(length);
    fillVector(values);
    //printVector(values);
   
    vector<int> values1(values);
    cout << "Simple Bubble Sort\n";
    //printVector(values1);
    timer = clock();
    bubbleSort(values1);
    cout << "exuction time:" << (double)(clock() - timer) / CLOCKS_PER_SEC << endl;
    //printVector(values1);
    (values1);

    cout << "\nOdd Even Bubble Sort\n";
    vector<int> values2(values);
    //printVector(values2);
    timer = clock();
    oddEvenBubbleSort(values2);
    cout << "exuction time:" << (double)(clock() - timer) / CLOCKS_PER_SEC << endl;
    //printVector(values2);


    cout << "\nParallel Odd Even Bubble Sort\n";
    vector<int> values3(values);
    //printVector(values3);
    timer = clock();
    parallelOddEvenBubbleSort(values3);
    cout << "exuction time:" << (double)(clock() - timer) / CLOCKS_PER_SEC << endl;
    //printVector(values3);
}