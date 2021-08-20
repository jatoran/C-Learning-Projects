#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> //time benchmarking, random number generation seed

typedef struct treeNode {
  int data;
  struct treeNode* right;
  struct treeNode* left;
} treeNode;

typedef struct {
  int* array;
  int size;
} superArray;

typedef struct {
  void (*function)();
  char* name;
  char* runTime;
} superSort;

typedef struct listNode{
  int data; 
  struct listNode* next; 
} listNode;

typedef struct stackNode{
  int data;
  struct stackNode* next;
} stackNode;

typedef struct queueNode{
  int data;
  struct queueNode* next;
} queueNode;

typedef struct stackNodeChar{
  char data;
  struct stackNodeChar* next;
} stackNodeChar;

// ---------------PROTOTYPES ----------------
//HELPER FUNCTIONS
  int validateConvertInput();
  void swapArrayValues(int* array, int a, int b);
  void printArray(superArray* a);
  void populateArray(superArray* a);
  void _manualArrayEntry(superArray* a);
  bool checkArrayPopulated(superArray* a);
  void _populateArray(superArray* a, int size, int min, int max);  
  void initArray(superArray* a, int size);
  void _populateBasicBitch(superArray* superArrays) ;
  void clearArray(superArray* a);
  bool checkSorted(superArray* a);
  void _sortShowdown(superSort* superSorts, int sortAlg1, int sortAlg2, int nMax);
  void initSuperSort(superSort* a, void(*f), char* name, char* runtime);
  void sortShowdown(superSort* superSorts);

  void mainMenu (superArray* superArrays, bool* running, superSort* superSorts, listNode** lists, stackNode** stacks, queueNode** queues, treeNode** trees);

//ARRAY MANAGEMENT
  void manageArray (superArray* superArrays, superArray* a, int atoiInput, superSort* superSorts);
  void arrayList(superArray* superArrays);
  void manageArrays (superArray* superArrays, superSort* superSorts);

//LINKED LIST MANAGEMENT
  void linkedLists(listNode** lists);
  void manageList(listNode** lists, listNode* a, int input);
  void populateList(listNode* a);
  void _populateList(listNode* a, int size, int  min, int max);
  void addNode(listNode* a);
  void _addNode(listNode*a, int value);
  void removeNode(listNode* a);
  void findNode(listNode* a);
  int _findNode(listNode* a, int atoiInput);
  void printList(listNode* a);
  void _linkedListList(listNode** lists);

//STACK MANAGEMENT
  void manageStacks(stackNode** stacks);
  void manageStack(stackNode** stacks, int input);
  int pop(stackNode** stacks, int input);
  void push(stackNode** stacks, stackNode* s, int input);
  void _stackList(stackNode** stacks);

//QUEUE MANAGEMENT
  void manageQueues(queueNode** queues);
  void manageQueue(queueNode** queues, int input);
  int deQueue(queueNode** queues, int input);
  void enQueue(queueNode* q);
  void _enQueue(queueNode*q, int value);
  void _queueList(queueNode** queues);

//SEARCH Algorithms
  //menu
  void searchMenu(superArray* superArrays, superArray* a); 
  //executor
  void runSearch(superArray* a, int(*f)(superArray* a, int search)); 
  //algorithms
  int binarySearch(superArray* a, int search);
  int linearSearch(superArray *a, int search);

//SORT Algorithms
  //menu
  void sortMenu(superArray* superArrays, superArray* a, superSort* superSorts);
  //executor
  void runSort(superArray* a, void(*f)(superArray* a));
  //algorithms
  void insertionSort(superArray* a);
  void selectionSort(superArray* a);
  void bubbleSort(superArray* a);
  void mergeSort(superArray* a);
  void quickSort(superArray* a);
  void _quickSort(superArray*, int, int);
  int partition(superArray* a, int low, int high);

//COMPOSITE Algorithms
  //menu
  void compositeMenu(superArray* superArrays, superSort* superSorts);
  //executor
  void runComposite(superArray* superArrays, int userInput); 
  //algorithms
  void sortedMerge(superArray* a, superArray* b, superArray* c);
  void blindMerge(superArray* a, superArray* b, superArray* c);
  void unionArray(superArray* a, superArray* b, superArray* c);
  void intersection(superArray* a, superArray* b, superArray* c);
// ---------------PROTOTYPES END----------------

//---ALGORITHM FUNCTION ARRAYS---
  //composite algorithms
  void(*compositeAlgorithms[])(superArray*, superArray*, superArray*) = {
    blindMerge,
    sortedMerge,
    intersection,
    unionArray
  };

  //sort algorithms
  void(*sortAlgorithms[])(superArray*) = {
    bubbleSort,
    selectionSort,
    insertionSort,
    mergeSort,
    quickSort
  };

  //search algorithms
  int(*searchAlgorithms[])(superArray*, int) = {
    binarySearch,
    linearSearch
  };
//---END ALGORITHM FUNCTION ARRAYS---

void initArray(superArray* a, int size){
  a->size = size;
  a->array = (int *)malloc(size * sizeof(int));
}

void _populateArray(superArray* a, int size, int min, int max){  
  a->size = size;
  a->array = (int *)realloc(a->array, a->size * sizeof(int));

  for (int i = 0; i < a->size; i++) a->array[i] = rand() % (max - min + 1) + min;
}

bool checkArrayPopulated(superArray* a){
  //check if array is populated
    if (a->size == 0){
    // printf("\nARRAY NOT YET POPULATED. POPULATE/GENERATE ONE FIRST.\n");
    return 0;
  }
  return 1;
}

void clearArray(superArray* a){
  a->size = 0;
  a->array = (int *)malloc(a->size * sizeof(int));
}

int validateConvertInput(){
  char input[5];
  bool inputValid = false;
  while (!inputValid) {
    scanf("%s",input);
    if (input[0] == '0') return 0; //handle atoi returning 0 on char
    if (atoi(input) == 0) printf("\n---Invalid Input---\n");
    else return atoi(input);
  }
  return 0;
}

int max(int a, int b){
  return (a > b) ? a : b;
}

