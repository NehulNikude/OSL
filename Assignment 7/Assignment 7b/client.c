#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    key_t key = ftok("server.c", 65); // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666); // Get shared memory segment
    char *str = (char *)shmat(shmid, NULL, 0); // Attach to shared memory

    // Get message input from user
    printf("Client: Enter a message: ");
    fgets(str, SHM_SIZE, stdin); // Read message into shared memory

    // Optionally, clear the newline character
    str[strcspn(str, "\n")] = '\0';

    // Detach from shared memory
    shmdt(str);

    return 0;
}