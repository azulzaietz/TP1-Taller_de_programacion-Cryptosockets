#define _POSIX_C_SOURCE 200112L
#include "common_socket.h"

void socket_init(socket_t* self, int fd){
	self->fd = fd;
}

void socket_uninit(socket_t* self){
	if (!self) {return;}
    if (shutdown(self->fd, SHUT_RDWR) == -1) {
		fprintf(stderr, "socket_uninit-->shutdown: %s\n", strerror(errno));
    } 
    if (close(self->fd) == -1) {
		fprintf(stderr, "socket_uninit-->close: %s\n", strerror(errno));
    }
}

struct addrinfo* _get_addrinfo
(socket_t* self, const char* host, const char* service, int flags) {
	int error;
	struct addrinfo *addr_list;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = FAMILY;
    hints.ai_socktype = SOCK_TYPE;
    hints.ai_protocol = PROTOCOL;    
	hints.ai_flags = flags;
	if ((error = getaddrinfo(host, service, &hints, &addr_list)) != 0) {
		fprintf(stderr, "_get_addrinfo: %s\n", gai_strerror(error));
        return NULL;
    }
	return addr_list;
}

bool socket_bind_and_listen
(socket_t* self, const char* host, const char* service){
	bool bind_error = false;
	int fd;
	int val = 1;
	struct addrinfo *addr, *addr_list;
	if ((addr_list = _get_addrinfo(self, host, service, SERVER_FLAGS)) == NULL) {
        return false;
    }

	for (addr = addr_list; addr && !bind_error; addr = addr->ai_next) {
        fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (bind(fd, addr->ai_addr, addr->ai_addrlen) == 0) bind_error = true;
    }
    freeaddrinfo(addr_list);
    
    if (!bind_error) {
		fprintf(stderr, "socket_bind_and_listen-->bind: %s\n", strerror(errno));
        return false;
    }

	socket_init(self, fd);

	if (listen(self->fd, 10) < 0) {
		socket_uninit(self);
		fprintf(stderr, "socket_bind_and_listen-->listen: %s\n", strerror(errno));
		return false;
	}
	return true;
}

int socket_accept(socket_t* listener, socket_t* peer){
	int fd = -1;

    puts("Waiting for incoming connections...");
    
	if ((peer->fd = accept(listener->fd, NULL, NULL)) < 0) {
		fprintf(stderr, "socket_accept-->accept: %s\n", strerror(errno));
        return fd;
	}

    puts("Connection accepted");
    fd = 0;
	return fd;
}

bool socket_connect(socket_t* self, const char* host, const char* service){
	int fd;
	bool connection = false;

    struct addrinfo *addr, *addr_list;
    if ((addr_list = _get_addrinfo(self, host, service, CLIENT_FLAGS)) == NULL) {
        return false;
    }

    for (addr = addr_list; addr && !connection; addr = addr->ai_next) {
        fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (connect(fd, addr->ai_addr, addr->ai_addrlen) != -1) connection = true;
    }
    freeaddrinfo(addr_list);

    if (!connection) {
		fprintf(stderr, "socket_connect-->connect: %s\n", strerror(errno));
        return false;
    }

	socket_init(self, fd);
    return true;
}

ssize_t socket_send(socket_t* self, unsigned char* buffer, size_t length){
	if (length == 0) return 0;

    int remaining_bytes = length;
    int total_bytes_sent = 0;

    while (total_bytes_sent < length) {
        ssize_t bytes = send(self->fd, &buffer[total_bytes_sent], 
                        remaining_bytes, MSG_NOSIGNAL);

        if (bytes == -1) {
			fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }

    return total_bytes_sent;
}

ssize_t socket_receive(socket_t* self, unsigned char* buffer, size_t length){
	if (length == 0) return 0;

    int remaining_bytes = length;
    int total_bytes_received = 0;

    while (total_bytes_received < length) {
        ssize_t bytes = recv(self->fd, &buffer[total_bytes_received],
                        remaining_bytes, 0);

        if (bytes == -1) {
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }

    return total_bytes_received;
}