void _manualArrayEntry(superArray* a){
  char userInput[25];
  int tempSize = 0;
  int tempArray[25];
  int input;

  printf("\nMANUAL ARRAY ENTRY\n"
  "Enter kill value:\n");
  int killValue = validateConvertInput();

  do{
    printf("Enter value or kill command(%d)", killValue);
    
    input = validateConvertInput();

    if (killValue != input) {
      tempArray[tempSize] = input;
      tempSize++;
    }

    //realloc temp array at intervals of 25
    if (tempSize %25 == 0)
      *tempArray = (int)realloc(tempArray, (2 * tempSize) * sizeof(int));
      
  } while (killValue != input);

  //populate a size attribute, increase array length, input values
  a->size = tempSize;
  a->array = (int *)realloc(a->array, a->size * sizeof(int));
  for (int i = 0; i < a->size; i++ ){
    a->array[i] = tempArray[i];
  }
}

bool checkSorted(superArray* a){
  for(int i = 0; i < a->size - 1; i++) {
    if (a->array[i] > a->array[i+1]) return false;
  }
  return true;
}

void populateArray(superArray* a){
  char userInput[25];
  int size, min, max;

  printf("Enter Array Size, or enter '-1' for manual entry\n");
  scanf("%s",userInput);
  int atoiInput = atoi(userInput);

  if (atoiInput == -1) _manualArrayEntry(a);

  else {
    size = atoiInput;
  
    printf("Enter Integer Min\n");
    scanf("%d", &min);

    printf("Enter Integer Max\n");
    scanf("%d", &max);

    _populateArray(a, size, min, max);
  }
}

void printArray(superArray* a){
  if (checkArrayPopulated(a)) {
  printf("[");

  if (a->size >= 100){
    for (int i = 0; i < 3; i++)printf("%d, ", a->array[i]);
    printf("..., ");
    for (int i = a->size-3; i < a->size; i++){
      if (i == a->size - 1) printf("%d]", a->array[i]);
      else printf("%d, ", a->array[i]);
    }
  }

  else {
    for (int i = 0; i < a->size; i++){
      if (i == a->size - 1) printf("%d]", a->array[i]);
      else printf("%d, ", a->array[i]);
    }
  }
  }
}

void arrayList(superArray* superArrays) {
  printf("\n-------------------------------------------------\n"
  "Array - Size - Sorted?\n");
    for (int i = 0; i<10; i++){
      printf("%-8d%-7d",i, superArrays[i].size);
      int sorted = checkSorted(&superArrays[i]);
      printf("%d    ",sorted);
      printArray(&superArrays[i]);
      printf("\n");
    }
    printf("-------------------------------------\n");
}

void swap (int* a, int* b) {
  *b = *a + *b;
  *a = *b - *a;
  *b = *b - *a;
}

int abs(int x){
  return (x >= 0) ? x : -1 * x;
}

void swapArrayValues(int* array, int a, int b){
  int temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}

void bubbleSort(superArray* a){
  bool sorted = false;
  int size = a->size;

  while (!sorted){
    sorted = true;

    for (int i = 0; i < a->size - 1; i++){
      if (a->array[i] > a->array[i + 1]){
        swapArrayValues(a->array, i, i + 1);
        sorted = false;
      }
    }
    size--;
  }
}

void selectionSort(superArray* a){
  int minIndex = 0; //index of smallest element encountered on current pass
  int target = 0;   //index of the first element of the unsorted part of the array
                    //in other words, the element we are preparing to swap if it's
                    //not the smallest thing left
  for (int i = 0; i < a->size; i++){
    minIndex = target;
    for (int j = target; j < a->size; j++){
      if (a->array[j] < a->array[minIndex]){
        minIndex = j;
      }
    }
    if (a->array[minIndex] < a->array[target]) swapArrayValues(a->array, minIndex, target);
    target++;
  }
}

void insertionSort(superArray* a){
  int marker, j;
  for (int i = 1; i < a->size; i++){
    marker = a->array[i];

    for (j = i-1; j >= 0; j--){
      if (a->array[j] > marker) {
        a->array[j+1] = a->array[j];
      }
      else break;
    }
    a->array[j+1] = marker;
  }
}

int linearSearch(superArray *a, int search){
  for (int i = 0; i < a->size; i++){
    if (a->array[i] == search){
      return i;
    }
  }
  return -1;
}

int binarySearch(superArray* a, int search){
  int mid = (a->size / 2 - 1);
  int midModifier = (a->size / 4);
  int stopCount = 0;

  while (1){
    if (search > a->array[mid]){
      printf("value %d > array position: %d (%d)\n\n", search, mid, a->array[mid]);
      mid = mid + midModifier - 1;
    }

    else if (search < a->array[mid]){
      printf("value %d < array position: %d (%d)\n\n", search, mid, a->array[mid]);
      mid = mid - midModifier + 1;
    }

    else if (search == a->array[mid]) return mid;

    midModifier = (midModifier / 2) + 1;

    //stop if value not found, functional up to size = 1024
    stopCount++;
    if (stopCount == 10) return -1;
  }
}

void runSearch(superArray* a, int(*f)(superArray* a, int search)){
  if (checkArrayPopulated(a)){
    int search;
    printf("\nEnter value to search for:\n");
    scanf("%d", &search);
    printf("--------------------\n");
    int foundValue = (*f)(a, search);

    if (foundValue >= 0){
      printf("LOCATED VALUE (%d) at array position: %d\n", search, foundValue);
    }
    else if (foundValue == -1){
      printf("Value not in array you stupidass trick\n");
    }
    
    printf("--------------------\n");
  }
}

void searchMenu(superArray* superArrays, superArray* a){
  bool running = true;

  while(running) {
    arrayList(superArrays);
    printf(
      "SEARCH ALGORITHM MENU\n"
      "--------------------------\n"
      "(1) Binary Search\n"
      "(2) Linear Search\n"
      "(3) Back\n"
    );
    int input = validateConvertInput();

    //binary search
    if (input == 1) runSearch(a, searchAlgorithms[0]);

    //linear search
    if (input == 2) runSearch(a, searchAlgorithms[1]);
    
    else if (input == 3) running = false;
  }
}

int partition(superArray* a, int low, int high) {
  int pivot = a->array[(high + low) / 2];
  int i = low - 1;
  int j = high + 1;
  
  while(1){
    do {i = i + 1;} while (a->array[i] < pivot);

    do {j = j - 1;} while (a->array[j] > pivot);

    if (i >= j) return j;

    swapArrayValues (a->array, i, j);
  }
}

void _quickSort(superArray* a, int low, int high){
  if (low < high) {
    int p = partition(a, low, high);
    _quickSort(a, low, p);
    _quickSort(a, p + 1, high);
  }
}

