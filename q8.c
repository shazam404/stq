#include <stdio.h>

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1], R[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
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

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n, choice, target, result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Choose search algorithm:\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the element to search: ");
    scanf("%d", &target);

    if (choice == 1) {
        result = linearSearch(arr, n, target);
        if (result != -1) {
            printf("Element %d found at index %d.\n", target, result);
        } else {
            printf("Element %d not found.\n", target);
        }
    } else if (choice == 2) {
        mergeSort(arr, 0, n - 1);
        result = binarySearch(arr, n, target);
        if (result != -1) {
            printf("Element %d found at index %d.\n", target, result);
        } else {
            printf("Element %d not found.\n", target);
        }
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
