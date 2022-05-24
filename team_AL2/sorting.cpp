/*
* File	: sorting.cpp
*
* Author1: Park Yongwoo
* Author2: Yun Jaesang
* Author3: Park Yuwon
* Author4: Kim Hyekang
*
* Date	:
*
* Course: Data Structures(14461_002)
*
* Summary of this file
*		:  Implement sorting algorithms and analyze their performances.
*
* Parts 1 ~ 5
* (Only Part 1, 2 and 3 will be implemented in this "sorting.cpp" file.
* On the other hand, part 4 would be plotted in Python or R.)
*
* Part 1: Implement random input generators
* Part 2: Implement sorting algorithms
* Part 3: Implement sorting evaluators
* Part 4: Plot performance comparison graphs
* Part 5: Submit 10-minutes Video Presentation Link
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <memory.h>

#define MAX_STR 10000

struct RANDS {
	FILE* pos ;
	FILE* ints ;
	FILE* doubles ;
	FILE* fixed ; // String
};

/* Cautions: This function get 'void' array "arr" as an input (so it can hold any type such as int, float and double)
 and write it into file with name "fileName"(parameter)
 * Return value : true(success to write file)
 * arrType value 0: char*(string), 1:int, 2:float, 3:double
 */
bool fileWriter2(char* fileName, const int arrType, const void* arr, const int len) {
	FILE* fd;
	// 1. File open as w(write) mode
	fd = fopen(fileName, "w");
	if (fd == NULL) {
		printf("Failed to open file adequately: ");
		printf("data can't be writed.\n");
		return false;
	}
	else {
		char tmp[MAX_STR];
		char* s_arr = ((char*)arr);
		int* int_arr = ((int*)arr);
		float* float_arr = ((float*)arr);
		double* double_arr = ((double*)arr);
		// 2. Write data into file
		switch (arrType) {
		case 0: // arr is string itself
			fprintf(fd, s_arr);
			break;
		case 1: // arr is int array
			memset(tmp, 0, MAX_STR);
			for (int i = 0, j = 0; i < len; i++)
				j += sprintf(&tmp[j], "%d ", int_arr[i]);
			fprintf(fd, tmp);
			break;
		case 2: // arr is float array
			memset(tmp, 0, MAX_STR);
			for (int i = 0, j = 0; i < len; i++)
				j += sprintf(&tmp[j], "%f ", float_arr[i]);
			fprintf(fd, tmp);
			break;
		case 3: // arr is double array
			memset(tmp, 0, MAX_STR);
			for (int i = 0, j = 0; i < len; i++)
				j += sprintf(&tmp[j], "%lf ", double_arr[i]);
			fprintf(fd, tmp);
			break;
		default:
			printf("Wrong arr Type\n");
			return false;
		}
		printf("File %s opened in writing mode successfully \n\n", fileName);
	}
	// 3. Close file descriptor then the file is saved as fileName.
	fclose(fd);
	return true;
}


/*
 Part1: Implement the following random input generator
 Level1: positive numbers
 Level2: integers (including positives, 0, and negatives)
 Level3: double precision numbers (e.g. -1000.000 < number < +1000.000)
 Level4: fixed length strings (e.g. 5-sized characters: “abcde”, “vwxyz”)
*/
FILE* pos_rand(const int n) {
	return NULL;
}
bool i_rand(const int n) {
	return false;

}
bool d_rand(const int n) {
	return false;
}

bool fx_rand(const int n) {
	return false;
}


/*
 Part2: Implement the following sorting algorithms:
 Category1: Insertion sort, Selection sort, Bubble sort
 Category2: Merge sort, Quick sort
 Category3: Heap sort, Radix sort
*/
void insertion_s() {
	int arr[] = { 12, 11, 13, 5, 6 }, int n = sizeof(arr) / sizeof(arr[0]);
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		// Move elements of arr[0..i-1], 
		// that are greater than key, to one
		// position ahead of their
		// current position
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void selection_s() {
	int arr[] = { 12, 11, 13, 5, 6 }, int n = sizeof(arr) / sizeof(arr[0]);
	int i, j, min_idx;

	// One by one move boundary of
	// unsorted subarray
	for (i = 0; i < n - 1; i++)
	{

		// Find the minimum element in
		// unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element
		// with the first element
		swap(&arr[min_idx], &arr[i]);
	}

}
void bubble_s() {

}
void merge_s() {

}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
void quick_s() {
	int arr[] = { 12, 11, 13, 5, 6 }, int n = sizeof(arr) / sizeof(arr[0]);
	int low = 0, int high = n - 1;

	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
void heap_s(FILE* fd) {

}
void radix_s(FILE* fd) {

}

/*
*
 Part3: Implement the following sorting evaluator:
 Level1: Load the generated lists from files / Save the evaluation results as separate files.
 Level2: The sorting correctness
 Level3: The running time
 Level4: The stability correctness
*/
bool result_load_and_saver(FILE* in) {

}
bool sort_corrector(FILE* fd) {

}
bool running_timer(FILE* fd) {

}
bool stability_corrector(FILE* fd) {

}

int main() {
	RANDS *rands;




	if (!(rands->pos = pos_rand(10000))) {
		printf("Cannot Create Positive Random numbers File\n");
		exit(1);
	}
	if (!i_rand(10000)) {
		printf("Cannot Create Integer Random numbers File\n");
		exit(1);
	}
	if (!d_rand(10000)) {
		printf("Cannot Create Double-Precision Random numbers File\n");
		exit(1);
	}
	if (!fx_rand(10000)) {
		printf("Cannot Create Fixed Length Random numbers File\n");
		exit(1);
	}


	insertion_s();
	selection_s();
	bubble_s();
	merge_s();
	quick_s();
	heap_s();
	radix_s();

	//close(fd);

	printf("Hello");
	return 0;
}
