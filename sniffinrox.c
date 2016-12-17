
/* Sniffinrox
 *  Kernel Space Sniffer
 *
 *  Coded by Evil && Shen139
 *   shen139 (at) eviltime [dot] com
 *   webmaster (at) eviltime [dot] com
 *
 * Compile with: gcc -I/usr/src/linux/include/ -O6 -c sniffinrox.c
 */

#define __KERNEL__
#define MODULE

#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>

#include <linux/skbuff.h>
#include <linux/ctype.h>
#include <linux/netdevice.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <linux/igmp.h>
#include <linux/tcp.h>
#include <linux/udp.h>

void sniff_icmp(struct sk_buff *snbuff);
void sniff_tcp (struct sk_buff *snbuff);
void sniff_udp (struct sk_buff *snbuff);
void sniff_igmp(struct sk_buff *snbuff);

struct packet_type our_packet;

/* HihihihihihI */
char* in_ntoa(__u32 in)
{
static char buff[18];
char *p;

	p=(char*) &in;
	sprintf(buff,"%d.%d.%d.%d", (p[0] & 255), (p[1] & 255), (p[2] & 255), (p[3] & 255));

return buff;
}

int sniffer(struct sk_buff *snbuff, struct device *dev, struct packet_type *pkt)
{
	snbuff->h.raw = snbuff->nh.raw + snbuff->nh.iph->ihl*4;
	snbuff->data = (unsigned char *)snbuff->h.raw +(snbuff->h.th->doff <<2);
	snbuff->len -= snbuff->nh.iph->ihl*4 + (snbuff->h.th->doff << 2);

	if (snbuff->pkt_type!=PACKET_HOST)
	{
		kfree(snbuff);
	return(0);
	}

	switch(snbuff->nh.iph->protocol)
	{
	case IPPROTO_ICMP:
		printk("ICMP packet\n");
		sniff_icmp(snbuff);
		break;
	case IPPROTO_IGMP:
		printk("IGMP packet\n");
		sniff_igmp(snbuff);
		break;
	case IPPROTO_TCP:
		printk("TCP packet\n");
		sniff_tcp(snbuff);
		break;
	case IPPROTO_UDP:
		printk("UDP packet\n");
		sniff_udp(snbuff);
		break;
	}
	kfree(snbuff);
return 1;
}

void sniff_icmp(struct sk_buff *snbuff)
{
	printk("source IP         = %s\n", in_ntoa(snbuff->nh.iph->saddr));
	printk("Destination IP    = %s\n", in_ntoa(snbuff->nh.iph->daddr));
	printk("ICMP type         = %X\n", snbuff->h.icmph->type);
	printk("ICMP code         = %X\n", snbuff->h.icmph->code);
	printk("----------------------------\n");
}

void sniff_tcp(struct sk_buff *snbuff)
{
	printk("Source IP         = %s\n", in_ntoa(snbuff->nh.iph->saddr));
	printk("Destination IP    = %s\n", in_ntoa(snbuff->nh.iph->daddr));
	printk("TCP source port   = %i\n", htons(snbuff->h.th->source));
	printk("TCP dest port     = %i\n", htons(snbuff->h.th->dest));
	printk("TCP seq           = %X\n", snbuff->h.th->seq);
	printk("TCP ack_seq       = %X\n", snbuff->h.th->ack_seq);
	if(snbuff->h.th->syn==1)
		printk("TCP flag(syn)     = ON\n");
	if(snbuff->h.th->ack==1)
		printk("TCP flag(ack)     = ON\n");
	if(snbuff->h.th->rst==1)
		printk("TCP flag(rst)     = ON\n");
	if(snbuff->h.th->fin==1)
		printk("TCP flag(fin)     = ON\n");
	if(snbuff->h.th->psh==1)
		printk("TCP flag(psh)     = ON\n");
	if(snbuff->h.th->urg==1)
		printk("TCP flag(urg)     = ON\n");
	printk("----------------------------\n");
}

void sniff_udp(struct sk_buff *snbuff)
{
	printk("Source IP         = %s\n", in_ntoa(snbuff->nh.iph->saddr));
	printk("Destination IP    = %s\n", in_ntoa(snbuff->nh.iph->daddr));
	printk("UDP source port   = %i\n", htons(snbuff->h.uh->source));
	printk("UDP dest port     = %i\n", htons(snbuff->h.uh->dest));
	printk("----------------------------\n");
}

void sniff_igmp(struct sk_buff *snbuff)
{
	printk("Source IP         = %s\n", in_ntoa(snbuff->nh.iph->saddr));
	printk("Destination IP    = %s\n", in_ntoa(snbuff->nh.iph->daddr));
	printk("IGMP type         = %X\n", snbuff->h.igmph->type);
	printk("IGMP code         = %X\n", snbuff->h.igmph->code);
	printk("----------------------------\n");
}

void cleanup_module()
{
	dev_remove_pack(&our_packet);
	printk("Bye\n\n");
}

int init_module()
{
	our_packet.type=htons(ETH_P_ALL);
	our_packet.func=sniffer;
	dev_add_pack(&our_packet);
return(0);
}

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR ("Evil && Shen139 :)");
MODULE_DESCRIPTION("Sniffer in kernel space");

/*EOF*/

