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
        for (int j = (i % 2) ? 0 : 1; j + 1 < A.size(); j += 2) {
            compareExchange(A, j, j+1);
        }
    }
}

// Параллельный алгоритм чет-нечетной перестановки
void parallelOddEvenBubbleSort(vector<int>& A, int number_threads, int thead_number)
{
    
    int length = A.size() / number_threads;
	int start = thead_number * length;
    if (number_threads == 1) {
        oddEvenBubbleSort(A);
    }
    else {
        for (int i = start; i < start + length; i++)
        {
            for (int j = i + 1; j < start + length; j++)
            {
                compareExchange(A, i, j);
            }
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