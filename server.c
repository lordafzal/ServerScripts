#include<signal.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>


int sockid, new;


void handle_sigint(int sig) 
{ 
	printf("Caught signal %d\n", sig); 
	close(new);
	close(sockid);
	//shutdown(sockid, 2);

	//closeSocket(sockid);
	sleep(1);
	exit(0);
} 


int main(int argc, char **argv)
{
	

    int port = atoi(argv[1]);
    struct sockaddr_in myaddr ,clientaddr;
    int newsockid;
    sockid=socket(AF_INET,SOCK_STREAM,0);
    memset(&myaddr,'0',sizeof(myaddr));
    myaddr.sin_family=AF_INET;
    myaddr.sin_port=htons(port);
    myaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    const int       optVal = 1;
	const socklen_t optLen = sizeof(optVal);

	int rtn = setsockopt(sockid, SOL_SOCKET, SO_REUSEADDR, (void*) &optVal, optLen);

	//assert(rtn == 0);   /* this is optional */
    signal(SIGINT, handle_sigint);
    if(sockid==-1)
    {
        perror("socket");
    }
    int len=sizeof(myaddr);
    if(bind(sockid,( struct sockaddr*)&myaddr,len)==-1)
    {
        perror("bind");
    }
    if(listen(sockid,10)==-1)
    {
        perror("listen");
    }
    int pid;
    static int counter=0;
    static int iterations=0;
    for(;;)
    {
            new = accept(sockid, (struct sockaddr *)&clientaddr, &len);
            if ((pid = fork()) == -1)
            {

                close(new);
                continue;
            }
            else if(pid > 0)
            {
            	char buf[100];
            	snprintf(buf, sizeof buf, "[%d] PID %d Iteration: #%d",port, pid,iterations);
                iterations++;
                sleep(2);
                send(new, buf, strlen(buf), 0);
                snprintf(buf, sizeof buf, "[%d] PID %d Iteration: #%d",port, pid,iterations);
                iterations++;
                sleep(2);
                send(new, buf, strlen(buf), 0);
                snprintf(buf, sizeof buf, "[%d] PID %d Iteration: #%d",port, pid,iterations);
                iterations++;
                sleep(2);
                send(new, buf, strlen(buf), 0);
                
                snprintf(buf, sizeof buf, "[%d] PID %d Iteration: #%d",port, pid,iterations);
                iterations++;
                sleep(2);
                send(new, buf, strlen(buf), 0);
                snprintf(buf, sizeof buf, "[%d] PID %d Iteration: #%d",port, pid,iterations);
                iterations++;
                sleep(2);
                send(new, buf, strlen(buf), 0);
                close(new);
                counter++;
                printf("here2\n");
                continue;
            }
            else if(pid == 0)
            {
                

                printf("here 1\n");

                close(new);
                break;
            }
    }
    printf("here3");
    close(new);
    close(sockid);
    return 0;
}




