#include "func.h"

std::mutex g_lock;

void compareExchange(vector<int>& A, int i, int j) {
    if (A[i] > A[j]) 
    {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}

// Последовательный алгоритм пузырьковой сортировки
void bubbleSort(vector<int>& A)
{
    for (int i = 0; i < (A.size() - 1); i++)
    {
        for (int j = 0; j < (A.size() - i - 1); j++)
        {
            compareExchange(A, j, j + 1);
        }
    }
}

// Последовательный алгоритм чет-нечетной перестановки
void oddEvenBubbleSort(vector<int>& A) 
{
    for (int i = 0; i < A.size(); i++) {
        for (int j = (i % 2) ? 0 : 1; (j + 1) < A.size(); j += 2) {
            compareExchange(A, j, j+1);
        }
    }
}

// Параллельный алгоритм чет-нечетной перестановки
void parallelOddEvenBubbleSort(vector<int>& A, my_barrier& barrier, int number_threads, int thead_number)
{
    
    static std::atomic <int> flags[32]{};
    if (thead_number == 0) {
        for (int i = 0; i < 32; i++) {
            flags[i] = 0;
        }
    }
    int length = A.size() / number_threads;
	int start = thead_number * length;
    int remainder = (number_threads-1 == thead_number) ? (A.size() % number_threads) : 0;
    if (number_threads == 1) {
        oddEvenBubbleSort(A);
    }
    else {
        for (int i = start; i < start + length + remainder; i++)
        {
            for (int j = i + 1; j < start + length + remainder; j++)
            {
                compareExchange(A, i, j);
            }
        }
        auto log2 = [](unsigned long long x) {x--; int i = 0;  while (x) { x >>= 1; i++; } return i; };
        for (int k = 1; k <= log2(number_threads); k++) {
            //barier
            g_lock.lock();
            //cout << "counter >= thread_count =>" << barrier.counter << ">=" << barrier.thread_count << endl;
            cout << "N=" << thead_number << " wait." << endl;
            g_lock.unlock();
            barrier.wait();
            /*g_lock.lock();
            cout << "N=" << thead_number << ", k=" << k << endl;
            g_lock.unlock();*/
            if (thead_number % (1<<k) != 0) {
                barrier.reduce();
                flags[thead_number] = k;
                g_lock.lock();
                cout << "k=" << k << ", N=" << thead_number << " return." << endl;
                g_lock.unlock();
                return;                
            }
            //g_lock.lock();
            //cout << "N=" << thead_number << endl;
            //cout << "(thead_number + (1 << (k - 1)))= (" << thead_number << "+ ( 1 << " << k-1 << " ) = " << (1 << (k - 1)) << endl;
            //g_lock.unlock();
            while (flags[thead_number + (1 << (k - 1))] < (k)) {}
            g_lock.lock();
            cout << "k=" << k << ", Before Merge N=" << thead_number;
            printVector(A);
            g_lock.unlock();
            mergeVector(A, number_threads, thead_number, length, remainder, k);
            g_lock.lock();
            cout << "k=" << k << ", After Merge N=" << thead_number;
            printVector(A);
            g_lock.unlock();
            flags[thead_number] = k;
        }
    }
}

void printVector(const vector<int>& A) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < A.size(); i++) {
        if (!first) {
            cout << ", " << A[i];
        }
        else {
            cout << A[i];
            first = false;
        }
    }
    cout << "}" << endl;
}

void fillVector(vector<int>& A)
{
    for (int i = 0; i < A.size(); i++) {
        A[i] = rand() % 100;
    }
}

bool check(const vector<int>& A)
{
    for (int i = 0; i < A.size() - 1; i++)
        if (!(A[i] <= A[i + 1]))
            return false;
    return true;
}

// Последовательный алгоритм пузырьковой сортировки
void mergeVector(vector<int>& A, int number_threads, int thead_number, int length, int remainder, int k)
{
    const int length1 = length * (1<<(k-1));
    const int start1 = thead_number * length1;
    const int start2 = (thead_number + 1) * length1;
    const int end = start2 + length1 + remainder - 1;
    g_lock.lock();
    cout << start1 << start2 << end << ": " << length  << "-" << length1  <<  endl;
    g_lock.unlock();
    int i = start1;
    int j = start2;
    while (i < end)
    {
        if (i == j) {
            j++;
            continue;
        }
        g_lock.lock();
        cout << "A[" << i << "] = " << A[i] << " > " << "A[" << j << "] = " << A[j] << endl;
        g_lock.unlock();
        if (A[i] > A[j]) {
            g_lock.lock();
            cout << "swap" << endl;
            g_lock.unlock();
            std::swap(A[i], A[j]);
        }
        i++;
    }
}