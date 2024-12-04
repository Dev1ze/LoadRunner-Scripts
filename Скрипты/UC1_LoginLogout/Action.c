Action()
{
	lr_start_transaction("UC1_LoginLogout"); /*ÍÀ×ÀËÎ ÃËÀÂÍÎÉ ÒĞÀÍÇÀÊÖÈÈ*/
	web_websocket_send("ID=0", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1733281038421\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	
	web_reg_find("Text=Welcome to the Web Tours site", LAST); //Ïğîâåğêà íà óñïåøíûé âõîä íà ãë. ñòğàíèöó
	
	lr_start_transaction("OpenLandingPage"); /*ÍÀ×ÀËÎ ÏÅĞÅÕÎÄÀ ÍÀ ÃËÀÂÍÓŞ ÑÒĞÀÍÈÖÓ*/
	web_set_sockets_option("SSL_VERSION", "AUTO");
	web_add_header("Sec-Fetch-Dest", "document");
	web_add_header("Sec-Fetch-Site", "none");
	web_add_header("Priority", "u=0, i");
	web_add_auto_header("Sec-Fetch-Mode", "navigate");
	web_add_header("Sec-Fetch-User", "?1");
	web_add_auto_header("Upgrade-Insecure-Requests", "1");
	lr_think_time(14);
	web_url("WebTours", 
		"URL=http://127.0.0.1:1080/WebTours", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);
	web_add_auto_header("Priority", "u=4");
	web_add_auto_header("Sec-Fetch-Dest", "frame");
	web_add_auto_header("Sec-Fetch-Site", "same-origin");
	web_url("header.html", 
		"URL=http://127.0.0.1:1080/WebTours/header.html", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	web_revert_auto_header("Upgrade-Insecure-Requests");
	web_add_auto_header("Upgrade-Insecure-Requests", "1");
	
/*Correlation comment - Do not change!  Original value='140404.85508303HcccAHtpHDDDDDDDtDDDcpttit' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);
		
	web_url("welcome.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("OpenLandingPage",LR_AUTO); /*ÇÀÂÅĞØÅÍÈÅ ÏÅĞÅÕÎÄÀ ÍÀ ÃËÀÂÍÓŞ ÑÒĞÀÍÈÖÓ*/
	
	
	web_reg_find("Text=Welcome, <b>{userName}</b>, to the Web Tours reservation pages", LAST); //Ïğîâåğêà íà óñïåøíîñòü àâòîğèçàöèè 
	
	
	lr_start_transaction("Login"); 	/*ÍÀ×ÀËÎ ÀÂÒÎĞÈÇÀÖÈÈ*/
	web_add_header("Origin", "http://127.0.0.1:1080");
	web_add_auto_header("Sec-Fetch-User", "?1");
	lr_think_time(25);
	web_submit_data("login.pl",
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t5.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={userName}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=52", ENDITEM,
		"Name=login.y", "Value=12", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);
	lr_end_transaction("Login",LR_AUTO); /*ÇÀÂĞÅØÅÍÈÅ ÀÂÒÎĞÈÇÀÖÈÈ*/
	
	
	web_reg_find("Text=please enter your account information",LAST); //Ïğîâåğêà íà âûõîä èç àêêàóíòà
	
	
	lr_start_transaction("SIGNOFF"); /*ÍÀ×ÀËÎ SIGN OFF*/
	web_revert_auto_header("Sec-Fetch-User");
	lr_think_time(4);
	web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("SIGNOFF",LR_AUTO); /*ÇÀÂĞÅØÅÍÈÅ SIGN OFF*/
	lr_think_time(7);
	web_websocket_close("ID=0", "Code=1000", LAST);
	
	
	
 	lr_end_transaction("UC1_LoginLogout", LR_AUTO); /*ÊÎÍÅÖ ÃËÀÂÍÎÉ ÒĞÀÍÇÀÊÖÈÈ*/
 	return 0;
}