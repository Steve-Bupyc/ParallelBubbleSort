#include "func.h"


int main(int argc, char* argv[]) {
    time_t timer;
    int length = 24;
    vector<int> values(length);
    const auto processor_count = std::thread::hardware_concurrency();
    vector<int> number_threads;
    if (processor_count == 8) {
        number_threads = {1,2,4,8,16};
    }
    else if (processor_count == 4) {
        number_threads = {1,2,4,8};
    }
    else {
        number_threads = { 1,2,4 };
    }
    
    fillVector(values);
   
    vector<int> values1(values);
    cout << "Simple Bubble Sort\n";
    //printVector(values1);
    timer = clock();
    bubbleSort(values1);
    cout << "exuction time:" << (double)(clock() - timer) / CLOCKS_PER_SEC << endl;
    cout << (check(values1) == 0 ? "false" : "true") << endl;
    //printVector(values1);
    (values1);

    cout << "\nOdd Even Bubble Sort\n";
    vector<int> values2(values);
    //printVector(values2);
    oddEvenBubbleSort(values2);
    cout << "exuction time:" << (double)(clock() - timer) / CLOCKS_PER_SEC << endl;
    cout << (check(values2) == 0 ? "false" : "true") << endl;
    //printVector(values2);

    cout << "\nParallel Odd Even Bubble Sort\n";
    vector<int> values3;
    timer = clock();
    for (int i = 0; i < number_threads.size(); i++) {
        if (length > number_threads[i]) {
            cout << "NUMBER THREADS = " << number_threads[i] << endl;
            vector<thread> threads;
            vector<int> values3(values);
            //printVector(values3);
            timer = clock();
            for (int j = 0; j < number_threads[i]; j++) {
                threads.push_back(thread(parallelOddEvenBubbleSort, ref(values3), number_threads[i], j));
            }
            for (auto& th : threads)
                th.join();
            //bubbleSort(values3);
            printVector(values3);
            //cout << (check(values3) == 0 ? "false" : "true") << endl;
            if (number_threads[i] != 1) {
                mergeVector(values3, number_threads[i], 0, 0, 0);
            }
            cout << "exuction time:" << (double)(clock() - timer) / CLOCKS_PER_SEC << endl;
            cout << (check(values3) == 0 ? "false" : "true") << endl;
            printVector(values3);
        }
    }
    system("PAUSE");
    return 0;
}