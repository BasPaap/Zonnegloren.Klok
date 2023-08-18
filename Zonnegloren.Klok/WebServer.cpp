// 
// 
// 

#include "WebServer.h"

Bas::WebServer::WebServer(Configuration configuration) : configuration(configuration)
{
}

void Bas::WebServer::initialize()
{
	server.begin();
}

void Bas::WebServer::update()
{
	WiFiClient client = server.available();

	if (client)
	{
		Serial.println("Web server client available.");

		client.println("HTTP/1.1 200 OK");
		client.println("Content-type:text/html");
		client.println();
		client.print(this->html);
		client.println();
		client.stop();
	}
}

void Bas::WebServer::setPageToServe(const char* html)
{
	this->html = html;
}
