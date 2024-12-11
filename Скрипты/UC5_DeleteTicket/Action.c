Action()
{
	int i;
	
	/*������ ������� ����������*/
    /*-------------------------*/
	lr_start_transaction("UC5_DeleteTicket");

	/*�������� ������� ��������*/
    /*-------------------------*/
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
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	web_websocket_send("ID=1", 
		"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1733540230607\\\"\"},\"use_webpush\":true}", 
		"IsBinary=0", 
		LAST);
	/*Connection ID 1 received buffer WebSocketReceive0*/
	lr_end_transaction("OpenLandingPage", LR_AUTO);
    /*-------------------------*/
	/*�������� ������� ��������*/

	
	lr_think_time(5);	
	
	
	/*������ �����������*/
    /*------------------*/
	lr_start_transaction("Login");
	/*�������� �� �������� �����������*/
	web_reg_find("Text=Welcome, <b>{userName}</b>, to the Web Tours reservation pages", LAST);
	/*--------------------------------*/
	web_revert_auto_header("Sec-Fetch-User");
	web_add_header("Origin", "http://127.0.0.1:1080");
	web_add_auto_header("Priority", "u=4");
	web_add_auto_header("Sec-Fetch-Dest", "frame");
	web_add_auto_header("Sec-Fetch-Site", "same-origin");
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
		"Name=login.x", "Value=67", ENDITEM, 
		"Name=login.y", "Value=9", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);
	lr_end_transaction("Login",LR_AUTO);
    /*-----------------*/
	/*����� �����������*/
	
	
	lr_think_time(5);	

	
	/*������� �� �������� ������� ������*/
    /*----------------------------------*/
	lr_start_transaction("Litinerary");
	/*�������� �� ������� �� �������� ������� ������*/
	web_reg_find("Text=Itinerary", LAST);
	/*----------------------------------------------*/
	web_add_auto_header("Sec-Fetch-User", "?1");
	web_reg_save_param("c_flightids",
    	"lb=<input type=\"hidden\" name=\"flightID\" value=\"",
    	"rb=\"  />",
    	"ord=all",
    	LAST);
    web_reg_save_param("c_cgifields",
    	"lb=<input type=\"hidden\" name=\".cgifields\" value=\"",
   		"rb=\"  />",
    	"ord=all",	
    	LAST);
	web_url("Itinerary Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("Litinerary",LR_AUTO);
    /*----------------------------------*/
	/*������� �� �������� ������� ������*/
	
	
	lr_think_time(5);	
	
	
 	/*������������ ���� ��� �������� �������� ������*/
	/*----------------------------------------------*/
	lr_save_string("", "c_buffer"); //c_buffer ����� ������ �������� � ������� "flightID=����������&.cgifields=�����������&flightID=����������&.cgifields=�����������&... � �.�"
	lr_param_sprintf("c_buffer","%s%s=on&", lr_eval_string("{c_buffer}"), lr_eval_string("{c_flightids_count}")); //������ ��������� �������. ������� ������� � �������� �������� cgifields (1) ������� ��� x=on& ��������(1=on&)
	for (i = 1; i <= atoi(lr_eval_string("{c_flightids_count}")); i++) //��������� ���� - c_buffer
    {
        lr_param_sprintf("c_buffer", "%sflightID=%s&", lr_eval_string("{c_buffer}"), lr_paramarr_idx("c_flightids", i));
        lr_param_sprintf("c_buffer", "%s.cgifields=%s&", lr_eval_string("{c_buffer}"), lr_paramarr_idx("c_cgifields", i));
    }
    lr_save_string(lr_eval_string("{c_buffer}removeFlights.x=36&removeFlights.y=4"), "c_wcr"); //� c_buffer ��������� �������� removeFlights.x=36&removeFlights.y=4 � ���������� � ���������� c_wcr
    /*----------------------------------------------*/
    
    
 	/*�������� �������� �����*/
	/*-----------------------*/    
	lr_start_transaction("DeleteTicket");
	/*�������� �� ���������� ���������� ������*/
	lr_param_sprintf(lr_eval_string(lr_eval_string("{c_flightids_{c_flightids_count}}")),"deletedTicket");
	web_reg_find("Text={deletedTicket}", "Fail=Found", LAST);
	/*----------------------------------------*/   
	web_add_header("Origin", "http://127.0.0.1:1080");
    web_custom_request("itinerary.pl_2",
        "URL=http://127.0.0.1:1080/cgi-bin/itinerary.pl",
        "Method=POST",
        "Resource=0",
        "RecContentType=text/html",
        "Referer=http://127.0.0.1:1080/cgi-bin/itinerary.pl",
        "Snapshot=t23.inf",
        "Mode=HTTP",
        "Body={c_wcr}", //���������� c_wcr
        LAST);
	lr_end_transaction("DeleteTicket",LR_AUTO);
	/*-----------------------*/  
 	/*�������� �������� �����*/
 	
 	
 	lr_think_time(5);	
 	
 	
 	/*����� �� ��������*/
	/*-----------------*/
	lr_start_transaction("SignOff");
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
	lr_end_transaction("SignOff",LR_AUTO);
	/*-----------------*/
	/*����� �� ��������*/
 	
	
 	
 	lr_end_transaction("UC5_DeleteTicket", LR_AUTO);
 	/*------------------------*/  
 	/*����� ������� ����������*/

	return 0;
}