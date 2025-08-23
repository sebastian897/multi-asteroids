void ClientInit();
void Send(const char* buf, int size);
void ClientReceive();
void ClientShutdown();
#define BUFLEN 1024
extern char buf[BUFLEN];
