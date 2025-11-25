#include <stdio.h>
#include <unistd.h>

int main() {
    printf("noop container started. Doing nothing forever.\n");
    // Sleep indefinitely
    while (1) {
        sleep(86400); // Sleep for a day
    }
    return 0;
}
