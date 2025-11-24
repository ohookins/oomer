# Use a minimal base image
FROM alpine:latest

# Install build tools
RUN apk add --no-cache gcc libc-dev

# Copy the source code
COPY main.c .

# Compile the C program
RUN gcc -static -O0 -o oomer main.c

# Set the entrypoint for the container
CMD ["./oomer"]
