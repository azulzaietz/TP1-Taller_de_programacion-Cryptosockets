#include "client.h"

int main(int argc, char const* argv[]) {

    client_t client;
    init_client(&client, argv[1], argv[2], argv[3], argv[4]);
    send_message_to_server(&client);

    return 0;
}