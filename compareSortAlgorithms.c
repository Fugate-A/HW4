
//Andrew Fugate

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mergeSort(int a[], int l, int r);
void merge( int a[], int l, int mid, int r);

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void merge( int a[], int l, int mid, int r)
{
  int sizeLeft = mid - l + 1;
  int sizeRight = r - mid;

  int *L = malloc( sizeof(int) * sizeLeft );
  extraMemoryAllocated++;
  int *R = malloc( sizeof(int) * sizeRight );
  extraMemoryAllocated++;

  for( int i = 0; i < sizeLeft; i++ )
    {
      L[i] = a[l+i];     
    }

  for( int j = 0; j < sizeRight; j++ )
    {
      R[j] = a[mid+1+j];
    }

  int i = 0;
  int j = 0;
  int k = l;

  while( i < sizeLeft && j < sizeRight )
    {
      if( L[i] < R[j])
      {
        a[k] = L[i];
        i++;
        //k++;
      }
      else              //either the same or R > L
      {
        a[k] = R[j];
        j++;
        //k++;
      }
      k++;
    }
  
  while( i < sizeLeft )
    {
      a[k] = L[i];
      i++;
      k++;
    }
  
  while( j < sizeRight )
    {
      a[k] = R[j];
      j++;
      k++;
    }

  free(L);
  free(R);
}

void mergeSort(int pData[], int l, int r)
{
	if(r > l)  
  {
    int mid = (l+r)/2;

    mergeSort(pData, l, mid);

    mergeSort(pData, mid+1, r);

    merge(pData, l, mid, r);
  }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	for( int i = 0; i < n; i++ )
    {
      int j;
      int hand = pData[i];
      for( j = i-1; j >= 0; j-- )
        {
          if( hand < pData[j] )
          {
            pData[j+1] = pData[j];
          }

          else
          {
            break;  
          }
          
        }

      pData[j+1] = hand;
    
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated

void swap( int *x, int *y )
{
  int temp = *x;
  *x = *y;
  *y = temp; 
}

void bubbleSort(int* pData, int n)
{
	int i;
  for( i = 0; i < n-1; i++ )
    {
      for( int j = 0; j < n-i-1; j++ )
        {
          if( pData[j] > pData[j+1] )
          {
            swap( &pData[j], &pData[j+1] );
          }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	for( int i = 0; i < n-1; i++ )
    {
      //find min from i to n-1
      int minIdx = i;
      
      for( int j = i+1; j < n; j++ )  //i+i because j should be after i
        {
          if( pData[j] < pData[minIdx] )
          {
            //a[minIdx] = a[j];
            minIdx = j;
          }
        }

        //swap( &a[minIdx], &a[i]);
        int temp = pData[i];
        pData[i] = pData[minIdx];
        pData[minIdx] = temp;
      
      }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for( int NoD = 0; NoD < dataSz; NoD++ )
			fscanf( inFile, "%d", &((*ppData)[NoD]));

		fclose(inFile);
	}
	
	return dataSz;
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