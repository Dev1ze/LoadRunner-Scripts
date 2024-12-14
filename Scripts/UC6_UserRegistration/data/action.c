Action()
{

	lr_start_transaction("homepage");

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_header("Sec-Fetch-Dest", 
		"document");

	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_header("Priority", 
		"u=0, i");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://127.0.0.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("Priority", 
		"u=4");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

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

	lr_end_transaction("homepage",LR_AUTO);

	lr_start_transaction("registrPage");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

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

	lr_end_transaction("registrPage",LR_AUTO);

	lr_start_transaction("send registr data");

	web_add_header("Origin", 
		"http://127.0.0.1:1080");

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
		"Name=username", "Value=artem1998", ENDITEM, 
		"Name=password", "Value=12345", ENDITEM, 
		"Name=passwordConfirm", "Value=12345", ENDITEM, 
		"Name=firstName", "Value=Artem", ENDITEM, 
		"Name=lastName", "Value=Kleimenov", ENDITEM, 
		"Name=address1", "Value=Rahmaninova", ENDITEM, 
		"Name=address2", "Value=Penza Octabrs 440066", ENDITEM, 
		"Name=register.x", "Value=67", ENDITEM, 
		"Name=register.y", "Value=8", ENDITEM, 
		LAST);

	lr_end_transaction("send registr data",LR_AUTO);

	lr_start_transaction("press continue");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

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

	lr_start_transaction("sign of");

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

	lr_end_transaction("sign of",LR_AUTO);

	return 0;
}