Action()
{
	char departCity[100];
	char arriveCity[100];
	char _numPassangers[50];
	
	/*ÍÀ×ÀËÎ ÃËÀÂÍÎÉ ÑÒĞÀÍÇÀÊÖÈÈ*/
	/*--------------------------*/
	lr_start_transaction("UC2_SearchTicket");

	
	/*ÍÀ×ÀËÎ ÏÅĞÅÕÎÄÀ ÍÀ ÃËÀÂÍÓŞ ÑÒĞÀÍÈÖÓ*/
	/*-----------------------------------*/
	lr_start_transaction("OpenLandingPage");
	/*Ïğîâåğêà íà óñïåøíóş âõîä íà ñòğàíèöó*/
	/*-------------------------------------*/
	web_reg_find("Text=Welcome to the Web Tours site", LAST);
	/*-------------------------------------*/
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
	/*ÇÀÂÅĞØÅÍÈÅ ÏÅĞÅÕÎÄÀ ÍÀ ÃËÀÂÍÓŞ ÑÒĞÀÍÈÖÓ*/
	
	
	/*ÍÀ×ÀËÎ ÀÂÒÎĞÈÈÇÀÖÈÈ*/
	/*-------------------*/
	lr_start_transaction("Login");
	/*Ïğîâåğêà íà óñïåøíóş àâòîğèçàöèş*/
	/*--------------------------------*/
	web_reg_find("Text=Welcome, <b>{userName}</b>, to the Web Tours reservation pages", LAST);
	/*--------------------------------*/
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
	/*ÊÎÍÅÖ ÀÂÒÎĞÈÈÇÀÖÈÈ*/

	
	/*ÍÀ×ÀËÎ ÎÒÊĞÛÒÈß ÑÒĞÀÍÈÖÛ ÏÎÈÑÊÀ ÁÈËÅÒÀ*/
	/*--------------------------------------*/
	lr_start_transaction("OpenPage_FindFlights");
	/*Ïğîâåğêà íà óñïåøíóş îòêğûòèå ñòğàíèöû ïîèñêà áèëåòà*/
	/*----------------------------------------------------*/
	web_reg_find("Text=Find Flight", LAST);
	/*----------------------------------------------------*/
	web_add_auto_header("Sec-Fetch-User", "?1");
	lr_think_time(27);
	/*Correlation comment - Do not change!  Original value='12/05/2024' Name ='departDate' Type ='RecordReplay'*/
	web_reg_save_param_attrib(
		"ParamName=departDate",
		"TagName=input",
		"Extract=value",
		"Name=departDate",
		"Type=text",
		SEARCH_FILTERS,
		"RequestUrl=*/reservations.pl*",
		LAST);

	/*Correlation comment - Do not change!  Original value='12/06/2024' Name ='returnDate' Type ='RecordReplay'*/
	web_reg_save_param_attrib(
		"ParamName=returnDate",
		"TagName=input",
		"Extract=value",
		"Name=returnDate",
		"Type=text",
		SEARCH_FILTERS,
		"RequestUrl=*/reservations.pl*",
		LAST);

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
	/*ÊÎÍÅÖ ÎÒÊĞÛÒÈß ÑÒĞÀÍÈÖÛ ÏÎÈÑÊÀ ÁÈËÅÒÀ*/
	

	
	/*ÒĞÀÍÇÀÊÖÈß ÂÛÁÎĞÀ ÊÎÍÊĞÅÒÍÎÃÎ ĞÅÉÑÀ*/
	/*-----------------------*/
	/*Ïğîâåğêà íà íå ñîâïàäåíèå ãîğîäîâ*/
	lr_set_debug_message(LR_MSG_CLASS_FULL_TRACE, LR_SWITCH_ON);
	strcpy(departCity, lr_eval_string("{depart}"));
	do 
	{ 
		strcpy(arriveCity, lr_eval_string("{arrive}"));
	} 
	while (strcmp(departCity, arriveCity) == 0);
	lr_save_string(departCity, "departCity");
	lr_save_string(arriveCity, "arriveCity");
	lr_output_message("Selected Depart City: %s", departCity);
	lr_output_message("Selected Arrive City: %s", arriveCity);
	/*---------------------------------*/
	lr_start_transaction("SubmitFlight");
	/*Ïğîâåğêà êîğğåêòíîñòè âûáğàííûõ ïóíêòîâ */
	web_reg_find("Text=Flight departing from <B>{departCity}</B> to <B>{arriveCity}</B> on <B>{departDate}</B>",LAST);
	/*----------------------------------------*/
	strcpy(_numPassangers, lr_eval_string("{numPassengers}"));
	lr_save_string(_numPassangers, "_numPassangers");
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
		"Name=depart", "Value={departCity}", ENDITEM,
		"Name=departDate", "Value={departDate}", ENDITEM,
		"Name=arrive", "Value={arriveCity}", ENDITEM,
		"Name=returnDate", "Value={returnDate}", ENDITEM,
		"Name=numPassengers", "Value={_numPassangers}", ENDITEM,
		"Name=seatPref", "Value={seatingPreference}", ENDITEM,
		"Name=seatType", "Value={typeSeat}", ENDITEM,
		"Name=findFlights.x", "Value=59", ENDITEM,
		"Name=findFlights.y", "Value=3", ENDITEM,
		"Name=.cgifields", "Value=roundtrip", ENDITEM,
		"Name=.cgifields", "Value=seatType", ENDITEM,
		"Name=.cgifields", "Value=seatPref", ENDITEM,
		LAST);
	lr_end_transaction("SubmitFlight",LR_AUTO);
	/*-----------------------*/
	/*ÊÎÍÅÖ ÒĞÀÍÇÀÊÖÈÈ ÂÛÁÎĞÀ ÊÎÍÊĞÅÒÍÎÃÎ ĞÅÉÑÀ*/
	
	
	lr_end_transaction("UC2_SearchTicket", LR_AUTO);
	/*-------------------------*/
	/*ÊÎÍÅÖ ÃËÀÂÍÎÉ ÒĞÀÍÇÀÊÖÈÈ*/

	return 0;
}