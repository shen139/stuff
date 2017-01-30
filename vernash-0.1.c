/*
 * Vernash v0.1
 * Coded by Shen139  07-02-2006
 *    shen139 (at_) eviltime [.dot.] com
 *
 * Stream cipher based on the Vernam cipher and Variable-Length Hashes
 *
 *
 * Compile with: $ gcc vernash.c -o vernash
 *
 *
 * Usage for encrypting a text:  ./vernash <text> <password>
 *  or
 * Usage for decrypting a text:  ./vernash -d <text> <password>
 *  or
 * Usage for generating an Hash: ./vernash -g <text> <length>
 *
 *
 * Usage examples:
 *  
 * (Encrypt "1234567890987654321" with password "abc")
$ ./vernash 1234567890987654321 abc

Text:           ---1234567890987654321---
Password:       ---abc---

Encrypted-Text: ---2;D>>:OKE>AI=K@79>F---
 *
 * (DeCrypt "2;D>>:OKE>AI=K@79>F" with password "abc")
$ ./vernash -d "2;D>>:OKE>AI=K@79>F" abc

Text:           ---2;D>>:OKE>AI=K@79>F---
Password:       ---abc---

Decrypted-Text: ---1234567890987654321---
 *
 * (Generate an hash of 50 bytes for "a")
$ ./vernash -g a 50

Hash(50) for ---a---:
---tmqiyiburudwvokwyhdwwuskwmrylcetzivzaaiubpzpqhnwce---
 *
 * (Generate an hash of 50 bytes for "aa")
$ ./vernash -g aa 50

Hash(50) for ---aa---:
---wvblxzhpqevedbbwumlaxlywvnrvtfnovijwpnzuzhirmlxztx---
 *
 * (Generate an hash of 30 bytes for "test123456789")
$ ./vernash -g test123456789 30

Hash(30) for ---test123456789---:
---xtjslsxkkokdlynprivlkjyqsughhg---
 *
 *
 *
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* UnComment the following line to enable debugs */
//#define DEBUG

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage(char* arg0)
{
    printf("Usage for encrypting a text: %s <text> <password>\n or\n",arg0);
    printf("Usage for decrypting a text: %s -d <text> <password>\n or\n",arg0);
    printf("Usage for generating an Hash: %s -g <text> <length>\n",arg0);
exit(0);
}

/* RotCharUp Examples
 * RotCharUp('a'+1,'a','z');   => 'b'
 * RotCharUp('a'+26,'a','z');  => 'a'
 * RotCharUp('a'+100,'a','z'); => 'w'
 */
char RotCharUp(unsigned int value, char lBound, char rBound)
{
    while(value>rBound)
        value=(unsigned int)lBound + (value-rBound-1);

return (char)value;
}

/* RotCharDown Examples
 * RotCharDown('a'-1,'a','z');   => 'z'
 * RotCharDown('a'-26,'a','z');  => 'a'
 * RotCharDown('a'-100,'a','z'); => 'e'
 */
char RotCharDown(int value, char lBound, char rBound)
{
    while(value<lBound)
        value=(unsigned int)rBound - (lBound-value-1);

return (char)value;
}

int avgDispersion(char* text)
{
int c;
int textLen=strlen(text);
int avg=0;

    for(c=0;c<textLen;c++)
        if(c)
            avg += (text[c]>text[c-1]) ? text[c]-text[c-1] : text[c-1]-text[c];

    if(c)
        avg /= textLen;

return avg+1;
}

int charWSum(char* text)
{
int c;
int textLen = strlen(text);
int sum = 0;
    
    for(c=0;c<textLen;c++)
		if(sum > 0xABC)
			sum = sum - ((text[c] * ((c*10)%0x10)) % 0xABC);
		else
			sum += text[c] * ((c*10)%0x12);

return sum;
}

/* hashum
 *  Variable hashes generator
 *
 *  Hashes Examples
 *
aa(50)      wvblxzhpqevedbbwumlaxlywvnrvtfnovijwpnzuzhirmlxztx
bb(50)      wanwdkdkqcmtnzwnpbhhlhdkzkdsyrkonuezejrdgvuqyyajzc
ab(50)      rafvlxzsqktaiknughvkonjqadmrtozjxnhqtcsesqzipyobrn
ba(50)      rybohexdwivajergruxenyjvafibvzsakgeqxrvnrtodlwhexh
aba(50)     nikwjervknzkvdrktbnmlejypaxqqmjthszbyqeccuiwwlnztr
baa(50)     pmwgbltcbmxetmtrletwluytivjnfgakryaauebqqkvjhsgyay
test(35)    xyuglkhsvoveuvxiszegxkvxkdqbjaqhbfg
shen139(25) rufvdrpkocxkiacadinktxqek
 *
 */
