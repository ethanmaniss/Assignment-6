#include <iostream>
#include <fstream>
#include <string>
#include <time.h> // http://www.cplusplus.com/reference/ctime/time/

using namespace std;

void merge(double theArray[], int l, int r, int m);

void bubbleSort(double myArray[], int n)
{
    for(int i = 0; i < n-1; ++i)
    {
        double temp = 0;
        for(int j = 0; j < n-1; ++j)
        {
            if(myArray[j] > myArray[j+1])
            {
                temp = myArray[j+1];
                myArray[j+1] = myArray[j];
                myArray[j] = temp;
            }
        }
    }
}

void selectionSort(double arr[], int n)
{
    int i, j, minIndex;
    double tmp;
    for(i = 0; i < n-1; i++)
    {
        minIndex = i;
        for(j = i+1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
            if(minIndex != i)
            {
                tmp = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = tmp;
            }
    }
}

void insertSort(double tArr[], int n)
{
    for(int j = 1; j < n; ++j) // marker
    {
        double temp = tArr[j]; // store marked item
        int k = j; // where to start shifting
        while(k > 0 && tArr[k-1] >= temp) // while the thing to the left is larger, shift
        {
            tArr[k] = tArr[k-1];
            --k;
        }
        tArr[k] = temp; // put marked item in right spot
    }
}

void mergeSort(double theArray[], int l, int r) // l is left index and r is right index
{
    int m; // m is the middle index
    if(l < r)
    {
        m = l+(r-l)/2;
        mergeSort(theArray, l, m);
        mergeSort(theArray, m+1, r);
        merge(theArray, l, m, r);
    }
}

void merge(double theArray[], int l, int m, int r)
{
    int i;
    int j;
    int k;
    int sizeL;
    int sizeR;

    sizeL = m - l + 1; // size left subarray
    sizeR = r - m; // size right subarray

    double lArray[sizeL]; // initialize the left and right subarrays
    double rArray[sizeR]; // subarrays are temp arrays

    for(int i = 0; i < sizeL; ++i)
    {
        lArray[i] = theArray[l + i];
    }
    for(int j = 0; j < sizeR; ++j)
    {
        rArray[j] = theArray[m + j + 1];
    }

    i = 0;
    j = 0;
    k = l;

    while(i < sizeL && j < sizeR)
    {
        if(lArray[i] <= rArray[j])
        {
            theArray[k] = lArray[i];
            i++;
        }
        else
        {
            theArray[k] = rArray[j];
            j++;
        }
        k++; // index for the full array is one position ahead of subarrays'
    }

    while(i < sizeL)
    {
        theArray[k] = lArray[i];
        i++;
        k++;
    }

    while(j < sizeR)
    {
        theArray[k] = rArray[j];
        j++;
        k++;
    }
}

int main(int argc, char** argv)
{
    if(argc == 2) // file input stuff
    {
        int arraySize;
        time_t before; // time object for when before algorithm started
        time_t after; // time object for when after algorithm ended
        double seconds;

        string fileName = argv[1];
        string line = "";
        ifstream file(fileName);
        if(file)
        {
            getline(file, line); // first line of file is number of items to sort
            arraySize = stoi(line); // converts size of array from a string to an integer
            double* a = new double[arraySize]; // initialize first array of doubles
            double* a2 = new double[arraySize]; // second array
            double* a3 = new double[arraySize]; // third array
            double* a4 = new double[arraySize]; // fourth array
            for(int i = 0; i < arraySize; ++i)
            {
                getline(file, line); // get doubles from the user file
                a[i] = stod(line);
                a2[i] = a[i]; // copy values to second array
                a3[i] = a[i]; // copy values to third array
                a4[i] = a[i]; // copy values to fourth array
            }

            time(&before);
            bubbleSort(a, arraySize);
            time(&after);                   // finds difference in time between when
            seconds = difftime(after, before); // algorithm started and ended
            cout << "Bubble Sort took " << seconds << " seconds." << endl;

            time(&before);
            selectionSort(a2, arraySize);
            time(&after);
            seconds = difftime(after, before);
            cout << "Selection Sort took " << seconds << " seconds." << endl;

            time(&before);
            insertSort(a3, arraySize);
            time(&after);
            seconds = difftime(after, before);
            cout << "Insertion Sort took " << seconds << " seconds." << endl;

            time(&before);
            mergeSort(a4, 0, arraySize-1);
            time(&after);
            seconds = difftime(after, before);
            cout << "Merge Sort took " << seconds << " seconds." << endl;

            delete []a; // delete arrays because memory is dynamically allocated
            delete []a2;
            delete []a3;
            delete []a4;
        }
        else
        {
            cout << "An error occurred trying to open the file." << endl;
        }
    }
    else
    {
        cout << "Incorrect format.\nEnter the text file as a command line argument." << endl;
    }

    return 0;
}
