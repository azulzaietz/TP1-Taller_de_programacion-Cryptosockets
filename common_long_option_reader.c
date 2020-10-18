#include "common_long_option_reader.h"

void read_long_options(const char** method, const char** key, 
int argc, char* const* argv) {	
    const char* str_key = "key";
    const char* str_method = "method";
	const char* method_cesar = "cesar";
    const char* method_vigenere = "vigenere";
    const char* method_rc4 = "rc4";

    const char* option;
    int option_index = 0;
    int c = 0;

    static struct option long_options[] = {
        {"method", required_argument, 0,  0 },
        {"key", required_argument, 0,  0 },
    };

	while (c != -1){
		c = getopt_long(argc, argv, "-:abc:d::", long_options, &option_index);

       	if (c == 0) {
        	option = long_options[option_index].name;

			if (strcmp(option, str_method) == 0) {
				if (strcmp(optarg, method_cesar) == 0){
		          	*method = "cesar";
				} else if (strcmp(optarg, method_vigenere) == 0){
					*method = "vigenere";
				} else if (strcmp(optarg, method_rc4) == 0){
					*method = "rc4";
				} else{
					printf("No se pasaron metodos\n");
				}
			} else if (strcmp(long_options[option_index].name, str_key) == 0){
				*key = optarg;
			}
        }
	}
}
