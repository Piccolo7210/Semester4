#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
// Flag to indicate termination for the thread
int terminate_thread = 0;

// Thread function to be executed
void *thread_task(void *arg) {
  while (!terminate_thread) {
    // Simulate some work done by the thread
    printf("Thread performing some work...\n");
    sleep(1);
  }
  printf("Thread terminated.\n");
  return NULL;
}

// Signal handler function
void signal_handler(int sig) {
  if (sig == SIGINT) {
    terminate_thread = 1;
    printf("SIGINT signal caught!\n");
    
  }
}

int main() {
  // Set up signal handler
  signal(SIGINT, signal_handler);

  // Create and start the thread
  pthread_t thread;
  pthread_create(&thread, NULL, thread_task, NULL);

  // Wait for the thread to finish (or be terminated)
  pthread_join(thread, NULL);

  printf("Program terminated.\n");
  return 0;
}
