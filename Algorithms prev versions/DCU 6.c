


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> //time benchmarking, random number generation seed

typedef struct {
  int* array;
  int size;
} superArray;

// ---------------PROTOTYPES START----------------
//HELPER FUNCTIONS
  void invalidInput();
  void swap(int* array, int a, int b);
  void printArray(superArray* a);
  void populateArray(superArray* a);
  void _manualArrayEntry(superArray* a);
  bool checkArrayEqual(char* firstArray, char* secondArray);
  bool checkArrayPopulated(superArray* a);
  void _populateArray(superArray* a, int size, int min, int max);  
  void initArray(superArray* a, int size);
  void _populateBasicBitch(superArray* superArrays) ;
  void clearArray(superArray* a);
  bool validateIntegerInput(char* userInput);
  bool checkSorted(superArray* a);

//MAIN MENUS
  void mainMenu (superArray* superArrays, bool* running);
  void manageArray (superArray* superArrays, superArray* a, int atoiInput);
  void arrayList(superArray* superArrays);
  void sortShowdown(superArray* superArrays);

//FUNCTION ARRAYS
  int(*searchAlgorithms[])(superArray*, int);
  void(*mergeAlgorithms[])(superArray*, superArray*, superArray*);
  void(*sortAlgorithms[])(superArray*);

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
  void sortMenu(superArray* superArrays, superArray* a);
  //executor
  void runSort(superArray* a, void(*f)(superArray* a));
  //algorithms
  void insertionSort(superArray* a);
  void selectionSort(superArray* a);
  void bubbleSort(superArray* a);
  void mergeSort(superArray* a);
  void quickSort(superArray* a, int, int);
    int _pivot(superArray*a, int, int);

//COMPOSITE Algorithms
  //menu
  void compositeMenu(superArray* superArrays);
  //executor
  void runComposite(superArray* superArrays, char* userInput); 
  //algorithms
  void sortedMerge(superArray* a, superArray* b, superArray* c);
  void blindMerge(superArray* a, superArray* b, superArray* c);
  void unionArray(superArray* a, superArray* b, superArray* c);
  void intersection(superArray* a, superArray* b, superArray* c);
// ---------------PROTOTYPES END----------------

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

bool checkArrayEqual(char* firstArray, char* secondArray){
  for (int i = 0; i < strlen(firstArray); i++){
    if (firstArray[i] != secondArray[i])  return false;
  }
  return true;
}

void clearArray(superArray* a){
  a->size = 0;
  a->array = (int *)malloc(a->size * sizeof(int));
}

bool validateIntegerInput(char* userInput) {
  if (userInput[0] == '0') {
    return true;
  }
  else if (atoi(userInput) == 0) return false;
  else return true;
}

void _manualArrayEntry(superArray* a){
  char userInput[25];
  char killValue[25];
  int tempSize = 0;
  int tempArray[25];
  int atoiInput = 0;

  printf("\nMANUAL ARRAY ENTRY\n"
  "Enter kill value:\n");
  scanf("%s", killValue);

  do{
    printf("Enter value or kill command(%s)", killValue);
    scanf("%s", userInput);
    
    if (validateIntegerInput(userInput))  {
      atoiInput = atoi(userInput);

      if (!checkArrayEqual(killValue, userInput)) {
        tempArray[tempSize] = atoiInput;
        tempSize++;
      }

      //realloc temp array at intervals of 25
      if (tempSize %25 == 0)
        *tempArray = (int)realloc(tempArray, (2 * tempSize) * sizeof(int));
      }

    else
      printf("Invalid/Non-Integer Input\n");
  } while (!checkArrayEqual(killValue, userInput));

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

void(*sortAlgorithms[])(superArray*) = {
  bubbleSort,
  selectionSort,
  insertionSort,
  mergeSort,
  // quickSort
};

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

//search algorithms
int(*searchAlgorithms[])(superArray*, int) = {
  binarySearch,
  linearSearch
};

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
  char userInput[25];
  bool inputValid = false;

  while(!inputValid) {
    arrayList(superArrays);
    printf(
      "SEARCH ALGORITHM MENU\n"
      "--------------------------\n"
      "(1) Binary Search\n"
      "(2) Linear Search\n"
      "(3) Back\n"
    );
    scanf("%s", userInput);

    //binary search
    if (userInput[0] == '1') runSearch(a, searchAlgorithms[0]);

    //linear search
    if (userInput[0] == '2') runSearch(a, searchAlgorithms[1]);
    
    else if (userInput[0] == '3') inputValid = true;
  }
}

int _pivot(superArray*a, int low, int high){
  int i = 0; //current element
  int k = 1; //tracks amount of spaces pivot must be swapped at end of loop
  //high is array/subarray length
  int pivot = a->array[high];
  while ((i + k) <= high) {
    if (a->array[i] < pivot) i++;

    else {
      swap(a->array, i, high-k);
      k++;
    }
  }
  swap(a->array, high, (high - k) + 1);
  return k;
}

