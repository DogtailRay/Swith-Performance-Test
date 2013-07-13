#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include "ethernet_sender.h"

sender_p* pkt_sender_init(char* iface, unsigned char dst[MAC_LEN], unsigned char src[MAC_LEN])
{
    sender_p* sender = malloc(sizeof(sender_p));
    char err_buff[LIBNET_ERRBUF_SIZE];
    sender->l = libnet_init(LIBNET_LINK, iface, err_buff);//iface denotes the device we used to send the packets
    if (sender->l == NULL) {
        printf("libnet init err!\n");
        fprintf(stderr, "%s", err_buff);
        return NULL;
    }
    memcpy(sender->dst_mac, dst, MAC_LEN);
    memcpy(sender->src_mac, src, MAC_LEN);
    sender->p_tag = 0;
    sender->proto = ETHERTYPE_IP;//use IPv4 protocol
    return sender;
}

void pkt_sender_close(sender_p* sender)
{
    libnet_destroy(sender->l);
    free(sender);
}

int pkt_sender_send(sender_p* sender, char* data)
{
    unsigned data_len = sizeof(data);//data_len varies between 46 and 1500
    //set up the payload of the packet
    memset(data_p, 0, data_len); 
    memcpy(data_p, data, data_len);

    free(data);
    return 1;
}
 
int pkt_sender_send_out(sender_p* sender, char* data)
{
    unsigned data_len = sizeof(data);//data_len varies between 46 and 1500
    sender->p_tag = libnet_build_ethernet(sender->dst_mac, sender->src_mac, sender->proto,
            data, data_len, sender->l, sender->p_tag);
    // Send the packet
    if (sender->p_tag == -1)
    {
        sender->p_tag = 0;
        printf("libnet_build_ethernet err!\n");
        return -1;
    }

    if (libnet_write(sender->l) == -1) 
    {
        printf("libnet_write err!\n");
    } 
    else 
    {
        //printf("libnet_write succeeded!\n");
    }

    return 0;
}

int main()
{
    char* iface;// We need to specify the device which send the packets
    unsigned char dst[MAC_LEN];//We will specify sender mac address and receiver mac address manually for the first stage.Later we may run the arp protocol and we will not need to specify the mac address.[But then we need to specify ip address instead] 
    unsigned char src[MAC_LEN];
    sender_p* sender;
    sender = pkt_sender_init(iface, dst[MAC_LEN], src[MAC_LEN]);
    char* data;
    int len;//Length of data that varies from 46 to 1500. We will manually decide the distribution of it.
    //We will manually decide the distribution of len here.
    for(len = DATA_MIN_LEN; len ++; len <= DATA_MAX_LEN)
    {
        memset(data, 'k', len);//We will send 'k' to destinition hosts
        pkt_sender_send(sender, data);
    } 
    pkt_sender_close(sender);
}
