Action()
{
	char userNameBuffer[100];
	char passwordBuffer[100];
	char passwordConfirmBuffer[100];
	char firtNameBuffer[100];
	char lastNameBuffer[100];
	char address1Buffer[100];
	char address2Buffer[100];
	
	char *filename = "../../data/users.dat";
	int countLines = 0;
	int iteration = 1;
	char buffer[1024];
	FILE *file = fopen(filename, "r");
	if (!file) 
	{
    	lr_output_message("Îøèáêà: íå óäàëîñü îòêğûòü ôàéë");
	}
	while (fgets(buffer, sizeof(buffer), file))
	{
	    countLines++;
	}
	lr_output_message("Êîëëè÷åñòâî %d", countLines-1);
	
	
	while(iteration < countLines)
	{
		strcpy(userNameBuffer, lr_eval_string("{userName}"));
		lr_save_string(userNameBuffer, "userNameBuffer");
		strcpy(passwordBuffer, lr_eval_string("{password}"));
		lr_save_string(passwordBuffer, "passwordBuffer");
		strcpy(passwordConfirmBuffer, lr_eval_string("{passwordConfirm}"));
		lr_save_string(passwordConfirmBuffer, "passwordConfirmBuffer");
		strcpy(firtNameBuffer, lr_eval_string("{firstName}"));
		lr_save_string(firtNameBuffer, "firtNameBuffer");
		strcpy(lastNameBuffer, lr_eval_string("{lastName}"));
		lr_save_string(lastNameBuffer, "lastNameBuffer");
		strcpy(address1Buffer, lr_eval_string("{address1}"));
		lr_save_string(address1Buffer, "address1Buffer");
		strcpy(address2Buffer, lr_eval_string("{address2}"));
		lr_save_string(address2Buffer, "address2Buffer");
			

		lr_output_message("Ğåãèñòğàöèÿ ¹%d", iteration);
		lr_output_message("Ïîëüçîâàòåëü ¹%s", userNameBuffer);
		
		/*ÍÀ×ÀËÎ ÎÒÊĞÛÒÈß ÃËÀÂÍÎÉ ÑÒĞÀÍÈÖÈ*/
	    /*--------------------------------*/
		lr_start_transaction("OpenLandingPage");
		/*Ïğîâåğêà íà îòêğûòèå ñòğàíèöû áåç àâòîğèçàöèè*/
		web_reg_find("Text=<B>sign up now</B></A> to get access to all our resources", LAST);
		/*---------------------------------------------*/
		web_set_sockets_option("SSL_VERSION", "AUTO");
		web_add_header("Sec-Fetch-Dest", "document");
		web_add_header("Sec-Fetch-Site", "none");
		web_add_header("Priority", "u=0, i");
		web_add_auto_header("Sec-Fetch-Mode", "navigate");
		web_add_header("Sec-Fetch-User", "?1");
		web_add_auto_header("Upgrade-Insecure-Requests", "1");
		web_url("WebTours", 
			"URL=http://127.0.0.1:1080/WebTours/", 
			"TargetFrame=", 
			"Resource=0", 
			"Referer=", 
			"Snapshot=t18.inf", 
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
			"Snapshot=t19.inf", 
			"Mode=HTML", 
			LAST);
		web_url("welcome.pl", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
			"TargetFrame=", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/WebTours/", 
			"Snapshot=t20.inf", 
			"Mode=HTML", 
			LAST);
		web_websocket_send("ID=2", 
			"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1733626630662\\\"\"},\"use_webpush\":true}", 
			"IsBinary=0", 
			LAST);
		/*Connection ID 2 received buffer WebSocketReceive0*/
		lr_end_transaction("OpenLandingPage",LR_AUTO);
		/*ÊÎÍÅÖ ÎÒÊĞÛÒÈß ÃËÀÂÍÎÉ ÑÒĞÀÍÈÖÈ*/
	    /*-------------------------------*/
		
		
		
		/*ÑÒĞÀÍÈÖÀ ĞÅÃÑÈÒĞÀÖÈÈ ÏÎËÜÇÎÂÀÒÅËß*/
	    /*---------------------------------*/
		lr_start_transaction("OpenRegistrationPage");
		web_add_auto_header("Sec-Fetch-User", "?1");
		lr_think_time(18);
		web_url("login.pl", 
			"URL=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/WebTours/home.html", 
			"Snapshot=t21.inf", 
			"Mode=HTML", 
			LAST);
		lr_end_transaction("OpenRegistrationPage",LR_AUTO);
	    /*---------------------------------*/
		/*ÑÒĞÀÍÈÖÀ ĞÅÃÑÈÒĞÀÖÈÈ ÏÎËÜÇÎÂÀÒÅËß*/
	
		
		
		/*ÎÒÏĞÀÂÊÀ ÄÀÍÍÛÕ ĞÅÃÑÈÒĞÀÖÈÈ ÏÎËÜÇÎÂÀÒÅËß*/
	    /*----------------------------------------*/
		lr_start_transaction("UserRegistered");
		/*Ïğîâåğêà óñïåøíîé ğåãèñòğàöèè*/
		web_reg_find("Text=Thank you, <b>{userNameBuffer}</b>, for registering and welcome to the Web Tours family", LAST);
		/*-----------------------------*/
		web_add_header("Origin", "http://127.0.0.1:1080");
		lr_think_time(47);
		web_submit_data("login.pl_2", 
			"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
			"Method=POST", 
			"TargetFrame=info", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
			"Snapshot=t22.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=username", "Value={userNameBuffer}", ENDITEM, 
			"Name=password", "Value={passwordBuffer}", ENDITEM, 
			"Name=passwordConfirm", "Value={passwordConfirmBuffer}", ENDITEM, 
			"Name=firstName", "Value={firstNameBuffer}", ENDITEM, 
			"Name=lastName", "Value={lastNameBuffer}", ENDITEM, 
			"Name=address1", "Value={address1Buffer}", ENDITEM, 
			"Name=address2", "Value={address2Buffer}", ENDITEM, 
			"Name=register.x", "Value=67", ENDITEM, 
			"Name=register.y", "Value=8", ENDITEM, 
			LAST);
		lr_end_transaction("UserRegistered",LR_AUTO);
		/*ÎÒÏĞÀÂÊÀ ÄÀÍÍÛÕ ĞÅÃÑÈÒĞÀÖÈÈ ÏÎËÜÇÎÂÀÒÅËß*/
	    /*----------------------------------------*/
		
		
	
		
		/*ÂÕÎÄ ÍÀ ÑÒĞÀÍÈÖÓ ÏÎÄ ÍÎÂÛÌ ÏÎËÜÇÎÂÀÒÅËÅÌ*/
	    /*----------------------------------------*/
		lr_start_transaction("press continue");
		/*Ïğîâåğêà íà óñïåøíûé âõîä ïîä íîâûì ïîëüçîâàòåëåì*/
		web_reg_find("Text=Welcome, <b>{userNameBuffer}</b>, to the Web Tours reservation pages", LAST);
		/*-------------------------------------------------*/
		web_revert_auto_header("Sec-Fetch-User");
		web_add_auto_header("Sec-Fetch-User", "?1");
		lr_think_time(23);
		web_url("button_next.gif", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=menus", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/login.pl", 
			"Snapshot=t23.inf", 
			"Mode=HTML", 
			LAST);
		lr_end_transaction("press continue",LR_AUTO);
	    /*----------------------------------------*/
		/*ÂÕÎÄ ÍÀ ÑÒĞÀÍÈÖÓ ÏÎÄ ÍÎÂÛÌ ÏÎËÜÇÎÂÀÒÅËÅÌ*/
	
		
		
		/*ÂÛÕÎÄ ÈÇ ÀÊÊÀÓÍÒÀ*/
	    /*-----------------*/
		lr_start_transaction("SignOff");
		/*Ïğîâåğêà íà âûçîä èç àêêàóíòà*/
		web_reg_find("Text=<B>sign up now</B></A> to get access to all our resources", LAST);
		/*-----------------------------*/
		web_revert_auto_header("Sec-Fetch-User");
		lr_think_time(22);
		web_url("SignOff Button", 
			"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
			"Snapshot=t24.inf", 
			"Mode=HTML", 
			LAST);
		lr_end_transaction("SignOff",LR_AUTO);
	    /*-----------------*/
		/*ÂÛÕÎÄ ÈÇ ÀÊÊÀÓÍÒÀ*/

		iteration++;
	}
	
	return 0;
}