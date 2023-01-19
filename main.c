#include <stdio.h>

// quick sort implementation
void swap(int *n1, int *n2){
    int n = *n1;
    *n1 = *n2;
    *n2 = n;
}

int partition(int *jobs, int *deadline, int *profit, int start, int end){
    int pivot = profit[end];
    int pIndex = start;
    int i;
    for(i=start; i<end; i++){
        if(profit[i] > pivot){
            swap(&deadline[i], &deadline[pIndex]);
            swap(&profit[i], &profit[pIndex]);
            swap(&jobs[i], &jobs[pIndex]);
            pIndex++;
        }
    }
    swap(&deadline[pIndex], &deadline[end]);
    swap(&profit[pIndex], &profit[end]);
    swap(&jobs[pIndex], &jobs[end]);
    return pIndex;
}

void quickSort(int *jobs, int *deadline, int *profit, int start, int end){
    if(start < end){
        int pivot = partition(jobs, deadline, profit, start, end);
        quickSort(jobs, deadline, profit, start, pivot-1);
        quickSort(jobs, deadline, profit, pivot+1, end);
    }
}
// end of quick sort implementation

void jobSequencing(int max_deadline, int *jobs, int *deadline, int *profit){
    int granttChart[max_deadline];
    int totalProfit = 0;

    int i;
    for(i=0 ; i<max_deadline ; i++)
        granttChart[i] = -1;

    for(i=0 ; i<max_deadline ; i++){
        int index = deadline[i]-1;
        if(granttChart[index] == -1){
            granttChart[index] = jobs[i];
            totalProfit += profit[i];
        }
        else{
            while (index != 0){
                if(granttChart[--index] == -1){
                 granttChart[index] = jobs[i];
                 totalProfit += profit[i];
                 break;
                }
            }
        }
    }

    printf("\n\n");
    for(i=0 ; i<max_deadline ; i++){
        printf("Job %d\n", granttChart[i]);
    }
    printf("\n Total profit : %d\n", totalProfit);
}

int main(int *argc, char **argv){
    int size;
    printf("Enter the number of jobs: ");
    scanf("%d",&size);
    
    // store the index of the each job 
    int jobs[size];
    int deadline[size];
    int profit[size];

    int max_deadline = 0;
    int i;
    for(i=0 ; i<size ; i++){
        printf("\nJob number %d:\n", i+1);
        jobs[i] = i+1;
        printf("Enter deadline: ");
        scanf("%d",&deadline[i]);
        if(deadline[i] > max_deadline)
            max_deadline = deadline[i];
        printf("Enter profit: ");
        scanf("%d",&profit[i]);
    }
    quickSort(jobs, deadline, profit, 0, size-1);
    jobSequencing(max_deadline, jobs, deadline, profit);

    /*for(i=0 ; i<size ; i++){
        printf("\nJob number %d:\n", jobs[i]);
        printf("Deadline: %d\n", deadline[i]);
        printf("Profit: %d\n", profit[i]);
    }*/

}