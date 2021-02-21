#ifndef FUNC
#define FUNC
#include <condition_variable>
#include <time.h>
#include <iostream>
#include <mutex>
#include <queue>
#include <set>
#include <thread>
#include <vector>
#include <map>
#include <cstdint>
#include <condition_variable>
using namespace std;

class my_barrier
{
    public:
        my_barrier(int count)
            : thread_count(count)
            , counter(0)
            , waiting(0)
        {}

        void wait()
        {
            //fence mechanism
            unique_lock<mutex> lk(m);
            ++counter;
            ++waiting;
            cv.wait(lk, [&] {return counter >= thread_count; });
            cv.notify_one();
            --waiting;
            if (waiting == 0)
            {
                //reset barrier
                counter = 0;
            }
            lk.unlock();
        }

        void reduce() {
            --thread_count;
        }

    //private:
        mutex m;
        condition_variable cv;
        int counter;
        int waiting;
        int thread_count;
};

void bubbleSort(vector<int>& A);
void oddEvenBubbleSort(vector<int>& A);
void parallelOddEvenBubbleSort(vector<int>& A, my_barrier& barrier, int number_threads, int thead_number);
void fillVector(vector<int>& vec);
void printVector(const vector<int>& vec);
bool check(const vector<int>& A);
void mergeVector(vector<int>& A, int number_threads, int thead_number, int length, int remainder, int k);

#endif