/*

	Network Stresser (Linux)

	Copyright 2003 Shen139 <shen139(at)eviltime(dot)com>

*/

struct psd_udp {
	struct in_addr src;
	struct in_addr dst;
	unsigned char pad;
	unsigned char proto;
	unsigned short udp_len;
	struct udphdr udp;
};

struct psd_tcp {
	struct in_addr src;
	struct in_addr dst;
	unsigned char pad;
	unsigned char proto;
	unsigned short tcp_len;
	struct tcphdr tcp;
};

unsigned short in_cksum(unsigned short *addr,int len)
{
register int sum = 0;
u_short answer = 0;
register u_short *w = addr;
register int nleft = len;

	while (nleft > 1) 
	{
		sum += *w++;
		nleft -= 2;
	}
	
	if (nleft == 1) 
	{
		*( u_char * )( &answer ) = *( u_char * )w ;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

return answer;
}

static inline unsigned short ip_fast_csum(unsigned char * iph, unsigned int ihl) 
{
unsigned int sum;

	__asm__ __volatile__(
	    "movl (%1), %0\n"
	    "subl $4, %2\n"
	    "jbe 2f\n"
	    "addl 4(%1), %0\n"
	    "adcl 8(%1), %0\n"
	    "adcl 12(%1), %0\n"
"1:	     adcl 16(%1), %0\n"
	    "lea 4(%1), %1\n"
	    "decl %2\n"
	    "jne	1b\n"
	    "adcl $0, %0\n"
	    "movl %0, %2\n"
	    "shrl $16, %0\n"
	    "addw %w2, %w0\n"
	    "adcl $0, %0\n"
	    "notl %0\n"
"2:\n"
	    
	/* Since the input registers which are loaded with iph and ipl
	   are modified, we must also specify them as outputs, or gcc
	   will assume they contain their original values. */
	: "=r" (sum), "=r" (iph), "=r" (ihl)
	: "1" (iph), "2" (ihl));

return(sum);
}
