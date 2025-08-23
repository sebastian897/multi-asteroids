void ClientInit();
void Send(const char* buf, int size);
void ClientReceive();
void ClientShutdown();
#define BUFLEN 512
extern char buf[BUFLEN];
