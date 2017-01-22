//Version coded by Shen139 && Traktopel
//shen139(at)libero(dot)it
//traktopel(at)everyday(dot)com
//Yet Another IIS Security Scanner 

#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <windows.h>

#define NVULNSTR	250
#define PORT		80

char vulnstr[NVULNSTR][200];
int iNumVulns=0,i,bCreateLog=0,bUseProxy=0,ProxyArg,FLogArg;
char VulnTMP[200];
int numc=100;

int LoadVulns(),usage(),StartUpWinsock(),LoadSocket();

FILE *fVulns,*fLog;

SOCKET sock;

SOCKADDR_IN saddr;

struct hostent *hp;

int main(int argc, char *argv[]) {
char text[1500],buffer[15];

if (argc!=2 && argc!=4 && argc!=5 && argc!=7) {
	usage();
	return(0);
}

if(argc==7)
{
	if (strcmp(argv[2],"-p")==0 || strcmp(argv[4],"-p")==0)
		bUseProxy=1;

	if (strcmp(argv[2],"-l")==0 || strcmp(argv[5],"-l")==0)
		bCreateLog=1;
}

if(argc==4 && strcmp(argv[2],"-l")==0)
	bCreateLog=1;

if(argc==5 && strcmp(argv[2],"-p")==0)
	bUseProxy=1;


if (bCreateLog)
{
	printf("Creating Logfile");
	if (strcmp(argv[2],"-l")==0)
		FLogArg=2;
	else
		FLogArg=5;

	if((fLog=fopen(argv[FLogArg+1],"w"))==NULL)
	{
		printf("\t\t\t [ERROR ]\n Unable to create file:%s\n",argv[2]);
		getchar();
		return 0;
	}
fprintf(fLog,"IIS scanner by Shen139\n");
printf("\t\t [  OK  ]\n%s created\n",argv[2]);
}

if(!LoadVulns()) return 0;

if(!StartUpWinsock()) return 0;

if(!LoadSocket()) return 0;

printf("GetHostByName");
if(bUseProxy)
{	

	if (strcmp(argv[2],"-p")==0)
		ProxyArg=2;
	else
		ProxyArg=5;
	
	hp=gethostbyname(argv[ProxyArg+1]);
}
else
	hp=gethostbyname(argv[1]);

if(hp==0) {
	printf("\t\t\t [ERROR ]\n");
	
	if (bCreateLog)
	{
		fprintf(fLog,"Gethostbyname error\n");
		fclose(fLog);
	}

	getchar();
	return(1);
}
printf("\t\t\t [  OK  ]\n");

saddr.sin_addr.s_addr=((struct in_addr *)(hp->h_addr))->s_addr;
saddr.sin_family = AF_INET;

if(bUseProxy)
	saddr.sin_port = htons(atoi(argv[ProxyArg+2]));
else
	saddr.sin_port = htons(PORT);


printf("Connecting...");
if (connect(sock, (LPSOCKADDR) &saddr, sizeof(saddr)) == 0)
	{
		printf("\t\t\t [ERROR ]\n");

		if (bCreateLog)
		{
			fprintf(fLog,"Connecting error\n");
			fclose(fLog);
		}

		getchar();
		return(1);
	}
	printf("\t\t\t [  OK  ]\n");
	printf("-Server response at GET / HTTP/1.1:\n----------[\n");
	text[0]='\0';
	send(sock,"GET / HTTP/1.1\r\n\r\n",18,0);
	recv(sock,text,68,0);
	buffer[68]='\0';
	printf("%s\n...\n]----------\n\n",text);
	if (bCreateLog)
		fprintf(fLog,"Server's response at GET / HTTP/1.1:\n----------[\n%s\n...\n]----------\n",text);
	

printf("-Trying...\n");
for(i=0;i<iNumVulns;i++) {
	closesocket(sock);
	sock=socket(AF_INET,SOCK_STREAM,0);
	if (connect(sock, (LPSOCKADDR) &saddr, sizeof(saddr)) != SOCKET_ERROR)
	{
		if(bUseProxy)
			sprintf(text,"GET http://%s%s  HTTP/1.0\r\n\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows 98; Win 9x 4.90)\r\nHost: %s\r\nProxy-Connection: Keep-Alive\r\n\r\n",argv[1],vulnstr[i],argv[1]);
		else
			sprintf(text,"GET %s  HTTP/1.0\n\n",vulnstr[i]);
		
		send(sock,text,strlen(text),0);
		recv(sock,buffer,sizeof(buffer),0);
		
		buffer[11]='\0';
		
		
		if( strcmp(buffer,"HTTP/1.1 40")!=0 && 
			strcmp(buffer,"HTTP/1.0 50")!=0 )
		{
			printf("\nVulns found(%i): %s%s",i,argv[1],vulnstr[i]);
	
			if (bCreateLog)
				fprintf(fLog,"Vulns found: %s%s",argv[1],vulnstr[i]);
		}

		closesocket(sock);
	} else {
		printf("\nConnecting error");
		getchar();
		return(1);
	}
	
}


if (bCreateLog)
{
	fprintf(fLog,"\nScan Finished\n");
	fclose(fLog);
	printf("Closing Logfile\n");
}

printf("\nScan Finished\n");
printf("Closing socket...\n");
closesocket(sock);
WSACleanup();
printf("\n\nThanks by Hacklab Crew\n");
getchar();
return(1);
}

