#include "client.h"

int main(int argc, char* const* argv) {
    client_t client;
    init_client(&client, argv[1], argv[2], argc, argv);
    send_coded_message_to_server(&client);

    return 0;
}
