#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdbool.h>

#define PORT 5150
#define BUFLEN 512

#define MAX_PLAYERS 16

typedef struct client{
    struct sockaddr_in addr;
    bool active;
} client;

static client clients[MAX_PLAYERS] = {0};
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

void Broadcast(const char* buf, int size){
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!clients[i].active) continue;
        if (sendto(sock, buf, size, 0, (struct sockaddr*)&clients[i].addr, slen) == SOCKET_ERROR) {
            printf("Server: sendto() failed: %d\n", WSAGetLastError());
        } else {
            printf("Server: Response sent to client.\n");
        }
    }
}

void Receive(){
    // Receive a packet
    struct sockaddr_in cl;
    int recv_len = recvfrom(sock, buf, BUFLEN-1, 0, (struct sockaddr*)&cl, &slen);
    if (recv_len == SOCKET_ERROR) {

        printf("Server: recvfrom() failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(1);
    } 
    bool found = false;
    int slot = -1;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!clients[i].active){
            if (slot == -1){
                slot = i;
            }
            continue;
        }
        if (clients[i].addr.sin_addr.S_un.S_addr == cl.sin_addr.S_un.S_addr &&
            clients[i].addr.sin_port == cl.sin_port) {
            found=true;
            break;
        }
    }
    if (!found && slot != -1){
        clients[slot].addr.sin_addr.S_un.S_addr = cl.sin_addr.S_un.S_addr;
        clients[slot].addr.sin_port = cl.sin_port;
        clients[slot].addr.sin_family = cl.sin_family;
        clients[slot].active = true;
    }
    buf[recv_len] = '\0';
    printf("Server: Received packet from %s:%d\n", inet_ntoa(cl.sin_addr), ntohs(cl.sin_port));
    printf("Server: Data: %s\n", buf);
}