void quickSort(superArray* a) {
  _quickSort(a, 0, a->size-1);
}

void mergeSort(superArray* a){
  int l = 0; //start point of array
  int r = a->size; //end point of array
  int m = (l + r) / 2; //midpoint of array

  //initialize temp arrays (superarrays to fit with DCU)
  int sizeLeft  = m - l;
  int sizeRight = r - m;
  superArray leftArray = 
    {.size = sizeLeft, .array = (int*)malloc(sizeof(int) * sizeLeft)};
  superArray rightArray = 
    {.size = sizeRight, .array = (int*)malloc(sizeof(int) * sizeRight)};

  if (l < r - 1) {
    //copy data to temp arrays
    for (int i = 0; i < sizeLeft; i++) 
      leftArray.array[i] = a->array[l + i]; 

    for (int i = 0; i < sizeRight; i++) 
      rightArray.array[i] = a->array[m + i]; 

    mergeSort(&leftArray);
    mergeSort(&rightArray);

    //call sorted merge, which takes in 3 superarrays and transforms the third into a composite sorted array
    sortedMerge(&leftArray, &rightArray, a);
  }
}

void runSort(superArray* a, void(*f)(superArray* a)){
  if (checkArrayPopulated(a)){
    printf("\nORIGINAL ARRAY:\n");
    printArray(a);
    (*f)(a);
    printf("\nSORTED ARRAY:\n");
    printArray(a);
  }
}

void blindMerge(superArray* a, superArray* b, superArray* c){
  //set target array new size 
  c->size = (a->size + b->size);
  c->array = (int*)realloc(c->array, (a->size + b->size) * sizeof(int));

  //append array a to c
  for (int i = 0; i< a->size; i++){
    c->array[i] = a->array[i];
  }
  //append array b to c, after a
  for (int i = a->size; i < c->size; i++){
    c->array[i] = b->array[i - a->size];
  }

  printf("\nMerged target array:\n");
  printArray(c);
}

//merge two sorted arrays into a new sorted array
void sortedMerge(superArray* a, superArray* b, superArray* c){
  bool sorted = false;
  int size = 0;
  int i = 0;
  int j = 0;

  //set target array new size 
  c->size = (a->size + b->size);
  c->array = (int*)realloc(c->array, (a->size + b->size) * sizeof(int));

  while (i < a->size || j < b->size) {
    //if we've reached the end of array a
    if (i == a->size){
      c->array[i + j] = b->array[j];
      j++;
    }
    //if we've reached the end of array b
    else if (j == b->size){
      c->array[i + j] = a->array[i];
      i++;
    }
    //given that we haven't reached the end of either array, if a's element < b's element
    else if (a->array[i] < b->array[j]) {
      c->array[i+j] = a->array[i];
      i++;
    }
    //catch-all else which is essentially "we haven't reached the end of either array and b's element <= a's element"
    else {
      c->array[i+j] = b->array[j];
      j++;
    }
  }
}

void intersection(superArray* a, superArray* b, superArray* c){
  int flag = 1;

  for (int i = 0; i < a->size; i++) { //loop through array a
    for (int j = 0; j < b->size; j++){  //for each a element, loop array b
      if (a->array[i] == b->array[j]){  //find matches
        for (int k = 0; k < c->size; k++){  //check c for duplicates
          flag = 1;  //reset flag variable
          if (a->array[i] == c->array[k]) { //duplicate found
            flag = 0; //set flag for duplicate found
            break; //break loop
          }
        }
        if (flag == 1) { //duplicate was not found for entire c loop
          c->size++;  //initialize new c array size to accept new element
          c->array = (int *)realloc(c->array, c->size * sizeof(int));
          c->array[c->size - 1] = a->array[i];
          break; //prevent unnecessary loops through array b after intersection           located
        }
      }
    }
  }
  if (c->size == 0) printf("\nNo Intersection nigga");
  else {
    printf("\n\nIntersection Array:\n\n");
    printArray(c);
  }
}

void unionArray(superArray* a, superArray* b, superArray* c){
  for (int i = 0; i < a->size; i++) { //loop through array a
    if (linearSearch(c, a->array[i]) == -1) { //search c for element
      c->size++;  //initialize new c array size to accept new element
      c->array = (int *)realloc(c->array, c->size * sizeof(int));
      c->array[c->size - 1] = a->array[i];
    }
  }
  
  //repeat for b array
  for (int i = 0; i < b->size; i++) {
    if (linearSearch(c, b->array[i]) == -1) {
      c->size++;  //initialize new c array size to accept new element
      c->array = (int *)realloc(c->array, c->size * sizeof(int));
      c->array[c->size - 1] = b->array[i];
    }
  }
  
  printf("\nUnion Array:\n");
  printArray(c);
}

void runComposite(superArray* superArrays, int userInput){
  int userIntInput1, userIntInput2;
  superArray* a;
  superArray* b;
  superArray* c;

  //select first Array
  printf("\nSpecify first array:\n");
  scanf("%d",&userIntInput1);
  a = &superArrays[userIntInput1];

  //select second array
  printf("Specify second array:\n");
  scanf("%d",&userIntInput2);
  b = &superArrays[userIntInput2];

  if (a->size > 0 && b->size > 0){
    //select target array
    printf("Specify target array:\n");
    scanf("%d",&userIntInput1);
    c = &superArrays[userIntInput1];

    printf("array 1:\n");
    printArray(a);
    printf("\narray 2:\n");
    printArray(b);

    clearArray(c);

    compositeAlgorithms[userInput](a,b,c);
  }
  
  else {
    printf("Selected array(s) not yet populated. Popoulate first mothafucka.\n");
  }
}

void sortMenu(superArray* superArrays, superArray* a,  superSort* superSorts){
  bool running = true;
  while (running) {
    arrayList(superArrays);
    printf(
      "SORT ALGORITHM MENU:\n"
      "--------------------------\n"
      "   (1) %s - %s\n"
      "   (2) %s - %s\n"
      "   (3) %s - %s\n"
      "   (4) %s - %s\n"
      "   (5) %s - %s\n"
      "   (6) Back\n",
        superSorts[0].name, superSorts[0].runTime, superSorts[1].name, superSorts[1].runTime, superSorts[2].name, superSorts[2].runTime, superSorts[3].name, superSorts[3].runTime, superSorts[4].name, superSorts[4].runTime);

      int input = validateConvertInput();

      //bubble sort
      if (input == 1) runSort(a, sortAlgorithms[0]);

      //selection sort
      else if (input == 2) runSort(a, sortAlgorithms[1]);

      //insertion sort
      else if (input == 3) runSort(a, sortAlgorithms[2]); 

      //mergeSort
      else if (input == 4) runSort(a, sortAlgorithms[3]); 

      //quickSort
      else if (input == 5) runSort(a, sortAlgorithms[4]);

      //back
      else if (input == 6) running = false;
  }
}

