#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "helper.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        usage(argv[0]);
    }

    unsigned short int port = (unsigned short int) atoi(argv[1]);

    if (!(port >= 1 && port <= 65535)) {
        fatal("incorrect port range");
    }

    printf("chosen port: %d\n", port);

    const unsigned short buffer_size = 1024;

    int sockfd, new_sockfd;
    struct sockaddr_in host_addr, client_addr;
    socklen_t sin_size;
    int recv_length = 1, yes = 1;
    char buffer[buffer_size];

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        fatal("in socket creation");
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        fatal("in setsockopt");
    }

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(host_addr.sin_zero), '\0', 8);

    if (bind(sockfd, (struct sockaddr *) &host_addr, sizeof(struct sockaddr)) == -1) {
        fatal("binding to socket");
    }

    if (listen(sockfd, 5) == -1) {
        fatal("listening on socket");
    }

    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        new_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size);

        if (new_sockfd == -1) {
            fatal("accepting connection");
        }

        printf("Server got new connection from [%s:%d]\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        char *send_string = "Hello, world!";
        send(new_sockfd, send_string, strlen(send_string), 0);

        recv_length = recv(new_sockfd, &buffer, buffer_size, 0);
        while (recv_length > 0) {
            printf("RECV: %d bytes\n", recv_length);
            dump(buffer, recv_length);
            recv_length = recv(new_sockfd, &buffer, buffer_size, 0);
        }
        close(new_sockfd);
    }

    return 0;
}
