#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>

struct MultiplyArgs {
  int mod;
  int begin;
  int end;
};

unsigned int Multiply(const struct MultiplyArgs *args) {
  unsigned int multiply = 1;
  // TODO: your code here 
  for(int i = args->begin; i < args->end; i++){
    multiply *= i;
    multiply %= args->mod;
  }
  return multiply;
}

void *ThreadMultiply(void *args) {
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
            if (k <= 0) {
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

  if (k == 0 || mod == 0 || pnum == 0) {
    printf("Usage: %s --k \"num\" --mod \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  pthread_t threads[pnum];
  struct MultiplyArgs args[pnum];
  struct timeval start_time;
  gettimeofday(&start_time, NULL);
  for (int i = 0; i < pnum; i++) {
    args[i].mod = mod;
    args[i].begin = (int)(k / pnum) * i + 1;
    if(i == pnum - 1) args[i].end = k + 1;
    else args[i].end = (int)(k / pnum) * (i + 1) + 1;
    if (pthread_create(&threads[i], NULL, ThreadMultiply, (void *) &args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }
  unsigned int total_multiply = 1;
  for (int i = 0; i < pnum; i++) {
    void* temp   = NULL;
    pthread_join(threads[i], &temp);
    unsigned int multiply = (unsigned)(size_t)temp;
    total_multiply *= multiply;
  }
  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;


  printf("Factorial mod %d: %u\n", mod, total_multiply % mod);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}