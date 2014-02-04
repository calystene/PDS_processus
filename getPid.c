
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main
(void) {
    printf("Je suis le fils : %d \n", getpid());
    printf("Je suis le père : %d \n", getppid());
}
