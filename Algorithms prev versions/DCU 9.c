//DCU phase 9.666666
//
//  3: remove a value from the tree (removes the first instance of a given value)
//    (actually when they remove value, let them enter for example: 6 to remove the first
//    6 that is found. or 6* to remove all instances of 6 and make sure to mention
//    to the user that they can suffix their value with a * to remove all instances)
//  4: change everything to BST's
//    https://www.geeksforgeeks.org/binary-search-tree-data-structure/
//  5: write a function that finds a node. and indicates its position in any way you want. i just want you to be utilizing the cool properties of BST's to efficiently find a value



//david notes:
//  invert,balance,find height of, determine if balanced
//  and then heap sort
//  and then on to c++

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

typedef struct node{
  int data; 
  struct node* next; 
} node;

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
  void swap(int* array, int a, int b);
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

  void mainMenu (superArray* superArrays, bool* running, superSort* superSorts, node** lists, stackNode** stacks, queueNode** queues, treeNode** trees);

//ARRAY MANAGEMENT
  void manageArray (superArray* superArrays, superArray* a, int atoiInput, superSort* superSorts);
  void arrayList(superArray* superArrays);
  void manageArrays (superArray* superArrays, superSort* superSorts);

//LINKED LIST MANAGEMENT
  void linkedLists(node** lists);
  void manageList(node** lists, node* a, int input);
  void populateList(node* a);
  void _populateList(node* a, int size, int  min, int max);
  void addNode(node* a);
  void _addNode(node*a, int value);
  void removeNode(node* a);
  void findNode(node* a);
  int _findNode(node* a, int atoiInput);
  void printList(node* a);
  void _linkedListList(node** lists);

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

