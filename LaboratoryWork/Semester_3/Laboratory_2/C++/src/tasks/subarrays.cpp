#include "../../include/dynamicArray.hpp"
#include <iostream>

using namespace std;

void createSubarrays(const DynamicArray<string>& arr, DynamicArray<string>& current, int idx, DynamicArray<DynamicArray<string>>& subarrays) {
    if (idx == arr.GetSize()) {
        subarrays.PushBack(current);
        return;
    }

    createSubarrays(arr, current, idx + 1, subarrays);
    
    current.PushBack(arr[idx]);
    createSubarrays(arr, current, idx + 1, subarrays);
    current.DelElm(current.GetSize() - 1);
}

void subarrays() {
    int n;
    cout << "Введите длину массива: ";
    cin >> n;

    cout << "Введите элементы массива: ";
    DynamicArray<string> arr;
    for (int i = 0; i < n; i++) {
        string currentElm;
        cin >> currentElm;
        arr.PushBack(currentElm);
    }
    
    DynamicArray<DynamicArray<string>> result;
    DynamicArray<string> current;
    createSubarrays(arr, current, 0, result);

    cout << "[ ";
    for (int i = 0; i < result.GetSize(); i++) {
        DynamicArray<string>& subarray = result[i];
        cout << "{";
        for (int j = 0; j < subarray.GetSize(); j++) {
            cout << subarray[j];
            if (j != subarray.GetSize() - 1) cout << ",";
        }
        cout << "}";
        if (i != result.GetSize() - 1) cout << " ";
    }
    cout << " ]" << endl;
}