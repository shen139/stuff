<?php
// Configuration file

	define("LASTLOG_FULL_PATH",   BASE_DIR . "log" . DIRECTORY_SEPARATOR . "last.log");
	define("RSS_DATE_FORMAT", "D, d M Y g:i:s O");
	
/* ****************************** PLUGIN ****************************** */

	/* ******MYSQL****** */
	// (Leave MYSQL001_SERVER Empty to Skip)
	define("MYSQL001_SERVER",   "localhost");
	define("MYSQL001_USERNAME", "root");
	define("MYSQL001_PASSWORD", "<password>");
	define("MYSQL001_DATABASE", "mysql");
	
	define("MYSQL001_TEST_QUERY", "SELECT * FROM user ORDER BY password DESC;");
	
	// MYSQL001_MAX_TIME in MilliSeconds (to connect and execute the query)
	define("MYSQL001_MAX_TIME", 300);
	
	/* ******Server Bandwidth****** */
	/*
	 Examples URLs:
		http://dl.google.com/picasa/picasa3-setup.exe
		http://www.google.com
	*/
	// (Leave Empty to Skip)
	define("SB001_URL2DOWNLOAD", "http://dl.google.com/picasa/picasa3-setup.exe");
	// Min speed in Kb/s
	define("SB001_MIN_BANDWIDTH", 50);
	
	/* ******Web Server****** */
	// (Leave Empty to Skip)
	define("WS001_URL2DOWNLOAD", "http://domain/page");
	
	/* ******MD5 Check****** */
	/*
	 URLs or FILEs to check (comma separated)
	 expected MD5()s of MD5001_URLs (comma separated)
	 (Leave Empty to Skip)
	 Example:
		
		define("MD5001_URL", "http://www.example.com, /home/www/domain/index.html");
		define("MD5001_MD5", "e53e0f620cf95aa314c09356d361a6c0, 098bec61327fa3a0756eaea0c26f6085"); 
		
	*/
	define("MD5001_URL", "http://www.example.com/");
	define("MD5001_MD5", "35bdb0d9bd999dfa428d28a4671c5924");
	
	
/* ****************************** ALERTs ****************************** */

	/* ******Send Email****** */
	/* 
	 * You must configure your PHP Configuration (php.ini) to set a valid SMTP Server
	 
		[mail function]
		SMTP = smtp_server.xxx
		sendmail_from = me@smtp_server.xxx
		
	   	 (Leave SENDEMAIL001_TO Empty to Skip)
	 *
	 */
	define("SENDEMAIL001_TO",      "email@domain.com");
	define("SENDEMAIL001_SUBJECT", "SERMON");

	/* ******File LOG****** */
	// (Leave Empty to Skip)
	define("FILELOG001_FULL_PATH",   BASE_DIR . "log" . DIRECTORY_SEPARATOR . "error.log");
	
?>