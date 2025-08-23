// udp_client.c
#include <stdio.h>
#include <winsock2.h>
#include "client.h"

#define SERVER "192.168.40.85"
#define PORT 5150

WSADATA wsa;
SOCKET sock;
struct sockaddr_in client;
static int slen = sizeof(client);
char buf[BUFLEN];

void ClientInit(){
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Client: WSAStartup failed: %d\n", WSAGetLastError());
        exit(1);
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Client: Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    // Setup client address
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = inet_addr(SERVER);
}

void Send(const char* buf, int size){
    // Send message
    if (sendto(sock, buf, size, 0, (struct sockaddr*)&client, slen) == SOCKET_ERROR) {
        printf("Client: sendto() failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
    printf("Client: Message sent. Waiting for reply...\n");
}

void ClientReceive(){
    // Receive response
    int recv_len = recvfrom(sock, buf, BUFLEN-1, 0, (struct sockaddr*)&client, &slen);
    if (recv_len == SOCKET_ERROR) {
        printf("Client: recvfrom() failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(1);
    } 
    
    buf[recv_len] = '\0';
    printf("Client: Server reply: %s\n", buf);
}

void ClientShutdown(){
    // Cleanup
    closesocket(sock);
    WSACleanup();
}
