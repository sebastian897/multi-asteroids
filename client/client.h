void ClientInit(void);
void Send(const char* buf, int size);
void ClientReceive(void);
void ClientShutdown(void);
#define BUFLEN 1024
extern char buf[BUFLEN];
