// Name: Ryan Brooks
// ID: 1530605
// Course: CKPUT 274 fall 2018
// assignment: Weekly exercise 7: Dr. moneybags
// C++ quicksort used in this exercise
// thanks to the CMPUT 274 team for the code
#include<stdio.h>
#include <iostream>
// include iostream and std namespace for ease
// of printing
using namespace std;
// global variables
int applicants;
int applicantArray[100000];
int N;
int counter;
int count;
// https://www.geeksforgeeks.org/quick-sort/
// Small changes by Paul Lu
/* C implementation QuickSort */
// A utility function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;  // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high);
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// main function
int main() {
    // take in input
    cin >> applicants;
    int x;
    for (int i = 0; i < applicants; i++) {
        cin >> applicantArray[i];
    }
    // sort the input and set N equal to the largest value
    // in the array
    quickSort(applicantArray, 0, applicants - 1);
    counter = applicantArray[applicants - 1];
    // iterate through the applicant array and
    // check for each number greater than or equal to
    // the threshold N value.  If the count value is
    // equal to i or the threshold then we exit the loop
    // and print the count value.
    for (int i = counter; i >= 0; i--) {
        count = 0;
        for (int j = 0; j < applicants; j++) {
            if (applicantArray[j] >= i) {
                count += 1;
            }
        }
        if (count >= i) {
            x = i;
            break;
        }
    }
    cout << x << endl;
}
