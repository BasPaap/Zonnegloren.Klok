#include "WebServer.h"

void Bas::WebServer::printFirstCalibrationPage(WiFiClient& client)
{
	printPageHeader(client, "Sanatorium Zonnegloren : De Klok - Eerste Kalibratie"); 
	client.print("    <h2>Eerste Kalibratie</h2>\n"\
		"    \n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Kalibratie</legend>\n"\
		"            <p class=\"explanation\">De klok is zojuist voor het eerst opgestart. Vul de tijd in die de wijzers <em>op dit moment</em> aangeven en klik op \"Kalibreren\".</p>\n"\
		"            <input type=\"time\" id=\"time\" name=\"time\" value=\"00:00\">\n"\
		"            <button name=\"submit\" value=\"firstCalibrationForm\" type=\"submit\">Kalibreren</button>\n"\
		"        </fieldset>\n"\
		"    </form>\n");

	printPageFooter(client);
}