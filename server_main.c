#include "server.h"

int main(int argc, char* const* argv) {
    server_t server;
    if (argc != 4) return -1;
    server_init(&server, argc, argv);
    receive_coded_message_from_client(&server);

    return 0;
}
