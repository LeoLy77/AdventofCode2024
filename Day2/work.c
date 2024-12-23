#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isGood(int* nums, int len) {
    int current_num = nums[0];
    int next_num;

    if (nums[1] == current_num)
        return false;

    bool is_increasing = nums[1] > current_num;
    bool is_decreasing = nums[1] < current_num;
    for (int i = 1; i < len; i++) {
        next_num = nums[i];

        int diff = next_num - current_num;
        if (diff == 0 || abs(diff) > 3 || abs(diff) < 1) {
            // for (int i = 0 ; i < len; i++)
            //     printf("| %d | ", nums[i]);
            // printf(" --> %d (2)\n", len);

            return false;
        }

        if ((is_increasing && diff <= 0) || (is_decreasing && diff >= 0)) {
            return false;
        }
    
        current_num = nums[i];
    }
    return true;
}

bool isIncreasingOrDecreasing(const int *arr, int size) {
    bool increasing = true, decreasing = true;

    for (int i = 1; i < size; i++) {
        if (arr[i] <= arr[i - 1]) increasing = false;
        if (arr[i] >= arr[i - 1]) decreasing = false;
    }

    return increasing || decreasing;
}

bool hasValidDifferences(const int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int diff = abs(arr[i] - arr[i - 1]);
        if (diff < 1 || diff > 3) return false;
    }
    return true;
}

bool isGoodPart2(int *arr, int size) {
    if (isIncreasingOrDecreasing(arr, size) && hasValidDifferences(arr, size)) {
        return true;
    }

    for (int i = 0; i < size; i++) {
        int temp[size - 1];
        int index = 0;

        for (int j = 0; j < size; j++) {
            if (j != i) {
                temp[index++] = arr[j];
            }
        }

        if (isIncreasingOrDecreasing(temp, size - 1) && hasValidDifferences(temp, size - 1)) {
            return true;
        }
    }

    return false;
}

int main(char argc, char** argv) {
    FILE *file = fopen("input.txt", "r");
    int MAX_NUMS = 8;

    char line[128];
    char* res;
    int num_cnt = 0;
    int nums[MAX_NUMS];
    int good_stuff = 0;
    memset(nums, 0, MAX_NUMS);

    while (fgets(line, sizeof(line), file)) {
        res = strtok(line, " ");

        while(res != NULL) {
            nums[num_cnt] = atoi(res);
            res = strtok(NULL, " ");
            num_cnt += 1;
        }

        // for (int i = 0 ; i < num_cnt; i++)
        //     printf("| %d | ", nums[i]);
        // printf(" --> %d \n", num_cnt);

        if (isGoodPart2_(nums, num_cnt)) {
            good_stuff += 1;
        }

        num_cnt = 0;
        memset(nums, 0, MAX_NUMS);
    }

    printf("Num good reports %d", good_stuff);
    
    fclose(file);
    return 0;
}