/* Vernash
 *   Stream cipher based on the Vernam cipher and Variable-Length Hashes
 *   
 * Author:  
 *   Stefano 'Shen139' Alimonti
 * 
 * Website:
 *   http://lab.openwebspider.org/vernash/
 *
 */

using System;
using System.Text;
using System.IO;

namespace Vernash
{
    class vernash
    {
        private int BLOCKS = 256;
        private int EXPANSION = 2;
        private int RANDOM_EXPANSION = 2;

        public static string vernashFileHeader = "VERNASH";

        private uint MAX_OUTPUT_LENGTH = 100000; //100k

        private static string msg001 = "Crypted text is too long. Please save it to a file using the \"Crypt a File To another File\" button!";
        private static string msg002 = "DeCrypted text is too long. Please save it to a file using the \"DeCrypt a File To another File\" button!";


        /* RotCharUp
         */
        private char RotCharUp(int value, char lBound, char rBound)
        {
            value += (lBound * 2);
            return (char)(lBound + ((value - lBound) % (rBound - lBound)));
        }

        /* RotCharDown
         */
        private char RotCharDown(int value, char lBound, char rBound)
        {
            value -= (lBound * 2);
            value = (value - lBound) % (rBound - lBound);
            if (value == 0)
                return lBound;
            return (char)(rBound + value);
        }

        private static void Swap(ref int a, ref int b)
        {
            int tmp = a;
            a = b;
            b = tmp;
        }

        /* genKeyPos
         *    Generates pseudorandom order for the string to be shuffled.
         */
        public int[] genKeyPos(int nPos, string key)
        {
            int[] iPos = new int[nPos];
            int newPos;
            int curW = 0;

            //init
            for (int i = 0; i < nPos; i++)
                iPos[i] = i;

            for (int x = 0; x < nPos; x++)
            {
                for (int y = 0; y < key.Length; y++)
                {
                    newPos = ((y + 1) * 2 + (x + 13) * 3 + nPos * 4 + (key.Length + 12) * 5 + key[y] * 13 + key[curW] * 7);
                    newPos = (newPos + key[y] + 1) % nPos;

                    curW++;
                    if (curW >= key.Length)
                        curW = 0;

                    // swap
                    Swap(ref iPos[x], ref iPos[newPos]);
                }
            }
            return iPos;
        }

        /* scrambleText 
         *    Shuffles a string.
         *  
         * Example:
         *   scrambleText  ("12345", "password"); ==> "53241"
         *   unScrambleText("53241", "password"); ==> "12345"
         *   
         *   scrambleText("abcdefghilmnopq1234567", "passphrase"); == "chan43mlopqdif6bg127e5"
         * 
         */
        public string scrambleText(string text, string key, int[] iPos)
        {
            char[] scrambled = new char[text.Length];

            // Optimizations
            if (text.Length % 4 == 0)
            {
                for (int x = 0; x < text.Length / 4; x++)
                {
                    // swap
                    scrambled[x * 4] = text[iPos[x * 4]];
                    scrambled[(x * 4) + 1] = text[iPos[(x * 4) + 1]];
                    scrambled[(x * 4) + 2] = text[iPos[(x * 4) + 2]];
                    scrambled[(x * 4) + 3] = text[iPos[(x * 4) + 3]];
                }
            }
            else if (text.Length % 2 == 0)
            {
                for (int x = 0; x < text.Length / 2; x++)
                {
                    // swap
                    scrambled[x * 2] = text[iPos[x * 2]];
                    scrambled[(x * 2) + 1] = text[iPos[(x * 2) + 1]];
                }
            }
            else
            {
                for (int x = 0; x < text.Length; x++)
                {
                    // swap
                    scrambled[x] = text[iPos[x]];
                }
            }
            return new string(scrambled);
        }

        /* unScrambleText
         * 
         * Example:
         *   scrambleText  ("12345", "password"); ==> "53241"
         *   unScrambleText("53241", "password"); ==> "12345"
         *   
         *   unScrambleText("chan43mlopqdif6bg127e5", "passphrase"); == "abcdefghilmnopq1234567"
         * 
         */
        public string unScrambleText(string text, string key, int[] iPos)
        {
            char[] scrambled = new char[text.Length];

            // Swap
            for (int x = 0; x < text.Length; x++)
            {
                scrambled[iPos[x]] = text[x];
            }

            return new string(scrambled);
        }