void manageArray (superArray* superArrays, superArray* a, int atoiInput, superSort* superSorts){
  int min = 0;
  int max = 0;
  bool running = true;

  while(running) {
    printf("\nARRAY MENU - Array %d:\n"
    "--------------------------\n", atoiInput);
    printArray(a);
    printf(
      "\n(1) Populate \n"
      "(2) Sort \n"
      "(3) Search \n"
      "(4) Back\n");
    int input = validateConvertInput();

    //populate array
    if (input == 1)
      populateArray(a);

    // sort
    else if (input == 2)
      sortMenu(superArrays,a, superSorts);

    // search
    else if (input == 3)
      searchMenu(superArrays, a);

    else if (input == 4) running = false;
  }
}


void _sortShowdown(superSort* superSorts, int sortAlg1, int sortAlg2, int nMax) {
  //initialize arrays
  superArray a;
  initArray(&a,2);
  superArray b;
  
  int n = 2;
  int arraySwapper = 0;

  for (int i = 1; i <= nMax * 2; i++) {
    //populate 2 identical arrays of length n, 0-100
    _populateArray(&a, n, 0, 1023);
    initArray(&b,n);
    for (int j = 0; j < a.size; j++){ //copy array a to b
      b.array[j] = a.array[j];
    }

    clock_t t;//initiate timer
    t = clock();
    //run sort 1 or 2
    if (arraySwapper % 2 == 0){ 
      sortAlgorithms[sortAlg1](&a); //run sort
    }
    else sortAlgorithms[sortAlg2](&b);

    t = clock()-t; //end timer

    if (checkSorted(&a) || checkSorted(&b)) { //double check sorted and algorithms are working
      double time_taken = ((double)t)/CLOCKS_PER_SEC; // calc time in seconds
      if (arraySwapper % 2 == 0){
        printf("%-13s() on %d elements(n^%d) took %f seconds to execute \n", superSorts[sortAlg1].name, n, (i / 2 + 1),time_taken); 
      }
      else {
        printf("%-13s() on %d elements(n^%d) took %f seconds to execute \n\n", superSorts[sortAlg2].name, n, (i / 2),time_taken); 
        n = n * 2;
      }
      arraySwapper++;
    }
    else printf("\n\nyour algorithm is fucked up\n\n");
  }
}

void sortShowdown(superSort* superSorts) {
  char userInput1[5];
  char userInput2[5];
  bool running = true;

  //print sorting algorithms
  while(running) {
    for (int i = 0; i < 5; i++) {
      printf("(%d) %s - %s\n", i, superSorts[i].name, superSorts[i].runTime);
    }
    printf("(9) - CANCEL\n");
    
    printf("Select 2 Sorting Algorithms to compare:\nFirst:");

    int atoiInput1 = validateConvertInput();
    printf("Second:");
    int atoiInput2 = validateConvertInput();
    if ((0 <= atoiInput1) && (0 <= atoiInput2) && (atoiInput1 < 5) && (atoiInput2 < 5)) {  
      printf("Specify 'n' for max array size 2^n that will be benchmarked.\n");
        int n = validateConvertInput();
        _sortShowdown(superSorts, atoiInput1, atoiInput2, n);    
    }
    else if (userInput1[0] == '9' || userInput2[0] == '9') {
      printf("\n\nCANCELLED\n\n");
      running = false;
    }
  }
}

void compositeMenu(superArray* superArrays, superSort* superSorts){
  char userInput[25];
  bool running = true;

  while(running) {
    arrayList(superArrays);
    printf(
      "COMPOSITE ALGORITHM MENU:\n"
      "(0) Blind Merge\n"
      "(1) Sorted Merge\n"
      "(2) Intersection\n"
      "(3) Union\n"
      "(4) Sort Showdown\n"
      "(5) Back\n");

    int userInput = validateConvertInput();

    if (userInput == 0) runComposite(superArrays, userInput);

    else if (userInput == 1) runComposite(superArrays, userInput);

    else if (userInput == 2) runComposite(superArrays, userInput);

    else if (userInput == 3) runComposite(superArrays, userInput);

    else if (userInput == 4) sortShowdown(superSorts);
    
    else if (userInput == 5) running = false;

  }
}

void _populateBasicBitch(superArray* superArrays){
  _populateArray(&superArrays[0], 9, 0, 19);
  _populateArray(&superArrays[1], 9, 0, 19);
  // runSort(&superArrays[0], sortAlgorithms[0]);
  // runSort(&superArrays[1], sortAlgorithms[0]);
}

void printList(listNode* a){
  listNode* current = a;
  printf("[");
  while(current->next != NULL) {
    printf("%d->",current->data);
    current = current->next;
  }
  printf("%d]",current->data);
}

void _linkedListList(listNode** lists) {
  printf("\n-------------------------------------------------\n"
  "List ID - Values\n");
  for (int i = 0; i < 5; i++){
    printf("%-8d  ",i);
    printList(lists[i]);
    printf("\n");
  }
  printf("-------------------------------------------------\n");
}

void _stackList(stackNode** stacks) {
  printf("\n-------------------------------------------------\n"
  "Stack ID - Top Value\n");
  for (int i = 0; i < 5; i++){
    printf("%-8d   %d",i, stacks[i]->data);
    printf("\n");
  }
  printf("-------------------------------------------------\n");
}

void _queueList(queueNode** queues) {
  printf("\n-------------------------------------------------\n"
  "Queue ID - Front Value\n");
  for (int i = 0; i < 5; i++){
    printf("%-8d   %d",i, queues[i]->data);
    printf("\n");
  }
  printf("-------------------------------------------------\n");
}

int _findNode(listNode* a, int atoiInput) {
  listNode* current = a;
  int index = 1;
  while(1){
    if (current->data == atoiInput) {
      return index;
    }

    else if (current->next == NULL) {
      return 0;
    }

    else {
      current = current->next;
      index++;
    }
  }
}

