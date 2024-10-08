#include <bits/stdc++.h>
using namespace std;

queue<int> readyQueue;
int pcount = 0;

void bsort(int n, int** arr) // Bubble sort function
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n-i-1; j++)
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

void roundRobin(int** arr, int n, int* schedule, int q) // Function that executes the scheduled processes
{
    int time = 0;
    int x = 0;
    readyQueue.push(0);
    arr[0][7] = 1;
    while(pcount < n)
    {
        int i = readyQueue.front();
        readyQueue.pop();
        if(arr[i][5] == -1)
        {
            arr[i][5] = time; // Start time of process
        }
        if(arr[i][6] > q)
        {
            time += q;
            arr[i][6] -= q;
        }
        else
        {
            time += arr[i][6];
            arr[i][6] = 0;
            arr[i][3] = time; // Completion time of process
            arr[i][4] = time - arr[i][2]; // TAT of process
            schedule[x++] = i; // Storing order of processes
            pcount++;
        }
        for(int j = 1; j < n; j++)
        {
            if(arr[j][2] < time && arr[j][6] > 0 && arr[j][7] == 0)
            {
                arr[j][7] = 1;
                readyQueue.push(j);
            }
        }
        cout << "Process " << arr[i][0] << " ";
    }
    cout << endl;
    cout << "Total Time Taken: " << time << endl;
}

int main()
{
    int n, x, y, q; // Variables to store input
    cout << endl;
    cout << "Enter time quantum: ";
    cin >> q;
    cout << endl;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << endl;
    
    int** arr;
    arr = (int**)malloc(n * sizeof(int*)); // Array to store process related data
    int* schedule = (int*)malloc(n * sizeof(int)); // To store the order of process execution
    
    for(int i = 0; i < n; i++)
    {
        arr[i] = (int*)malloc(8 * sizeof(int));
        arr[i][0] = i + 1;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> x;
        arr[i][1] = x;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> y;
        arr[i][2] = y;
        arr[i][5] = -1;
        arr[i][6] = x; // Remaining time for execution
        arr[i][7] = 0;
        cout << endl;
    }

    bsort(n, arr);

    // Giving summary of entered data
    for(int i = 0; i < n; i++)
    {
        cout << "Process ID: " << arr[i][0] << endl;
        cout << "Burst time: " << arr[i][1] << endl;
        cout << "Arrival time: " << arr[i][2] << endl;
        cout << endl;
    }

    // Printing final result
    cout << "Sequence: " << endl;
    roundRobin(arr, n, schedule, q);
    cout << endl;

    // Free allocated memory
    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
    free(schedule);
}
