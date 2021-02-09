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
void parallelOddEvenBubbleSort(vector<int>& A, int number_threads, int thead_number)
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
        /*auto log2 = [](unsigned long long x) {x--; int i = 0;  while (x >>= 1) { i++; } return i; };
        cout << "log2(number_threads) = " << log2(number_threads) << endl;
        for (int k = 1; k < log2(number_threads); k++) {
            cout << "k = " << k << endl;
            cout << "1<<k = " << 1<<k << endl;
            if (thead_number % (1<<k) == 0) {
                while (flags[thead_number + 1] == (k-1)) {}
                mergeVector(A, number_threads, thead_number, length, remainder);
                flags[thead_number] = k;
            }
            else {
                flags[thead_number] = k;
            }
        }*/
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
void mergeVector(vector<int>& A, int number_threads, int thead_number, int length, int remainder)
{
    int i = 0;
    int next = A.size() / number_threads - 1;
    //cout << next << endl << endl;
    while(i < (A.size() - 2))
    //for (int i = 0; i < (A.size() - 1); i++)
    {
        for (int j = ((i + 1) > next) ? (i+1) : next; j < A.size(); j++)
        {
            if (A[i] > A[j]) {
                cout << "A[" << i << "] = " << A[i] << " > " << "A[" << j << "] = " << A[j] << endl;
                std::swap(A[i], A[j]);
                if (j != (A.size() - 1)) {
                    //cout << "i = 0" << endl;
                    i = 0;
                }
                break;
            }
        }
        i++;
    }
    /*const int start1 = thead_number * length;
    const int start2 = (thead_number + 1) * length;
    const int end = start2 + length + remainder - 1;
    int i = start1;
    int j = start2;
    while (i < end)
    {
        if (i == j) {
            j++;
            continue;
        }
        if (A[i] > A[j]) {
            std::swap(A[i], A[j]);
        }
        i++;
    }*/

}