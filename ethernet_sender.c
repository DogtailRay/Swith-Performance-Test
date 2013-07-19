#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnet.h>
#include "pkt_sender.h"

sender_p* pkt_sender_init(char* iface)
{
    unsigned char dst[MAC_LEN] = {0x60,0xde,0x44,0x75,0x14,0x49};//We will specify sender mac address and receiver mac address     manually for the first stage.Later we may run the arp protocol     and we will not need to specify the mac address.[But then we n    eed to specify ip address instead  
    unsigned char src[MAC_LEN] = {0x60,0xde,0x44,0x75,0x14,0x2e};
    sender_p* sender = malloc(sizeof(sender_p));
    char err_buff[LIBNET_ERRBUF_SIZE];
    sender->l = libnet_init(LIBNET_LINK_ADV, iface, err_buff);//iface denotes the device we used to send the packets, such as 'etho', etc.
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

int pkt_sender_send_out(sender_p* sender, char* data)
{
    unsigned data_len = sizeof(data);//data_len varies between 46 and 1500
    sender->p_tag = libnet_build_ethernet(sender->dst_mac, sender->src_mac, sender->proto,data, data_len, sender->l, sender->p_tag);
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
        printf("libnet_write succeeded!\n");
    }

    return 0;
}

int main()
{
    char* iface="eth0";// We need to specify the device which send the packets
    //unsigned char dst[MAC_LEN] = {0x60,0xde,0x44,0x75,0x14,0x3a};//We will specify sender mac address and receiver mac address manually for the first stage.Later we may run the arp protocol and we will not need to specify the mac address.[But then we need to specify ip address instead    
    //unsigned char src[MAC_LEN] = {0x10,0x47,0x80,0x01,0x69,0xd8};
    int step;//when data size varies, "step" sets the step size
    sender_p* sender;
    sender = pkt_sender_init(iface);
    char* data;
    int len;//Length of data that varies from 46 to 1500. We will manually decide the distribution of it.
    //We will manually decide the distribution of len here.


    //Now the variables below need to be specified manually.

    //MAC_1 = {0x60,0xde,0x44,0x75,0x14,0x46};
    //MAC_2 = {0x60,0xde,0x44,0x75,0x14,0x48};    

    //src = MAC_1;
    //dst = MAC_2;
    step = 2;
    printf("bbbbbbbbb\n");
    while(1)
    {
      len = 1024;
      //for(len = DATA_MIN_LEN; len ++; len <= DATA_MAX_LEN)
      //{
          printf("come on, baby! %d       ",len);
          memset(data, 'k', len);//We will send 'k' to destinition hosts
         // print("%s",data);
          printf("aaaaaaaaaaaa\n");
          pkt_sender_send_out(sender, data
                //}
      printf("Success!\n");
      //sleep(1);
    }
    pkt_sender_close(sender);
}



