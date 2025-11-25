# Builder stage
FROM alpine:latest AS builder
RUN apk add --no-cache gcc libc-dev

# Build oomer
COPY main.c .
RUN gcc -static -O0 -o oomer main.c

# Build noop
COPY noop.c .
RUN gcc -static -O0 -o noop noop.c

# Final stage for oomer
FROM scratch AS oomer
COPY --from=builder /oomer /oomer
CMD ["/oomer"]

# Final stage for noop
FROM scratch AS noop
COPY --from=builder /noop /noop
CMD ["/noop"]