        /* hashum
         *    Variable-Length Hashes Generator
         */
        public string hashum(string sWord, int iTextLength)
        {
            char[] hash = new char[iTextLength];

            if (sWord.Length < 1)
                return string.Empty;

            int x, y;
            int curC;
            int curW = 0;

            Array.Clear(hash, 0, hash.Length);

            for (x = 0; x < iTextLength; x++)
            {
                for (y = 0; y < iTextLength; y++)
                {
                    curC = (sWord[curW] + hash[x] + hash[y] + x + y + curW) % 139;

                    curW++;
                    if (curW >= sWord.Length)
                        curW = 0;

                    hash[x] = RotCharUp(curC + sWord.Length, 'A', 'Z');

                    curC += sWord.Length + curW + iTextLength + x + y + (((x + y + curC) * 9) % 139);

                    hash[y] = RotCharUp(curC, 'A', 'Z');
                }
            }
            return new string(hash);
        }

        /* expandText
         *    expandText("ABC") ==> "414243"
         */
        private string expandText(byte[] text)
        {
            //string expandedText = string.Empty;

            // OLD Version
            /*
            foreach (byte c in text)
            {
                expandedText += String.Format("{0:X" + EXPANSION + "}", (int)c);
            }
            return expandedText;
            */

            StringBuilder expandedText = new StringBuilder();

            if (text.Length % 2 == 0)
            {
                for (uint i = 0; i < text.Length / 2; i++)
                {
                    expandedText.Append(String.Format("{0:X" + EXPANSION + "}", (int)text[i * 2]));
                    expandedText.Append(String.Format("{0:X" + EXPANSION + "}", (int)text[(i * 2 ) + 1]));
                }
            }
            else
            {
                for (uint i = 0; i < text.Length; i++)
                {
                    expandedText.Append(String.Format("{0:X" + EXPANSION + "}", (int)text[i]));
                }
            }

            return expandedText.ToString();
        }

        /* reduceString
         *    reduceString("414243") = "ABC"
         */
        private byte[] reduceString(string text)
        {
            byte[] reducedT = new byte[text.Length / EXPANSION];
            int iTP;
            int i = 0;
            int pos = 0;
            try
            {

                for (i = 0; i < text.Length; i += EXPANSION)
                {

                    iTP = Convert.ToInt32(text.Substring(i, EXPANSION), 16);

                    reducedT[pos] = (byte)iTP;
                    pos++;
                }
            }
            catch
            {
                reducedT = null;
            }
            return reducedT;
        }

        /* randomExpansion
         *    Expand 1 byte to 2 bytes:
         *     1# byte is a random number from 0 to byte value
         *     2# is the rest.
         * 
         * Example: randomExpansion('a') =>
         *      random_number = random number from 0 to 'a'
         *      randomExpansion = random_number & ('a' - random_number)
         *          ==> random_number + 'a' - random_number = 'a'
         */
        private byte[] randomExpansion(byte[] text)
        {
            byte[] expandedText = new byte[text.Length * 2];
            int i = 0;
            Random random = new Random();

            for (uint c = 0; c < text.Length; c++)
            {
                expandedText[i++] = (byte)random.Next(0, ((int)text[c]));
                expandedText[i++] = (byte)(((int)text[c]) - expandedText[i - 2]);
            }
            return expandedText;
        }

        /* randomReduction
         *    randomReduction("xyzkts") => x+y & z+k & t+s
         *     x, z and t are random generated numbers;
         *     y, k and s are complementary values of their respective random genetare value;
         * 
         *     x+y = original char1
         *     z+k = original char2
         *     t+s = original char3
         */
        private byte[] randomReduction(byte[] text)
        {
            byte[] reducedT = new byte[text.Length / 2];

            for (int i = 0; i < text.Length / 2; i++)
            {
                reducedT[i] = (byte)((int)text[i * 2] + (int)text[(i * 2) + 1]);
            }
            return reducedT;
        }

