/*
Joseph Brinton
Group 9 Lab #1
CS 3310 Section 001
*/

#define _SCL_SECURE_NO_WARNINGS 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <dos.h>
#include <iomanip>
#include <vector>
#include <algorithm>      
#include <random>

using namespace std;
using std::setw;

int basic_operations = 0;

//Merge function for Merge Sort
void merge(int low, int mid, int high, std::vector<int>& arr) {
	int i, j, k;
	i = low;
	j = mid + 1;
	k = 0;
	
	std::vector<int> U(high - low +1);
	
	while (i <= mid&& j <= high) {
		basic_operations++;
		if (arr[i] < arr[j]) { // This comparison is basic operation for Merge Sort
			U[k] = arr[i];
			
			i++;
		}
		else {
			
			U[k] = arr[j];
			j++;
		}
		k++;
	}

	if (i > mid) {

		for (int a = j; a <=high; a++, k++) {
			U[k] = arr[a];
		}


	}
	else {

		for (int a = i; a <= mid; a++, k++) {
			U[k] = arr[a];
		}


	}

	for (int a = low; a <=high; a++) {
		arr[a] = U[a-low];
	}


}


// Recursive function for Merge Sort
void mergeSort(int low, int high, std::vector<int> &arr) {

	int mid;
	if (low < high) {
		mid = static_cast<int>(floor((low + high) / 2));
		mergeSort(low, mid, arr);
		mergeSort(mid + 1, high, arr);
		merge(low, mid, high, arr);

	}
}

//Partition function for Quick Sort
void partition(int low, int high, int & pivotpoint, std::vector<int>& arr) {
	int i, j;
	int pivot = arr[low];
	j = low;
	for (i = low + 1; i <= high; i++) { // This comparison is basic operation for Quick Sort
		basic_operations++;
		if (arr[i] < pivot) {
			j++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	pivotpoint = j;
	int temp = arr[low];
	arr[low] = arr[pivotpoint];
	arr[pivotpoint] = temp;
}

//Recursive function for Quick Sort
void quickSort(int low, int high, std::vector<int>& arr) {
	int pivotpoint;

	if (high > low) {

		partition(low, high, pivotpoint, arr);
		quickSort(low, pivotpoint - 1, arr);
		quickSort(pivotpoint + 1, high, arr);
	}
}


// Random list generator
void listGen(double size, std::vector<int>& arr) {
	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, size);
	for (int i =0 ; i < size; i++) {
		arr.push_back(dis(gen));
	}

}


int main()
{
	while (true) {
		std::vector<int> arr;
		int exp;
		
		int count = 0;
		cout << "Enter a exponent that will determine the size of the list: ";
		cin >> exp;
		while(!cin||exp<0){
			cin.clear();
			cin.ignore();
			cout << "Input invalid. Enter a exponent that will determine the size of the list: ";
			cin >> exp;
		} 
		
		double size = pow(2, exp);

		listGen(size, arr);
		count = size;
		
		std::vector<int> M = arr;
		std::vector<int> Q = arr;

		cout << setw(11) << std::left << "Sorting" << setw(11) << std::left << "Number of" << setw(11) << std::left << "Time" << setw(11) << std::left << "Basic" << endl;
		cout  << setw(11) << std::left << "Algorithm" << setw(11) << std::left << "Items (n)" << setw(11) << std::left << "Elapsed" << setw(11) << std::left << "Operations" << endl;
		
		clock_t start;
		clock_t end;
		clock_t elapsed_clock;
		clock_t elapsed_time;

		start = clock();	

		mergeSort(0, count - 1, M);
		

		end = clock();	
		elapsed_clock = end - start;
		elapsed_time = ((end - start) / (CLK_TCK));

		//print sorting stats
		cout << setw(11) << "Merge Sort" << setw(11) << count << setw(11) << elapsed_clock << setw(11) << basic_operations << endl;

		//reset stats
		basic_operations = 0;
		start = 0;
		end = 0;
		elapsed_clock = 0;
		elapsed_time = 0;

		start = clock();

		quickSort(0, count - 1, Q);

		end = clock();
		elapsed_clock = end - start;
		elapsed_time = ((end - start) / (CLK_TCK));

		//print sorting stats
		cout << setw(11) << "Quick Sort" << setw(11) << count << setw(11) << elapsed_clock << setw(11) << basic_operations << endl;

		basic_operations = 0;

	}

}

