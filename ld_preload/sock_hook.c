#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol) {
    printf("socket(domain=%d, type=%d, protocol=%d)\n", domain, type, protocol);
    return 1000;
}

int setsockopt(int sockfd, int level, int optname,
               const void *optval, socklen_t optlen) {
    printf(
        "setsockopt(sockfd=%d, level=%d, optname=%d, ...)\n",
        sockfd, level, optname);
    return 0;
}

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen) {
    printf("sendto(sockfd=%d, ...)\n", sockfd);
    return len;
}

int close(int fd) {
    printf("close(fd=%d)\n", fd);
    return 0;
}

__attribute__((constructor))
void sock_hook_ctor() {
    printf("sock_hook_ctor()\n");
}

__attribute__((destructor))
void sock_hook_dtor() {
    printf("sock_hook_dtor()\n");
}
