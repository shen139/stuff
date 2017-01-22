<?php

	if( trim( FILELOG001_FULL_PATH ) != "" )
	{
		
		$myFile = FILELOG001_FULL_PATH;
		$fh = fopen( FILELOG001_FULL_PATH, 'a');
		if( $fh != FALSE )
		{
			fwrite($fh, "===============================\r\n");
			fwrite($fh, date("F j, Y, g:i:s a") . "\r\n");
			fwrite($fh, "Plugin: " . $source_alert . "\r\n");
			fwrite($fh, "Error: " . $alert_msg . "\r\n\r\n");
			fclose($fh);
		}
		else
		{
			$alert_out .=  "FILELOG001: Unable to open file: " . FILELOG001_FULL_PATH . "\r\n\r\n";
		}

	}
	
	
?>