void findNode(listNode* a){
  char userInput[5];
  int targetValue;

  printf("Input value to search for: ");

  targetValue = validateConvertInput();
  int index = _findNode(a,targetValue);

  if (index >= 1) 
    printf("\nValue(%d) found at Index(%d)\n", targetValue,index);

  else printf("\nValue not found\n");
}

void removeNode(listNode* a){
  char userInput[5];
  int targetValue;
  listNode* current = a;
  listNode* previous = a; //set to a to initialize it easier so dont have to malloc it
  int currentValue = current->data;

    printf("Input value of element to remove: ");
    targetValue = validateConvertInput();

    if (current != NULL && current->data == targetValue){
      if (current->next == NULL) free(a);
      else *a = *current->next;
      return;
    }

    while(currentValue != targetValue && current != NULL) {
      previous = current;
      current = current->next;
      currentValue = current->data;
    }

    if (current == NULL) printf("\nValue not in LIST you FUCK. NICE TRY PRICK\n");

    else previous->next = current->next;
}

void _addNode(listNode*a, int value) {
  listNode* current = a;

  if (!a->data) { //check if no head value
    current->data = value; //populate head
  }
  else { 
    while(1){ //loop to end of list
      if (current->next == NULL) { //if listNode has no next, create new listNode
        listNode* newNode = (listNode*)malloc(sizeof(listNode));
        newNode->data = value;
        current->next = newNode;
        
        break;
      }
      else  //if listNode has a next element, traverse to next
        current = current->next;
    }
  }
}

void addNode(listNode* a){
  bool running = true;

  while(running) {
    printf("Enter value to append to list: ");
    int input = validateConvertInput();
      _addNode(a,input);
      running = false;
  }
}

void _populateList(listNode* a, int size, int  min, int max){
  a->next = NULL;
  for (int i = 0; i < size; i++) {
    _addNode(a, rand() % (max - min + 1) + min);
  }
}
void problemPopulateList(listNode* a){
  a->next = NULL;
  for (int i = 0; i < 10; i++) {
    _addNode(a, rand() % (100 - 0 + 1) + 0);
  }
}

void populateList(listNode* a){
  char userInput[5];
  int size, min, max;

  printf("Enter list size\n");
  size = validateConvertInput();

  printf("Enter randomized value min:\n");
  min = validateConvertInput();

  printf("Enter randomized value max:\n");
  max = validateConvertInput();

  _populateList(a,size,min,max);
}

void manageList(listNode** lists, listNode* a, int input){
  bool running = true;

  while(running) {
    _linkedListList(lists);
    printf("Managing List %d:\n"
    "(1) - Add listNode member to list (auto-creates head)\n"
    "(2) - Remove Element from list\n"
    "(3) - Find Element and return index\n"
    "(4) - Populate List\n"
    "(5) - Back\n", input);
    int validInput = validateConvertInput();

    if (validInput == 1) addNode(a);

    else if (validInput == 2) removeNode(a);

    else if (validInput == 3) findNode(a);

    else if (validInput == 4) populateList(a);

    else if (validInput == 5) running = false;
  }
}

void linkedLists(listNode** lists) {
  bool running = true;
  while(running) {
  _linkedListList(lists);
  printf("LINKED LISTS MENU\n"
  "(0-4) Enter ID of list you wish to manage:\n"
  "(5)   Back\n");

  int validInput = validateConvertInput();

  if (validInput >= 0 && validInput < 5) 
    manageList(lists, lists[validInput], validInput);

  else if (validInput == 5) running = false;
  }
}


void push(stackNode** stacks, stackNode* s, int input){
  bool running = true;
    printf("Enter value to add to top of Stack: ");
    stackNode* newStack = (stackNode*)malloc(sizeof(stackNode));
    newStack->data = validateConvertInput();
    newStack->next = stacks[input];
    stacks[input] = newStack;
}

int pop(stackNode** stacks, int input){
  int temp;
  if (!stacks[input]->data) {
    printf("No values in stack");
    return 0;
  }
  else {
    temp = stacks[input]->data;
    if (!stacks[input]->next) {
      free(stacks[input]);
      stacks[input] = (stackNode*)malloc(sizeof(stackNode));
    }
    else stacks[input] = stacks[input]->next;
    return temp;
  }
}

void _enQueue(queueNode* q, int value) {
  queueNode* current = q;
  if (!q->data) { //check if no head value
    current->data = value; //populate head
  }

  else { 
    while(1){ //loop to end of list
      if (current->next == NULL) { //if listNode has no next, create new listNode
        queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
        newNode->data = value;
        current->next = newNode;
        
        break;
      }
      else  //if listNode has a next element, traverse to next
        current = current->next;
    }
  }
}

void enQueue(queueNode* q){
  bool running = true;

  while(running) {
    printf("Enter value to add to end of Queue: ");
    int input = validateConvertInput();
    _enQueue(q,input);
    running = false;
  }
}

int deQueue(queueNode** queues, int input){
  bool running = true;
  int temp;

  while(running) {
    if (!queues[input]->data) {
      printf("Queue Empty. Nothing to deQueue");
      return 0;
    }
    else {
      temp = queues[input]->data;
      if (!queues[input]->next){
        free(queues[input]);
        queues[input] = (queueNode*)malloc(sizeof(queueNode));
      }
      else queues[input] = queues[input]->next;
      return temp;
    }
  }
  return 0;
}

void manageQueue(queueNode** queues, int input){
  bool running = true;

  while(running) {
    _queueList(queues);
    printf("Managing Queue %d:\n"
    "(1) - Enqueue (auto-creates Front)\n"
    "(2) - Dequeue\n"
    "(5) - Back\n", input);
    int validInput = validateConvertInput();

    if (validInput == 1) enQueue(queues[input]);

    else if (validInput == 2) deQueue(queues, input);

    else if (validInput == 5) running = false;
  }
}

void manageStack(stackNode** stacks, int input){
  bool running = true;

  while(running){
    _stackList(stacks);
    printf("Managing Stack %d:\n"
    "(1) - Push (auto-creates Top)\n"
    "(2) - Pop\n"
    "(5) - Back\n", input);
    int validInput = validateConvertInput();

    if (validInput == 1) push(stacks, stacks[input], input);

    else if (validInput == 2) pop(stacks, input);

    else if (validInput == 5) running = false;
  }
}

