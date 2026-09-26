#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr

int main(int argc, char** argv) {
  const size_t kSize = sizeof(struct sockaddr_in);
  int buffer_size;
  int port;
  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"port", required_argument, 0, 0},
                                      {"buffer_size", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            port = atoi(optarg);
            if(port <= 0) {
              printf("port is a positive number\n");
              return 1;
            }
            // your code here
            // error handling
            break;
          case 1:
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

  if (port == 0 || buffer_size == 0) {
    printf("Usage: %s  --port \"num\" --buffer_size \"num\" \n",
           argv[0]);
    return 1;
  }
  int lfd, cfd;
  int nread;
  char *buf;
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  if(argc < 3){
    printf("Too few arguments\n");
    exit(1);
  }
  buf = malloc(sizeof(char) * buffer_size);

  if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  memset(&servaddr, 0, kSize);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(lfd, (SADDR *)&servaddr, kSize) < 0) {
    perror("bind");
    exit(1);
  }

  if (listen(lfd, 5) < 0) {
    perror("listen");
    exit(1);
  }

  while (1) {
    unsigned int clilen = kSize;

    if ((cfd = accept(lfd, (SADDR *)&cliaddr, &clilen)) < 0) {
      perror("accept");
      exit(1);
    }
    printf("connection established\n");

    while ((nread = read(cfd, buf, buffer_size)) > 0) {
      write(1, buf, nread);
    }

    if (nread == -1) {
      perror("read");
      exit(1);
    }
    close(cfd);
  }
  free(buf);
}
