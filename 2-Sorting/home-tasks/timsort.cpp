#include <iostream>
#include <sstream>
#include <vector>

const int RUN = 32; // Size of the run for Insertion sort

// Helper Insertion sort function for subarrays
void insertionSort(std::vector<int> &arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merge two sorted subarrays
void merge(std::vector<int> &arr, int l, int m, int r)
{
    int len1 = m - l + 1;
    int len2 = r - m;

    std::vector<int> left(len1);
    std::vector<int> right(len2);

    for (int i = 0; i < len1; i++)
    {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < len2; i++)
    {
        right[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < len2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void timSort(std::vector<int> &arr)
{
    int n = arr.size();

    // Sort small blocks (runs) using Insertion Sort
    for (int i = 0; i < n; i += RUN)
    {
        insertionSort(arr, i, std::min(i + RUN - 1, n - 1));
    }

    // Merge the sorted runs
    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);

            if (mid < right)
            {
                merge(arr, left, mid, right);
            }
        }
    }
}

void setVector(std::vector<int> &arr)
{
    std::string input;

    std::cout << "Enter numbers separated by space:\n";
    std::getline(std::cin, input);
    std::stringstream ss(input);

    while (ss >> input)
    {
        arr.push_back(std::stoi(input));
    }
}

int main()
{
    std::vector<int> numbers;
    setVector(numbers);

    timSort(numbers);

    std::cout << "Sorted numbers:" << std::endl;
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

