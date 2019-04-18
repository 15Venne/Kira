#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>
#include<unistd.h>
#include<sys/mman.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>

#define SERVERIP "192.168.5.215"
#define SERVERPORT 2015

void toJoin(int);
void titleprint();
