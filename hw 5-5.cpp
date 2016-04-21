#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int comparisons = 0;
int exchanges = 0;

void bubble(int A[], int n)				//Bubble sort for an array with n elements
{
	int i, j, temp;
	for (i = 1; i < n; i++)				//number of passes
	{
		for (j = 0; j < n - 1; j++)		//j varies from 0 to n-1
		{
			comparisons++;				//increment comparisons
			if (A[j] > A[j + 1])		//compares to successive numbers
			{
				temp = A[j];
				A[j] = A[j + 1];		//if statement swaps A[j] with A[j+1] (the number after)
				A[j + 1] = temp;
				exchanges++;
			}
		}
	}
}

void insertion(int A[], int n)		//insertions sort array with n elements
{
	int i, j, element;
	for (i = 1; i < n; i++)
	{
		element = A[i];				//insert i(th) element into the array
		j = i;
		comparisons++;							//comparisons increments
		while ((j > 0) && (A[j - 1] > element))  //compare if A[j-1] is greater than element
		{
			A[j] = A[j - 1];					//shift elements
			j = j - 1;
			exchanges++;						//exchange increments
		}
		A[j] = element;
	}
}


/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int a[], int left, int right, int pivotIndex)
{
	int pivot = a[pivotIndex];      //pivot
	do
	{
		while (a[left] < pivot)
		{
			left++;
			comparisons++;
		}
		while (a[right] > pivot)
		{
			right--;
			comparisons++;
		}

		if (left < right && a[left] != a[right])
		{
			swap(a[left], a[right]);
			exchanges++;
		}
		else
		{
			return right;
		}
	} while (left < right);
	return right;
}

/* The main function that implements QuickSort
a[] --> Array to be sorted,
left  --> Starting index,
right  --> Ending index */
void quick(int a[], int left, int right)
{
	if (left < right)
	{
		int pivot = (left + right) / 2; // middle
		int pivotNew = partition(a, left, right, pivot);
		quick(a, left, pivotNew - 1);
		quick(a, pivotNew + 1, right);
	}
}

void shell(int A[], int n)						//shell sort for an array with n elements
{				
	int temp, gap, i;							
	int swapped;
	gap = n / 2;								//gap set equal to half the number of total elements to be sorted
	do
	{
		do
		{
			swapped = 0;
			for (i = 0; i < n - gap; i++)
			{
				comparisons++;
				if (A[i] > A[i + gap])			//checks if i(th) numbers is greater than the number after i+gap (in the second half of the set)
				{
					exchanges++;				//increment exchange.	
					temp = A[i];				//swaps number with succeeding number
					A[i] = A[i + gap];
					A[i + gap] = temp;
					swapped = 1;
				}
			}
		} while (swapped == 1);
	} while ((gap = gap / 2) >= 1);
}

void merge(int *a, int low, int high, int mid)
{
	int i, j, k, c[11000];
	i = low;
	k = low;
	j = mid + 1;
										/*merge arrays into array [low-high]*/
	while (i <= mid && j <= high)
	{
		comparisons++;
		if (a[i] < a[j])
		{
			c[k] = a[i];
			k++;
			i++;
			comparisons++;
			exchanges++;
		}
		else
		{
			c[k] = a[j];
			k++;
			j++;
			exchanges++;
		}
	}
	/*copy remaining elements of array a if any are left*/
	while (i <= mid)
	{
		c[k] = a[i];
		k++;
		i++;
	}
	/*copy remaining elements of array c if any are left*/
	while (j <= high)
	{
		c[k] = a[j];
		k++;
		j++;
	}
	for (i = low; i < k; i++)
	{
		a[i] = c[i];
	}
}

void mergesort(int *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		/*sort first and secon halves*/
		mergesort(a, low, mid);
		mergesort(a, mid + 1, high);
		merge(a, low, high, mid);
	}
	return;
}

