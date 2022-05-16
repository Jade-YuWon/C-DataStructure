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

struct RANDS {
	FILE* pos ;
	FILE* ints ;
	FILE* doubles ;
	FILE* fixed ;
};

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
void insertion_s(FILE* fd) {
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
void selection_s(FILE* fd) {
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
void bubble_s(FILE* fd) {

}
void merge_s(FILE* fd) {

}
void quick_s(FILE* fd) {

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


	insertion_s(fd);
	selection_s(fd);
	bubble_s(fd);
	merge_s(fd);
	quick_s(fd);
	heap_s(fd);
	radix_s(fd);

	//close(fd);

	printf("Hello");
	return 0;
}