void manageQueues(queueNode** queues){
  bool running = true;

  while(running){
    _queueList(queues);
    printf("QUEUES MENU\n"
    "(0-4) Enter ID of Queue you wish to manage:\n"
    "(5)  Back\n");

    int validInput = validateConvertInput();

    if (validInput >= 0 && validInput < 5) 
      manageQueue(queues, validInput);

    else if (validInput == 5) running = false;
    }
}

void manageStacks(stackNode** stacks){
  bool running = true;

  while(running){
    _stackList(stacks);
    printf("STACKS MENU\n"
    "(0-4) Enter ID of Stack you wish to manage:\n"
    "(5)  Back\n");

    int validInput = validateConvertInput();

    if (validInput >= 0 && validInput < 5) 
      manageStack(stacks, validInput);

    else if (validInput == 5) running = false;
    }
}

void manageArrays (superArray* superArrays, superSort* superSorts){
  bool running = true;
  while(running) {
    arrayList(superArrays);
    printf("ARRAY MANAGEMENT\n"
    "(0-9) Select Array to Manage\n"
    "(10) Composite Algorithms Menu \n"
    "(11)  Basic Bitch Populate Option\n"
    "(12)  Back\n");
    int validInput = validateConvertInput();

    if (validInput >= 0 && validInput < 10) 
      manageArray(superArrays, &superArrays[validInput], validInput, superSorts);

    else if (validInput == 10)
      compositeMenu(superArrays, superSorts);

    else if (validInput == 11) 
      _populateBasicBitch(superArrays);

      else if (validInput == 12) running = false;
  }
}

void bubbleSortLinkedList(listNode*a){
  bool sorted = false;
  
  while(!sorted) {
    sorted = true;
    listNode* current = a;
    listNode* next = current->next;

    while (current->next != NULL){
      if (current->data > next->data) {
        int temp = current->data;
        current->data = next->data;
        next->data = temp;
        sorted = false;
      }
      else {
        current = next;
        next = current->next;
      }
    }
  }
}

void reverseList(listNode** lists, listNode* a){
  listNode* previous = NULL;
  listNode* current = a;
  listNode* next = NULL;

  while(current!= NULL) {
    next = current->next;
    current->next = previous;

    previous = current;
    current = next;
  }
  lists[0] = previous;
}

char* concatString(char* a, char* b){
  char *returnString;
  returnString = (char*)malloc(strlen(a)+strlen(b)+3);
  returnString[0] = '\0';
  strcat(returnString, a);
  strcat(returnString, " - ");
  strcat(returnString, b);

  return returnString;
}

void charPush(stackNodeChar** head, char input){
  bool running = true;
  stackNodeChar* newStack = (stackNodeChar*)malloc(sizeof(stackNodeChar));
  newStack->data = input;
  newStack->next = *head;
  *head = newStack;
}

char charPop(stackNodeChar** stack){
  stackNodeChar* head = *stack;
  if (!head) return '0';
  *stack = head->next;
  head->next = NULL;
  free(head);
  return head->data;
}

char* parenBalanced(char* paren){
  stackNodeChar* stack;
  int size = strlen(paren);
  int i = 0;
  bool balanced = true;

  while((i < size) && balanced) {
    if (paren[i] == '(') charPush(&stack, paren[i]);
    else if (charPop(&stack) == '0')  return concatString(paren, "False");
    i++;
  }
  if (charPop(&stack) != '0') return concatString(paren, "False");

  return concatString(paren, "True");
}

void printListMid(listNode* a){
  listNode* current = a;
  int* temp = malloc(1*(sizeof(int))); //init temp not in stack so can be resized
  int i = 0;

  //traverse list, bumping all elements into an array
  while(current->next != NULL) {
    temp[i] = current->data;
    current = current->next;
    i++;
    temp = realloc(temp, 1 + i * sizeof(int));
  }
  printf("%d",temp[i/2]); //print array[mid]
}

void manageProblems(listNode** lists){
  bool running = true;
  while(running){
    printf("\nPROBLEMS LIST\n"
    "(1) Bubble Sort Linked List\n"
    "(2) Reverse Linked List\n"
    "(3) Print Linked List Mid\n"
    "(4) Check Parenthesis Balance\n"
    "(5) Back\n");

    int input = validateConvertInput();

    if (input == 1) {
      problemPopulateList(lists[0]);
      printList(lists[0]);
      printf("\n");
      bubbleSortLinkedList(lists[0]);
      printf("\n");
      printList(lists[0]);
    }
    else if (input == 2){
      problemPopulateList(lists[0]);
      printf("\n");
      printList(lists[0]);
      printf("\n");
      reverseList(lists,lists[0]);
      printList(lists[0]);
    }
    else if (input == 3){
      problemPopulateList(lists[0]);
      printList(lists[0]);
      printf("\n");
      printListMid(lists[0]);
    }
    else if (input == 4){
      stackNodeChar* stacks[5];
      for(int i = 0; i < 5; i++) {
        stacks[i] = (stackNodeChar*)malloc(sizeof(stackNodeChar));
      }
      char* parenProblems[12] = {
        "((()))",
        "((((()())))((",
        "((((()))))",
        "((((()))))(())",
        "((((()))))()",
        ")((()()(",
        "()()()()()",
        "((())))",
        "((((())))",
        "((((()())))",
        "()(()(())))",
        "())(()(())))"};
      for (int i = 0; i < 12; i++) {
        printf("%s\n", parenBalanced(parenProblems[i]));
      }
    }
    else if (input == 5)
      running = false;
  }
}

typedef struct treeQueueNode {
  treeNode* data;
  struct treeQueueNode* next;
} treeQueueNode;

