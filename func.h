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
using namespace std;

void bubbleSort(vector<int>& A);
void oddEvenBubbleSort(vector<int>& A);
void parallelOddEvenBubbleSort(vector<int>& A, int number_threads, int thead_number);
void fillVector(vector<int>& vec);
void printVector(const vector<int>& vec);
bool check(const vector<int>& A);
void mergeVector(vector<int>& A, int number_threads, int thead_number, int length, int remainder, int k);
void sortsort(vector<int>& A, int number_threads);

#endif