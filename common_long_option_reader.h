#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* *****************************************************************
 *                PRIMITIVAS DEL LONG OPTION READER
 * *****************************************************************/

void read_long_options(const char** method, const char** key, int argc, char* const* argv);