#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

int main() {
    char buffer[256];
    int fd;

    // Create FIFOs
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while (1) {
        printf("Enter a sentence (type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Write to FIFO1
        fd = open(FIFO1, O_WRONLY);
        write(fd, buffer, sizeof(buffer));
        close(fd);
        
        // Read from FIFO2
        fd = open(FIFO2, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        printf("Received from Process 2: %s", buffer);
        close(fd);
    }

    return 0;
}