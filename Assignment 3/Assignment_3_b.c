#include <stdio.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 100

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
};

struct Execution {
    int process_id;
    int start_time;
    int end_time;
};

void enqueue(int queue[], int *rear, int process_id) {
    if (*rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full. Process P%d couldn't be enqueued.\n", process_id);
        return;
    }
    queue[++(*rear)] = process_id;
}

int dequeue(int queue[], int *front, int *rear) {
    if (*front > *rear) {
        return -1; // Queue is empty
    }
    return queue[(*front)++];
}

void printGanttChart(struct Execution executions[], int exec_count, int total_time) {
    printf("\nGantt Chart:\n");
    printf("Time |");
    for (int i = 0; i <= total_time; i++) {
        printf(" %-2d |", i);
    }
    printf("\n");
    for (int i = 0; i < exec_count; i++) {
        printf("P%d |", executions[i].process_id);
        for (int j = 0; j <= total_time; j++) {
            if (j >= executions[i].start_time && j < executions[i].end_time) {
                printf(" P%d |", executions[i].process_id);
            } else {
                printf("     |");
            }
        }
        printf("\n");
    }
}

void printStats(struct Process processes[], int n) {
    int total_turnaround_time = 0, total_waiting_time = 0;
    printf("\nCompletion Time | Burst Time | Turnaround Time | Waiting Time\n");
    for (int i = 0; i < n; i++) {
        int turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        int waiting_time = turnaround_time - processes[i].burst_time;
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
        printf("P%d: %15d %15d %17d %15d\n", processes[i].id,
               processes[i].completion_time, processes[i].burst_time, turnaround_time, waiting_time);
    }
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

void RR() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    int queue[MAX_QUEUE_SIZE], front = 0, rear = -1;
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
    }
    int current_time = 0;
    int exec_count = 0;
    struct Execution executions[MAX_QUEUE_SIZE];
    bool all_completed;
    do {
        all_completed = true;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                all_completed = false;
                int execute_time = (processes[i].remaining_time < time_quantum) ?
                                   processes[i].remaining_time : time_quantum;
                processes[i].remaining_time -= execute_time;
                executions[exec_count].process_id = processes[i].id;
                executions[exec_count].start_time = current_time;
                current_time += execute_time;
                executions[exec_count].end_time = current_time;
                exec_count++;
                if (processes[i].remaining_time == 0) {
                    processes[i].completion_time = current_time;
                } else {
                    enqueue(queue, &rear, i);
                }
            }
        }
        if (all_completed)
            break;
        if (front <= rear) {
            int next_process = dequeue(queue, &front, &rear);
            if (next_process != -1) {
                enqueue(queue, &rear, next_process);
            }
        } else {
            current_time++;
        }
    } while (!all_completed);
    printGanttChart(executions, exec_count, current_time);
    printStats(processes, n);
}

int main() {
    RR();
    return 0;
}