#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>

void stringToFile(const char *filepath, const char *data)
{
    FILE *fp = fopen(filepath, "ab");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

int sockid;

void handle_sigint(int sig) 
{ 
	printf("Caught signal %d\n", sig); 
	close(sockid);
	exit(0);
} 
int main(int argc, char **argv)
{

    int port = atoi(argv[1]);
    struct sockaddr_in myaddr ,serveraddr;
    //int sockid;
    sockid=socket(AF_INET,SOCK_STREAM,0);
    memset(&myaddr,'0',sizeof(myaddr));
    myaddr.sin_family=AF_INET;
    myaddr.sin_port=htons(8888);
    myaddr.sin_addr.s_addr=inet_addr("54.202.194.183");
    signal(SIGINT, handle_sigint);
    if(sockid==-1)
    {
        perror("socket");
    }
    int len=sizeof(myaddr);
    if(connect(sockid,(const struct sockaddr*)&myaddr,len)==-1)
    {
        perror("connect");
    }
    //fprintf(stdout,"Client Online....");

char buffer[8192]; // or whatever you like, but best to keep it large
int count = 0;
int total = 0;
char fileString[1000];
while ((count = recv(sockid, &buffer, sizeof buffer - count, 0)) > 0)
{
    total += count;
    // At this point the buffer is valid from 0..total-1, if that's enough then process it and break, otherwise continue
    //recv(sockid,&buffer,10000,0);

    //fprintf(stdout,"[%d]", getpid());
    puts(buffer);
    //memset(buffer, 0, sizeof buffer);
    //char buffer[8192];
    strcat(fileString, buffer);

}
if (count == -1)
{
    perror("recv");
}
else if (count == 0)
{
    // EOS on the socket: close it, exit the thread, etc.
}
/*
	char s[10000];


        //gets(s);
        //send(sockid,s,10000,0);
        recv(sockid,&s,10000,0);
        fprintf(stdout,"Server says....");
        puts(s);
        recv(sockid,&s,10000,0);
        fprintf(stdout,"Server says....");
        puts(s);
        recv(sockid,&s,10000,0);
        fprintf(stdout,"Server says....");
        puts(s);
        recv(sockid,&s,10000,0);
        fprintf(stdout,"Server says....");
        puts(s);
        recv(sockid,&s,10000,0);
        fprintf(stdout,"Server says....");
        puts(s);
        recv(sockid,&s,10000,0);
        fprintf(stdout,"Server says....");
        puts(s); */

sleep(10);  

    close(sockid);
    stringToFile(argv[2], fileString);
    return 0;
}