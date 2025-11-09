#include "../../include/Subarrays.hpp"

void createSubarrays(const DynamicArray<string>& arr, DynamicArray<string>& current, int idx, DynamicArray<DynamicArray<string>>& subarrays) {
    if (idx == arr.size()) {
        subarrays.push_back(current);
        return;
    }

    createSubarrays(arr, current, idx + 1, subarrays);
    
    current.push_back(arr[idx]);
    createSubarrays(arr, current, idx + 1, subarrays);
    current.DelElm(current.size() - 1);
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
        arr.push_back(currentElm);
    }
    
    DynamicArray<DynamicArray<string>> result;
    DynamicArray<string> current;
    createSubarrays(arr, current, 0, result);

    cout << "[ ";
    for (int i = 0; i < result.size(); i++) {
        DynamicArray<string>& subarray = result[i];
        cout << "{";
        for (int j = 0; j < subarray.size(); j++) {
            cout << subarray[j];
            if (j != subarray.size() - 1) cout << ",";
        }
        cout << "}";
        if (i != result.size() - 1) cout << " ";
    }
    cout << " ]" << endl;
}