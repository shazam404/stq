#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

// Insertion Sort
void insertionSort(int arr[], int n, int *count) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            (*count)++;
            arr[j + 1] = arr[j];
            j--;
        }
        (*count)++;
        arr[j + 1] = key;
    }
}

// Merge Sort
void mergeSort(int arr[], int l, int r, int *count) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, count);
        mergeSort(arr, m + 1, r, count);

        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1], R[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            (*count)++;
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
}

// Quick Sort
void quickSort(int arr[], int low, int high, int *count) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            (*count)++;
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;

        quickSort(arr, low, pi - 1, count);
        quickSort(arr, pi + 1, high, count);
    }
}

// Bucket Sort
void bucketSort(int arr[], int n, int *count) {
    int i, j, k, bucket[MAX][MAX], count[MAX];
    int max = arr[0];

    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (i = 0; i < n; i++) {
        count[i] = 0;
    }

    for (i = 0; i < n; i++) {
        j = (arr[i] * n) / (max + 1);
        bucket[j][count[j]++] = arr[i];
    }

    for (i = 0; i < n; i++) {
        insertionSort(bucket[i], count[i], count);
    }

    k = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < count[i]; j++) {
            arr[k++] = bucket[i][j];
        }
    }
}

// Radix Sort
void radixSort(int arr[], int n, int *count) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int output[n], count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}

void countSort(int arr[], int n, int *count) {
    int output[n];
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int countArr[max + 1];
    for (int i = 0; i <= max; i++) {
        countArr[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        countArr[arr[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        countArr[i] += countArr[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[countArr[arr[i]] - 1] = arr[i];
        countArr[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}



int main() {
    int arr[MAX], n, choice, count;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    while (1) {
        count = 0;
        printf("\nChoose sorting algorithm:\n");
        printf("1. Insertion Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Quick Sort\n");
        printf("4. Bucket Sort\n");
        printf("5. Radix Sort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int arrCopy[MAX];
        for (int i = 0; i < n; i++) arrCopy[i] = arr[i];  // Copy original array for each sort

        switch (choice) {
            case 1:
                insertionSort(arrCopy, n, &count);
                break;
            case 2:
                mergeSort(arrCopy, 0, n - 1, &count);
                break;
            case 3:
                quickSort(arrCopy, 0, n - 1, &count);
                break;
            case 4:
                bucketSort(arrCopy, n, &count);
                break;
            case 5:
                radixSort(arrCopy, n, &count);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
                continue;
        }

        printf("Sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arrCopy[i]);
        }
        printf("\ncount: %d\n", count);
    }

    return 0;
}
