#define _GNU_SOURCE

#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sched.h>
#include <malloc.h>

#define STACK_SIZE (1 << 20)

typedef struct ProcessStartInfo
{
    char* Command;
    char** Argv;
} ProcessStartInfo;

// char **parentArgv: {"run.exe\0", "child.exe\0", "arg1\0", "arg2\0" }
// Should become
// char** childArgv: {"child.exe\0", "arg1\0", "arg2\0", NULL }
ProcessStartInfo CreateProcessStartInfo(int parentArgc, char **parentArgv)
{
    ProcessStartInfo startInfo;

    startInfo.Command = parentArgv[1];

    int argc = parentArgc;
    startInfo.Argv = malloc(sizeof(char*) * argc);
    startInfo.Argv[argc - 1] = NULL;
    for (int i = 0; i < argc - 1; i++)
    {
        startInfo.Argv[i] = parentArgv[i + 1];
    }

    return startInfo;
}

void DestroyProcessStartInfo(ProcessStartInfo *startInfo)
{
    free(startInfo->Argv);
}

int child_main(void *args)
{
    ProcessStartInfo *pStartInfo = (ProcessStartInfo*)args;
    return execv(pStartInfo->Command, pStartInfo->Argv);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: run.exe PATH [ARG...]\n");
        return 0;
    }

    char *pFirstStackByte = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_STACK | MAP_PRIVATE, -1, 0);
    char *pLastStackByte = pFirstStackByte + STACK_SIZE;

    ProcessStartInfo startInfo = CreateProcessStartInfo(argc, argv);
    pid_t childPid = clone(child_main, pLastStackByte, CLONE_NEWPID | SIGCHLD, &startInfo);
    waitpid(childPid, NULL, 0);
    DestroyProcessStartInfo(&startInfo);

    return 0;
}
