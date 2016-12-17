/*  ASS 2 
 *
 *	 Coded by Shen139	31-7-2005
 *	  shen139(_at_) eviltime(.dot.) com
 *
 *	$ gcc ASS2.c -o ASS2
 *	$ ./ASS2
 */

/*
Dump of assembler code for function shencode:
0x08049560 <shencode+0>:        xor    %ecx,%ecx
0x08049562 <shencode+2>:        jmp    0x8049566 <shencode+6>
0x08049564 <shencode+4>:        jmp    0x804956b <shencode+11>
0x08049566 <shencode+6>:        call   0x8049564 <shencode+4>
0x0804956b <shencode+11>:       pop    %eax
0x0804956c <shencode+12>:       add    $0xe,%eax
0x0804956f <shencode+15>:       xorb   $0x2,(%eax)
0x08049572 <shencode+18>:       inc    %eax
0x08049573 <shencode+19>:       inc    %ecx
0x08049574 <shencode+20>:       cmp    $0x37,%ecx
0x08049577 <shencode+23>:       jne    0x804956f <shencode+15>
0x08049579 <shencode+25>:       xor    %edx,%eax
0x0804957b <shencode+27>:       xor    %ecx,%ebx
0x0804957d <shencode+29>:       xor    %ebx,%ecx
0x0804957f <shencode+31>:       xor    %eax,%edx
0x08049581 <shencode+33>:       push   %edx
0x08049582 <shencode+34>:       push   $0x612c6a08
0x08049587 <shencode+39>:       insl   (%dx),%es:(%edi)
0x08049588 <shencode+40>:       outsl  %ds:(%esi),(%dx)
0x08049589 <shencode+41>:       push   $0x76
0x0804958b <shencode+43>:       imul   $0x6a,0x67(%edi),%ebp
0x0804958f <shencode+47>:       addr16 je 0x80495fd
0x08049592 <shencode+50>:       outsb  %ds:(%esi),(%dx)
0x08049593 <shencode+51>:       push   $0x33
0x08049595 <shencode+53>:       xor    %edi,(%ebx)
0x08049597 <shencode+55>:       inc    %edx
0x08049598 <shencode+56>:       push   $0x71
0x0804959a <shencode+58>:       push   $0x67
0x0804959c <shencode+60>:       insb   (%dx),%es:(%edi)
0x0804959d <shencode+61>:       mov    %ebx,%esp
0x0804959f <shencode+63>:       mov    $0x17,%al
0x080495a1 <shencode+65>:       mov    $0x6,%dl
0x080495a3 <shencode+67>:       iret
0x080495a4 <shencode+68>:       (bad)
0x080495a5 <shencode+69>:       xor    %edx,%eax
0x080495a7 <shencode+71>:       xor    %ecx,%ebx
0x080495a9 <shencode+73>:       mov    $0x3,%dl
0x080495ab <shencode+75>:       iret
0x080495ac <shencode+76>:       (bad)
0x080495ad <shencode+77>:       rcll   $0x0,0x92(%edx)

****************************: after decryption :****************************
    
Dump of assembler code for function shencode:
0x08049560 <shencode+0>:        xor    %ecx,%ecx
0x08049562 <shencode+2>:        jmp    0x8049566 <shencode+6>
0x08049564 <shencode+4>:        jmp    0x804956b <shencode+11>
0x08049566 <shencode+6>:        call   0x8049564 <shencode+4>
0x0804956b <shencode+11>:       pop    %eax
0x0804956c <shencode+12>:       add    $0xe,%eax
0x0804956f <shencode+15>:       xorb   $0x2,(%eax)
0x08049572 <shencode+18>:       inc    %eax
0x08049573 <shencode+19>:       inc    %ecx
0x08049574 <shencode+20>:       cmp    $0x37,%ecx
0x08049577 <shencode+23>:       jne    0x804956f <shencode+15>
0x08049579 <shencode+25>:       xor    %eax,%eax
0x0804957b <shencode+27>:       xor    %ebx,%ebx
0x0804957d <shencode+29>:       xor    %ecx,%ecx
0x0804957f <shencode+31>:       xor    %edx,%edx
0x08049581 <shencode+33>:       push   %eax
0x08049582 <shencode+34>:       push   $0xa
0x08049584 <shencode+36>:       push   $0x6d6f632e
0x08049589 <shencode+41>:       push   $0x656d6974
0x0804958e <shencode+46>:       push   $0x6c697665
0x08049593 <shencode+51>:       push   $0x40393331
0x08049598 <shencode+56>:       push   $0x6e656873
0x0804959d <shencode+61>:       mov    %esp,%ecx
0x0804959f <shencode+63>:       mov    $0x15,%dl
0x080495a1 <shencode+65>:       mov    $0x4,%al
0x080495a3 <shencode+67>:       int    $0x80
0x080495a5 <shencode+69>:       xor    %eax,%eax
0x080495a7 <shencode+71>:       xor    %ebx,%ebx
0x080495a9 <shencode+73>:       mov    $0x1,%al
0x080495ab <shencode+75>:       int    $0x80
0x080495ad <shencode+77>:       ret
0x080495ae <shencode+78>:       nop
0x080495af <shencode+79>:       nop

*/

char shencode[]="\x33\xC9\xEB\x02\xEB\x05\xE8\xF9\xFF\xFF\xFF\x58\x83\xC0\x0E"
                "\x80\x30\x02\x40\x41\x83\xF9\x37\x75\xF6\x33\xC2\x33\xD9\x33"
                "\xCB\x33\xD0\x52\x68\x08\x6A\x2C\x61\x6D\x6F\x6A\x76\x6B\x6F"
                "\x67\x6A\x67\x74\x6B\x6E\x6A\x33\x31\x3B\x42\x6A\x71\x6A\x67"
                "\x6C\x8B\xE3\xB0\x17\xB2\x6\xCF\x82\x33\xC2\x33\xD9\xB2\x3"
                "\xCF\x82\xC1\x92\x92";

int main(void)
{
void (*funct) ();

	(long)funct = shencode;
	funct();

return 1;
}

/*EOF*/

