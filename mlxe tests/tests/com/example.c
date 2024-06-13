// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char message[BUFSIZ];

    // Ouvrir le FIFO en lecture et écriture
	fd = -1;
	printf("Waiting for writer...\n");
	while (fd == -1)
    	fd = open(FIFO_FILE, O_RDONLY | O_NONBLOCK);
	printf("fd = %d\n", fd);
	read(fd, message, 5);
    while (1) {
		
        // Lire depuis l'entrée standard (stdin)
        /*printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        // Écrire dans le FIFO
        write(fd, message, strlen(message));
		close(fd);
		getchar();*/

        // Lire la réponse du FIFO
        int a = read(fd, message, sizeof(message));
		if (a == -1) {
			continue;
		}
		if (a == 0) {
			//check if the writer is still alive
			int fd2 = open(FIFO_FILE, O_RDONLY | O_NONBLOCK);
			if (fd2 == -1) {
				printf("Writer is dead\n");
				break;
			}
			close(fd2);
			continue;
		}
		message[a] = '\0';
        printf("Received message: %s", message);
    }

    close(fd);

    return 0;
}
