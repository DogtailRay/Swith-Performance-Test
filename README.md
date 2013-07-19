Swith-Performance-Test
======================
We will test various protocols in this test, including IPv4 protocol, TCP protocol, etc. 
ethernet_sender.c: it is used to generate a link layer packet and we will use it to test the performance of L2 switch.

To run pkt_sender.c, you need to: 1) type: gcc pkt_sender.c -o sender -lnet
                                  2) type: sudo ./sender
