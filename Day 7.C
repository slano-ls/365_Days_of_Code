//      $$$$$$\   $$$$$$\  $$$$$$$\      $$$$$$$\                                               $$$$$$\       $$$$$$\                  $$\
//     $$ ___$$\ $$  __$$\ $$  ____|     $$  __$$\                                             $$  __$$\     $$  __$$\                 $$ |
//     \_/   $$ |$$ /  \__|$$ |          $$ |  $$ | $$$$$$\  $$\   $$\  $$$$$$$\      $$$$$$\  $$ /  \__|    $$ /  \__| $$$$$$\   $$$$$$$ | $$$$$$\
//        $$$$$ / $$$$$$$\  $$$$$$$\     $$ |  $$ | \____$$\ $$ |  $$ |$$  _____|    $$  __$$\ $$$$\         $$ |      $$  __$$\ $$  __$$ |$$  __$$\
//       \___$$\ $$  __$$\ \_____$$\     $$ |  $$ | $$$$$$$ |$$ |  $$ |\$$$$$$\      $$ /  $$ |$$  _|        $$ |      $$ /  $$ |$$ /  $$ |$$$$$$$$ |
//     $$\   $$ |$$ /  $$ |$$\   $$      $$ |  $$ |$$  __$$ |$$ |  $$ | \____$$\     $$ |  $$ |$$ |          $$ |  $$\ $$ |  $$ |$$ |  $$ |$$   ____|
//     \$$$$$$  | $$$$$$  |\$$$$$$  |    $$$$$$$  |\$$$$$$$ |\$$$$$$$ |$$$$$$$  |    \$$$$$$  |$$ |          \$$$$$$  |\$$$$$$  |\$$$$$$$ |\$$$$$$$\
//      \______/  \______/  \______/     \_______/  \_______| \____$$ |\_______/      \______/ \__|           \______/  \______/  \_______| \_______|
//                                                             $$\   $$ |
//                                                             \$$$$$$  |
//                                                              \______/
// Author : Saihaj Law
// Date : January 7th
// Project : Ping Utility in C
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <ip address>\n", argv[0]);
        return 1;
    }

    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Create the ICMP header and message
    char sendbuf[1024];
    memset(sendbuf, 0, sizeof(sendbuf));
    struct icmphdr *icmp = (struct icmphdr *) sendbuf;
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.sequence = 1;
    icmp->un.echo.id = getpid();
    icmp->checksum = 0;
    icmp->checksum = in_cksum((unsigned short *)icmp, sizeof(sendbuf));

    // Send the message to the destination
    int bytes_sent;
    if ((bytes_sent = sendto(sockfd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr))) < 0) {
        perror("sendto");
        return 1;
    }

    // Receive a response from the destination
    char recvbuf[1024];
    memset(recvbuf, 0, sizeof(recvbuf));
    struct sockaddr_in src_addr;
    memset(&src_addr, 0, sizeof(src_addr));
    socklen_t src_addr_len = sizeof(struct sockaddr_in);
    int bytes_recvd;
    if ((bytes_recvd = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&src_addr, &src_addr_len)) < 0) {
        perror("recvfrom");
        return 1;
    }

    // Check the response to see if it is an ICMP "echo reply" message
    char *recv_icmp_ptr = recvbuf + sizeof(struct iphdr);
    struct icmphdr *recv_icmp = (struct icmphdr *) recv_icmp_ptr;
    if (recv_icmp->type == ICMP_ECHOREPLY) {
        printf("Destination reached!\n");
    } else {
        printf("Error: Destination unreachable!\n");
    }

    close(sockfd);

    return 0;
}

// Function to compute the checksum for the ICMP header
unsigned short in_cksum(unsigned short *addr, int len)
{
    int nleft = len;
    int sum = 0;
    unsigned short *w = addr;
    unsigned short answer = 0;

    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    if (nleft == 1) {
        *(unsigned char *)(&answer) = *(unsigned char *)w;
        sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;

    return answer;
}
