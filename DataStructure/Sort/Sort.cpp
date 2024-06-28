#include <iostream>

void PrintArray(int input[], int count)
{
	for (int i = 0; i < count; i++)
	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

void Swap(int &value1, int &value2)
{
	int temp = value1;
	value1 = temp;
	value1 = value2;
	value2 = temp;
}

// 순차 정렬
// Time Complexity : O(n^2)
// Space Complexity : O(n)
// 나 자신과 모든 값을 비교
void SequentialSort(int input[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (input[i] > input[j])
			{
				Swap(input[i], input[j]);
			}
		}
	}
}

// 선택 정렬
//Time Complexity : O(n^2)
//Space Complexity : O(n)
// 가장 작은 값을 찾아 가장 앞으로 보내는 방식
void SelectionSort(int input[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int minIndex = i;
		for (int j = i; j < size; j++)
		{
			if (input[minIndex] > input[j])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			Swap(input[i], input[minIndex]);
		}
	}
}

// 거품 정렬
//Time Complexity : O(n^2)
//Space Complexity : O(n)
// 인접한 두개의 원소를 검사하여 큰 값을 뒤로 보내는 과정을 반복
void BubbleSort(int input[], int size)
{
	for (int phase = 0; phase < size - 1; phase++)
	{
		for (int k = 0; k < size - phase - 1; k++)
		{
			if (input[k] > input[k + 1])
			{
				Swap(input[k], input[k + 1]);
			}
		}
	}
}

// 삽입 정렬
//Time Complexity : O(n^2)
//Space Complexity : O(n)
// 자신이 위치해야할 곳에 값을 삽입하는 방식
void InsertionSort(int input[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int j = i;
		int target = input[i];

		while (--j >= 0 && target > input[j])
		{
			input[j + 1] = input[j];
			input[j] = target;
		}
	}
}

// 합병(병합) 정렬
// // Time Complexity : O(n log n)
// Space Complexity : O(n + n) = O(n)
// 분할 정복 할고리즘을 사용한 정렬, 작은 문제로 분할하여 해결
void Merge(int input[], int start, int half, int end, int temp[])
{
	int i = start;
	int j = half + 1;
	int tempIndex = 0;

	// 왼쪽 오른쪽 블럭들을 정렬 합병
	while (i <= half && j <= end)
	{
		if (input[i] < input[j])
		{
			temp[tempIndex++] = input[i++];
		}
		else
		{
			temp[tempIndex++] = input[j++];
		}
	}

	// 남은 인덱스들 병합, 한쪽 블럭이 남아 있을 경우 대비해 각각 병함
	while (i <= half)
	{
		temp[tempIndex++] = input[i++];
	}

	while (j <= end)
	{
		temp[tempIndex++] = input[j++];
	}

	//복사
	tempIndex = 0;
	for (int i = start; i <= end; i++)
	{
		input[i] = temp[tempIndex++];
	}
}

void MergeSort(int input[], int start, int end, int temp[])
{
	if (start >= end)
	{
		return;
	}

	int half = (start + end) / 2;

	MergeSort(input, start, half, temp);
	MergeSort(input, half + 1, end, temp);
	Merge(input, start, half, end, temp);
}

// 퀵 정렬
// 가장 많이 사용됨, 분할정복 사용, 
// 1. 특정 원소를 피벗값으로 지정하고 2. 피벗값보다 작으면 왼쪽, 크면 오른쪽 정렬
// 3. 피벗 기준으로 리스트를 좌/우로 분할, 1 ~ 3번 반복
// // Time Complexity : O(n log n)
// Space Complexity : O(n + n) = O(n)
void QuickSort(int numbers[], int start, int end)
{
	int i = start;
	int j = end;
	int pivot = numbers[(start + end) / 2];
	do
	{
		while (numbers[i] < pivot)
		{
			i++;
		}
		while (numbers[j] > pivot)
		{
			j--;
		}

		if (i <= j)
		{
			int temp = numbers[i];
			numbers[i] = numbers[j];
			numbers[j] = temp;

			i++;
			j--;
		}
	} while (i <= j);

	if (start < j)
	{
		QuickSort(numbers, start, j);
	}
	if (i < end)
	{
		QuickSort(numbers, i, end);
	}
}
int main()
{
	const int size = 7;
	int array[size]{ 1,5,3,7,2,9,6 };
	int tempArray[size];

	//InsertionSort(array, size);
	
	MergeSort(array, 0, size - 1, tempArray);
	PrintArray(array, size);
}
