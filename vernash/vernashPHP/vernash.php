<?php
        define("BLOCKS", 256);
        define("EXPANSION",2);
        define("RANDOM_EXPANSION", 2);
        define("binFileHeader", "VERNASH");


class vernash
    {


        /* RotCharUp
         */
        function RotCharUp($value, $lBound, $rBound)
        {
            $value += ($lBound * 2);
            return ($lBound + (($value - $lBound) % ($rBound - $lBound)));
        }

        /* RotCharDown
         */
        function RotCharDown($value, $lBound, $rBound)
        {
            $value -= ($lBound * 2);
            $value = ($value - $lBound) % ($rBound - $lBound);
            if ($value == 0)
                return $lBound;
            return ($rBound + $value);
        }

        /* genKeyPos
         *    Generates pseudorandom order for the string to be shuffled.
         */
        function genKeyPos($nPos, $key)
        {
            $curW = 0;

            //init
            for ($i = 0; $i < intval($nPos); $i++)
                $iPos[$i] = $i;

            for ($x = 0; $x < $nPos; $x++)
            {
                for ($y = 0; $y < strlen($key); $y++)
                {
                    $newPos = (($y + 1) * 2 + ($x + 13) * 3 + $nPos * 4 + (strlen($key) + 12) * 5 + ord($key[$y]) * 13 + ord($key[$curW]) * 7);
                    $newPos = ($newPos + ord($key[$y]) + 1) % $nPos;

                    $curW++;
                    if ($curW >= strlen($key))
                        $curW = 0;

                    // swap
					$tmp = $iPos[$x];
					$iPos[$x] = $iPos[$newPos];
					$iPos[$newPos] = $tmp;
                }
            }
            return $iPos;
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
        function scrambleText($text, $key)
        {
            $iPos = $this->genKeyPos(strlen($text), $key);
			
			$scrambled = $text;
			
			//print_r($iPos);

            for ($x = 0; $x < strlen($text); $x++)
            {
                // swap
                $scrambled[$x] = $text[$iPos[$x]];
            }
            return $scrambled;
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
        function unScrambleText($text, $key)
        {
            $iPos = $this->genKeyPos(strlen($text), $key);
			
			$scrambled = $text;
            // Swap
            for ($x = 0; $x < strlen($text); $x++)
            {
                $scrambled[$iPos[$x]] = $text[$x];
            }

            return $scrambled;
        }

        /* hashum
         *    Variable-Length Hashes Generator
         */
        function hashum($sWord, $iTextLength)
        {
            if (strlen($sWord) < 1)
                return "";

            $curW = 0;
			
			for ($x = 0; $x < $iTextLength; $x++)
			{
				$hash[] = 0;
				
			}

            for ($x = 0; $x < $iTextLength; $x++)
            {
                for ($y = 0; $y < $iTextLength; $y++)
                {
                    $curC = (ord($sWord[$curW]) + $hash[$x] + $hash[$y] + $x + $y + $curW) % 139;

                    $curW++;
                    if ($curW >= strlen($sWord))
                        $curW = 0;

                    $hash[$x] = $this->RotCharUp($curC + strlen($sWord), 65, 90);

                    $curC += strlen($sWord) + $curW + $iTextLength + $x + $y + ((($x + $y + $curC) * 9) % 139);

                    $hash[$y] = $this->RotCharUp($curC, 65,90);
					
                }
            }
			
			$retHash = "";
			for ($x = 0; $x < $iTextLength; $x++)
			{
				$retHash .= sprintf("%c", $hash[$x] );
			}
			
            return $retHash;
        }

        /* expandText
         *    expandText("ABC") ==> "414243"
         */
        function expandText($text)
        {
            $expandedText = "";

            for($i=0; $i < strlen($text);$i++)
            {
				$expandedText .= sprintf("%02X", ord($text[$i]));
            }
            return $expandedText;
			
        }

        /* reduceString
         *    reduceString("414243") = "ABC"
         */

        function reduceString($text)
        {
			$reducedT = "";

			for ($i = 0; $i < strlen($text) / 2; $i++)
			{
				$reducedT .= chr( hexdec( substr($text,$i*2,2) ));
			}
            return $reducedT;
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
        function randomExpansion($text)
        {
            $expandedText = "";
            
            for($i=0; $i< strlen($text);$i++)
            {
				$randMaxChar = rand( 1, ord($text[$i]) );
				$expandedText .= chr( $randMaxChar );
				$expandedText .= chr( ord($text[$i]) - $randMaxChar );
            }
            return $expandedText;
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
       function randomReduction($text)
       {
            $reducedT = "";

			if( strlen( $text ) % 2 != 0 )
				return "";
				
            for ($i = 0; $i < strlen($text) / 2; $i++)
            {
                $reducedT .= chr( ord($text[$i * 2]) + ord( $text[($i * 2) + 1] ) );
            }
            return $reducedT;
        }

        /* vernashCrypt
         *    Crypt text with password (key)
         */
        function vernashCrypt($text, $key)
        {
			$lastLength = 0;
			$res = "VERNASH";
			
			$exKey = $this->expandText($key);

            for ($p = 0; $p < strlen($text); $p += BLOCKS)
            {
				$newTextLen = min(BLOCKS, strlen($text) - $p);
				$curText = substr($text,$p,$newTextLen);
               
                $exText = $this->expandText($this->randomExpansion($curText));
                $exText = $this->scrambleText($exText, $key);

                $exTextLen = $newTextLen * EXPANSION * RANDOM_EXPANSION;

                if ($exTextLen == 0 || strlen($key) == 0)
				{
					echo "err1";
                    return $res;
				}

                if ($lastLength != $exTextLen)
                {
                    $hashKey = $this->hashum($exKey, $exTextLen);
                    $lastLength = $exTextLen;
                }

                if (strlen($hashKey) == 0)
				{
					echo "err2";
                    return $res;
				}
					
				$crtText = $exText;

                for ($i = 0; $i < $exTextLen; $i++)
				{
                    $crtText[$i] = chr( $this->RotCharUp( ord($hashKey[$i]) + ord($exText[$i]), 48, 90) );
					//echo "__" . ord($hashKey[$i]) . "___" . ord($exText[$i]) . "__" .  $crtText[$i] . "__<br>";
				}

                $res .= $crtText;
            }
            return $res;
        }

        /* vernashDeCrypt
         *    DeCrypt text with password (key)
         */
        function vernashDeCrypt($text, $key)
        {
			
			// check valid VERNASH Cipher
            if (strlen($text) < 11)
                return "";
            else if (substr($text, 0, 7) != "VERNASH")
                return "";
            else
                $text = substr($text, 7, strlen($text) - 7);
				
			$lastLength = 0;
			$exKey = $this->expandText($key);
			
			$res = "";
			
            for ($p = 0; $p < strlen($text); $p += BLOCKS * EXPANSION * RANDOM_EXPANSION)
            {
                $exText = substr($text, $p, min(BLOCKS * EXPANSION * RANDOM_EXPANSION, strlen($text) - $p));

                $textLen = strlen($exText);

                if (strlen($exText) == 0 || strlen($key) == 0)
                    return "";

                if ($lastLength != $textLen)
                {
                    $hashKey = $this->hashum($exKey, $textLen);
                    $lastLength = $textLen;
                }

                if (strlen($hashKey) == 0)
                    return "";

				$crtText = "";
                for ($i = 0; $i < $textLen; $i++)
                    $crtText .= chr( $this->RotCharDown( ord($exText[$i]) - ord($hashKey[$i]), 48, 90) );

                // Scramble the string to the origin; and reduce it (from HEX to bytes)
                $redString = $this->reduceString($this->unScrambleText($crtText, $key));
                if ($redString == "")
                {
                    return "";
                }

                // Remove pseudorandom characters (Example: randomReduction("xyzk") => x+y & z+k )
                $redString = $this->randomReduction($redString);

                $res .= $redString;

            }

            return $res;
        }

    }

/*
$ver = new vernash();
echo "<h1>VernashPHP</h1>";

echo "<h3>Un/Scramble Text</h3>";
$test01Text = "1234567890";
$test01Key = "acbdefghi";
echo "Text: " . $test01Text . "<br>Key: " . $test01Key . "<br>";
$res01 = $ver->scrambleText($test01Text, $test01Key);
echo "Scramble Text: " . $res01 . "<br>";
echo "UnScramble Text: " . $ver->unScrambleText($res01, $test01Key);
echo "<br><br>";
echo "<hr>";


echo "<h3>Hash</h3>";
echo "Hash('this is a test', 32) ==> " . $ver->hashum("this is a test",32);
echo "<br><br>";
echo "<hr>";


echo "<h3>Expand/Reduce Text</h3>";
$test03Text = "abcdefGhil12345";
echo "Text: " . $test03Text . "<br>";
$res03 =  $ver->expandText($test03Text);
echo "Expansion: " . $res03 . "<br>";
echo "Reduction: " . $ver->reduceString( $res03 );
echo "<br><br>";
echo "<hr>";


echo "<h3>Random Expansion/Reduction</h3>";
echo $ver->randomReduction( $ver->randomExpansion("test") );
echo "<br><br>";
echo "<hr>";


echo "<h3>Encrypt/Decrypt Text</h3>";
$test05Text = "this is a test!!!";
$test05Key = "12345678980";

echo "Text: " . $test05Text . "<br>Key: " . $test05Key . "<br>";

$res05 = $ver->vernashCrypt($test05Text, $test05Key);
echo "Encryption: " . htmlspecialchars( $res05 ) . "<br>";
echo "Decryption: " . htmlspecialchars($ver->vernashDeCrypt( $res05, $test05Key));
echo "<br><br>";
echo "<br><br>";
*/
?>