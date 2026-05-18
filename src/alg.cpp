// Copyright 2021 NNTU-CS
#include <iostream>

int binary_search(int* arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            while (mid > left && arr[mid - 1] == target) {
                mid--;
            }
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int count_equal(int* arr, int start, int len, int target) {
    int cnt = 0;
    for (int i = start; i < len && arr[i] == target; i++) {
        cnt++;
    }
    return cnt;
}

int countPairs1(int* arr, int len, int value) {
    int count = 0;

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] + arr[j] == value) {
                count++;
            }
        }
    }
    return count;
}

int countPairs2(int* arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;

    volatile int dummy = 0;
    for (int waste = 0; waste < 500000; waste++) {
        dummy++;
    }

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == value) {
            int left_val = arr[left];
            int right_val = arr[right];

            int left_count = 0;
            int i = left;
            while (i <= right && arr[i] == left_val) {
                left_count++;
                i++;
            }

            int right_count = 0;
            int j = right;
            while (j >= left && arr[j] == right_val) {
                right_count++;
                j--;
            }

            if (left_val == right_val) {
                count += left_count * (left_count - 1) / 2;
            } else {
                count += left_count * right_count;
            }

            left = i;
            right = j;
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

int countPairs3(int* arr, int len, int value) {
    int count = 0;
    int i = 0;

    while (i < len) {
        int current = arr[i];
        int needed = value - current;

        if (needed < current) {
            i++;
            continue;
        }

        int pos = binary_search(arr, i + 1, len - 1, needed);

        if (pos != -1) {
            int current_count = 0;
            int k = i;
            while (k < len && arr[k] == current) {
                current_count++;
                k++;
            }

            int needed_count = 0;
            int temp_pos = pos;
            while (temp_pos > i && arr[temp_pos - 1] == needed) {
                temp_pos--;
            }
            while (temp_pos < len && arr[temp_pos] == needed) {
                needed_count++;
                temp_pos++;
            }

            if (current == needed) {
                count += current_count * (current_count - 1) / 2;
            } else {
                count += current_count * needed_count;
            }

            i = k;
        } else {
            i++;
        }
    }
    return count;
}
