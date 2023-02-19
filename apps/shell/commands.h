#pragma once

#include <Clock.h>
#include <Serial.h>

#define BUFFER_SIZE         64
#define COMMAND_BUFFER_SIZE 16

extern char     command[COMMAND_BUFFER_SIZE];
extern Serial_t uart;
extern Clock_t  clk;

void log_string(const char *message);
void log_num(const char *message, long number);
void print_shell(eer_t *menu);
void print_command_not_found(eer_t *menu);
void print_version(void *arg);
void print_memory(void *arg);
void write_memory(char *request);
void print_time(void *arg);
