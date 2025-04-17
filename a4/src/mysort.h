/**
 * -------------------------------------
 * @file  mysort.h
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-02-01
 *
 * -------------------------------------
 */
#ifndef MYSORT_H
#define MYSORT_H

// your code document
void select_sort(void *a[], int left, int right);

// your code document
void quick_sort(void *a[], int left, int right);

// your code document
void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*));

#endif

