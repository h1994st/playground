// Client side implementation of UDP client-server model
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/can.h>
#include <net/if.h>

#define PORT    8080
#define MAXLINE 1024

#define NANOSECONDS_PER_SECOND 1000000000L

#define MSG_BUF "haha"
#define MSG_LEN 5

// Driver code
int main(int argc, char *argv[]) {
  int ret = EXIT_SUCCESS;
  int ifindex = 0; // -i iface
  char ifname[IF_NAMESIZE];
  size_t ifname_len;
  int broadcast = 0; // -b

  int sockfd;
  struct sockaddr_in servaddr;

  // Parsing command-line options
  int opt;
  while ((opt = getopt(argc, argv, "i:bc:s:r:")) != -1) {
//  while ((opt = getopt(argc, argv, "bc:s:r:")) != -1) {
    switch (opt) {
      case 'i': {
        ifindex = if_nametoindex(optarg);
        if (ifindex == 0) {
          perror("if_nametoindex failed");
          exit(EXIT_FAILURE);
        }
        ifname_len = strlen(optarg);
        memcpy(ifname, optarg, ifname_len + 1);
        break;
      }
      case 'b': {
        broadcast = 1;
        break;
      }
      default: {
        fprintf(stderr, "unknown command-line options\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Binding to an interface
  if (ifindex != 0) {
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, ifname, ifname_len)
        == -1) {
      perror("setsockopt failed");
      ret = EXIT_FAILURE;
      goto out;
    }
  }

  // Setting broadcast
  if (broadcast != 0) {
    // `broadcast` should not have `bool` type, which will result in an error
    // of "invalid argument"
    // - `sizeof(bool)` depends on implementations
    if (setsockopt(
        sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))
        == -1) {
      perror("setsockopt failed");
      ret = EXIT_FAILURE;
      goto out;
    }
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
//  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_addr.s_addr = INADDR_BROADCAST;

  ssize_t len = MSG_LEN;
  ssize_t n;

  n = sendto(
      sockfd, MSG_BUF, len, MSG_CONFIRM,
      (const struct sockaddr *) &servaddr, sizeof(servaddr));
  if (n != len) {
    perror("sendto failed");
    ret = EXIT_FAILURE;
    goto out;
  }

out:
  close(sockfd);
  return ret;
}
