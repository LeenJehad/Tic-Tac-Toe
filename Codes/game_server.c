// Leen Alsarayreh 20180869
// Omar Abbadi 20170022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <termios.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#define MAXLINE 200
void sig_chld(int signo);

int playerselection();
void X_O(int , int ); 

int main(){
int acceptfd, acceptfd2;
socklen_t clilen;
int any; 
int x; 
pid_t pid;
char buff[MAXLINE];
int sockfd;
struct sockaddr_in serv,cli,cli2;
if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0){
    printf("ERROR CREATING SOCKET");
}
bzero(&serv, sizeof(serv));
serv.sin_family = AF_INET;
serv.sin_port = htons(5555);
serv.sin_addr.s_addr = htonl(INADDR_ANY);
if((bind(sockfd, (struct sockaddr*)&serv, sizeof(serv))) < 0 )
{
    perror("Error binding  \n ");
    exit(0);
}
if(listen(sockfd,5)<0){
    printf("Error listening\n");
};
signal(SIGCHLD, sig_chld);
for(;;){

clilen=sizeof(cli);
while((acceptfd=accept(sockfd,(struct sockaddr*)&cli,&clilen))<0);

puts("player connected\n");

clilen=sizeof(cli2);
while((acceptfd2=accept(sockfd,(struct sockaddr*)&cli2,&clilen))<0);
sleep(1);
puts("Game Begins");
write(acceptfd,"Game started\n", sizeof("Game started\n"));    
write(acceptfd2,"Game started\n", sizeof("Game started\n"));
sleep(1);
puts("Players connected");
    
    
x=playerselection();
if(x==1){
    write(acceptfd,"You start first\n", sizeof("You start first\n"));
    write(acceptfd2,"You are player 2\n",sizeof("You are player 2\n"));
 }else
 {
    write(acceptfd2,"You start first\n", sizeof("You start first\n"));
    write(acceptfd,"You are player 2\n",sizeof("You are player 2\n"));
    any = acceptfd2; 
    acceptfd2= acceptfd; 
    acceptfd= any;
 }
 if((pid=fork())==0)
 {
    close(sockfd);
  for(;;)
  {
    X_O(acceptfd, acceptfd2);
  }

    close(acceptfd);
    close(acceptfd2);      
    exit(0);
  }
}

}

int playerselection(){
    srand(time(0));
    int r = rand()%2;
    if(r%2==0){
        return 1;
    }
    else
        return 2;
}


void X_O(int accept1 , int accept2 )
{
    int test = 0;
    char square[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int player = 1, choice;
    char mark;
    int gamestatus;
    char buff[MAXLINE];
    bzero(&buff, MAXLINE);
    int counter=0;
    do
    {
        if(player ==1 )
        {
            write(accept1, "\n\n\tTic Tac Toe\n\n", sizeof("\n\n\tTic Tac Toe\n\n"));
            sleep(1); 
            write(accept1, square, sizeof(square));
            bzero(&buff, MAXLINE);
            while (read(accept1, buff,MAXLINE )<0);
            choice = atoi(buff);
            mark = 'X';
            player=2 ; 
        }
        else 
        {
            write(accept2, "\n\n\tTic Tac Toe\n\n", sizeof("\n\n\tTic Tac Toe\n\n"));
            sleep(1); 
            write(accept2, square, sizeof(square));
            bzero(&buff, MAXLINE);
            while (read(accept2, buff,MAXLINE )<0);
            choice = atoi(buff);
            mark = 'O';
            player=1 ; 
        }
        if (choice == 1 && square[1] == '1')
            square[1] = mark;
        else if (choice == 2 && square[2] == '2')
            square[2] = mark;
        else if (choice == 3 && square[3] == '3')
            square[3] = mark;
        else if (choice == 4 && square[4] == '4')
            square[4] = mark;
        else if (choice == 5 && square[5] == '5')
            square[5] = mark;
        else if (choice == 6 && square[6] == '6')
            square[6] = mark;
        else if (choice == 7 && square[7] == '7')
            square[7] = mark;
        else if (choice == 8 && square[8] == '8')
            square[8] = mark;
        else if (choice == 9 && square[9] == '9')
            square[9] = mark;
        else
        
        {
            if(player==1)
            {
                write(accept2, "Invalid move\n",sizeof("Invalid move\n") );
                player = 2;
            }
            else 
            { 
                write(accept1, "Invalid move\n",sizeof("Invalid move\n") );
                player = 1;
            }
             sleep(1);
        }
    if (square[1] == square[2] && square[2] == square[3])
        test=1;

    else if (square[4] == square[5] && square[5] == square[6])
        test=1;
    else if (square[7] == square[8] && square[8] == square[9])
         test=1;
    else if (square[1] == square[4] && square[4] == square[7])
         test=1;
    else if (square[2] == square[5] && square[5] == square[8])
        test=1;

    else if (square[3] == square[6] && square[6] == square[9])
        test=1;

    else if (square[1] == square[5] && square[5] == square[9])
        test=1;

    else if (square[3] == square[5] && square[5] == square[7])
        test=1;

    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] 
        != '7' && square[8] != '8' && square[9] != '9')
        test=2;
        gamestatus = test;
    }
    while (gamestatus == 0);
    printf("\n\n\tTic Tac Toe\n\n");
    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);
    printf("     |     |     \n\n");
    if (gamestatus == 1)
    {
        if(player==2)
        {
            write(accept1,"Congratulations. You won!", sizeof("Congratulations. You won!"));
            write(accept2,"Game Over. You Lose!", sizeof("Game Over. You Lose!"));
        }
        if (player==1)
        {
            write(accept2,"Congratulations. You won!", sizeof("Congratulations. You won!"));
            write(accept1,"Game Over. You Lose!", sizeof("Game Over. You Lose!"));
        }
    }
    else
    {
        write(accept1,"DRAW!", sizeof("DRAW!"));
        write(accept2,"DRAW!", sizeof("DRAW!"));      
    }
        

   sleep(1); 

 }

 void sig_chld(int signo){
    pid_t pid;
    int stat;

    pid=wait(&stat);
    printf("child %d terminated\n",pid);
    return;
 }