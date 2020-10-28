#include "client.h"

int main(int argc, char* const* argv) {
    client_t client;
    if (argc != 5) return -1;
    init_client(&client, argc, argv);
    send_coded_message_to_server(&client);

    return 0;
}
