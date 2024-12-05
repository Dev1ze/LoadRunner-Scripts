Action()
{
	/*Õ¿◊¿ÀŒ √À¿¬ÕŒ… —“–¿Õ«¿ ÷»»*/
	/*--------------------------*/
	lr_start_transaction("UC2_SearchTicket");

	/*Õ¿◊¿ÀŒ œ≈–≈’Œƒ¿ Õ¿ √À¿¬Õ”ﬁ —“–¿Õ»÷”*/
	/*-----------------------------------*/
	lr_start_transaction("OpenLandingPage"); 
	web_set_sockets_option("SSL_VERSION", "AUTO");
	web_add_auto_header("Sec-Fetch-Dest", "document");
	web_add_auto_header("Sec-Fetch-Site", "none");
	web_add_auto_header("Priority", "u=0, i");
	web_add_auto_header("Sec-Fetch-Mode", "navigate");
	web_add_auto_header("Sec-Fetch-User", "?1");
	web_add_auto_header("Upgrade-Insecure-Requests", "1");
	/*Correlation comment - Do not change!  Original value='140408.070797894HcccctApVtVzzzzHtDDDDpttAif' Name ='userSession' Type ='ResponseBased'*/
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
	
	web_url("WebTours", 
		"URL=http://127.0.0.1:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	web_websocket_send("ID=0", "Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1733335428139\\\"\"},\"use_webpush\":true}", "IsBinary=0", LAST);
	/*Connection ID 0 received buffer WebSocketReceive0*/
	lr_end_transaction("OpenLandingPage",LR_AUTO);
	/*---------------------------------------*/
	/*«¿¬≈–ÿ≈Õ»≈ œ≈–≈’Œƒ¿ Õ¿ √À¿¬Õ”ﬁ —“–¿Õ»÷”*/
	
	
	/*Õ¿◊¿ÀŒ ¿¬“Œ–»»«¿÷»»*/
	/*-------------------*/
	lr_start_transaction("Login");
	web_revert_auto_header("Sec-Fetch-User");
	web_add_header("Origin", "http://127.0.0.1:1080");
	web_add_auto_header("Priority", "u=4");
	web_add_auto_header("Sec-Fetch-Dest", "frame");
	web_add_auto_header("Sec-Fetch-Site", "same-origin");
	lr_think_time(8);
	web_submit_data("login.pl",
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={userName}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=36", ENDITEM,
		"Name=login.y", "Value=12", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);
	lr_end_transaction("Login",LR_AUTO); 
	/*------------------*/
	/* ŒÕ≈÷ ¿¬“Œ–»»«¿÷»»*/

	
	/*Õ¿◊¿ÀŒ Œ“ –€“»ﬂ —“–¿Õ»÷€ œŒ»— ¿ ¡»À≈“¿*/
	/*--------------------------------------*/
	lr_start_transaction("OpenPage_FindFlights");
	
	web_set_max_html_param_len("2048000");
	web_reg_save_param_ex(
	    "ParamName=ArriveDropdown",
	    "LB=\<select name\=\"depart\" \>\n",
	    "RB=\<option",
	    "Ordinal=1",
	    LAST);
	
	web_reg_save_param_ex(
    	"ParamName=ArriveCityList",
    	"LB=<option value=\"",
    	"RB=\">",
    	"SourceString={ArriveDropdown}",
    	"Ordinal=All",
    	LAST);

	
	web_add_auto_header("Sec-Fetch-User", "?1");
	lr_think_time(27);
	web_url("Search Flights Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("OpenPage_FindFlights",LR_AUTO);
	/*-------------------------------------*/
	/* ŒÕ≈÷ Œ“ –€“»ﬂ —“–¿Õ»÷€ œŒ»— ¿ ¡»À≈“¿*/
	
	
	/*¬€¡Œ–  ŒÕ –≈“ÕŒ√Œ –≈…—¿*/
	/*-----------------------*/
	lr_start_transaction("SubmitFlight");
	web_add_header("Origin", "http://127.0.0.1:1080");
	web_submit_data("reservations.pl", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value=Denver", ENDITEM, 
		"Name=departDate", "Value=12/05/2024", ENDITEM, 
		"Name=arrive", "Value=London", ENDITEM, 
		"Name=returnDate", "Value=12/06/2024", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=seatType", "Value=Coach", ENDITEM, 
		"Name=findFlights.x", "Value=59", ENDITEM, 
		"Name=findFlights.y", "Value=3", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);
	lr_end_transaction("SubmitFlight",LR_AUTO);
	/*-----------------------*/
	/*¬€¡Œ–  ŒÕ –≈“ÕŒ√Œ –≈…—¿*/
	
	
	lr_end_transaction("UC2_SearchTicket", LR_AUTO);
	/*-------------------------*/
	/* ŒÕ≈÷ √À¿¬ÕŒ… “–¿Õ«¿ ÷»»*/

	return 0;
}