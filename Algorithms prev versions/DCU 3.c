//DCU phase 3
//create a struct called superArray with three members:
//  a pointer to an array of integers
//  an integer that keeps track of the size of the array
//  a bool that states whether the array is sorted or not
//  a bool that states whether this superArray is initialized
//  create an initiArray function that, (after creating an instance of superArray)
//  sets that instance's array pointer equal to a realloc of the correct size
//  size will be a parameter to the initArray function
//  note: whenever this array gets sorted, make sure to toggle the bool
//  and when instances of this struct are initialized, make sure the bool starts off as
//  false
//  when the superArray struct and its initArray method are functional,
//  refactor all your code to use it.
//  and then for the program itself, at the beginning, create an array of this struct
//  of size 10.
//  and replace your "populate default array" and "generate custom array" options
//  with "manage arrays"
//  this will lead to a sub menu that allows you to initialize an array in any of ten
//  slots or to re-initialize (create a new array) in an already used slot
//  when you got o sorting algorithms and search algorithms, you will have to specify which
//  slot it will use.
//  in order to see the contents of one of your arrays you'll have to either
//  a. go to the "manage arrays" option and see your list of arrays
//  b. sort/search one and it will show the result




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  int* array;
  int size;
  bool sorted;
  bool initialized;
  bool populated;
} superArray;

// PROTOTYPES - fuck these unless necessary for now
// void populateArray(superArray*, int, int, int) ;
// void printArray(superArray*, int);
// void swap(superArray*, int, int);
// void bubbleSort(superArray*, int);
// void selectionSort(superArray*, int) ;
// void binarySearch(superArray*, int);
// bool checkArrayPopulated (int*);
// void runSort(superArray*, int, void(*f)(int*, int));
// void HUD();
void manageArrays (char*, superArray*);


void initArray(superArray* a, int size) {
  a->array = (int *)malloc(size * sizeof(int));
  a->size = size;
  a->sorted = false;
  a->initialized = true;
  a->populated = false;
}

void populateArray(superArray* a) {
  int min, max;
  srand(time(0));
  printf("Enter Integer Min\n");
  scanf("%d", &min);

  printf("Enter Integer Max\n");
  scanf("%d", &max);
  
  printf("Enter Array Size\n");
  scanf("%d", &a->size);
  a->array = (int *)realloc(a->array, a->size * sizeof(int));

  for (int i = 0; i < a->size; i++) {
    a->array[i] = rand() % (max - min + 1) + min;
  }
  a->populated = true;
}

void printArray(superArray* a) {
  for (int i = 0; i < a->size; i++) {
    printf("%d ", a->array[i]);
  }

  printf("\n");
}

void swap(int* array, int a, int b) {
  int temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}

void bubbleSort(superArray* a) {
  bool sorted = false;
  int size = a->size;

  while (!sorted) {
    sorted = true;

    for (int i = 0; i < a->size - 1; i++) {
      if (a->array[i] > a->array[i + 1]) {
        swap(a->array, i, i + 1);
        sorted = false;
      }
    }
    size--;
  }
}

void selectionSort(superArray* a) {
  int minIndex = 0; //index of smallest element encountered on current pass
  int target = 0;   //index of the first element of the unsorted part of the array
                    //in other words, the element we are preparing to swap if it's
                    //not the smallest thing left
  for (int i = 0; i < a->size; i++) {
    minIndex = target;
    for (int j = target; j < a->size; j++) {
      if (a->array[j] < a->array[minIndex]) {
        minIndex = j;
      }
    }
    if (a->array[minIndex] < a->array[target]) swap(a->array, minIndex, target);
    target++;
  }
}

void(*sortAlgorithms[])(superArray*) = {
  bubbleSort,
  selectionSort,
};

