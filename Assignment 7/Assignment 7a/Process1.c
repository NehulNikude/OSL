#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define OUTPUT_FILE "output.txt"

int main() {
    char buffer[256];
    int fd;
    FILE *file;

    while (1) {
        // Read from FIFO1
        fd = open(FIFO1, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        close(fd);

        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Count characters, words, and lines
        int chars = strlen(buffer);
        int words = 0, lines = 0;
        
        for (char *p = buffer; *p; p++) {
            if (*p == ' ' || *p == '\n') {
                words++;
            }
            if (*p == '\n') {
                lines++;
            }
        }
        words++; // To account for the last word if there is any

        // Write to output file
        file = fopen(OUTPUT_FILE, "a");
        fprintf(file, "Characters: %d, Words: %d, Lines: %d\n", chars, words, lines);
        fclose(file);

        // Prepare message to send back
        snprintf(buffer, sizeof(buffer), "Characters: %d, Words: %d, Lines: %d\n", chars, words, lines);

        // Write to FIFO2
        fd = open(FIFO2, O_WRONLY);
        write(fd, buffer, sizeof(buffer));
        close(fd);
    }

    return 0;
}