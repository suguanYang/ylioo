#include <stdlib.h>

// for 1 to size:
//      j = i - 1
//      insertion = arr[i]
//      while (j>=0 && arr[j] > insertion):
//          arr[j+1] = arr[j]
//          j--
//      arr[j+1] = insertion
void insert_sort(int *arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        int j = i - 1;
        int insertion = arr[i];
        while(j >= 0 && arr[j] > insertion)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = insertion; 
    }
}