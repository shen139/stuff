/* 

  Advanced Shen139' Shellcode (TesT01)
	 Coded by Shen139	10/5/2004 - 14:10
	  shen139(at)eviltime(dot)com

	$ gcc shllcdadv.c -o shllcdadv -O6
	$ ./shllcdadv 
*/

char shellcode[]=	"SHEN\x5b\x40\x4d\x46\x68\x02\xce\x81\xc4\x68\xc1\x32"
					"\xdc\xb1\x68\x05\xce\x81\x32\x68\xe2\xb3\x16\xb1\x68\x69\x66\x6f"
					"\x8a\x68\x3a\x41\x69\x74\x68\x6d\x69\x32\x34\x68\x69\x66\x77\x6a"
					"\x68\x75\x6a\x6e\x66\x68\x64\x70\x6e\x69\x68\x6b\x0b\x69\x2f\x68"
					"\xca\x32\xd3\x51\x68\x91\x32\xdc\x32\x31\xc9\x89\xe3\x80\x2b\x01"
					"\x83\xc3\x01\x83\xc1\x01\x83\xf9\x35\x75\xf2\x54\xc3";

/*	write.s
0x8049460 <main>:       xor    %eax,%eax
0x8049462 <main+2>:     xor    %ebx,%ebx
0x8049464 <main+4>:     xor    %ecx,%ecx
0x8049466 <main+6>:     xor    %edx,%edx
0x8049468 <main+8>:     push   %eax
0x8049469 <main+9>:     push   $0xa
0x804946b <main+11>:    push   $0x6d6f632e
0x8049470 <main+16>:    push   $0x656d6974
0x8049475 <main+21>:    push   $0x6c697665
0x804947a <main+26>:    push   $0x40393331
0x804947f <main+31>:    push   $0x6e656873
0x8049484 <main+36>:    mov    %esp,%ecx
0x8049486 <main+38>:    mov    $0x15,%dl
0x8049488 <main+40>:    mov    $0x4,%al
0x804948a <main+42>:    int    $0x80
0x804948c <main+44>:    xor    %eax,%eax
0x804948e <main+46>:    xor    %ebx,%ebx
0x8049490 <main+48>:    mov    $0x1,%al
0x8049492 <main+50>:    int    $0x80
0x8049494 <main+52>:    ret
*/

int main(void)
{
void (*funct) ();

	(long)funct = shellcode;
	funct();

/*
	__asm__ __volatile__
	("	push	%ebx			\n"			//S
	"	dec		%eax			\n"			//H
	"	inc		%ebp			\n"			//E
	"	dec		%esi			\n"			//N
	"	pop		%ebx			\n"
	"	inc		%eax			\n"
	"	dec		%ebp			\n"
	"	inc		%esi			\n"
	"	push	$0xc481ce02		\n"			//Puts into the stack the write.s' shellcode
	"	push	$0xb1dc32c1		\n"			//inverted and with each opcodes plus 1
	"	push	$0x3281ce05		\n"
	"	push	$0xb116b3e2		\n"
	"	push	$0x8A6f6669		\n"
	"	push	$0x7469413a		\n"
	"	push	$0x3432696d		\n"
	"	push	$0x6a776669		\n"
	"	push	$0x666e6a75		\n"
	"	push	$0x696e7064		\n"
	"	push	$0x2f690b6b		\n"
	"	push	$0x51d332ca		\n"
	"	push	$0x32dc3291		\n"
	"	xor		%ecx,%ecx		\n"			//Restore the opcodes in the stack (opcode less 1)
	"	mov		%esp,%ebx		\n"
	"	subb	$0x1,(%ebx)		\n"
	"	add		$0x1,%ebx		\n"
	"	add		$0x1,%ecx		\n"
	"	cmp		$0x35,%ecx		\n"
	"	jne		label			\n"			//Push in the stack esp
	"	push	%esp			\n"			//"call esp"
	"	ret						\n");
*/
	
return 1;
}

/*EOF*/
