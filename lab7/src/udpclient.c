#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr
#define SLEN sizeof(struct sockaddr_in)

int main(int argc, char **argv) {
  int sockfd, n;
  char* sendline, recvline;
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  char ip[20];
  int port;
  int buffer_size;
  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"ip", required_argument, 0, 0},
                                      {"port", required_argument, 0, 0},
                                      {"buffer_size", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            memcpy(ip, optarg, strlen(optarg));
            ip[strlen(optarg)] = '\0';
            // your code here
            // error handling
            break;
          case 1:
            port = atoi(optarg);
            if(port <= 0) {
              printf("port is a positive number\n");
              return 1;
            }
            // your code here
            // error handling
            break;
          case 2:
            buffer_size = atoi(optarg);
            if(buffer_size <= 0) {
              printf("buffer_size is a positive number\n");
              return 1;
            }
            // your code here
            // error handling
            break;
          default:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Too few arguments\n");
    return 1;
  }

  if (!ip || port == 0 || buffer_size == 0) {
    printf("Usage: %s --ip \"xxx.yyy.zzz.aaa\" --port \"num\" --buffer_size \"num\" \n",
           argv[0]);
    return 1;
  }
  sendline = malloc(sizeof(char) * buffer_size);
  recvline = malloc(sizeof(char) * buffer_size + 1);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);

  if (inet_pton(AF_INET, ip, &servaddr.sin_addr) < 0) {
    perror("inet_pton problem");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }

  write(1, "Enter string\n", 13);

  while ((n = read(0, sendline, buffer_size)) > 0) {
    if (sendto(sockfd, sendline, n, 0, (SADDR *)&servaddr, SLEN) == -1) {
      perror("sendto problem");
      exit(1);
    }

    if (recvfrom(sockfd, recvline, buffer_size, 0, NULL, NULL) == -1) {
      perror("recvfrom problem");
      exit(1);
    }

    printf("REPLY FROM SERVER= %s\n", recvline);
  }
  close(sockfd);
  free(recvline);
  free(sendline);
}
