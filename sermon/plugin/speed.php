<?php

$plugin_name =  "Speed Test";

	if( trim( SB001_URL2DOWNLOAD ) != "" )
	{
	
		$sb001_time_start = microtime(true);
		
		// Download an URL
		$ctx = stream_context_create(array
				( 
				'http' => array
					( 
						'timeout' => 20
					) 
				) 
			); 
		$sb001_content = file_get_contents(SB001_URL2DOWNLOAD, 0 , $ctx);
	
		if( $sb001_content == FALSE || $sb001_content == "")
		{
			$alert = true;
			$alert_msg = "Speed Test Error: Unable to download [" . SB001_URL2DOWNLOAD . "]";
		}
		else
		{
			// calculate time and speed	
			$sb001_time_end = microtime(true);
			$sb001_time = $sb001_time_end - $sb001_time_start;
			$sb001_kb_s = intval(((strlen($sb001_content) / $sb001_time) / 1024));
			
			$sb001_content = "";
			
			if( $sb001_kb_s < SB001_MIN_BANDWIDTH )
			{
				$alert = true;
				$alert_msg = "Speed Test Error: Downloaded [" . SB001_URL2DOWNLOAD . "] in " 
				. number_format($sb001_time, 3, ".", "") . "s at " . $sb001_kb_s 
				. "Kb/s instead of " . SB001_MIN_BANDWIDTH . "Kb/s";
			}
		}
		
	}	
	
	
?>