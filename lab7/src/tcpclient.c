#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) {
  int fd;
  int nread;
  char* buf;
  int buffer_size;
  int port;
  char ip[20];
  struct sockaddr_in servaddr;
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

  buf = malloc(sizeof(char) * buffer_size);

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creating");
    exit(1);
  }

  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;

  if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0) {
    perror("bad address");
    exit(1);
  }

  servaddr.sin_port = htons(port);

  if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
    perror("connect");
    exit(1);
  }

  write(1, "Input message to send\n", 22);
  while ((nread = read(0, buf, buffer_size)) > 0) {
    if (write(fd, buf, nread) < 0) {
      perror("write");
      exit(1);
    }
  }

  close(fd);
  free(buf);
  exit(0);
}
