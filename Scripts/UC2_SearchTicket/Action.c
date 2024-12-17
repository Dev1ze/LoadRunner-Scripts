Action()
{
	char departCity[100];
	char arriveCity[100];
	char _numPassengers[50];
	int numPassengersInt;
	int i, countTicket;
	char *randTicketId;
	char paramName[50];
    int randomValue;
    char *token; 
    char priceTicket[10];
    int priceTicketInt;
    int totalPrice;
    char totalPriceStr[10];
	
	/*������ ������� ����������*/
    /*-------------------------*/
	lr_start_transaction("UC2_SearchTicket");

	/*������ �������� ������� ��������*/
    /*--------------------------------*/
	lr_start_transaction("OpenLandingPage");
	/*�������� �� �������� ���� �� ��������*/
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
	/*-------------------------------*/
	/*����� �������� ������� ��������*/
	
	
	lr_think_time(5);
	

	web_websocket_send("ID=2", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1733335428139\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);
	
	/*������ ������������*/
	/*-------------------*/
	lr_start_transaction("Login");
	/*�������� �� �������� �����������*/
	/*--------------------------------*/
	web_reg_find("Text=Welcome, <b>{userName}</b>, to the Web Tours reservation pages", LAST);
	/*--------------------------------*/
	web_revert_auto_header("Origin");
	web_add_auto_header("Sec-Fetch-User", "?1");
	web_submit_data("login.pl_2",
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
		"Name=login.x", "Value=48", ENDITEM,
		"Name=login.y", "Value=13", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);
	lr_end_transaction("Login",LR_AUTO);
	/*-----------------*/
	/*����� �����������*/
	
	
	lr_think_time(5);

	
	/*������ �������� �������� ������ ������*/
	/*--------------------------------------*/
	lr_start_transaction("OpenPage_FindFlight");
	/*�������� �� �������� �������� �������� ������ ������*/
	/*----------------------------------------------------*/
	web_reg_find("Text=Find Flight", LAST);
	/*----------------------------------------------------*/
	web_revert_auto_header("Sec-Fetch-User");
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
	lr_end_transaction("OpenPage_FindFlight",LR_AUTO);
	/*-------------------------------------*/
	/*����� �������� �������� ������ ������*/
	
	
	lr_think_time(5);
	
	
	/*������ ���� ��������� �������*/
	/*-----------------------------*/
	web_reg_save_param_regexp(
		"ParamName=idTicket",
		"RegExp=name\=\"outboundFlight\" value\=\"(.*?)\"",
		"Ordinal=ALL", // ������ ���� ����������
         LAST);
	/*-----------------------------*/
	
	
	/*���������� ������ ����������� �����*/
	/*-----------------------------------*/
	/*�������� �� �� ���������� �������*/
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
	/*�������� ������������ ��������� ������� */
	web_reg_find("Text=Flight departing from <B>{departCity}</B> to <B>{arriveCity}</B> on <B>{departDate}</B>",LAST);
	/*----------------------------------------*/
	strcpy(_numPassengers, lr_eval_string("{numPassengers}"));
	lr_save_string(_numPassengers, "_numPassengers");
	web_add_header("Origin", "http://127.0.0.1:1080");
	web_add_header("Sec-Fetch-User", "?1");
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
		"Name=numPassengers", "Value={_numPassengers}", ENDITEM, 
		"Name=seatPref", "Value={seatingPreference}", ENDITEM, 
		"Name=seatType", "Value={typeSeat}", ENDITEM, 
		"Name=findFlights.x", "Value=68", ENDITEM, 
		"Name=findFlights.y", "Value=6", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);
	lr_end_transaction("SubmitFlight",LR_AUTO);
	/*-----------------------------------------*/
	/*����� ���������� ������ ����������� �����*/
	
	
	lr_think_time(5);
	
	
	/*��������� ���������� id ������ �� ���� �� ��������*/
	/*--------------------------------------------------*/
	countTicket = atoi(lr_eval_string("{idTicket_count}"));
	srand(time(NULL));
    randomValue = (rand() % (countTicket - 0)) + 1;
    lr_output_message("Random  - %d", randomValue);
	sprintf(paramName, "{idTicket_%d}", randomValue);
	randTicketId = lr_eval_string(paramName); 
    lr_output_message("Random ticket - %s", randTicketId);
    lr_save_string(randTicketId, "randTicketId");
    /*--------------------------------------------------*/
    
    /*���������� ���� �� id ������*/
	/*----------------------------*/
	token = strtok(randTicketId, ";");
	token = strtok(NULL, ";");
	strcpy(priceTicket, token);
	lr_output_message("���� ������: %s", priceTicket);
	/*----------------------------*/
	
	/*������ ��� �������� ���� ������ �� ��������*/
	/*-------------------------------------------*/
	web_reg_save_param_regexp(
		"ParamName=totalPrice",
		"RegExp=\\$ (.*?)\<tr",
		"Ordinal=1",
         LAST);
	/*-------------------------------------------*/
	
	/*�������� �������� ���� ������*/
	/*-----------------------------*/
	priceTicketInt = atoi(priceTicket);
	numPassengersInt = atoi(_numPassengers);
	totalPrice = priceTicketInt * numPassengersInt;
	sprintf(totalPriceStr, "%d", totalPrice);
	lr_save_string(totalPriceStr, "totalPriceStr");
	lr_output_message("totalPriceStr - %s", totalPriceStr);
	web_reg_find("Text=Total for {_numPassengers} ticket(s) is \= $ {totalPriceStr}", LAST);
	/*-----------------------------*/
	
    /*���������� ������ ������� �����*/
	/*-------------------------------*/
	lr_start_transaction("�hooseDepartureTime");
	web_submit_data("reservations.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={randTicketId}", ENDITEM, 
		"Name=numPassengers", "Value={_numPassengers}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={typeSeat}", ENDITEM, 
		"Name=seatPref", "Value={seatingPreference}", ENDITEM, 
		"Name=reserveFlights.x", "Value=42", ENDITEM, 
		"Name=reserveFlights.y", "Value=9", ENDITEM, 
		LAST);
	lr_end_transaction("�hooseDepartureTime",LR_AUTO);
	/*-------------------------------------*/
	/*����� ���������� ������ ������� �����*/
	

	lr_think_time(5);
	
	
	/*����� �� ��������*/
	/*-----------------*/
	lr_start_transaction("Logout");
	/*�������� �� ����� �� ��������*/
	web_reg_find("Text=<B>sign up now</B></A> to get access to all our resources", LAST);
	/*-----------------------------*/
	web_revert_auto_header("Sec-Fetch-User");
	web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t24.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("Logout",LR_AUTO);
	   /*-----------------*/
	/*����� �� ��������*/
	
	
	lr_end_transaction("UC2_SearchTicket", LR_AUTO);
	/*-------------------------*/
	/*����� ������� ����������*/

	return 0;
}