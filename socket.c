/* $Id: socket.c 1.1 1995/01/01 07:11:14 cthuang Exp $
 *
 * This module has been modified by Radim Kolar for OS/2 emx
 */

/***********************************************************************
  module:       socket.c
  program:      popclient
  SCCS ID:      @(#)socket.c    1.5  4/1/94
  programmer:   Virginia Tech Computing Center
  compiler:     DEC RISC C compiler (Ultrix 4.1)
  environment:  DEC Ultrix 4.3 
  description:  UNIX sockets code.
 ***********************************************************************/
 
#include <sys/types.h> //type.h - for
#include <sys/socket.h>//socket.h - for
#include <fcntl.h>     //fcntl.h - for
#include <netinet/in.h>//netinet/in.h - for
#include <arpa/inet.h> //arpa/inet.h - for
#include <netdb.h>     //netdb.h - for
#include <sys/time.h>  //time.h - for
#include <string.h>    //string.h - for
#include <unistd.h>    //unistd.h - for
#include <stdio.h>     //stdio.h - for
#include <stdlib.h>    //stdlib.h - for
#include <stdarg.h>    //stdarg.h - for

/*
 * function des: build the socket connection with host and Port
 * parameters: host - net addr, clientPort - port number of client
 * return: socket or -1 when connection failed
 * date: 2015.09.11
 * writer: jinxingbay@163.com
*/
int Socket(const char *host, int clientPort)
{
    int sock;
    unsigned long inaddr;
    struct sockaddr_in ad;
    struct hostent *hp;
    
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;

    inaddr = inet_addr(host); //tranlate the dotParase ip to <unsigned long> type
    if (inaddr != INADDR_NONE) //host translate success 
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    else //host is domain name, getHostByName
    {
        hp = gethostbyname(host);//get host of the domain name
        if (hp == NULL) //cannot get the ip
            return -1; //connection failed
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    ad.sin_port = htons(clientPort);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
        return -1;
    return sock;
}

