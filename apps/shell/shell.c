/* Used components */
#include "commands.h"
#include <IO.h>
#include <Clock.h>
#include <Serial.h>
#include <Menu.h>
#include <eers.h>

// https://github.com/MightyPork/avr-lib/blob/master/lib/uart.h - useful
// terminal

Clock(clk, &hw(timer), TIMESTAMP);

/* indicator */
bool  is_led_on = false;
pin_t led_pin   = hw_pin(B, 1);
IO_new(led, _({
                .io   = &hw(gpio),
                .pin  = &led_pin,
                .mode = IO_OUTPUT,
            }));

/* Menu commands and state */
char           command[COMMAND_BUFFER_SIZE];
Menu_command_t commands[] = {{"time", print_time},
                             {"version", print_version},
                             {"read", print_memory, command},
                             {0}};

Menu(tty, _({.menu    = commands,
             .command = command,

             .on = {
                 .command   = print_shell,
                 .not_found = print_command_not_found,
             }}));
/**
 * \brief    Echo each symbol from input to output
 */
void read_symbol(eer_t *uart_ptr)
{
    Serial_write(&uart, eer_state(Serial, &uart, sending));
}

/**
 * \brief    Read command from buffer
 */
void read_command(eer_t *uart)
{
    char *    command_symbol = command;
    lr_data_t data;

    while (Serial_read(uart, &data) == OK && data) {
        *command_symbol++ = (uint8_t)data;
    }
    *--command_symbol = 0;
}

/* UART communication */
struct lr_cell     cells[BUFFER_SIZE] = {0};
struct linked_ring buffer             = {cells, BUFFER_SIZE};
Serial(uart,
       _({.handler  = &hw(uart),
          .baudrate = BAUDRATE,
          .buffer   = &buffer,
          .on       = {
              .receive_block = read_command, /* Read and execute command */
              .receive       = read_symbol,  /* Echo input */
          }}));


int main(void)
{
    print_shell(0);

    loop(clk, uart, tty)
    {
        apply(IO, led,
              _({
                  .level = is_led_on,
              }));
    }

    return 0;
}
