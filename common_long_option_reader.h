#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/* *****************************************************************
 *                PRIMITIVAS DEL LONG OPTION READER
 * *****************************************************************/

//Lee los parametros de la linea de comandos pasados con el formato 
// "--parametro=parametro"
void read_long_options(const char** method, const char** key, int argc, char* const* argv);