        /* vernashCrypt
         *    Crypt text with password (key)
         */
        public string vernashCrypt(byte[] text, string key, bool saveToFile, string filename)
        {
            int textLen;
            StringBuilder res = new StringBuilder(vernashFileHeader);
            string hashKey = string.Empty;
            int lastLength = 0;
            string exKey = expandText(System.Text.Encoding.UTF8.GetBytes(key));
            byte[] tmpExText;
            string exText;
            char[] crtText;
            int i;
            int[] scramblePos = null;

            // saveToFile ?!?
            FileStream fileStream;
            BinaryWriter bw = null;

            if (saveToFile)
            {
                try
                {
                    fileStream = new FileStream(filename, FileMode.Create);
                    bw = new BinaryWriter(fileStream);

                    // writes header : "VERNASH"
                    bw.Write(System.Text.Encoding.UTF8.GetBytes(vernashFileHeader));
                }
                catch (Exception e)
                {
                    return "ERROR: " + e.Message;
                }
            }

            for (int p = 0; p < text.Length; p += BLOCKS)
            {
                tmpExText = new byte[Math.Min(BLOCKS, text.Length - p)];
                Buffer.BlockCopy(text, p, tmpExText, 0, Math.Min(BLOCKS, text.Length - p));

                /*
                 * 1) Expand text with pseudorandom chars
                 * 2) Expand to HEX chars (example: "ABC" = "414243")
                 * 3) Scramble text (example: "12345" => "43521")
                 */
                exText = expandText(randomExpansion(tmpExText));

                if (exText.Length != lastLength)
                    scramblePos = genKeyPos(exText.Length, key);

                exText = scrambleText(exText, key, scramblePos);

                textLen = exText.Length;
                crtText = new char[textLen];

                if (exText.Length == 0 || key.Length == 0)
                    return res.ToString();

                if (lastLength != textLen)
                {
                    hashKey = hashum(exKey, textLen);
                    lastLength = textLen;
                }

                if (hashKey.Length == 0)
                    return res.ToString();

                for (i = 0; i < textLen; i++)
                    crtText[i] = RotCharUp(hashKey[i] + exText[i], '0', 'Z');

                if (saveToFile)
                {
                    try
                    {
                        bw.Write(System.Text.Encoding.UTF8.GetBytes(new string(crtText, 0, textLen)));
                    }
                    catch (Exception e)
                    {
                        return "ERROR: " + e.Message;
                    }
                }
                else
                {
                    if (res.Length + textLen > MAX_OUTPUT_LENGTH)
                        return msg001;

                    res.Append(new string(crtText, 0, textLen));
                }
            }

            if (saveToFile)
                bw.Close();

            return res.ToString();
        }

        /* vernashDeCrypt
         *    DeCrypt text with password (key)
         */
        public byte[] vernashDeCrypt(string text, string key, bool saveToFile, string filename)
        {
            int textLen;
            byte[] res = new byte[text.Length / EXPANSION / RANDOM_EXPANSION];
            byte[] redString;
            string hashKey = string.Empty;
            int lastLength = 0;
            string exKey = expandText(System.Text.Encoding.UTF8.GetBytes(key));
            string exText;
            char[] crtText;
            int i;
            int[] scramblePos = null;

            // check valid VERNASH Cipher
            if (text.Length < vernashFileHeader.Length + 4)
                return null;
            else if (text.Substring(0, vernashFileHeader.Length) != vernash.vernashFileHeader)
                return null;
            else
                text = text.Substring(vernashFileHeader.Length);


            // saveToFile ?!?
            FileStream fileStream;
            BinaryWriter bw = null;

            if (saveToFile)
            {
                try
                {
                    fileStream = new FileStream(filename, FileMode.Create);
                    bw = new BinaryWriter(fileStream);
                }
                catch (Exception e)
                {
                    return System.Text.Encoding.UTF8.GetBytes("ERROR: " + e.Message);
                }
            }

            for (int p = 0; p < text.Length; p += BLOCKS * EXPANSION * RANDOM_EXPANSION)
            {
                exText = text.Substring(p, Math.Min(BLOCKS * EXPANSION * RANDOM_EXPANSION, text.Length - p));

                textLen = exText.Length;
                crtText = new char[textLen];

                if (exText.Length == 0 || key.Length == 0)
                    return null;

                if (lastLength != textLen)
                {
                    hashKey = hashum(exKey, textLen);
                    lastLength = textLen;
                    scramblePos = genKeyPos(exText.Length, key);
                }

                if (hashKey.Length == 0)
                    return null;

                for (i = 0; i < textLen; i++)
                    crtText[i] = RotCharDown(exText[i] - hashKey[i], '0', 'Z');

                // Scramble the string to the origin; and reduce it (from HEX to bytes)
                redString = reduceString(unScrambleText(new string(crtText, 0, textLen), key, scramblePos));
                if (redString == null)
                {
                    return null;
                }

                // Remove pseudorandom characters (Example: randomReduction("xyzk") => x+y & z+k )
                redString = randomReduction(redString);

                if (saveToFile)
                {
                    try
                    {
                        bw.Write(redString, 0, redString.Length);
                    }
                    catch (Exception e)
                    {
                        return System.Text.Encoding.UTF8.GetBytes("ERROR: " + e.Message);
                    }
                }
                else
                {
                    if (res.Length + textLen > MAX_OUTPUT_LENGTH)
                        return System.Text.Encoding.UTF8.GetBytes(msg002);
                    Buffer.BlockCopy(redString, 0, res, p / EXPANSION / RANDOM_EXPANSION, redString.Length);
                }

            }

            if (saveToFile)
                bw.Close();

            return res;
        }

    }
}