void swap(int* array, int a, int b){
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
        swap(a->array, i, i + 1);
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
    if (a->array[minIndex] < a->array[target]) swap(a->array, minIndex, target);
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

    swap (a->array, i, j);
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

void printList(node* a){
  node* current = a;
  printf("[");
  while(current->next != NULL) {
    printf("%d->",current->data);
    current = current->next;
  }
  printf("%d]",current->data);
}

void _linkedListList(node** lists) {
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

int _findNode(node* a, int atoiInput) {
  node* current = a;
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

void findNode(node* a){
  char userInput[5];
  int targetValue;

  printf("Input value to search for: ");

  targetValue = validateConvertInput();
  int index = _findNode(a,targetValue);

  if (index >= 1) 
    printf("\nValue(%d) found at Index(%d)\n", targetValue,index);

  else printf("\nValue not found\n");
}

void removeNode(node* a){
  char userInput[5];
  int targetValue;
  node* current = a;
  node* previous = a; //set to a to initialize it easier so dont have to malloc it
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

void _addNode(node*a, int value) {
  node* current = a;

  if (!a->data) { //check if no head value
    current->data = value; //populate head
  }
  else { 
    while(1){ //loop to end of list
      if (current->next == NULL) { //if node has no next, create new node
        node* newNode = (node*)malloc(sizeof(node));
        newNode->data = value;
        current->next = newNode;
        
        break;
      }
      else  //if node has a next element, traverse to next
        current = current->next;
    }
  }
}

void addNode(node* a){
  bool running = true;

  while(running) {
    printf("Enter value to append to list: ");
    int input = validateConvertInput();
      _addNode(a,input);
      running = false;
  }
}

void _populateList(node* a, int size, int  min, int max){
  a->next = NULL;
  for (int i = 0; i < size; i++) {
    _addNode(a, rand() % (max - min + 1) + min);
  }
}
void problemPopulateList(node* a){
  a->next = NULL;
  for (int i = 0; i < 10; i++) {
    _addNode(a, rand() % (100 - 0 + 1) + 0);
  }
}

void populateList(node* a){
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

void manageList(node** lists, node* a, int input){
  bool running = true;

  while(running) {
    _linkedListList(lists);
    printf("Managing List %d:\n"
    "(1) - Add node member to list (auto-creates head)\n"
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

void linkedLists(node** lists) {
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
      if (current->next == NULL) { //if node has no next, create new node
        queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
        newNode->data = value;
        current->next = newNode;
        
        break;
      }
      else  //if node has a next element, traverse to next
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

void bubbleSortLinkedList(node*a){
  bool sorted = false;
  
  while(!sorted) {
    sorted = true;
    node* current = a;
    node* next = current->next;

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

void reverseList(node** lists, node* a){
  node* previous = NULL;
  node* current = a;
  node* next = NULL;

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
    if (paren[i] == '('){
      charPush(&stack, paren[i]);
    }
    else {
      if (charPop(&stack) == '0')  return concatString(paren, "False");
    }
    i++;
  }
  if (charPop(&stack) != '0') return concatString(paren, "False");

  return concatString(paren, "True");
}

void printListMid(node* a){
  node* current = a;
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

void manageProblems(node** lists){
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

void enQueueTree(treeQueueNode* q, treeNode* root) {
  treeQueueNode* current = q;
  if (!q->data) { //check if no head value
    current->data = root;
  }

  else { 
    while(1){
      //if node has no next, create new node
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
      else {
        *queue = *queue->next;
      }
      return temp;
    }
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

treeNode* newTreeNode (int data) {
  treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
  temp->data = data;
  return temp;
}

//0 inserts left, 1 inserts right
treeNode* insertRandomLeaf(treeNode* node, int data){
  treeNode* newBranch = newTreeNode(data);
  
  if (rand() % 2 == 0) node->left = newBranch;
  else node->right = newBranch;
  return node;
}

//prototype
treeNode* _insertTreeNode(treeNode* node, int data);

void insertTreeNode(treeNode* node){
  printf("Enter Integer Value to Insert\n");
  int data = validateConvertInput();

  if (!node) {
    printf("--Inserted first branch to Tree--\n");
    node = newTreeNode(data);
  }

  else if (!node->data) node->data = data;

  else _insertTreeNode(node,data);
}

treeNode* _insertTreeNode(treeNode* node, int data) {
  bool running = true;

  if (!node->left && !node->right){
    node = insertRandomLeaf(node, data);
    return node;
  }
  else if (!node->left && node->right){
    node->left = newTreeNode(data);
    return node;
  }
  else if (node->left && !node->right){
    node->right = newTreeNode(data);
    return node;
  }
  
  //if both exist
  if (rand() % 2 == 0) node->right = _insertTreeNode(node->right, data); //traverse right
  else node->left = _insertTreeNode(node->left, data);  //traverse left

  return node;
}

void _deleteTreeNode(treeNode* node, int key) {
  if (node == NULL) return;

  else if (node->data != key) {
    if (node->left) _deleteTreeNode(node->left, key);
    if (node->right) _deleteTreeNode(node->right, key);
  }

  else{ 
    if(node->right && node->left) {
      treeNode* tempNode = newTreeNode(node->right->data);
      node = node->left;
      node->left = tempNode;
    }
    else {
      if (node->left == NULL) node = node->right;
      else if (node->right == NULL) node = node->left;
    }
  }
  return;
}

void deleteTreeNode(treeNode* node) {
  printf("Enter value to remove\n");
  int key = validateConvertInput();

  _deleteTreeNode(node, key);
}

void manageTree(treeNode* node, int input) {
  bool running = true;
  while(running) {
    
    printf("\nTREE #%d MANAGEMENT\n", input);
    printf("(1) Insert Value\n"
    "(2) Remove Value\n"
    "(3) Print Tree\n"
    "(4) Back\n");
    
    int validInput = validateConvertInput();

    if (validInput == 1) {
      insertTreeNode(node);
    }
    if (validInput == 2) {
      deleteTreeNode(node);
    }
    if (validInput == 3) {
      printTreeMenu(node);
    }
    if (validInput == 4) running = false;
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

    if (validInput >= 0 && validInput < 5) {
      manageTree(trees[validInput],validInput);
    }

    if (validInput == 5) 
      running = false;
  }
}

void mainMenu (superArray* superArrays, bool* running, superSort* superSorts, node** lists, stackNode** stacks, queueNode** queues, treeNode** trees){
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
  node* lists[5];
  for(int i = 0; i < 5; i++) {
    lists[i] = (node*)malloc(sizeof(node));
  }

  //initilate array of stacks
  stackNode* stacks[5];
  for(int i = 0; i < 5; i++) {
    stacks[i] = (stackNode*)malloc(sizeof(stackNode));
  }

  //initialize array of queues
  queueNode* queues[5];
  for(int i = 0; i < 5; i++) {
    queues[i] = (queueNode*)malloc(sizeof(queueNode));
  }

  //initialize array of trees
  treeNode* trees[5];
  for(int i = 0; i < 5; i++) {
    trees[i] = (treeNode*)malloc(sizeof(treeNode));
  }

    // testing tree:
    //        1
    //   2        3
    // 4   5

    trees[0]->data = 1;
    trees[0]->left = (treeNode*)malloc(sizeof(treeNode));
    trees[0]->left->data = 2;
    trees[0]->left->left = (treeNode*)malloc(sizeof(treeNode));
    trees[0]->left->left->data = 4;
    trees[0]->left->right = (treeNode*)malloc(sizeof(treeNode));
    trees[0]->left->right->data = 5;
    trees[0]->right = (treeNode*)malloc(sizeof(treeNode)); 
    trees[0]->right->data = 3;
    // trees[0] = insertTreeNode(trees[0],1,5);


    // trees[0] = newTreeNode(1);
    // trees[0] = _insertTreeNode(trees[0],2);
    // trees[0] = _insertTreeNode(trees[0],3);
    // trees[0] = _insertTreeNode(trees[0],4);
    // trees[0] = _insertTreeNode(trees[0],5);
    // trees[0] = _insertTreeNode(trees[0],6);
    // trees[0] = _deleteTreeNode(trees[0],5);
    
    
    // trees[0] = newTreeNode(3);
    
    // printf("%d",trees[0]->left->data);
    // printf("%d",trees[0]->right->data);


    // while(1) {
    // removeTreeNode(trees[0]);
    // }


    
    printf("\nPre:\n");
    printPreOrder(trees[0]);
    printf("\n\nPost:\n");
    printPostOrder(trees[0]);
    printf("\n\nIn:\n");
    printInOrder(trees[0]);
    printf("\n\nLevelWise:\n");
    printLevelWise(trees[0]);
  //main program loop
  // while (running) mainMenu(superArrays, &running, superSorts, lists, stacks, queues,trees);
  
  return 0;
}