#include <inttypes.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Don't compile this with any optimizations as it will likely have the useless mallocs
// removed.

uint64_t total_memory = 4ULL * 1024ULL * 1024ULL * 1024ULL; // -m
int oom_seconds = 60;                                       // -s

void signal_handler(int signum)
{
  printf("\nCaught signal %d, exiting gracefully.\n", signum);
  exit(0);
}

void usage()
{
  printf("Attempt to OOM the process in oom_seconds (-s) by allocating up to total_memory (-m).\n");
  printf("We allocate every second so the usage should be linear.\n");
  exit(0);
}

void parse_args(int argc, char **argv)
{
  int ch;
  while ((ch = getopt(argc, argv, "m:s:")) != -1)
  {
    switch (ch)
    {
    case 'm':
      total_memory = strtoull(optarg, NULL, 10);
      break;
    case 's':
      oom_seconds = atoi(optarg);
      break;
    case '?':
    default:
      usage();
    }
  }
  argc -= optind;
  argv += optind;
}

int main(int argc, char **argv)
{
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  parse_args(argc, argv);
  printf("Attempting to allocate up to %" PRIu64 " bytes of memory in %d seconds.\n", total_memory, oom_seconds);

  uint64_t mem_per_alloc = total_memory / oom_seconds;
  printf("That equates to %" PRIu64 " bytes per allocation.\n", mem_per_alloc);
  printf("Starting memory allocation loop...\n");

  uint64_t allocated_memory = 0ULL;
  for (int i = 0; i < oom_seconds; i++)
  {
    void *x = malloc(mem_per_alloc);
    if (x == NULL)
    {
      printf("Failed to allocate memory\n");
      exit(1);
    }
    memset(x, 0, mem_per_alloc);
    allocated_memory += mem_per_alloc;
    printf("  Iteration %d: %" PRIu64 " allocated / %" PRIu64 " total (at %p)\n", i + 1, allocated_memory, total_memory, x);
    sleep(1);
  }

  printf("Completed successfully without being killed off!\n");
  return 0;
}
