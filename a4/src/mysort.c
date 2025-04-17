/**
 * -------------------------------------
 * @file  mysort.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-02-01
 *
 * -------------------------------------
 */

#include "mysort.h"

// swap pointers
void swap(void **x, void **y) {
	void *temp = *y;
	*y = *x;
	*x = temp;
}

// a compare floating values pointed by void pointers.
int cmp(void *x, void *y) {
	float a = *(float*) x;
	float b = *(float*) y;
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

void select_sort(void *a[], int left, int right) {
	int i;
	int j;
	//*(float*) a[i]
	for (i = left; i <= right; ++i) {
		int k = i;
		for (j = 1 + i; j <= right; ++j) {
			if (cmp(a[j], a[k]) < 0) {
				k = j;
			}
		}
		if (i != k) {
			swap(&a[i], &a[k]);
		}
	}

}

void quick_sort(void *a[], int left, int right) {
	if (left < right) {

		int j = left; // comparator
		int i = left - 1; // trailer

		while (j != right) {
			if (cmp(a[j], a[right]) < 0) { //a[j] < a[pivot]
				i++;
				swap(&a[i], &a[j]);

			}
			j++;

		}
		i++;
		swap(&a[i], &a[right]);

		quick_sort(a, left, i - 1);
		quick_sort(a, i + 1, right);

	}

}

void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*)) {
	if (left < right) {
		int j = left;
		int i = left - 1;
		while (j != right) {
			if ((*cmp)(a[j], a[right]) < 0) {
				i++;
				swap(&a[i], &a[j]);
			}
			j++;
		}
		i++;
		swap(&a[i], &a[right]);
		my_sort(a, left, i - 1, (*cmp));
		my_sort(a, i + 1, right, (*cmp));
	}
}

