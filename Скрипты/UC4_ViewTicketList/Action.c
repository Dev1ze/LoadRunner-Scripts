Action()
{
	/*КОНЕЦ ГЛАВНОЙ ТРАНЗАКЦИИ*/
	/*------------------------*/
	lr_start_transaction("UC4_ViewTicketList");

	/*НАЧАЛО ОТКРЫТИЯ ГЛАВНОЙ СТРАНИЦИ*/
    /*--------------------------------*/
	lr_start_transaction("OpenLandingPage");
	
	/*Проверка на успешную вход на страницу*/
	web_reg_find("Text=Welcome to the Web Tours site", LAST);
	/*-------------------------------------*/
	
	web_set_sockets_option("SSL_VERSION", "AUTO");
	web_add_auto_header("Sec-Fetch-Dest", "document");
	web_add_auto_header("Sec-Fetch-Site", "none");
	web_add_auto_header("Priority", "u=0, i");
	web_add_auto_header("Sec-Fetch-Mode", "navigate");
	web_add_auto_header("Sec-Fetch-User", "?1");
	web_add_auto_header("Upgrade-Insecure-Requests", "1");
	
	/*Correlation comment - Do not change!  Original value='140413.998298906HcccftfpADHftDDDfpcHAccf' Name ='userSession' Type ='ResponseBased'*/
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
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("OpenLandingPage",LR_AUTO);
	/*-------------------------------*/
	/*КОНЕЦ ОТКРЫТИЯ ГЛАВНОЙ СТРАНИЦИ*/
	
	
	lr_think_time(5);
	
	
	/*АВТОРИЗАЦИЯ*/
    /*-----------*/
	lr_start_transaction("Login");
	
	/*Проверка на успешную авторизацию*/
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
		"Snapshot=t3.inf",
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
	/*-----------*/
	/*АВТОРИЗАЦИЯ*/
	
	
	lr_think_time(5);
	
	
	/*ПРОСМОТР СПИСКА БИЛЕТОВ*/
	/*-----------------------*/
	/*Проверка на успешный переход на страницу со списком*/
	/*---------------------------------------------------*/
	web_reg_find("Text=Itinerary", LAST);
	/*---------------------------------------------------*/
	
	lr_start_transaction("ViewTicketList");
	web_add_header("Sec-Fetch-User", "?1");
	web_add_header("Upgrade-Insecure-Requests", "1");
	web_url("Itinerary Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("ViewTicketList",LR_AUTO);
	/*-----------------------*/
	/*ПРОСМОТР СПИСКА БИЛЕТОВ*/
	
	
	lr_think_time(5);
	
	
	/*ВЫХОД ИЗ АККАУНТА*/
	/*-----------------*/
	lr_start_transaction("SignOff");
	/*Проверка на вызод из аккаунта*/
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
	/*ВЫХОД ИЗ АККАУНТА*/

	
	
	lr_end_transaction("UC4_ViewTicketList", LR_AUTO);
	/*------------------------*/
	/*КОНЕЦ ГЛАВНОЙ ТРАНЗАКЦИИ*/
 
	return 0;
}
