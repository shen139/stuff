<?php

$plugin_name =  "MD5 Check";

	if( trim( MD5001_URL ) != "" &&  trim( MD5001_MD5 ) != "" )
	{
		$MD5001_URLs = explode(",", MD5001_URL);
		$MD5001_MD5s = explode(",", MD5001_MD5);
	
		// if we have n URLs and n MD5s and n > 0
		if( count($MD5001_URLs) == count($MD5001_MD5s) && count($MD5001_URLs) > 0 )
		{
			for( $i = 0; $i < count($MD5001_MD5s); $i++  )
			{
				$MD5001_md5_file = md5_file( trim( $MD5001_URLs[$i] ) );
				if( $MD5001_md5_file != trim($MD5001_MD5s[$i]) )
				{
					$alert = true;
					$alert_msg .= "MD5 Check Error: MD5(" . trim( $MD5001_URLs[$i] ) . ") = [" . $MD5001_md5_file . "]; Expected: [" . trim($MD5001_MD5s[$i]) . "]\r\n";
				}
			}
		}
		else
		{
			$alert = true;
			$alert_msg = "MD5 Check Error: We have " . count($MD5001_URLs) . " URLs and " . count($MD5001_MD5s) . " MD5 Hashes ";
		}
	}
	
?>