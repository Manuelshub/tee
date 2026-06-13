#include "tee.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * tee - the tee command takes input from stdin and puts in a file and also prints it to stdout.
 * 
 * Note: this program should support the option -a which should be the first argument to the program
 */
int main(int ac, char **av) {
    char buffer[1024];
    int open_fd, a_flags, flags;
    ssize_t n_read;
    mode_t modes;

    modes = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    flags = O_WRONLY | O_CREAT | O_TRUNC;
    a_flags = O_WRONLY | O_CREAT | O_APPEND;
    
    if (ac == 2 && strcmp(av[1], "-a")) {
        open_fd = open(av[1], flags, modes);
        if (open_fd == -1) {
            perror("open");
            return EXIT_FAILURE;
        }
    }
    else if (ac == 3 && !strcmp(av[1], "-a")) {
        open_fd = open(av[2], a_flags, modes);
        if (open_fd == -1) {
            perror("open");
            return EXIT_FAILURE;
        }
    }
    else
        open_fd = -1;

    while (1) {
        n_read = read(0, buffer, sizeof(buffer) - 1);
        if (n_read == -1) {
            perror("read");
            return EXIT_FAILURE;
        }
        buffer[n_read] = '\0';
        if (n_read == 0) break;

        if (open_fd != -1) {
            if (write(open_fd, buffer, n_read) == -1) {
                perror("write");
                return EXIT_FAILURE;
            }
        }
        if (write(1, buffer, n_read) == -1) {
            perror("write");
            return EXIT_FAILURE;
        }
    }
    
    close(open_fd);
    return EXIT_SUCCESS;
}