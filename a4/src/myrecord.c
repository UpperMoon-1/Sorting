/**
 * -------------------------------------
 * @file  myrecord.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-02-01
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"

GRADE grade(float score) {
	GRADE r = { "F" };
	// your code
	char grade[14][5] = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-",
			"D+", "D", "D-", "F" };
	float mark[] = { 100, 90, 85, 80, 77, 73, 70, 67, 63, 60, 57, 53, 50, 0 };
	int i;
	int n = sizeof(mark) / sizeof(float);
	for (i = 0; i < n; i++) {
		if (score >= mark[i + 1]) {
			break;
		}
	}
	strcpy(r.letter_grade, grade[i]);
	return r;
}

int import_data(FILE *fp, RECORD *dataset) {
	int count;
	count = 0;
	char delimiters[] = ",\n\r";
	char buf[128];
	char *tok;

	while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		tok = (char*) strtok(buf, delimiters);
		strcpy(dataset[count].name, tok);

		tok = (char*) strtok(NULL, delimiters);
		sscanf(tok, "%f", &dataset[count].score);

		count++;

	}

	return count;
}

STATS process_data(RECORD *dataset, int count) {
	STATS stats = { 0 };
	stats.count = count;
	int i;

	float sum;
	sum = 0;

	float mean;
	mean = 0;

	for (i = 0; i < count; i++) {
		sum += dataset[i].score;

	}
	mean = (sum / count);

	stats.mean = mean; //the mean is correct

	float *a[count];
	for (int i = 0; i < count; i++) {
		a[i] = &dataset[i].score;
	}

	select_sort((void*) a, 1, count - 1);
	int middle = count / 2;
	float med = 0.0;

	if (count % 2 == 0) {
		med = (*a[middle - 1] + *a[middle]) / 2;
	} else {
		med = *a[middle];
	} //medan calculation is correct

	//printf("median: %0.1f\n", med);
	stats.median = med;

	float squared = 0;

	for (i = 0; i < count; i++) {
		squared += (dataset[i].score - mean) * (dataset[i].score - mean);
	}
	squared = squared / count;
	squared = sqrt(squared);
	stats.stddev = squared;

	return stats;
}

int report_data(FILE *fp, RECORD *dataset, STATS stats) {
	int n = stats.count;

	if (n < 1) {
		return 0;
	}
	fprintf(fp, "stats:value\n");
	fprintf(fp, "count:%d\n", stats.count);
	fprintf(fp, "mean:%0.1f\n", stats.mean);
	fprintf(fp, "stddev:%0.1f\n", stats.stddev);
	fprintf(fp, "median:%0.1f\n", stats.median);
	fprintf(fp, "\n");

	fprintf(fp, "name:score,grade\n");
	int i;
	for (i = n; i > 0; i--) {
		fprintf(fp, "%s:%0.1f,%s\n", dataset[i - 1].name, dataset[i - 1].score,
				grade(dataset[i - 1].score));
	}

	return 1;
}

