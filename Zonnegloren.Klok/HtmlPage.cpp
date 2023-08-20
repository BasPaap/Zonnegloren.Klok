#include "WebServer.h"

void Bas::WebServer::printPageHeader(WiFiClient& client, const char* title)
{
	client.print("<!DOCTYPE html>\n"\
		"\n"\
		"<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">\n"\
		"<head>\n"\
		"    <meta charset=\"utf-8\" />\n"\
		"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
		"    <title>");
	
	client.print(title);

	client.print("</title>\n"\
		"\n"\
		"    <style>\n"\
		"        body {\n"\
		"            background-color: darkslategray;\n"\
		"            color: white;\n"\
		"            font-size: 16px;\n"\
		"            font-family: Verdana, Geneva, Tahoma, sans-serif;\n"\
		"            margin-left: 5%;\n"\
		"            margin-right: 5%;\n"\
		"        }\n"\
		"\n"\
		"        progress {\n"\
		"            width: 80%;\n"\
		"            margin-top: 30px;\n"\
		"        }\n"\
		"\n"\
		"        .centered {\n"\
		"            text-align: center;\n"\
		"        }\n"\
		"\n"\
		"        h1, h2, h3 {\n"\
		"            text-align: center;\n"\
		"        }\n"\
		"\n"\
		"        h3 {\n"\
		"            margin-bottom: 0px;\n"\
		"        }\n"\
		"\n"\
		"        h1 {\n"\
		"            margin-top: 0px;\n"\
		"            margin-bottom: 5px;\n"\
		"        }\n"\
		"\n"\
		"        h4 {\n"\
		"            margin-top: 40px;\n"\
		"        }\n"\
		"\n"\
		"        .setting {\n"\
		"            font-weight: bold;\n"\
		"            font-family: monospace, monospace\n"\
		"        }\n"\
		"\n"\
		"        #domainName {\n"\
		"            text-align: right;\n"\
		"        }\n"\
		"\n"\
		"        .domainElements {\n"\
		"            white-space: nowrap;\n"\
		"        }\n"\
		"\n"\
		"        .submitButton {\n"\
		"            padding: 10px;\n"\
		"        }\n"\
		"\n"\
		"        fieldset {\n"\
		"            margin-top: 5px;\n"\
		"            margin-bottom: 5px;\n"\
		"        }\n"\
		"\n"\
		"        .hidden {\n"\
		"            display: none;\n"\
		"        }\n"\
		"\n"\
		"        .visible {\n"\
		"            display: block;\n"\
		"        }\n"\
		"\n"\
		"        .deviceData {\n"\
		"            margin-top: 10px;\n"\
		"            font-size: smaller\n"\
		"        }\n"\
		"\n"\
		"        form {\n"\
		"            margin-top: 20px;\n"\
		"        }\n"\
		"\n"\
		"        .explanation {\n"\
		"            font-size: smaller;\n"\
		"        }\n"\
		"\n"\
		"        .speed {\n"\
		"            width: 10%;\n"\
		"        }\n"\
		"    </style>\n"\
		"</head>\n"\
		"<body>\n"\
		"    <h3>Sanatorium Zonnegloren</h3>\n"\
		"    <h1>De Klok</h1>\n");
}

void Bas::WebServer::printPageFooter(WiFiClient& client)
{
	client.print("</body>\n"\
		"</html>");
}