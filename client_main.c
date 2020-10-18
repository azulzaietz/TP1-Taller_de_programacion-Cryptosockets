#include "client.h"

int main(int argc, char* const* argv) {
    client_t client;
    init_client(&client, argc, argv);
    send_coded_message_to_server(&client);

    return 0;
}
