//DCU phase 4 - complete

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  int* array;
  int size;
  bool sorted;
  bool populated;
} superArray;

// NECESSARY PROTOTYPES
void manageArrays (superArray*);


void initArray(superArray* a, int size) {
  a->size = size;
  a->array = (int *)malloc(size * sizeof(int));
  a->sorted = false;
  a->populated = false;
}

void populateArray(superArray* a, int test) {
  int min, max;
  

  if (test == 0) {
    printf("Enter Integer Min\n");
    scanf("%d", &min);

    printf("Enter Integer Max\n");
    scanf("%d", &max);
    
    printf("Enter Array Size\n");
    scanf("%d", &a->size);
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }

  //testing bypass for no entries
  else if (test == 1) {
    min = 0; 
    max = 20; 
    a->size = 20;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }

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

void insertionSort(superArray* a) {
  int marker, j;
  for (int i = 1; i < a->size; i++) {
    marker = a->array[i];
      j = i-1;
      while (j>=0 && a->array[j] > marker) {
        a->array[j+1] = a->array[j];
        j=j-1;
      }
      a->array[j+1] = marker;
  }
}

void(*sortAlgorithms[])(superArray*) = {
  bubbleSort,
  selectionSort,
  insertionSort
};


int linearSearch(superArray *a, int search) {
  for (int i = 0; i < a->size; i++) {
    if (a->array[i] == search) {
      printf("LOCATED VALUE (%d) at array position: %d\n", search, i);
      break;
    }
    else if (i == a->size - 1) {
      printf("Value not in array you stupidass trick\n");
    }
  }
  return 0;
}

int binarySearch(superArray* a, int search) {
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
      
      return mid;
    }

    midModifier = (midModifier / 2) + 1;

    //stop if value not found, functional up to size = 1024
    stopCount++;
    if (stopCount == 10) {
      return 0;
    }
  }
}

int(*searchAlgorithms[])(superArray*, int) = {
  binarySearch,
  linearSearch
};

