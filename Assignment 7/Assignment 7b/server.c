#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    key_t key = ftok("server.c", 65); // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Create shared memory segment
    char *str = (char *)shmat(shmid, NULL, 0); // Attach to shared memory

    // Wait for the client to write the message
    printf("Server: Waiting for client message...\n");
    while (1) {
        if (strlen(str) > 0) { // Check if the message is written
            printf("Server: Received message: %s\n", str);
            break;
        }
        sleep(1); // Sleep to prevent busy waiting
    }

    // Detach from shared memory
    shmdt(str);

    // Cleanup: remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}