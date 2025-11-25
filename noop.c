#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int signum)
{
    printf("\nCaught signal %d, exiting gracefully.\n", signum);
    exit(0);
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("noop container started. Doing nothing forever.\n");
    // Sleep indefinitely
    while (1)
    {
        sleep(86400); // Sleep for a day
    }
    return 0;
}
