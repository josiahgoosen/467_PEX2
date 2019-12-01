//
// Created by Josiah on 12/1/19.
//

// Function to conduct 3-way handshake with server.  Establishes initial
//   SEQ and ACK numbers.  Returns a tcp_info structure to the MP3Client
//   that can later be passed to TCPSend/Receive.
struct tcp_info* TCPConnect(int sockfd,  struct sockaddr_in * servaddr){

}

// Replaces all instances of "recvfrom" in your MP3Client.
// UNIQUE PARAMETERS:
//  appdata: pointer to the buffer where the application data in the packet
//           will be stored (just like recvfrom()).  TCP header info is stripped
//           from the packet before it is returned.
//  connection_info: structure that contains info about current connection
int TCPReceive(int sockfd, char *appdata, int appdata_length, struct sockaddr_in *addr,
               struct tcp_info *connection_info){

}

// Replaces all instances of "sendto" in your MP3Client.
// UNIQUE PARAMETERS:
//  appdata: pointer to the buffer that contains the application data the
//           MP3Client is trying to send.  TCP header information is added to
//           the beginning of this data before it is sent.
//  connection_info: structure that contains info about current connection
int TCPSend(int sockfd, char* appdata, int appdata_length, struct sockaddr_in * addr, struct tcp_info *connection_info){

}
