#ifndef SIMPLE_SERVER_HELPER_H
#define SIMPLE_SERVER_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char const *const app_name);

void fatal(char const *const message);

void dump(char const *const data_buffer, unsigned int const length);

#endif