char* hashum(char* word, int length)
{
int wordLen = strlen(word);
char* hash = (char*)malloc(length+1);

int i;
unsigned int curC=0;
int hashLen;

    if(hash == NULL || wordLen<1)
        return NULL;

    hash[0]='\0';

    for(i=0;i<length;i++)
    {
        hashLen = strlen(hash);
        if(i==0)
            curC = wordLen + avgDispersion(word) + charWSum(word);
        else
            curC = i + avgDispersion(hash) + charWSum(hash) + word[hashLen%wordLen] + (wordLen^hashLen);
       
        curC += 'a' ;
        curC = RotCharUp(curC,'a','z');
        
        hash[i]=hash[curC%(hashLen+1)];
        hash[curC%(hashLen+1)]=curC;
        hash[i+1]='\0';
    }
return hash;
}

/* vernash
 *  Crypt text with password (key)
 */
char* vernash(char* text, char* key)
{
int textLen = strlen(text);
char* hashKey;
char* crtText;
int i;

    if(text==NULL)
        return NULL;

    crtText = (char*)malloc(textLen);
    hashKey = hashum(key, textLen);

    if(crtText==NULL || hashKey==NULL)
        return NULL;

#ifdef DEBUG
    printf("%s\n%s  +\n",hashKey,text);
#endif

    for(i=0; i<textLen;i++)
        crtText[i] = RotCharUp( 'a' + (hashKey[i]-'a') + (text[i]-'a') ,' ','}' );

    crtText[i]='\0';

#ifdef DEBUG
    printf("%s  =\n\n",crtText);
#endif

    free(hashKey);
return crtText;
}

/* vernash
 *  DeCrypt text with password (key)
 */
char* unVernash(char* text, char* key)
{
int textLen = strlen(text);
char* hashKey;
char* crtText;
int i;

    if(text==NULL)
        return NULL;

    crtText = (char*)malloc(textLen);
    hashKey = hashum(key, textLen);

    if(crtText==NULL || hashKey==NULL)
        return NULL;

#ifdef DEBUG
    printf("%s\n%s  -\n",hashKey,text);
#endif

    for(i=0; i<textLen;i++)
        crtText[i] = RotCharDown( 'a' + (text[i]-'a') - (hashKey[i]-'a') ,' ','}' );

    crtText[i]='\0';

#ifdef DEBUG
        printf("%s  =\n\n",crtText);
#endif

    free(hashKey);
return crtText;
}

/* *************** */
int main(int argc, char* argv[])
{
char* encryptedText;
int decrypt = 0 ;
char *text, *key;

#ifdef DEBUG
    printf("aa   %s\n",hashum("aa",50));
    printf("bb   %s\n",hashum("bb",50));
    printf("ab   %s\n",hashum("ab",50));    
    printf("ba   %s\n",hashum("ba",50));
    printf("aba  %s\n",hashum("aba",50));
    printf("baa  %s\n",hashum("baa",50));

    printf("\n\n");

    unVernash(vernash("abcdefghilmnopqrstuvz","bububuudfgidfug"),"bububuudfgidfug");

    printf("\n============debug=========\n\n");
#endif

    printf("\n\n");

    if(argc==4)
    {
        if( strcmp(argv[1],"-g")==0 )
        {
            printf("Hash(%s) for ---%s---:\n---%s---\n\n",argv[3], argv[2], hashum(argv[2],atoi(argv[3])) );
            return 1;
        }
        else if( strcmp(argv[1],"-d")==0 )
        {
            decrypt = 1;
            text = (char*) malloc( strlen( argv[2] ) );
            key  = (char*) malloc( strlen( argv[3] ) );

            strcpy(text, argv[2]);
            strcpy(key, argv[3]);
        }
        else
            usage(argv[0]);
    }
    else
    if(argc!=3)
        usage(argv[0]);
    else
    {
        text = (char*) malloc( strlen( argv[1] ) );
        key  = (char*) malloc( strlen( argv[2] ) );

        strcpy(text, argv[1]);
        strcpy(key, argv[2]);
    }

    printf("Text:           ---%s---\nPassword:       ---%s---\n",text,key);

    if(decrypt)
    {
        encryptedText = unVernash(text, key);

        if( strcmp(vernash(encryptedText, key) ,text) == 0 )
            printf("\nDecrypted-Text: ---%s---\n\n", encryptedText);
        else
            printf("\n (ERROR) :@# \n\n");

    }
    else
    {
        encryptedText = vernash(text, key);

        if( strcmp(unVernash(encryptedText, key) ,text) == 0 )
            printf("\nEncrypted-Text: ---%s---\n\n", encryptedText);
        else
            printf("\n (ERROR) :@# \n\n");
    }

return 1;
}

/* EOF */

