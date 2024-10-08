#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function prototypes
void SSTF(int requests[], int size, int head);
void SCAN(int requests[], int size, int head, int direction);
void C_LOOK(int requests[], int size, int head);
void C_SCAN(int requests[], int size, int head, int direction);

// Main function
int main() {
    int requests[MAX_REQUESTS];
    int size, head, direction;

    printf("Enter the number of disk requests (max %d): ", MAX_REQUESTS);
    scanf("%d", &size);
    
    if (size > MAX_REQUESTS || size <= 0) {
        printf("Invalid number of requests. Please enter a value between 1 and %d.\n", MAX_REQUESTS);
        return 1;
    }

    printf("Enter the disk requests:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    printf("Enter the direction of SCAN/C-SCAN (1 for upward, 0 for downward): ");
    scanf("%d", &direction);
    
    printf("\nDisk Scheduling Algorithms\n");
    printf("===========================\n");
    
    printf("1. Shortest Seek Time First (SSTF):\n");
    SSTF(requests, size, head);
    
    printf("\n2. SCAN:\n");
    SCAN(requests, size, head, direction);

    printf("\n3. C-LOOK:\n");
    C_LOOK(requests, size, head);

    printf("\n4. C-SCAN:\n");
    C_SCAN(requests, size, head, direction);
    
    return 0;
}

// Shortest Seek Time First (SSTF) Algorithm
void SSTF(int requests[], int size, int head) {
    int completed[MAX_REQUESTS] = {0};
    int totalHeadMovement = 0;
    int currentPos = head;
    int count = 0;

    printf("Initial Head Position: %d\n", currentPos);
    while (count < size) {
        int minIndex = -1;
        int minDistance = 10000;

        for (int i = 0; i < size; i++) {
            if (!completed[i]) {
                int distance = abs(requests[i] - currentPos);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1) {
            totalHeadMovement += minDistance;
            printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                   requests[minIndex], currentPos, requests[minIndex], minDistance);
            currentPos = requests[minIndex];
            completed[minIndex] = 1;
            count++;
        }
    }

    printf("Total Head Movement in SSTF: %d\n", totalHeadMovement);
}

// SCAN Algorithm
void SCAN(int requests[], int size, int head, int direction) {
    int totalHeadMovement = 0;
    int currentPos = head;

    // Sort requests
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int startIndex;
    for (startIndex = 0; startIndex < size; startIndex++) {
        if (requests[startIndex] >= head) {
            break;
        }
    }

    printf("Initial Head Position: %d\n", currentPos);
    // Move in the given direction
    if (direction == 1) { // Upward
        for (int i = startIndex; i < size; i++) {
            totalHeadMovement += abs(currentPos - requests[i]);
            printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                   requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
            currentPos = requests[i];
        }
        // Move to the end and back
        totalHeadMovement += abs(currentPos - 199); // Assuming 199 is the last track
        printf("Head moved to end: 199 (Difference: %d)\n", abs(currentPos - 199));
        currentPos = 199;

        for (int i = startIndex - 1; i >= 0; i--) {
            totalHeadMovement += abs(currentPos - requests[i]);
            printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                   requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
            currentPos = requests[i];
        }
    } else { // Downward
        for (int i = startIndex - 1; i >= 0; i--) {
            totalHeadMovement += abs(currentPos - requests[i]);
            printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                   requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
            currentPos = requests[i];
        }
        // Move to the beginning and back
        totalHeadMovement += abs(currentPos - 0); // Assuming 0 is the first track
        printf("Head moved to start: 0 (Difference: %d)\n", abs(currentPos - 0));
        currentPos = 0;

        for (int i = startIndex; i < size; i++) {
            totalHeadMovement += abs(currentPos - requests[i]);
            printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                   requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
            currentPos = requests[i];
        }
    }

    printf("Total Head Movement in SCAN: %d\n", totalHeadMovement);
}

// C-LOOK Algorithm
void C_LOOK(int requests[], int size, int head) {
    int totalHeadMovement = 0;
    int currentPos = head;

    // Sort requests
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("Initial Head Position: %d\n", currentPos);
    // Move to the nearest request greater than head
    int startIndex;
    for (startIndex = 0; startIndex < size; startIndex++) {
        if (requests[startIndex] >= head) {
            break;
        }
    }

    // Serve requests from startIndex to end
    for (int i = startIndex; i < size; i++) {
        totalHeadMovement += abs(currentPos - requests[i]);
        printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
               requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
        currentPos = requests[i];
    }

    // Jump to the first request
    if (startIndex > 0) {
        totalHeadMovement += abs(currentPos - requests[0]);
        printf("Jumped to first request: %d, Head moved from %d to %d (Difference: %d)\n",
               requests[0], currentPos, requests[0], abs(currentPos - requests[0]));
        currentPos = requests[0];
    }

    // Serve requests from start to startIndex - 1
    for (int i = 0; i < startIndex; i++) {
        totalHeadMovement += abs(currentPos - requests[i]);
        printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
               requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
        currentPos = requests[i];
    }

    printf("Total Head Movement in C-LOOK: %d\n", totalHeadMovement);
}

// C-SCAN Algorithm
void C_SCAN(int requests[], int size, int head, int direction) {
    int totalHeadMovement = 0;
    int currentPos = head;

    // Sort requests
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("Initial Head Position: %d\n", currentPos);
    // Move in the given direction
    if (direction == 1) { // Upward
        // Serve requests from the current position to the end
        for (int i = 0; i < size; i++) {
            if (requests[i] >= currentPos) {
                totalHeadMovement += abs(currentPos - requests[i]);
                printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                       requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
                currentPos = requests[i];
            }
        }
        // Jump to the start (assuming 0 is the first track)
        totalHeadMovement += abs(currentPos - 199); // Move to end
        printf("Head moved to end: 199 (Difference: %d)\n", abs(currentPos - 199));
        currentPos = 199;
        totalHeadMovement += abs(currentPos - 0); // Jump to start
        printf("Jumped to start: 0 (Difference: %d)\n", abs(currentPos - 0));
        currentPos = 0;

        // Serve remaining requests from start
        for (int i = 0; i < size; i++) {
            if (requests[i] >= currentPos) {
                totalHeadMovement += abs(currentPos - requests[i]);
                printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                       requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
                currentPos = requests[i];
            }
        }
    } else { // Downward
        // Serve requests from the current position to the beginning
        for (int i = size - 1; i >= 0; i--) {
            if (requests[i] <= currentPos) {
                totalHeadMovement += abs(currentPos - requests[i]);
                printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                       requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
                currentPos = requests[i];
            }
        }
        // Jump to the end (assuming 199 is the last track)
        totalHeadMovement += abs(currentPos - 0); // Move to start
        printf("Head moved to start: 0 (Difference: %d)\n", abs(currentPos - 0));
        currentPos = 0;
        totalHeadMovement += abs(currentPos - 199); // Jump to end
        printf("Jumped to end: 199 (Difference: %d)\n", abs(currentPos - 199));
        currentPos = 199;

        // Serve remaining requests from end
        for (int i = size - 1; i >= 0; i--) {
            if (requests[i] <= currentPos) {
                totalHeadMovement += abs(currentPos - requests[i]);
                printf("Serviced Request: %d, Head moved from %d to %d (Difference: %d)\n",
                       requests[i], currentPos, requests[i], abs(currentPos - requests[i]));
                currentPos = requests[i];
            }
        }
    }

    printf("Total Head Movement in C-SCAN: %d\n", totalHeadMovement);
}