int usage() {

	printf("************************BETA VERSION*************************\n");
	printf("*             Yet Another IIS Security Scanner              *\n");
	printf("*               Writed by Shen139 & Traktopel               *\n");
	printf("*************************************************************\n\n\n");
	printf("*************************************************************\n");
	printf("*                                                           *\n");
	printf("* Usage: skan139 www.hostname.com(-p PROXY port -l Logfile) *\n");
	printf("*                                                           *\n");
	printf("*************************************************************\n");
    getchar();
	return(0);

}


int LoadVulns()
{

	printf("Loading vulns");
	if((fVulns=fopen("vulns.txt","r"))==NULL)
	{
		printf("\t\t\t [ERROR ]\n Unable to open the file vulns.txt\n");
		getchar();
		return 0;
	}
	while(!feof(fVulns) && iNumVulns<=NVULNSTR)
	{
		if(fgets(VulnTMP,200,fVulns)!=NULL)  //100 Maximum number of characters to read
		{
			strcpy(vulnstr[iNumVulns],VulnTMP);
			vulnstr[iNumVulns][strlen(vulnstr[iNumVulns])-1]='\0';
			iNumVulns++;
		}
	}	
	fclose(fVulns);
	printf("\t\t\t [  OK  ]\nVulns loaded: %i\n",iNumVulns);
	if (bCreateLog)
		fprintf(fLog,"Vulns loaded: %i\n",iNumVulns);
	return 1;
}

int StartUpWinsock()
{
//4winzoz
WSADATA wsadata;

	printf("WSAStartup");
	if((WSAStartup(MAKEWORD(1,1),&wsadata))!=0 || (LOBYTE(wsadata.wVersion )!=1 || HIBYTE(wsadata.wVersion)!=1))
	{

		printf("\t\t\t [ERROR ]\n");
		
		if (bCreateLog)
		{
			fprintf(fLog,"WSAStartup error\n");
			fclose(fLog);
		}
		getchar();
		return 0;
	}
	printf("\t\t\t [  OK  ]\n");
	return 1;
}

int LoadSocket()
{
	printf("Loading socket");
	sock=socket(AF_INET,SOCK_STREAM,0);

	if (sock==INVALID_SOCKET) {
		
		printf("\t\t\t [ERROR ]\n");

		if (bCreateLog)
		{
			fprintf(fLog,"Socket error\n");
			fclose(fLog);
		}

		getchar();
		return 0;
	}
	printf("\t\t\t [  OK  ]\n");
	return 1;
}