void binarySearch(superArray* a) {
  int search;
  printf("\nEnter value to search for:\n");
  scanf("%d", &search);
  printf("--------------------\n");

  int mid = (a->size / 2 - 1);
  int midModifier = (a->size / 4);
  int stopCount = 0;

  while (1) {
    if (search > a->array[mid]) {
      printf("value %d > array position: %d (%d)\n\n", search, mid, a->array[mid]);
      mid = mid + midModifier - 1;
    }

    else if (search < a->array[mid]) {
      printf("value %d < array position: %d (%d)\n\n", search, mid, a->array[mid]);
      mid = mid - midModifier + 1;
    }

    else if (search == a->array[mid]) {
      printf("LOCATED VALUE (%d) at array position: %d\n", search, mid);
      break;
    }

    midModifier = (midModifier / 2) + 1;

    //stop if value not found, functional up to size = 1024
    stopCount++;
    if (stopCount == 10) {
      printf("Value not in array you stupidass trick\n");
      break;
    }
  }
  printf("--------------------\n");
}

bool checkArrayPopulated (superArray* a) {
  //check if array is populated
  if ((a->array[1] == a->array[3]) && (a->array[1] == 0)) {
    printf("ERROR: ARRAY NOT YET POPULATED. POPULATE/GENERATE ONE FIRST.\n");
    return 0;
  }
  return 1;
}

void runSort(superArray* a, void(*f)(superArray* a)) {
  if (checkArrayPopulated(a)) {
    printf("ORIGINAL ARRAY:\n");
    printArray(a);
    (*f)(a);
    printf("SORTED ARRAY:\n");
    printArray(a);
    a->sorted = true;
  }
}

void HUD() {
  printf("\n(1) Manage Arrays\n(2) Sorting Algorithms\n(3) Search Algorithms\n(4) Exit\n");
}

void manageArray (superArray* a, int userIntInput) {
  char userInput[25];
  int min = 0;
  int max = 0;
  printf("Array %d:\n", userIntInput);
  printArray(a);
  printf("(1) Populate \n(2) Sort \n(3) Search \n(4) Select Another Array \n(5) Back to main menu\n");
  scanf("%s", userInput);

  //populate array
  if (userInput[0] == '1') {

    populateArray(a);

    manageArray(a, userIntInput);
    
  }
  // sort
  if (userInput[0] == '2') {
    printf("\nSelect Sorting Algorithm:\n(1) bubbleSort\n(2) selectionSort\n");

    scanf("%s", userInput);
    //bubble sort
    if (userInput[0] == '1') {
      runSort(a, sortAlgorithms[0]);
    }

    //selection sort
    else if (userInput[0] == '2') {
      runSort(a, sortAlgorithms[1]); 
    }
  }
  // search
  if (userInput[0] == '3') {
    if (checkArrayPopulated(a)) {
      //pre-sort array with bubbleSort
      runSort(a, sortAlgorithms[0]);

      binarySearch(a);
    }
  }
  // select different array
  if (userInput[0] == '4') {
    manageArrays(userInput, a);
  }
}

void manageArrays (char* userInput, superArray* superArrays) {
  int userIntInput = 0;
  
  printf("ARRAY MANAGEMENT\n-------------------------------------\n");
  printf("Array - Size - Init? - Pop? - Sorted?\n");
  for (int i = 0; i<10; i++) {
    printf("%-8d%-7d%-8d%-7d%-6d\n",i, superArrays[i].size, superArrays[i].initialized,superArrays[i].populated, superArrays[i].sorted);
  }
  printf("-------------------------------------\n");
  
  printf("Enter designation of array you wish to manage:\n");
  scanf("%d", &userIntInput);

  manageArray(&superArrays[userIntInput], userIntInput);

}

int main() {
  char userInput[25];
  int running = 1;
  int userIntInput;

  //initialize superArrays
  superArray superArrays[10];
  for (int i = 0; i < 10; i++) {
    initArray(&superArrays[i], 0);
  }

  while (running) {
    HUD();
    scanf("%s", userInput);

    if (userInput[0] == '1') {
      manageArrays(userInput, superArrays);  
    }
    if (userInput[0] == '2') {
      manageArrays(userInput, superArrays);  
    }
    if (userInput[0] == '3') {
      manageArrays(userInput, superArrays);  
    }

    else if (userInput[0] == '4') running = 0;
  }
  
  return 0;
}