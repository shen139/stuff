<?php

	error_reporting(0);

// the folder of SERMON
define('BASE_DIR', dirname(__FILE__) . DIRECTORY_SEPARATOR);

require( BASE_DIR . "configure.php" );
require( BASE_DIR . "fnc" . DIRECTORY_SEPARATOR . "fnc.php" );

	$time_start = microtime(true);

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>SERMON</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link rel="stylesheet" href="style.css" type="text/css">
<script type="text/javascript">
function showDiv(d)
{
	document.getElementById(d).style.display = "";
}
</script>
</head> 
<body vlink="#0000FF" alink="#0000FF" style="font-family:Arial, Helvetica, sans-serif; font-size:18px; color:222222;"> 
<center> 
  <a href="index.php"><img src="img/sermon.jpg" style="border:0;" alt="SerMon"></a>
  <div id="rnd_container" style="width:700px;"> <b class="rnd_top"><b class="rnd_b1"></b><b class="rnd_b2"></b><b class="rnd_b3"></b><b class="rnd_b4"></b></b> 
    <div class="rnd_content" style="padding:40px; text-align:left;"> 
	
	<div style="border:1px solid #FFAAAA; margin:0; padding:2px;"><?php drawNavBar(); ?></div>
<?php
	$lastLog = "";
	
	writeLastLog( date( RSS_DATE_FORMAT ) . " :: Starting ...", "w");
	
	$plugin_folder = BASE_DIR . 'plugin' . DIRECTORY_SEPARATOR;

	// Loop through directory, strip out . and ..
	if ( $handle = opendir ( $plugin_folder ) ) 
	{
		while ( false !== ( $file = readdir ( $handle ) ) ) 
		{
			if ( strtolower(substr($file, strlen($file)-4,4)) == ".php" )
			{
				$plugin_name = "N\\A";
				
				$plugin_time_start = microtime(true);
				
				$alert = false;
				$alert_msg = "";
				
				// Include or require file here
				include_once( $plugin_folder . $file );
				
				$plugin_time_end = microtime(true);
				$plugin_time = $plugin_time_end - $plugin_time_start;

				echo "<div class='plugin_box' id='div_" . md5( $file ) . "'>";
				echo "Plugin Name [" . $file . "]: <span class='resp'>" . $plugin_name . "</span><br />";
				
				echo "Execution Time: <span class='resp'>" . number_format($plugin_time, 3, ".", "") . "s</span><br />";
				
				$lastLog = date( RSS_DATE_FORMAT ) . " :: " . $plugin_name . " (" . number_format($plugin_time, 3, ".", "") . "s)";
				
				echo "Status: ";
				if( $alert == true )
				{
					echo "<span class='resp_err'>ERROR</span><br />Error Message:<br /><textarea readonly style=\"width:550px; height:100px; border:1px solid #CCCCCC;\">" . $alert_msg . "</textarea><br />";
					$lastLog .= " [ERROR: " . str_replace("\n", " -- ", str_replace("\r", "", $alert_msg)) ."]";
					$ext_alert_out = SendAlerts($plugin_name, $alert_msg);
					
					if( trim( $ext_alert_out ) != "" )
					{
						echo "Alert Plugin Message:<br /><textarea readonly style=\"width:550px; height:100px; border:1px solid #CCCCCC;\">" . $ext_alert_out . "</textarea><br />";
					}
				}
				else
				{
					// status: OK
					echo "<span class='resp'>OK</span><br />";
					$lastLog .= " [OK]";
				}
				
				echo "</div>";
				
				writeLastLog( $lastLog, "a");
				
			}
		}
		closedir($handle);
	}
		
	$time_end = microtime(true);
	$time = $time_end - $time_start;
	
	echo "<br /><hr />";
	
	echo "Total Execution time: " . number_format($time, 3, ".", ""). "s";
	
	writeLastLog( date( RSS_DATE_FORMAT ) . " :: Execution time: " . number_format($time, 3, ".", ""). "s", "a");

?>      
    </div> 
    <b class="rnd_bottom"><b class="rnd_b4"></b><b class="rnd_b3"></b><b class="rnd_b2"></b><b class="rnd_b1"></b></b> </div> 
  </p> 
</center> 
<br> 
<br> 
</body>
</html>