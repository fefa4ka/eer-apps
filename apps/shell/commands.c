#include "commands.h"

typedef struct {
    unsigned long  quot;
    unsigned short rem;
} divmod10_t;

static char         utoa_buffer[13];

static inline void divmodu10(divmod10_t *res, unsigned long n)
{
    res->quot = n >> 1;
    res->quot += res->quot >> 1;
    res->quot += res->quot >> 4;
    res->quot += res->quot >> 8;
    res->quot += res->quot >> 16;
    unsigned long qq = res->quot;

    res->quot >>= 3;
    res->rem = (unsigned short)(n - ((res->quot << 1) + (qq & ~7ul)));
    if (res->rem > 9) {
        res->rem -= 10;
        res->quot++;
    }
}

// utoa fast div
char *utoa(unsigned long value)
{
    char *buffer = &utoa_buffer[1];

    buffer += 11;
    *--buffer = 0;

    do {
        divmod10_t res = {0};
        divmodu10(&res, value);
        *--buffer = res.rem + '0';
        value     = res.quot;
    } while (value != 0);

    return buffer;
}

// utoa fast div
char *itoa(long value)
{
    /* FIXME: make better abs */
    unsigned long unsigned_value = value;

    if (value < 0)
        unsigned_value = (unsigned long)(value - (2 * value));

    char *unsigned_string = utoa(unsigned_value);

    // Add symbol minus if negative
    if (value < 0) {
        unsigned_string--;
        *unsigned_string = '-';
    }

    return unsigned_string;
}

void log_string(const char *message) { Serial_write_string(&uart, message); }

void log_num(const char *message, long number)
{
    log_string(message);
    log_string(itoa(number));
}
// function to convert decimal to binary
void log_binary(char n)
{
    // array to store binary number
    int binaryNum[8];

    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n            = n / 2;
        i++;
    }

    // printing binary array in reverse order
    for (int j = 8; j >= 0; j--)
        Serial_write(&uart, (binaryNum[j] == 1) ? '1' : '0');
}

void log_nl()
{
    char newline[] = "\r\n";
    Serial_write_string(&uart, newline);
}

static const long hextable[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,
    9,  -1, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1};

/**
 * @brief convert a hexidecimal string to a signed long
 * will not produce or process negative numbers except
 * to signal error.
 *
 * @param hex without decoration, case insensitive.
 *
 * @return -1 on error, or result (max (sizeof(long)*8)-1 bits)
 */
long hexdec(unsigned const char *hex)
{
    long ret = 0;
    while (*hex && ret >= 0) {
        ret = (ret << 4) | hextable[*hex++];
    }
    return ret;
}

void print_shell(eer_t *menu)
{
    *command = 0;

    log_nl();
    log_string("$ > ");
}

void print_command_not_found(eer_t *menu)
{
    log_nl();
    log_string(command);
    log_string(" not found.");

    print_shell(menu);
}

void print_version(void *arg)
{
    log_nl();
    log_num("e-react ver. ", 1);
}

void log_memory(char *data)
{
    log_nl();
    log_string(data);
    log_string(": ");
    log_binary(*data);
}

void print_memory(void *address)
{
    char *address_hex     = address + 5;
    void *address_pointer = (void *)hexdec(address_hex);

    log_memory(address_pointer);
}

void dump_memory(char *request)
{
    char *address_hex     = request + 5;
    address_hex[4]        = '\0';
    void *address_pointer = (void *)hexdec(address_hex);

    int size = (int)*(char *)itoa((long)(address_hex + 5));

    for (int i = 0; i < size; i++) {
        log_memory(address_pointer++);
    }
}

void write_memory(char *request)
{
    char *address_hex     = request + 5;
    address_hex[4]        = '\0';
    char *address_pointer = (char *)hexdec(address_hex);

    char *value_hex = address_hex + 5;
    char *value     = (char *)hexdec(value_hex);

    *address_pointer = *value;
}



void print_time(void *arg)
{
    struct Clock_time *time = &Clock_time(&clk);
    log_nl();
    log_string("Timestamp: ");
    log_string(utoa(time->timestamp));
    log_string(" s ");
    log_string(utoa(time->us));
    log_string(" us");
}
