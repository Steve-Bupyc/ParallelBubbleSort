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
using namespace std;

const int length = 100;

void bubbleSort(vector<int>& A);
void oddEvenBubbleSort(vector<int>& A);
void parallelOddEvenBubbleSort(vector<int>& A);
void fillVector(vector<int>& vec);
void printVector(const vector<int>& vec);

#endif