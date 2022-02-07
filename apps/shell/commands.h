#pragma once

#include <Clock.h>
#include <Serial.h>

#define BAUDRATE            9600
#define BUFFER_SIZE         32
#define COMMAND_BUFFER_SIZE 16

extern char     command[COMMAND_BUFFER_SIZE];
extern Serial_t uart;
extern Clock_t  clk;

void log_string(char *message);
void log_num(char *message, long number);
void print_shell(eer_t *menu);
void print_command_not_found(eer_t *menu);
void print_version(void *arg);
void print_memory(void *arg);
void print_time(void *arg);
