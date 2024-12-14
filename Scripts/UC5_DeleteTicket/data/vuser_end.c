vuser_end()
{

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

	web_custom_request("WebTours", 
		"URL=http://127.0.0.1:1080/WebTours/", 
		"Method=GET", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t41.inf", 
		"Mode=HTTP", 
		LAST);

	web_add_auto_header("Priority", 
		"u=4");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	lr_think_time(15);

	web_custom_request("header.html", 
		"URL=http://127.0.0.1:1080/WebTours/header.html", 
		"Method=GET", 
		"Resource=0", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t42.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("welcome.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t43.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("home.html", 
		"URL=http://127.0.0.1:1080/WebTours/home.html", 
		"Method=GET", 
		"Resource=0", 
		"Referer=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t44.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t45.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_websocket_send("ID=2", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1733565016261\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 2 received buffer WebSocketReceive0*/

	web_add_header("Origin", 
		"http://127.0.0.1:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(10);

	web_custom_request("login.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t46.inf", 
		"Mode=HTTP", 
		"Body=userSession=140428.654759012HccDcQipQcQVzzzHtDDDQpHQDfHf&username=artemironman&password=12345&login.x=36&login.y=6&JSFormSubmit=off", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("nav.pl_2", 
		"URL=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Snapshot=t47.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("login.pl_2", 
		"URL=http://127.0.0.1:1080/cgi-bin/login.pl?intro=true", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Snapshot=t48.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_custom_request("Itinerary Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t49.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("itinerary.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/itinerary.pl", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t50.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl_3", 
		"URL=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t51.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_start_transaction("delete");

	web_add_header("Origin", 
		"http://127.0.0.1:1080");

	lr_think_time(36);

	web_custom_request("itinerary.pl_2", 
		"URL=http://127.0.0.1:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t52.inf", 
		"Mode=HTTP", 
		"Body=1=on&flightID=210311124-823-AK&flightID=210297416-1577-AK&removeFlights.x=30&removeFlights.y=7&.cgifields=1&.cgifields=2", 
		LAST);

	lr_end_transaction("delete",LR_AUTO);

	return 0;
}