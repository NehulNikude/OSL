#include <stdio.h>
#include <stdlib.h>

int count = 0; //To keep count of processes scheduled

void ganttChart(int* schedule, int n, int** arr) //Function to print Gantt Chart
{
	int time = 0; //Varible used to account for idle time between processes
	//Printing order in which processes got executed
	printf("|"); 
	for(int i=0;i<n;i++)
	{
		int j = schedule[i];
		if(time != arr[j][5])
		{
			printf(" Idle |");
			time = arr[j][5];
			i--;
		}
		else
		{
			printf(" P%d |",arr[j][0]);
			time += arr[j][1];
		}
	}
	//Printing the time
	printf("\n");
	printf("%d",0);
	time = 0;
	for(int i=0;i<n;i++)
	{
		int j = schedule[i];
		if(time != arr[j][5])
		{
			printf("      %d",arr[j][5]);
			time = arr[j][5];
			i--;
		}
		else
		{
			printf("    %d",arr[j][3]);
			time += arr[j][1];
		}
	}
}

void bsort(int n, int** arr) //Bubble sort function
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j][2] > arr[j+1][2])
			{
				int* temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int scheduler(int t, int** arr, int n, int* visited) //Function to select the shortest job
{
	int minBT = __INT_MAX__;
	int indexp = -1;
	for(int i=0;i<n;i++)
	{
		if(arr[i][2] <= t && visited[i] != 1 && arr[i][1]<minBT)
		{
			minBT = arr[i][1];
			indexp = i;
		}
	}
	if(indexp != -1)
		visited[indexp] = 1;
	return indexp;
}

void SJF(int** arr, int n, int* visited, int* schedule) //Function that executes the scheduled processes
{
	int time = 0;
	int x = 0;
	while(count<n)
	{
		int i = scheduler(time, arr, n, visited);
		if(i == -1)
			time++;
		else
		{
			count++;
			arr[i][5] = time; //Start time of process
			time += arr[i][1];
			arr[i][3] = time; //Completion time of process
			arr[i][4] = time - arr[i][2]; //TAT of process
			schedule[x++] = i; //Storing order of processes
			printf("Process %d ",arr[i][0]);
		}
	}
	printf("\n");
	printf("Total Time Taken : %d",time);
}
//arr = {0.ID, 1.BT, 2.AT, 3.CT, 4.TAT, 5.ST}
int main()
{
	int n, x, y; //Variables to store input
	printf("\n");
	printf("Enter number of processes : ");
	scanf("%d", &n);
	printf("\n");
	int** arr;
	arr = (int**)malloc(n*sizeof(int*)); //Array to store process related data
	int* visited = (int*)malloc(n*sizeof(int)); //To identify which processes have been scheduled
	int* schedule = (int*)malloc(n*sizeof(int)); //To store the order of process execution
	for(int i=0;i<n;i++)
	{
		arr[i] = (int*)malloc(6*sizeof(int));
		arr[i][0] = i+1;
		printf("Enter burst time for process %d : ",i+1);
		scanf("%d", &x);
		arr[i][1] = x;
		printf("Enter arrival time for process %d : ",i+1);
		scanf("%d", &y);
		arr[i][2] = y;
		printf("\n");
	}
	printf("\n");
	bsort(n, arr);
	//Giving summary of entered data
	for(int i=0;i<n;i++)
	{
		printf("Process ID : %d\n",arr[i][0]);
		printf("Burst time : %d\n",arr[i][1]);
		printf("Arrival time : %d\n",arr[i][2]);
		printf("\n");
	}
	
	//Printing final result
	printf("Sequence \n");
	SJF(arr, n, visited, schedule);
	printf("\n\n");
	printf("Gantt Chart \n");
	ganttChart(schedule, n, arr);
	printf("\n");

	// Free allocated memory
    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
    free(schedule);
	free(visited);
}