bool read_in(string file_name, int lineData[])
{
	ifstream  file(file_name);								//attempts to open file with name given
	string temp="";											//creates empty string
	string   line;											//creates line string
	int j = 0;									
	if (file.is_open())										//checks if file is open
	{
			
		while (getline(file, line))							//while loops while file has data to be read
		{

			//stringstream  lineStream(line);

																//for loop checks if chracrter being read is a space character.
																//If it is, it is not read. Numbers are then read into temp and converted 
																//from a string to an int using stoi, and stored in an array*/
			for (int i = 0; i < line.length(); i++)			
			{
				if (line[i] != ' '&& line[i] != '/n')		
				{
					temp += line[i];						
				}
				else
				{
					lineData[j] =stoi(temp);				
					j++;
					temp = "";
				}
			}
			int value;

			/*while (lineStream >> value)
			{
				lineData[i]=value;
				i++;
			}*/
			

		}
	}
	else
	{
		cout << "file not found" << endl;					//if file not opened, cout to user that file was not found
		return false;										//returns false
	}

	return true;
}


int main()
{
	


												
	int sorted[11000];									//temp sorted array created to store the sorted numbers from files****/
	string fileNames[4];								//file names stored in an array to be used in for loop****/
	fileNames[0] = "FewUnique.txt";            
	fileNames[1] = "NearlySorted.txt";
	fileNames[2] = "Random.txt";
	fileNames[3] = "Reversed.txt";

	//int tmp[] = { 1, 2, 3, 5, 4 };
	//shell (tmp,5);
	//cout << comparisons << endl;
	//cout << exchanges << endl;
	//cout << tmp[4] << endl;

	for (int i = 0; i<4; i++)												//for each of the four files, mergesort is preformed and answers are outputed to console.
	{
		comparisons = exchanges = 0;									
		read_in(fileNames[i], sorted);
		mergesort(sorted, 1, 10000);
		cout << "merge sort: " << fileNames[i] << endl;
		cout << "comparisons: " << comparisons << endl;
		cout << "exchanges: " << exchanges << endl;
	}
	cout << "________________________________________" << endl;
	for (int i = 0; i<4; i++)												//for each of the four files, insertion sort is preformed and answers are outputed to console.
	{
		comparisons = exchanges = 0;
		read_in(fileNames[i], sorted);

		insertion(sorted, 10000);

		cout << "insertion sort: " << fileNames[i] << endl;
		cout << "comparisons: " << comparisons << endl;
		cout << "exchanges: " << exchanges << endl;
	}
	cout << "________________________________________" << endl;	
	for (int i = 0; i<4; i++)												//for each of the four files, bubble sort is preformed and answers are outputed to console.
	{
		comparisons = exchanges = 0;
		read_in(fileNames[i], sorted);

		bubble(sorted, 10000);

		cout << "bubble sort: " << fileNames[i] << endl;
		cout << "comparisons: " << comparisons << endl;
		cout << "exchanges: " << exchanges << endl;

	}
	cout << "________________________________________" << endl;
	for (int i = 0; i<4; i++)												//for each of the four files, shell sort is preformed and answers are outputed to console.
	{
		comparisons = exchanges = 0;
		read_in(fileNames[i], sorted);

		shell(sorted, 10000);
		cout << "shell sort: " << fileNames[i] << endl;
		cout << "comparisons: " << comparisons << endl;
		cout << "exchanges: " << exchanges << endl;
	}
	cout << "________________________________________" << endl;
	for (int i = 0; i<4; i++)												//for each of the four files, quick sort is preformed and answers are outputed to console.
	{
		comparisons = exchanges = 0;
		read_in(fileNames[i], sorted);

		quick(sorted, 0, 10000);
		cout << "quick sort sort: " << fileNames[i] << endl;
		cout << "comparisons: " << comparisons << endl;
		cout << "exchanges: " << exchanges << endl;
	}

	system("pause");
	return 0;
}

