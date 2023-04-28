// Leen Alsarayreh 20180869
// Omar Abbadi 20170022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#define MAXLINE 200
int main() {
    
    char buff[MAXLINE], buff2[MAXLINE];
    int clfd;
    struct sockaddr_in serv;
    if ((clfd = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf("ERROR CREATING SOCKET");
    }
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(5555);

    // Connect to Server
    if(connect(clfd, (struct sockaddr*) &serv, sizeof(serv))<0){
        printf("ERROR CONNECTING");
        exit(0);
    }
    
    while(read(clfd,buff,MAXLINE)<0);
    puts(buff);
    bzero(&buff,MAXLINE);
    while(read(clfd,buff,MAXLINE)<0);
    puts(buff);

    for(;;) 
    {
        bzero(&buff, MAXLINE);
        bzero(&buff2, MAXLINE);
        while(read(clfd,buff,MAXLINE)<0);
        memcpy((char*)&buff2,"\n\n\tTic Tac Toe\n\n",MAXLINE);
        if(strcmp(buff2, buff)==0)
        {
           
            puts(buff); 
            bzero(&buff, MAXLINE);
            while(read(clfd,buff,MAXLINE)<0);

            printf("Player 1 (X)  -  Player 2 (O)\n\n\n");
            printf("     |     |     \n");
            printf("  %c  |  %c  |  %c \n", buff[1], buff[2], buff[3]);   
            printf("     |     |     \n");
            printf("  %c  |  %c  |  %c \n", buff[4], buff[5], buff[6]);
            printf("     |     |     \n");
            printf("  %c  |  %c  |  %c \n", buff[7], buff[8], buff[9]);
            printf("     |     |     \n\n");
            memset(&buff,'\0', MAXLINE);
            fgets(buff, MAXLINE, stdin);
            write(clfd, buff,MAXLINE);
        }
        bzero(&buff2, MAXLINE);
        memcpy((char*)&buff2,"Invalid move\n",MAXLINE);
        if(strcmp(buff2, buff)==0 )
        {
            puts(buff);
        }
        
        bzero(&buff2, MAXLINE);
        memcpy((char*)&buff2,"Congratulations. You won!", MAXLINE);
        if(strcmp(buff2, buff)==0 )
        {
            puts(buff);
            exit(0);
        }
        
        bzero(&buff2, MAXLINE);
        memcpy((char*)&buff2,"Game Over. You Lose!", MAXLINE);
        if(strcmp(buff2, buff)==0 )
        {
            puts(buff);
            exit(0);
        }
        
        bzero(&buff2, MAXLINE);
        memcpy((char*)&buff2,"DRAW!", MAXLINE);
        if(strcmp(buff2, buff)==0 )
        {
            puts(buff);
            exit(0);
        }

    }
    // Closes client connection
    close(clfd);

    return 0;
}