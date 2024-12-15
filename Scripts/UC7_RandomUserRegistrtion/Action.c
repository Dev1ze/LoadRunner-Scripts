Action()
{
	int i,j;
	char randomString[11]; 
	int randomLength;
	int minLength = 4;
	int maxLength = 10; 
	char userDatas[6][10]; //userDatas[username][password][firstname][lastname][address1][address2]. [10] - максимальное число сиволов слова
	int vuserId;
	
	lr_whoami(&vuserId, NULL, NULL);

	// »нициализаци€ генератора случайных чисел с уникальным seed
	srand(time(NULL) + vuserId); 
	
	for (j = 0; j < 6; j ++) 
	{
		randomLength = (rand() % (maxLength - minLength + 1)) + minLength;
		lr_output_message("–андоное число %d", randomLength);
		for (i = 0; i < randomLength; i++) randomString[i] = (char)('A' + rand() % 26); //Ќачинаю с числа 65 (символ 'A') и делю его на случайное число от 0 до 25
		randomString[randomLength] = '\0'; 
		strcpy(userDatas[j], randomString);
		lr_save_string(userDatas[j], "userData");
		lr_output_message("Valuse %d - %s", j, lr_eval_string("{userData}"));
	}
	
	lr_save_string(userDatas[0], "userName");
	lr_save_string(userDatas[1], "password");
	lr_save_string(userDatas[2], "firstName");
	lr_save_string(userDatas[3], "lastName");
	lr_save_string(userDatas[4], "address1");
	lr_save_string(userDatas[5], "address2");

	
	lr_start_transaction("UC7_RandomUserRegistrtion");

	lr_start_transaction("OpenLandingPage");
	web_reg_find("Text=<B>sign up now</B></A> to get access to all our resources", LAST);
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
		"Snapshot=t6.inf", 
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
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	web_url("welcome.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);
	web_websocket_send("ID=0", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1733650816519\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);
	/*Connection ID 0 received buffer WebSocketReceive0*/
	lr_end_transaction("OpenLandingPage",LR_AUTO);

	
	lr_think_time(4);
	
	
	lr_start_transaction("OpenRegistrationPage");
	web_reg_find("Text=Customer Profile", LAST);
	web_add_auto_header("Sec-Fetch-User", "?1");
	web_url("login.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/home.html", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("OpenRegistrationPage",LR_AUTO);
	
	
	lr_think_time(4);
	
	
	lr_start_transaction("UserRegistered");
	lr_output_message("Current user name: %s", lr_eval_string("{userName}"));
	web_reg_find("Text=Thank you, <b>{userName}</b>, for registering and welcome to the Web Tours family", LAST);
	web_add_header("Origin", "http://127.0.0.1:1080");
	web_submit_data("login.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={userName}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=register.x", "Value=73", ENDITEM, 
		"Name=register.y", "Value=17", ENDITEM, 
		LAST);
	lr_end_transaction("UserRegistered",LR_AUTO);
	
	
	lr_think_time(4);
	

	lr_start_transaction("press continue");
	web_reg_find("Text=Welcome, <b>{userName}</b>, to the Web Tours reservation pages", LAST);
	web_revert_auto_header("Sec-Fetch-User");
	web_add_auto_header("Sec-Fetch-User", "?1");
	web_url("button_next.gif", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("press continue",LR_AUTO);
	
	
	lr_think_time(4);
	

	lr_start_transaction("SignOff");
	web_reg_find("Text=<B>sign up now</B></A> to get access to all our resources", LAST);
	web_revert_auto_header("Sec-Fetch-User");
	web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("SignOff",LR_AUTO);
	
	lr_end_transaction("UC7_RandomUserRegistrtion", LR_AUTO);

	return 0;
}