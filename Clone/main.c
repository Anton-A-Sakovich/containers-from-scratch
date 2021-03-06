#define _GNU_SOURCE

#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define STACK_SIZE (1024 * 1024)

#define APPERR_MMAP_FAILED 201
#define APPERR_WAIT_FAILED 202

static int child_main(void *arg)
{
    printf("Child PID as seen from child: %i\n", getpid());
    return 0;
}

int main(int argc, char **argv)
{
    char *pFirstStackByte = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    if (pFirstStackByte == MAP_FAILED)
    {
        return APPERR_MMAP_FAILED;
    }

    char *pLastStackByte = pFirstStackByte + STACK_SIZE;

    pid_t pid = clone(child_main, pLastStackByte,  CLONE_NEWPID | SIGCHLD, NULL);
    if (pid == -1)
    {
        return errno;
    }

    printf("Child PID as seen from host: %i\n", pid);

    pid = waitpid(pid, NULL, 0);
    if (pid == -1)
    {
        return APPERR_WAIT_FAILED;
    }

    exit(EXIT_SUCCESS);
}
