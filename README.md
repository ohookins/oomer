# OOMer

A simple C program designed to get itself OOM-killed.

## What it does

`oomer` allocates a specified amount of memory over a given period. This is useful for testing OOM-killing behavior in containerized environments like Docker or Kubernetes.

The program takes two arguments:
*   `-m <bytes>`: The total memory to allocate (default: 4GB).
*   `-s <seconds>`: The number of seconds over which to allocate the memory (default: 60).

## Building and Running with Docker

A `Dockerfile` is provided to build and run the program.

1.  **Build the image:**
    ```sh
    docker build -t oomer .
    ```

2.  **Run the container:**
    To run with a memory limit and see it get OOM-killed:
    ```sh
    # This will try to allocate memory, but Docker will kill it when it exceeds 128MB.
    docker run --rm -ti --memory=128m oomer
    ```
    You can also pass arguments to the program:
    ```sh
    # Allocate 256MB in 10 seconds
    docker run --rm -ti --memory=128m oomer -m 268435456 -s 10
    ```
