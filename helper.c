#include "helper.h"

void usage(char const *const app_name) {
    printf("%1$s {port}\nExample: %1$s 7890\n", app_name);
}

void fatal(char const *const message) {
    const unsigned short error_message_size = 100;

    char error_message[error_message_size];

    char *error_message_base_text = "[!!] Fatal Error - ";
    strcpy(error_message, error_message_base_text);
    strncat(error_message, message, error_message_size - strlen(error_message_base_text));
    perror(error_message);

    exit(-1);
}

void dump(char const *const data_buffer, unsigned int const length) {
    char byte;
    unsigned int i, j;
    for (i = 0; i < length; i++) {
        byte = data_buffer[i];
        printf("%02x ", byte);
        if (((i % 16) == 15) || (i == length - 1)) {
            for (j = 0; j < 15 - (i % 16); j++) {
                printf("   ");
            }

            printf("| ");

            for (j = (i - (i % 16)); j <= i; j++) {
                byte = data_buffer[j];
                if ((byte > 31) && (byte < 127)) {
                    printf("%c", byte);
                } else {
                    printf(".");
                }
            }

            printf("\n");
        }
    }
}
