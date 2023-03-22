#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
int *leftArray;
int *rightArray;

void mergeSortSaveMemory(int pData[], int l, int r);

void mergeSort(int pData[], int l, int r) {
  // make two list arrays
  leftArray = (int *)malloc(sizeof(int) * ((r-l+1)/2));    // just half the list 
  extraMemoryAllocated += sizeof(int) * ((r-l+1)/2);
  
  rightArray = (int *)malloc(sizeof(int) * ((r-l+1)/2));   // other half of the list 
  extraMemoryAllocated += sizeof(int) * ((r-l+1)/2);
  
  mergeSortSaveMemory(pData, l, r);
  
  free(leftArray);
  free(rightArray);
}

void mergeSortSaveMemory(int pData[], int l, int r) {
  int middle;
  middle = ( l + r ) / 2;
  if (l >= r ) {
 return;
  }
  if (r !=0) 
  mergeSortSaveMemory(pData, l, middle);
  mergeSortSaveMemory(pData, middle+1, r);
  
  // Merge the two lists => (l, middle) and (middle+1, r)
  // use saved memory space leftArray and rightArray
  
  int x;
  for (x = 0; x < (middle-l+1); x++) {
      leftArray[x] = pData[x+l];
  }
  for (int x = 0; x < (r-middle); x++) {
      rightArray[x] = pData[x+middle+1];
  }
  
  int y;
  int finalPosn = l;
  x = 0;
  y = 0;
  // copy over the smallest from each list to final position
  while ((x < (middle-l+1)) && (y < (r-middle))) {
      if (leftArray[x] <= rightArray[y]) {
         pData[finalPosn++] = leftArray[x++];
      } else {
         pData[finalPosn++] = rightArray[y++];
      }
  }
  // copy the rest of the left list
  while (x < (middle-l+1)) {
      pData[finalPosn++] = leftArray[x++];
  }
  // copy the rest of the right list
  while (y < (r-middle)) {
      pData[finalPosn++] = rightArray[y++];
  }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
int x;
int y;
int temp;
    extraMemoryAllocated += sizeof(int);
    for (x = 1; x < n; x++) { // check each one
   y = x;
        temp = pData[y];
   while ((pData[y-1] > temp) &&(y > 0)) {
            pData[y] = pData[y-1];
   y--;
}
pData[y] = temp;
}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
int x;
int y;
int temp;
    extraMemoryAllocated += sizeof(int);
bool swapMade;
    swapMade = true;
x = 0;
    while (swapMade == true) { 
        swapMade = false;
        for (y = x+1; y < n; y++) {
            if (pData[x] > pData[y]) {
                temp = pData[x];
                pData[x] = pData[y];
                pData[y] = temp;
swapMade = true;
            }
        } 
x++; 
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
int x;
int y;
int findSmallest = 0;
int temp;
    extraMemoryAllocated = sizeof(int);
    for (x = 0; x < n - 1; x++) {
findSmallest = x;
        for (y = x + 1; y < n; y++) {            // look at the rest of the list
            if (pData[findSmallest] > pData[y])  // is this the new smallest number?
                findSmallest = y;                // keep it
        }
// swap the smallest to the current place
        temp = pData[x];
        pData[x] = pData[findSmallest];
        pData[findSmallest] = temp;
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
FILE* inFile = fopen(inputFileName,"r");
int dataSize = 0;
    int x;
int valueIn;
if (inFile) {
   fscanf(inFile,"%d\n", &dataSize);
   *ppData = (int *)malloc(sizeof(int) * dataSize);
int *ppPtr = *ppData;
for(x = 0; x < dataSize; ++x) {
fscanf(inFile,"%d", &valueIn);
*ppPtr = valueIn;
ppPtr = ppPtr + 1;
}
} else {
printf("Could not find file %s\n", inputFileName);
}

return dataSize;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
int i, sz = dataSz - 100;
printf("\tData:\n\t");
for (i=0;i<100;++i)
{
printf("%d ",pData[i]);
}
printf("\n\t");

for (i=sz;i<dataSz;++i)
{
printf("%d ",pData[i]);
}
printf("\n\n");
}

int main(void)
{
clock_t start, end;
int i;
    double cpu_time_used;
char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

for (i=0;i<3;++i)
{
int *pDataSrc, *pDataCopy;
int dataSz = parseData(fileNames[i], &pDataSrc);

if (dataSz <= 0)
continue;

pDataCopy = (int *)malloc(sizeof(int)*dataSz);

printf("---------------------------\n");
printf("Dataset Size : %d\n",dataSz);
printf("---------------------------\n");

printf("Selection Sort:\n");
memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
extraMemoryAllocated = 0;
start = clock();
selectionSort(pDataCopy, dataSz);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
printArray(pDataCopy, dataSz);

printf("Insertion Sort:\n");
memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
extraMemoryAllocated = 0;
start = clock();
insertionSort(pDataCopy, dataSz);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
printArray(pDataCopy, dataSz);

printf("Bubble Sort:\n");
memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
extraMemoryAllocated = 0;
start = clock();
bubbleSort(pDataCopy, dataSz);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
printArray(pDataCopy, dataSz);

printf("Merge Sort:\n");
memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
extraMemoryAllocated = 0;
start = clock();
mergeSort(pDataCopy, 0, dataSz - 1);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
printArray(pDataCopy, dataSz);

free(pDataCopy);
free(pDataSrc);
}

}
