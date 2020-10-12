#include<iostream>
#include<vector>


void merge(std::vector<int>& arr, size_t start, size_t middle, size_t end) {
    std::vector<int> leftPart, rightPart;
    size_t leftPartSize = middle - start + 1;
    size_t rightPartSize = end - middle;

    for(int i = 0; i < leftPartSize; i++) {
        leftPart.push_back(arr[start + i]);
    }

    for(int i = 0; i < rightPartSize; i++) {
        rightPart.push_back(arr[middle + i + 1]);
    }
    int i = 0, j = 0, k = start;

    while( i < leftPartSize && j < rightPartSize) {
        if(leftPart[i] < rightPart[j]) {
            arr[k] = leftPart[i++];
        } else {
            arr[k] = rightPart[j++];
        }
        k++;
    }

    while(i < leftPartSize) {
        arr[k++] = leftPart[i++];
    }

    while(j < rightPartSize) {
        arr[k++] = rightPart[j++];
    }

}

void mergeSplitSort(std::vector<int>& arr, size_t start, size_t end) {
    if (start >= end) {
        return;
    }
    size_t middleElement = (end + start) / 2;
    mergeSplitSort(arr, start, middleElement);
    mergeSplitSort(arr, middleElement + 1, end);
    merge(arr, start, middleElement, end);
}

void mergeSort(std::vector<int>& arr) {
    // middleElement = ...
    // mergeSort(arrLeft)
    // mergeSort(arrRight)
    mergeSplitSort(arr,0, arr.size() - 1);
}

int main() {
    std::vector<int> A = { 1, 3, 2, 8, 150, 29 };
    mergeSort(A);
    for (int element : A) {
        std::cout << element << ' ';
    }
}


