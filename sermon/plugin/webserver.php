<?php

$plugin_name =  "WebServer";

	if( trim( WS001_URL2DOWNLOAD ) != "" )
	{

		$ctx = stream_context_create(array
				( 
				'http' => array
					( 
						'timeout' => 20
					) 
				) 
			); 
	
		if( file(WS001_URL2DOWNLOAD ,0 ,$ctx) == FALSE )
		{
			$alert = true;
			$alert_msg = "WebServer Error Downloading [" . WS001_URL2DOWNLOAD . "]";
		}

	}
	
	
?>