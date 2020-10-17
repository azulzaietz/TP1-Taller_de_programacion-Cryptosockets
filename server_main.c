#include "server.h"

int main(int argc, char const* argv[]) {
    server_t server;
    server_init(&server, argv[1], argv[2], argv[3]);
    receive_coded_message_from_client(&server);

    return 0;
}
