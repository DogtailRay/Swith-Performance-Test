#ifndef _ETHERNET_SENDER_H_
#define _ETHERNET_SENDER_H_

#define MAC_LEN 6
#define DATA_MIN_LEN 46
#define DATA_MAX_LEN 1500
#define PROTO 0x0800 //IPv4 protocol

//Now we will specify the NIC MAC address on 10.10.0.201
#define MAC_1 60:de:44:75:14:46(eth0)
#define MAC_2 60:de:44:75:14:48(eth2)
#define MAC_3 60:de:44:75:14:49(eth3)
#define MAC_4 10:47:80:01:69:C8(eth4)

//Sender packet struct
typedef struct pkt_sender
{
char* device;//use different NICs within a single machine to send/receive packets
unsigned char dst_mac[MAC_LEN];
unsigned char src_mac[MAC_LEN];
unsigned short proto;
libnet_t *l;
libnet_ptag_t p_tag;
}sender_p;

//functions
sender_p* pkt_sender_init(char* iface, unsigned char dst[MAC_LEN], unsigned char src[MAC_LEN]);
int pkt_sender_send(sender_p* sender, char* data);
void pkt_sender_close(sender_p* sender);
int pkt_sender_send_out(sender_p* sender, char* data);


#endif
