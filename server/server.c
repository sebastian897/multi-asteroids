#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdbool.h>
#include "constants.h"
#include "buffer_control.h"

#define PORT 5150
#define BUFLEN 511


typedef struct client{
    struct sockaddr_in addr;
    bool active;
} client;

static client clients[PLAYERS_MAX] = {0};
static SOCKET sock;
static int slen = sizeof(struct sockaddr_in);

char buf[BUFLEN];

void ServerInit(){
    struct sockaddr_in server;
    WSADATA wsa;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Server: WSAStartup failed: %d\n", WSAGetLastError());
        exit(1);
    }

    // Create UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
            printf("Server: Socket creation failed: %d\n", WSAGetLastError());
            WSACleanup();
            exit(1);
    }    

    // Prepare server address
    server.sin_family = AF_INET;
    const char* ip_str = "192.168.40.85"; 
     if (inet_pton(AF_INET,ip_str,&server.sin_addr.s_addr) != 1) {
        printf("Server: WSAStartup failed: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    server.sin_port = htons(PORT);

    // Bind
    if (bind(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Server: Bind failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(1);
    }

    printf("Server: Waiting for UDP packet on port %s:%d...\n", ip_str, PORT);
}

void ServerShutdown(){
    closesocket(sock);
    WSACleanup();
}

void Broadcast(char* buf, int size){
    for (signed char i = 0; i < PLAYERS_MAX; i++) {
        if (!clients[i].active) continue;
        memcpy(buf, &i, 1);
        if (sendto(sock, buf, size, 0, (struct sockaddr*)&clients[i].addr, slen) == SOCKET_ERROR) {
            printf("Server: sendto() failed: %d\n", WSAGetLastError());
        } else {
            printf("Server: Response sent to client.\n");
        }
    }
}

void RecordClient(struct sockaddr_in* cl,int recv_len){
    bool found = false;
    int slot = -1;
    for (int i = 0; i < PLAYERS_MAX; i++) {
        if (!clients[i].active){
            if (slot == -1){
                slot = i;
            }
            continue;
        }
        if (clients[i].addr.sin_addr.S_un.S_addr == cl->sin_addr.S_un.S_addr &&
            clients[i].addr.sin_port == cl->sin_port) {
            found=true;
            break;
        }
    }
    if (!found && slot != -1){
        clients[slot].addr.sin_addr.S_un.S_addr = cl->sin_addr.S_un.S_addr;
        clients[slot].addr.sin_port = cl->sin_port;
        clients[slot].addr.sin_family = cl->sin_family;
        clients[slot].active = true;
    }
    printf("Server: Received packet from %s:%d\n", inet_ntoa(cl->sin_addr), ntohs(cl->sin_port));
}

void Receive(){
    struct sockaddr_in cl;
    // Receive a packet
    int recv_len = recvfrom(sock, buf, BUFLEN-1, 0, (struct sockaddr*)&cl, &slen);
    if (recv_len == SOCKET_ERROR) {

        printf("1Server: recvfrom() failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(1);
    } 
    RecordClient(&cl, recv_len);
}

int ReceiveMultiple(){
    #define SILENCE_TIMEOUT_MS 10
    int ret;        
    struct sockaddr_in cl;
    int packets = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = SILENCE_TIMEOUT_MS * 1000;  // convert ms to µs   

    // Collect packets until no activity for SILENCE_TIMEOUT_MS
    while (1) {


        ret = select(0, &readfds, NULL, NULL, &timeout);
        printf("ret = %d)\n", ret);
        if (ret == SOCKET_ERROR) {
            printf("select() failed: %d\n", WSAGetLastError());
            exit(1);
        } else if (ret == 0) {
            // No data received in timeout
            printf("Silence timeout reached (%d ms)\n", SILENCE_TIMEOUT_MS);
            return packets;
        }

        if (FD_ISSET(sock, &readfds)) {
            int bytesReceived = recvfrom(sock, buf, BUFLEN-1, 0, (struct sockaddr*)&cl, &slen);
            if (bytesReceived == SOCKET_ERROR) {
                printf("2Server: recvfrom() failed: %d\n", WSAGetLastError());
                closesocket(sock);
                WSACleanup();
                exit(1);
            } 
            RecordClient(&cl, bytesReceived);
            StoreInputs(buf);
            packets++;
        }
    }
    return packets;
}