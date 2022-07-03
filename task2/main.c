#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

char buf_read[256];
char buf_write[256];

void thread_tcp()
{
    short port;
    scanf("%i",&port);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("can't create connection"); exit(1);
    }
    struct sockaddr_in sai;
    sai.sin_family = AF_INET;
    sai.sin_addr.s_addr = htonl(INADDR_ANY);
    sai.sin_port = htons(port);
    bind(sock, (struct sockaddr*)&sai,sizeof(sai));
    listen(sock, 10);
    int conn = accept(sock, (struct sockaddr*)NULL, NULL);
    while(1)
    {
        read(conn, buf_read, 256);
        if(strlen(buf_write))
        {
            write(conn, buf_write,strlen(buf_write));
            printf(buf_write);
            strcpy(buf_write,"");
        }
    }
}

int main()
{
    pthread_t thread_1;
    pthread_create(&thread_1, NULL, thread_tcp, NULL);
    while(1)
    {
        if(strlen(buf_read))
        {
            int j = strlen(buf_read);
            char temp_buf[j];
            j--;
            for(int i = 0;j>=0; j--,i++)
            {
                temp_buf[i] = buf_read[j];
            }
            sprintf(buf_write,temp_buf);
            strcpy(buf_read,"");
        }
    }
    return 0;
}