treeNode* newTreeNode (int data) {
  treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

void enQueueTree(treeQueueNode* q, treeNode* root) {
  treeQueueNode* current = q;
  if (!q->data) current->data = root;

  else { 
    while(1){
      //if listNode has no next, create new node
      if (current->next == NULL) { 
        treeQueueNode* newNode = (treeQueueNode*)malloc(sizeof(treeQueueNode));
        newNode->data = root;
        current->next = newNode;
        break;
      }
      //if node has a next element, traverse to next
      else current = current->next;
    }
  }
}

treeNode* deQueueTree(treeQueueNode* queue) {
  if (!queue->data) return NULL;
  else {
    treeNode* temp = queue->data;
    if (!queue->next){
      free(queue);
      queue = (treeQueueNode*)malloc(sizeof(treeQueueNode));
    }
    else *queue = *queue->next;
    return temp;
  }
}

int bstHeight(treeNode* root){
  if (root) return max(bstHeight(root->left), bstHeight(root->right)) + 1;
  else return 0;
}

treeNode* invertTree(treeNode* root){
  if (root == NULL) return NULL;
  treeNode* temp = root->right;
  root->right = invertTree(root->left);
  root->left = invertTree(temp);
  return root;
}

void printLevel(treeNode* root, int level){
  if (root != NULL && level == 0) printf("%d ", root->data);
  else if (root != NULL){
    printLevel(root->left, level - 1);
    printLevel(root->right, level - 1);
  }
}

void printPrettyTree(treeNode* root){
  int i;
  int levelCount = bstHeight(root);
  for (i = 0; i < levelCount; i++){
    printLevel(root, i);
    printf("\n");
  }
}

int count(treeNode* root) {
  return (root) ? 1 + count(root-> left) + count(root-> right) : 0;
}

//traverse inOrder
int copyBSTtoArray(treeNode *root, int* arr, int i){
  if(root == NULL) return i;
  if (root->left != NULL) i = copyBSTtoArray(root->left, arr, i);
  arr[i] = root->data;
  i++;
  if (root->right != NULL) i = copyBSTtoArray(root->right, arr, i);
  return i;
}

treeNode* buildBalancedBST(int* arr, int start, int end){
  if (start > end) return NULL;
  int mid = ((start + end) / 2);
  treeNode* root = newTreeNode(arr[mid]);
  root->left = buildBalancedBST(arr, start, mid - 1);
  root->right = buildBalancedBST(arr, mid + 1, end);
  return root;
}

void balanceBST(treeNode* root){
  int size = count(root);
  //calloc() allocates the memory and also initializes the allocated memory block to zero.
  int* arr = calloc(size, sizeof(int));
  copyBSTtoArray(root, arr, 0);
  free(root);
  root = buildBalancedBST(arr, 0, size - 1);
}

treeNode* findMin(treeNode* node){
  if (node == NULL) return NULL;
  else if (node->left != NULL) return findMin(node->left);
  return node;
}


bool isBalanced(treeNode* root){
  return ((!root) || ((isBalanced(root->left) && isBalanced(root->right) && abs(bstHeight(root->left) - bstHeight(root->right)) <= 1)))? true : false;
}

void printPreOrder(treeNode* root) {
  if (root == NULL) return;
  printf("%d", root->data);
  printPreOrder(root->left);
  printPreOrder(root->right);
}

void printPostOrder(treeNode* root) {
  if (root == NULL) return;
  printPostOrder(root->left);
  printPostOrder(root->right);
  printf("%d", root->data);
}

void printInOrder(treeNode* root) {
  if (root == NULL) return;
  printInOrder(root->left);
  printf("%d", root->data);
  printInOrder(root->right);
}

void heapify(int* heap, int i, int size){
  int root = i; //index of parent
  int left = (2 * i) + 1; //index of left child
  int right = (2 * i) + 2; //index of right child

  //left < size checks if left exists
  if (left < size && heap[left] > heap[root]) {
    root = left;
  }

  if (right < size && heap[right] > heap[root]){
    root = right;
  }
  
  if (root != i){
    swap(&heap[root], &heap[i]);
    heapify(heap, root, size);
  }
}

int* buildMaxHeap(int* heap, int size){
  //as left child = (2*parentIndex)+1, and right child = (2*parentIndex)+2, to start at bottom up, the bottom-most parent's index of an array size n can be located by the index of  (n -2) /2
  for (int i = (size - 2) / 2; i >= 0; i--){
    heapify(heap, i, size);
  }
  return heap;
}

void heapSort(int* heap, int size) {
  heap = buildMaxHeap(heap, size);
  while (size > 1) {
    swap(&heap[0], &heap[size-1]);
    size--;
    heapify(heap, 0, size);
  }
}

bool isHeap(int* arr, int i, int n) { 
  if (i > (n - 2)/2)  return true; 
    
  if (arr[i] >= arr[2 * i + 1] && arr[i] >= arr[2 * i + 2] &&  isHeap(arr, 2 * i + 1, n) && isHeap(arr, 2 * i + 2, n)) return true; 
  
  return false; 
} 

void printLevelWise(treeNode* root) {
  treeQueueNode* levels = (treeQueueNode*)malloc(sizeof(treeQueueNode));
  treeNode* current = root;

  while(current) {
    printf("%d", current->data);
    if (current->left) enQueueTree(levels, current->left);
    if (current->right) enQueueTree(levels, current->right);
    current = deQueueTree(levels);
  }
}

void printTreeMenu(treeNode* tree) {
  bool running = true;
  while(running) {
    printf("\nPrint Traversal Options:\n"
    "(1) preOrder\n"
    "(2) postOrder\n"
    "(3) inOrder\n"
    "(4) levelWise\n"
    "(5) Back \n");
    int input = validateConvertInput();
    if (input == 1) printPreOrder(tree);
    else if (input == 2) printPostOrder(tree);
    else if (input == 3) printInOrder(tree);
    else if (input == 4) printLevelWise(tree);
    else if (input == 5) running = false;
  }
}

void treeList(treeNode** trees){
  printf("\n-------------------------------------------------\n"
  "Tree ID - Root\n");
  for (int i = 0; i < 5; i++){
    printf("%-8d  ",i);
    printf("%d",trees[i]->data);
    printf("\n");
  }
  printf("-------------------------------------------------\n");
}

//0 inserts left, 1 inserts right
treeNode* insertRandomLeaf(treeNode* node, int data){
  treeNode* newBranch = newTreeNode(data);
  
  if (rand() % 2 == 0) node->left = newBranch;
  else node->right = newBranch;
  return node;
}

treeNode* _searchBST(treeNode* node, int key){
  if (!node || node->data == key) return node;
  else if (key < node->data) return _searchBST(node->left, key);
  else if (key > node->data) return _searchBST(node->right, key);
}

void searchBST(treeNode* node) {
  printf("Enter Integer Value to search for\n");
  int data = validateConvertInput();

  if (!_searchBST(node,data)) printf("value not found");
}

treeNode* _insertTreeNode(treeNode* node, int key) {
  if (node == NULL) return newTreeNode(key);
  else if (key > node->data) node->right = _insertTreeNode(node->right,key);
  else node->left = _insertTreeNode(node->left,key);
  return node;
}

void insertTreeNode(treeNode* node){
  printf("Enter Integer Value to Insert\n");
  int data = validateConvertInput();

  if (!node) {
    printf("--Inserted first node to Tree--\n");
    node = newTreeNode(data);
  }
  else if (!node->data) node->data = data;
  else node = _insertTreeNode(node, data);
}

treeNode* _deleteTreeNode(treeNode* node, int key){
  //searching for key
  if(node == NULL) return NULL;
  if (key > node->data) node->right = _deleteTreeNode(node->right, key);
  else if(key < node->data) node->left = _deleteTreeNode(node->left, key);

  //deletion of found key
  else {
    //no children
    if(node->left == NULL && node->right == NULL) {
      free(node);
      return NULL;
    }
    //one child
    else if(node->left == NULL || node->right == NULL) {
      treeNode *temp;
      if(node->left==NULL) temp = node->right;
      else temp = node->left;
      free(node);
      return temp;
    }
    //two children
    else {
      treeNode *temp = findMin(node->right);
      node->data = temp->data;
      node->right = _deleteTreeNode(node->right, temp->data);
    }
  }
  return node;
}

void deleteTreeNode(treeNode* node) {
  printf("Enter value to remove\n");
  int key = validateConvertInput();

  if (_searchBST(node,key)) node = _deleteTreeNode(node, key);
  else printf("Value not found in tree\n");
}

void manageTree(treeNode* node, int input) {
  bool running = true;
  while(running) {
    printf("\nTREE #%d MANAGEMENT\n", input);
    printf("(1) Insert Value\n"
    "(2) Search for Value\n"
    "(3) Remove Value\n"
    "(4) Print Tree\n"
    "(5) Back\n");
    
    int validInput = validateConvertInput();

    if (validInput == 1) insertTreeNode(node);
    if (validInput == 2) searchBST(node);
    if (validInput == 3) deleteTreeNode(node);
    if (validInput == 4) printTreeMenu(node);
    if (validInput == 5) running = false;
  }
}

void manageTrees(treeNode** trees) {
  bool running = true;
  while(running){
    treeList(trees);
    printf("\nTREE MANAGEMENT\n"
    "(0-4) Select Tree to Manage\n"
    "(5) Back\n");
    int validInput = validateConvertInput();

    if (validInput >= 0 && validInput < 5) manageTree(trees[validInput],validInput);
    

    if (validInput == 5) running = false;
  }
}

void mainMenu (superArray* superArrays, bool* running, superSort* superSorts, listNode** lists, stackNode** stacks, queueNode** queues, treeNode** trees){
  printf("\nMAIN MENU\n"
  "(1) Arrays\n"
  "(2) Linked Lists\n"
  "(3) Stacks\n"
  "(4) Queues\n"
  "(5) Trees\n"
  "(6) Problems\n"
  "(7) Quit\n");

  int validInput = validateConvertInput();

  if (validInput == 1) manageArrays(superArrays, superSorts);
  else if (validInput == 2) linkedLists(lists);
  else if (validInput == 3) manageStacks(stacks);
  else if (validInput == 4) manageQueues(queues);
  else if (validInput == 5) manageTrees(trees);
  else if (validInput == 6) manageProblems(lists);
  else if (validInput == 7) *running = false;
}

void initSuperSort(superSort* a, void(*f), char* name, char* runtime) {
  a->function = (f);
  a->name = (char*)malloc(strlen(name) * sizeof(char));
  a->runTime = (char*)malloc(strlen(runtime) * sizeof(char));
  strcpy(a->name, name);
  strcpy(a->runTime, runtime);
}

int main(){
  bool running = true;
  srand(time(NULL)); //call srand in main so it only seeds once, this prevents duplicates when rand() is called multiple times within one second

  //initialize superArrays
  superArray superArrays[10];
  for (int i = 0; i < 10; i++) initArray(&superArrays[i], 0);

  //initialize superSorts array and elements
  superSort superSorts[5];
  initSuperSort(&superSorts[0], sortAlgorithms[0], "bubbleSort", "n^2");
  initSuperSort(&superSorts[1], sortAlgorithms[1], "selectionSort", "n^2");
  initSuperSort(&superSorts[2], sortAlgorithms[2], "insertionSort", "n^2");
  initSuperSort(&superSorts[3], sortAlgorithms[3], "mergeSort", "nlog(n)");
  initSuperSort(&superSorts[4], sortAlgorithms[4], "quickSort", "nlog(n)");

  //initialize array of 20 head nodes
  listNode* lists[5];
  for(int i = 0; i < 5; i++) lists[i] = (listNode*)malloc(sizeof(listNode));

  //initilate array of stacks
  stackNode* stacks[5];
  for(int i = 0; i < 5; i++) stacks[i] = (stackNode*)malloc(sizeof(stackNode));

  //initialize array of queues
  queueNode* queues[5];
  for(int i = 0; i < 5; i++) queues[i] = (queueNode*)malloc(sizeof(queueNode));

  //initialize array of trees
  treeNode* trees[5];
  for(int i = 0; i < 5; i++) trees[i] = (treeNode*)malloc(sizeof(treeNode));




  //testing code for heapSort
    // treeNode* test = newTreeNode(5); _insertTreeNode(test,1); _insertTreeNode(test,10); _insertTreeNode(test,4); _insertTreeNode(test,30); _insertTreeNode(test,2); _insertTreeNode(test,8); _insertTreeNode(test,7); _insertTreeNode(test,6); _insertTreeNode(test,11); _insertTreeNode(test,10); _insertTreeNode(test,31);
  // printf("\ninOrder Tree:\n"); printInOrder(test);
  // printf("\n");
  // //heapify using max heap
  
  // int arr[] = {3,5,7,10,11,12,15,16,1,2,4,8};
  // int size = sizeof(arr)/sizeof(arr[0]);
  // printf("Array:\n");
  // for(int i = 0; i<size; i++) printf("%d,",arr[i]);
  // printf("\n");

  // heapSort(arr, size);
  // printf("Heapsorted Array:\n");

  // buildMaxHeap(arr,size);
  // printf("build max heap array:\n");
  // printf("\nisMaxHeap?:%d\n",isHeap(arr,0,size));
  // for(int i = 0; i<size; i++) printf("%d,",arr[i]);

  //main program loop
  while (running) mainMenu(superArrays, &running, superSorts, lists, stacks, queues,trees);
  
  return 0;
}