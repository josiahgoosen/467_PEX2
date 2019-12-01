//Code obtained and modified from https://www.geeksforgeeks.org/udp-server-client-implementation-c/
/***Samuel Butler, Josiah Goosen
* PEX1 for CompSci 467
* UDP_Client.c used to be the client with the UDP_Server.c
* Documentation Statement:C2C Jesse Sidhu suggested that I use a while loop to continually loop and run my server and client. I implemented the loop so my client could rin again and agian.
*C2C Manny Riolo instructed us in methods to write our mp3 to a file in order to save it, he walked me through the thought process involved in putting my write file into a loop so I can read multiple packets.
*/

//This is a test of github

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/time.h>
#include "tcp_functions.h"

#define PORT     4240
#define MAXLINE 1024

// Driver code
int main() {
    int sockfd; //Socket descriptor, like a file-handle
    char buffer[MAXLINE]; //buffer to store message from server
    struct sockaddr_in servaddr;  //we don't bind to a socket to send UDP traffic, so we only need to configure server address
    char userInputOpt[50];
    char song1[60] = "START_STREAM\nSuzanne Vega - Toms Diner.mp3";
    char song2[60] = "START_STREAM\nBilly Joel - We Didn't Start the Fire.mp3";
    char userIn[35];

    while (strcmp(userInputOpt, "3") != 0) {


        //print options to command line
        printf("%s\n", "1) List");
        printf("%s\n", "2) Stream");
        printf("%s\n", "3) Quit\n");
        scanf("%s", userInputOpt);
        int n, len = sizeof(servaddr);

        if (strcmp(userInputOpt, "1") == 0 || strcmp(userInputOpt, "2") == 0) {
            // Creating socket file descriptor
            if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("socket creation failed");
                exit(EXIT_FAILURE);
            }

            // Filling server information
            servaddr.sin_family = AF_INET; //IPv4
            servaddr.sin_port = htons(
                    PORT); // port, converted to network byte order (prevents little/big endian confusion between hosts)
            servaddr.sin_addr.s_addr = INADDR_ANY; //localhost


            //send request to the server

            //option one, request songs
            if (strcmp(userInputOpt, "1") == 0) {
                strcpy(userInputOpt, "LIST_REQUEST");
                sendto(sockfd, (const char *) userInputOpt, strlen(userInputOpt), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));    //send request to server
            }else if(strcmp(userInputOpt, "2") == 0){
                printf("Please enter the name of the song exactly as displayed:\n");
                scanf("%s",userIn);
                if (strcmp(userIn,"Suzanne")==0) {
                    sendto(sockfd, (const char *) song1, strlen(song1), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
                    FILE * fp = fopen("./Song.mp3", "a+");
                    while((n = recvfrom(sockfd, (char *) buffer, MAXLINE, 0, (struct sockaddr *) &servaddr, &len))==0){
                        for(int i = 4; i < n; i++){
                            fprintf(fp, "%c", buffer[n]);
                        }
                    }
                }else if(strcmp(userIn,"Billy")==0){
                    sendto(sockfd, (const char *) song2, strlen(song2), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
                    FILE * fp = fopen("./Song.mp3", "a+");
                    while((n = recvfrom(sockfd, (char *) buffer, MAXLINE, 0, (struct sockaddr *) &servaddr, &len))==0){
                        for(int i = 4; i < n; i++){
                            fprintf(fp, "%c", buffer[n]);
                        }
                    }
                }else if(strcmp(userIn, "3")==0){
                    sendto(sockfd, (const char *) userInputOpt, strlen(userInputOpt), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));    //send request to server
                    printf("Exiting now...");
                    close(sockfd);
                    return 0;
                }
            }

            // Set the timeout for the socket:
            struct timeval timeout; //structure to hold our timeout
            timeout.tv_sec = 5; //5 second timeout
            timeout.tv_usec = 0; //0 milliseconds
            if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) < 0) {
                perror("setsockopt failed");
                exit(EXIT_FAILURE);
            }
// ...address configuration and possibly a send command would happen here...

// Receive data with a timeout:
            if ((n = recvfrom(sockfd, (char *) buffer, MAXLINE, 0, (struct sockaddr *) &servaddr, &len)) < 0) {
                // Handle errors here.  Errno 11, "Resource Temporarily Unavailable" is returned as a result of a timeout.
                perror("ERROR");
                printf("Errno: %d. ", errno);
                exit(EXIT_FAILURE);
            }
            //Sending message to server
            buffer[n+12] = '\0'; //terminate message
            printf("%s\n", buffer);

        }
        else if (strcmp(userInputOpt, "3") == 0) {
            sendto(sockfd, (const char *) userInputOpt, strlen(userInputOpt), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));    //send request to server
            printf("Exiting now...");
            close(sockfd);
            return 0;
        }else {
            printf("Please enter a 1, 2, or 3.\n");
        }


    }
}