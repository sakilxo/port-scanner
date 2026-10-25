#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define _POSIX_C_SOURCE 200112L
#define CONNECT_TIMEOUT_SECONDS 1


static void usage(const char *program) {
    fprint(stderr, "usage: %s <IPv4 address> <start-port> <end-port> \n", program);
    fprintf(stderr, "example: %s 127.0.0.1 1 1000 \n", program);
}

static int parse_port(const char *text, int *port) {
    char *end = NULL;
    errno = 0;
    long value = strtol(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' || value < 1 || value > 65535) {
        return 0;
    }

    *port = (int)value;
    return 1;
}

static int port_is_open(const struct in_addr *address, int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1) {
        perror("socket");
        return 0;
    }

    struct timeval timeout = {
        .tv_sec = CONNECT_TIMEOUT_SECONDS,
        .tv_usec = 0
    };

    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
        perror("setsockopt");
        close(fd);
        return 0;
    }

    struct sockaddr_in target;
    memset(&target, 0, sizeof(target));
    target.sin_family = AF_INET;
    target.sin_port = htons((unsigned short) port);
    target.sin_addr = *address;

    int result = connect(fd, (struct sockaddr *) &target, sizeof(target));
    int saved_errno = errno;
    close(fd);

    if (result == 0) {
        return 1;
    }

    errno = saved_errno;
    return 0;
    
}