int runSearch(superArray* a, int(*f)(superArray* a, int search)) {
  int search;
  printf("\nEnter value to search for:\n");
  scanf("%d", &search);
  printf("--------------------\n");
  int foundValue = (*f)(a, search);
  if (foundValue > 0){
    printf("LOCATED VALUE (%d) at array position: %d\n", search, foundValue);
  }
  else if (foundValue == 0) {
    printf("Value not in array you stupidass trick\n");
  }
  
  printf("--------------------\n");
  return 0;
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

void blindMerge(superArray* a, superArray* b, superArray* c){
  //set target array new size 
  c->size = (a->size + b->size);
  c->array = (int*)realloc(c->array, (a->size + b->size) * sizeof(int));

  //append array a to c
  for (int i = 0; i< a->size; i++) {
    c->array[i] = a->array[i];
  }
  //append array b to c, after a
  for (int i = a->size; i < c->size; i++) {
    c->array[i] = b->array[i - a->size];
  }

  printf("merged target array:\n");
  printArray(c);

  c->populated = true;
}

void sortedMerge(superArray* a, superArray* b, superArray* c){
  //set target array new size 
  c->size = (a->size + b->size);
  c->array = (int*)realloc(c->array, (a->size + b->size) * sizeof(int));

  //pre-merge array
  blindMerge(a,b,c);

  //sorting code
  runSort(c, sortAlgorithms[0]);

  printf("merged and sorted target array:\n");
  printArray(c);
  
  c->sorted = true;
}

void intersectionMerge(superArray* a, superArray* b, superArray* c){
  //pre-sort original Arrays
  runSort(a, sortAlgorithms[0]);
  runSort(b, sortAlgorithms[0]);

  int i = 0;
  int j = 0;
  int n = 0;

  while(i < a->size && j < b->size) {
    if (a->array[i] < b->array[j]){
      i++;
    }
    else if (b->array[j] < a->array[i]) {
      j++;
    }
    // duplicate handling
    else if (c->array[n-1] == a->array[i]) {
      i++;
    }
    else {
      c->size++;
      c->array = (int*)realloc(c->array, c->size * sizeof(int));
      c->array[n] = a->array[i];
      i++;
      n++;
    }
  }
  
  c->populated = true;
  c->sorted = true;
  printf("Intersection Array:\n");
  printArray(c);
}

void unionMerge(superArray* a, superArray* b, superArray* c){
  //pre-sort original Arrays
  runSort(a, sortAlgorithms[0]);
  runSort(b, sortAlgorithms[0]);

  int n = 0;
  int i = 0;
  int j = 0;

  while (i < a->size && j < b->size) {
    if (a->array[i] < b->array[j]) {
      if (c->array[n-1] != a->array[i] || (a->array[i] == 0 && n == 0)) {
        c->size++;
        c->array = (int*)realloc(c->array, c->size * sizeof(int));
        c->array[n] = a->array[i];
        n++;
      }
      i++;
    }

    else if (b->array[j] < a->array[i]) {
      if (c->array[n-1] != b->array[j] || (b->array[j] == 0 && n == 0)) {
        c->size++;
        c->array = (int*)realloc(c->array, c->size * sizeof(int));
        c->array[n] = b->array[j];
        n++;
      }
      j++;
    }
    else {
      i++;
    }
  }

  c->populated = true;
  c->sorted = true;
  printf("\nUnion Array:\n");
  printArray(c);
}

void(*mergeAlgorithms[])(superArray*, superArray*, superArray*) = {
  blindMerge,
  sortedMerge,
  intersectionMerge,
  unionMerge
};

void runMerge(superArray* superArrays, void(*f)(superArray* a, superArray* b, superArray* c)){
  int userIntInput1, userIntInput2;
  superArray* a;
  superArray* b;
  superArray* c;

  //select first Array
  printf("Specify first array:");
  scanf("%d",&userIntInput1);
  a = &superArrays[userIntInput1];

  //select second array
  printf("Specify first array:");
  scanf("%d",&userIntInput2);
  b = &superArrays[userIntInput2];

  if (a->populated && b->populated) {
    //select target array
    printf("Specify target array:");
    scanf("%d",&userIntInput1);
    c = &superArrays[userIntInput1];

    printf("array 1:\n");
    printArray(a);
    printf("array 2:\n");
    printArray(b);
    (*f)(a,b,c);

    printf("Enter 1 to confirm and return to main menu.");
    scanf("%d",&userIntInput1);

  }
  else {
    printf("Selected array(s) not yet populated. Popoulate first mothafucka./n Enter 1 to confirm\n");
    scanf("%d", &userIntInput1);
  }

}

int manageArray (superArray* a, int userIntInput) {
  char userInput[25];
  int min = 0;
  int max = 0;
  printf("Array %d:\n", userIntInput);

  printArray(a);
  
  printf("(1) Populate \n(2) Sort \n(3) Search \n(4) Back\n");
  scanf("%s", userInput);

  //populate array
  if (userInput[0] == '1') {

    populateArray(a, 0);

    manageArray(a, userIntInput);
    
  }

  // sort
  if (userInput[0] == '2') {
    printf("\nSelect Sorting Algorithm:\n(1) bubbleSort\n(2) selectionSort\n(3) insertionSort\n");

    scanf("%s", userInput);
    //bubble sort
    if (userInput[0] == '1') {
      runSort(a, sortAlgorithms[0]);
    }

    //selection sort
    else if (userInput[0] == '2') {
      runSort(a, sortAlgorithms[1]); 
    }

    //insertion sort
    else if (userInput[0] == '3') {
      runSort(a, sortAlgorithms[2]); 
    }
  }

  // search
  if (userInput[0] == '3') {
    if (checkArrayPopulated(a)) {
      //pre-sort array with bubbleSort
      runSort(a, sortAlgorithms[0]);

      runSearch(a, searchAlgorithms[0]);
    }
  }
  
  // select different array
  if (userInput[0] == '4') {
    return 0;
  }
  return 0;
}

void clear(){
  printf("\033[H\033[J");
}

void manageArrays (superArray* superArrays) {
  clear();
  int userIntInput = 0;
  
  printf("ARRAY MANAGEMENT\n-------------------------------------\n");
  printf("Array - Size - Pop? - Sorted?\n");
  for (int i = 0; i<10; i++) {
    printf("%-8d%-7d%-7d%-6d\n",i, superArrays[i].size,superArrays[i].populated, superArrays[i].sorted);
  }
  printf("-------------------------------------\n");
  
  printf("(0-9) Enter designation of array you wish to manage:\n (10) Composite Algorithms Menu \n (11) Quit\n");
  scanf("%d", &userIntInput);

  if (userIntInput < 10 && userIntInput >=0) {
    manageArray(&superArrays[userIntInput], userIntInput);
  }
  if (userIntInput == 10) {
    printf("Which composite algorithm:\n(0) Blind Merge\n(1) Sorted Merge\n(2) Intersection\n(3) Union\n");
    scanf("%d", &userIntInput);
    runMerge(superArrays, mergeAlgorithms[userIntInput]);
  }

  if (userIntInput == 11) exit(0);

}

int main() {
  srand(time(NULL)); //call srand in main so it only seeds once, thsi prevents duplicates when called rand() is called multiple times in one second
  char userInput[25];
  int running = 1;
  int userIntInput;

  //initialize superArrays
  superArray superArrays[10];
  for (int i = 0; i < 10; i++) {
    initArray(&superArrays[i], 0);
  }

  while (running) {
    manageArrays(superArrays);  
  }
  
  return 0;
}