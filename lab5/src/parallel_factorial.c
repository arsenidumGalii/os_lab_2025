#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>

struct MultiplyArgs {
  int begin;
  int end;
};

unsigned int Multiply(const struct MultiplyArgs *args) {
  unsigned int multiply = 1;
  // TODO: your code here 
  for(int i = args->begin; i < args->end; i++){
    multiply *= i;
  }
  return multiply;
}

void *Thread(void *args) {
  struct MultiplyArgs *multiply_args = (struct MultiplyArgs *)args;
  return (void *)(size_t)Multiply(multiply_args);
}


int main(int argc, char** argv){
  uint32_t k = 0;
  uint32_t pnum = 0;
  uint32_t mod = 0;
  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            k = atoi(optarg);
            if (seed <= 0) {
              printf("k is a positive number\n");
              return 1;
            }
            // your code here
            // error handling
            break;
          case 1:
            mod = atoi(optarg);
            if(mod <= 0) {
              printf("mod is a positive number\n");
              return 1;
            }
            // your code here
            // error handling
            break;
          case 2:
           pnum = atoi(optarg);
           if(pnum <= 0) {
              printf("pnum is a positive number\n");
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
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (k == 0 || mode == 0 || pnum == 0) {
    printf("Usage: %s --k \"num\" --mode \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  pthread_t threads[pnum];
  struct MultiplyArgs args[pnum];
  struct timeval start_time;
  gettimeofday(&start_time, NULL);
  for (int i = 0; i < pnum; i++) {
    args[i].begin = (int)(k / threads_num) * i + 1;
    if(i == threads_num - 1) args[i].end = k + 1;
    else args[i].end = (int)(k / threads_num) * (i + 1) + 1;
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *) &args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }
}