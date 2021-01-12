#include "func.h"

const int max_threads = (length + 1) / 2;
thread threads[max_threads];

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
    //cout << "n = " << n << endl;
    for (int i = 0; i < (length - 1); i++)
    {
        //cout << "i =" << i << endl;
        for (int j = 0; j < (length - i - 1); j++)
        {
            //cout << "j =" << j << endl;
            compareExchange(A, j, j + 1);
        }
    }
}

// Последовательный алгоритм чет-нечетной перестановки
void oddEvenBubbleSort(vector<int>& A) 
{
    //for (int i = 1; i < length; i++) {
    //    if (i % 2 == 1) { // нечетная итерация
    //        for (int j = 0; j < length/2 - 2; j++)
    //            compareExchange(A, 2*j + 1, 2*j + 2);
    //        if (n % 2 == 1) // сравнение последней пары при нечетном n
    //            compareExchange(A, length - 2, length - 1);
    //    }
    //    if (i % 2 == 0) // четная итерация
    //        for (int j = 1; j < length/2 - 1; j++)
    //            compareExchange(A, 2*j, 2*j + 1);
    //}
    for (int i = 0; i < length; i++) {
        // (i % 2) ? 0 : 1 возвращает 1, если i четное, 0, если i не четное
        for (int j = (i % 2) ? 0 : 1; j + 1 < length; j += 2) {
            compareExchange(A, j, j+1);
        }
    }
}

void parallelOddEvenBubbleSort(vector<int>& A)
{
    //for (int i = 0; i < length; i++) {
    //    // (i % 2) ? 0 : 1 возвращает 1, если i четное, 0, если i не четное
    //    for (int j = (i % 2) ? 0 : 1; j + 1 < max_threads; j += 2) {
    //        threads[j] = thread(compareExchange, ref(A), j, j+1);
    //    }
    //    for (int j = (i % 2) ? 0 : 1; j + 1 < max_threads; j++) {
    //        threads[j].join();
    //    }
    //}
    int i, j;
    for (i = 1; i <= length; i++) {
        // Odd step 
        if (i % 2 == 1) {
            for (j = 0; j < max_threads; j++) {

                threads[j] = thread(compareExchange, ref(A), j, j + 1);
            }
            for (j = 0; j < max_threads; j++) {
                //cout << "Process id" << threads[j].get_id() << endl;
                threads[j].join();
            }
        }

        // Even step 
        else {
            for (j = 0; j < max_threads - 1; j++) {
                threads[j] = thread(compareExchange, ref(A), j, j + 1);
            }
            for (j = 0; j < max_threads - 1; j++)
                threads[j].join();
        }
    }
    
}

void printVector(const vector<int>& A) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < length; i++) {
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
    for (int i = 0; i < length; i++) {
        A[i] = rand() % 100;
    }
}