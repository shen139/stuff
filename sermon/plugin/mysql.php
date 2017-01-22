<?php

$plugin_name = "Mysql";

	if( trim( MYSQL001_SERVER ) != "" )
	{
	
		$mysql_start_time =  microtime(true);
		
		$mysql_conn = mysql_connect(MYSQL001_SERVER, MYSQL001_USERNAME, MYSQL001_PASSWORD);
			
		if ($mysql_conn == FALSE)
		{
			$alert = true;
			$alert_msg = "Mysql Error: Unable to Connect to MySQL Server [" . MYSQL001_SERVER . "]";
		}
		else
		{
			mysql_select_db(MYSQL001_DATABASE, $mysql_conn);
			
			$result = mysql_query( MYSQL001_TEST_QUERY , $mysql_conn);
			if($result==false)
			{
				$alert = true;
				$alert_msg = "Mysql Error: ". mysql_error($mysql_conn);
			}
		
			mysql_close($mysql_conn);
		}		
	
		$mysql_time_end = microtime(true);
		$mysql_time = ($mysql_time_end - $mysql_start_time) * 1000;
		
		if( $mysql_time > MYSQL001_MAX_TIME )
		{
			$alert = true;
			$alert_msg .= "\r\nMysql Error: Time Limit: " . MYSQL001_MAX_TIME . " ms -- Time Elapsed: " . number_format($mysql_time, 0, "", "") . " ms";
		}

	}
	
	
?>