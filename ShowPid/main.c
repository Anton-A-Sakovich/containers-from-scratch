#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    pid_t pid = getpid();
    printf("My PID is %i\n", pid);
    return 0;
}