void quickSort(superArray* a, int low, int high){
  int i = 0; //current element
  int k = 1; //tracks amount of spaces pivot must be swapped at end of loop
  //high is array/subarray length
  int pivot = a->array[high];

  while ((i + k) <= high) {
    if (a->array[i] < pivot) i++;

    else {
      swap(a->array, i, high-k);
      k++;
    }
  }
  swap(a->array, high, (high - k) + 1);

  //recursively sort subarrays
  //excludes pivots new position because it is now in correct index
  if (low < high - 1) {
    quickSort(a, low, high - k);
    quickSort(a, (high - k) + 2, high);
  }
  
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

void(*mergeAlgorithms[])(superArray*, superArray*, superArray*) = {
  blindMerge,
  sortedMerge,
  intersection,
  unionArray
};

void runComposite(superArray* superArrays, char* userInput){
  int userIntInput1, userIntInput2;
  superArray* a;
  superArray* b;
  superArray* c;
  int atoiInput = atoi(userInput);

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

    mergeAlgorithms[atoiInput](a,b,c);
  }
  
  else {
    printf("Selected array(s) not yet populated. Popoulate first mothafucka.\n");
  }
}

void sortMenu(superArray* superArrays, superArray* a){
  char userInput[25];
  bool inputValid = false;
  while (!inputValid) {
    arrayList(superArrays);
    printf(
      "SORT ALGORITHM MENU:\n"
      "--------------------------\n"
      "n^2 SORTING ALGORITHMS\n"
      "   (1) bubbleSort\n"
      "   (2) selectionSort\n"
      "   (3) insertionSort\n"
      "nlog(n) SORTING ALGORITHMS\n"
      "   (4) mergeSort\n"
      "   (5) quickSort\n"
      "(6) Back\n");
    
      scanf("%s", userInput);

      //bubble sort
      if (userInput[0] == '1') runSort(a, sortAlgorithms[0]);

      //selection sort
      else if (userInput[0] == '2') runSort(a, sortAlgorithms[1]);

      //insertion sort
      else if (userInput[0] == '3') runSort(a, sortAlgorithms[2]); 

      //mergeSort
      else if (userInput[0] == '4') runSort(a, sortAlgorithms[3]); 

      //quickSort
      else if (userInput[0] == '5') {
        quickSort(a,0,a->size-1);
      }

      //back
      else if (userInput[0] == '6') inputValid = true;

      else invalidInput();
  }
}

void manageArray (superArray* superArrays, superArray* a, int atoiInput){
  int min = 0;
  int max = 0;
  bool inputValid = false;
  char userInput[5];

  while(!inputValid) {
    arrayList(superArrays);
    printf("ARRAY MENU - Array %d:\n"
    "--------------------------\n", atoiInput);
    printArray(a);
    printf(
      "\n(1) Populate \n"
      "(2) Sort \n"
      "(3) Search \n"
      "(4) Back\n");
    scanf("%s", userInput);

    //populate array
    if (userInput[0] == '1')
      populateArray(a);

    // sort
    else if (userInput[0] == '2')
      sortMenu(superArrays,a);

    // search
    else if (userInput[0] == '3')
      searchMenu(superArrays, a);

    else if (userInput[0] == '4') inputValid = true;

    else invalidInput();
  }

}

void invalidInput(){
  printf("\nInvalid Input Idiot\n");
}

void compositeMenu(superArray* superArrays){
  char userInput[25];
  bool inputValid = false;

  while(!inputValid) {
    arrayList(superArrays);
    printf(
      "COMPOSITE ALGORITHM MENU:\n"
      "(0) Blind Merge\n"
      "(1) Sorted Merge\n"
      "(2) Intersection\n"
      "(3) Union\n"
      "(4) Back\n");

    scanf("%s", userInput);

    if (userInput[0] == '0') runComposite(superArrays, &userInput[0]);

    else if (userInput[0] == '1') runComposite(superArrays, &userInput[0]);

    else if (userInput[0] == '2') runComposite(superArrays, &userInput[0]);

    else if (userInput[0] == '3') runComposite(superArrays, &userInput[0]);
    
    else if (userInput[0] == '4') inputValid = true;

    else invalidInput();
  }
}

void _populateBasicBitch(superArray* superArrays){
  _populateArray(&superArrays[0], 9, 0, 19);
  _populateArray(&superArrays[1], 9, 0, 19);
  // runSort(&superArrays[0], sortAlgorithms[0]);
  // runSort(&superArrays[1], sortAlgorithms[0]);
}

void sortShowdown(superArray* superArrays) {
  char userInput[25];
  printf("Select 2 Sorting Algorithms");
  scanf("%s", userInput);
}

void mainMenu (superArray* superArrays, bool* running){
  char userInput[25];
  bool inputValid = false;
  
  while(!inputValid){
    arrayList(superArrays);
    printf("MAIN MENU\n"
    "(0-9) Enter designation of array you wish to manage:\n"
    "(10) Composite Algorithms Menu \n"
    "(-1) Quit\n"
    "(55) Basic Bitch Populate Option\n");

    scanf("%s", userInput);

    int atoiInput = atoi(userInput);

    if (atoiInput >= 0 && atoiInput < 10) 
      manageArray(superArrays, &superArrays[atoiInput], atoiInput);

    else if (atoiInput == 55) 
      _populateBasicBitch(superArrays);

    else if (atoiInput == 10)
      compositeMenu(superArrays);

    else if (atoiInput == -1){
      inputValid = true;
      *running = false;
    }
  
    else invalidInput();
  }
}

int main(){
  bool running = true;
  srand(time(NULL)); //call srand in main so it only seeds once, this prevents duplicates when rand() is called multiple times within one second

  //initialize superArrays
  superArray superArrays[10];
  for (int i = 0; i < 10; i++) initArray(&superArrays[i], 0);

  //main program loop
  while (running) mainMenu(superArrays, &running);
  
  return 0;
}