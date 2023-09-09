#include "WebServer.h"

void Bas::WebServer::printControlPage(WiFiClient& client, IPAddress localIpAddress, uint8_t hours, uint8_t minutes, float constantSpeed, uint8_t startHours, uint8_t startMinutes, float variableStartSpeed, uint8_t endHours, uint8_t endMinutes, float variableEndSpeed)
{
	printPageHeader(client, "Sanatorium Zonnegloren: De Klok");

	client.print("\n"\
		"    <table class=\"deviceData\">\n"\
		"        <tr>\n"\
		"            <td>IP-adres:</td>\n"\
		"            <td>");
	client.print(localIpAddress);
	client.print("</td> \n"\
		"        </tr>\n"\
		"        <tr>\n"\
		"            <td>Huidige tijd:</td>\n"\
		"            <td>");
	
	char paddedHours[3];
	sprintf(paddedHours, "%02d", hours);
	client.print(paddedHours);
	
	client.print(":");
	
	char paddedMinutes[3];
	sprintf(paddedMinutes, "%02d", minutes);
	client.print(paddedMinutes);
	client.print("</td> \n"\
		"        </tr>\n"\
		"        <tr>\n"\
		"            <td>Huidige snelheid:</td>\n"\
		"            <td>");
	client.print(constantSpeed);
	client.print("</td>\n"\
		"        </tr>\n"\
		"\n"\
		"        <tr>\n"\
		"            <td>Variabele snelheid:</td>\n"\
		"            <td>tussen <strong>"); 
	
	char paddedStartHours[3];
	sprintf(paddedStartHours, "%02d", startHours);
	client.print(paddedStartHours);
	
	client.print(":");
	
	char paddedStartMinutes[3];
	sprintf(paddedStartMinutes, "%02d", startMinutes);
	client.print(paddedStartMinutes);

	client.print("</strong> en <strong>"); 

	char paddedEndHours[3];
	sprintf(paddedEndHours, "%02d", endHours);
	client.print(paddedEndHours);

	client.print(":");

	char paddedEndMinutes[3];
	sprintf(paddedEndMinutes, "%02d", endMinutes);
	client.print(paddedEndMinutes);

	client.print("</strong> van <strong>");
	client.print(variableStartSpeed);
	client.print("</strong> naar <strong>");
	client.print(variableEndSpeed);
	client.print("</strong>.</td>\n"\
		"        </tr>\n"\
		"    </table>\n"\
		"\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Tijd</legend>\n"\
		"            <input type=\"time\" id=\"time\" name=\"time\" value=\""); 
	
	client.print(paddedHours);
	client.print(":");
	client.print(paddedMinutes);

	client.print("\">\n"\
		"            <button name=\"submit\" value=\"timeForm\" type=\"submit\">Tijd aanpassen</button>\n"\
		"        </fieldset>\n"\
		"    </form>\n"\
		"\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Snelheid</legend>\n"\
		"            <input type=\"number\" maxlength=\"10\" id=\"speed\" name=\"speed\" class=\"speed\" value=\""); 

	client.print(constantSpeed);

	client.print("\">\n"\
		"            <button name=\"submit\" value=\"speedForm\" type=\"submit\">Snelheid aanpassen</button>\n"\
		"            <p class=\"explanation\">Het aantal seconden per seconde, mag negatief zijn. 1 = normaal, -1 is normaal maar achteruit, 0.5 is half zo snel als normaal, enzovoort.</p>\n"\
		"            <p class=\"explanation\">Deze snelheid wordt niet gebruikt als een variabele snelheid (zie hieronder) actief is!</p>\n"\
		"        </fieldset>\n"\
		"    </form>\n"\
		"\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Variabele snelheid</legend>\n"\
		"            <p>\n"\
		"                Van\n"\
		"                <input type=\"time\" id=\"startTime\" name=\"startTime\" value=\""); 

	client.print(paddedStartHours);
	client.print(":");
	client.print(paddedStartMinutes);

	client.print("\" title=\"startTijd\" placeholder=\""); 
	
	client.print(paddedStartHours);
	client.print(":");
	client.print(paddedStartMinutes);
		
	client.print("\">\n"\
		"                tot\n"\
		"                <input type=\"time\" id=\"endTime\" name=\"endTime\" value=\""); 

	client.print(paddedEndHours);
	client.print(":");
	client.print(paddedEndMinutes);

	client.print("\" title=\"eindtijd\" placeholder=\"");
	
	client.print(paddedEndHours);
	client.print(":");
	client.print(paddedEndMinutes);

	client.print("\">\n"\
		"                moet de snelheid lineair aangepast worden van\n"\
		"                <input type=\"number\" maxlength=\"10\" id=\"startSpeed\" name=\"startSpeed\" class=\"speed\" value=\""); 
	
	client.print(variableStartSpeed);
	client.print("\" title=\"startsnelheid\" placeholder=\""); 
	client.print(variableStartSpeed);

	client.print("\">\n"\
		"                naar\n"\
		"                <input type=\"number\" maxlength=\"10\" id=\"endSpeed\" name=\"endSpeed\" class=\"speed\" value=\""); 
	
	client.print(variableEndSpeed);
	client.print("\" title=\"eindsnelheid\" placeholder=\""); 
	client.print(variableEndSpeed);
	client.print("\">.\n"\
		"                <button name=\"submit\" value=\"variableSpeedForm\" type=\"submit\">Snelheid aanpassen</button>\n"\
		"            </p>\n"\
		"        </fieldset>\n"\
		"    </form>\n"\
		"\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Kalibratie</legend>\n"\
		"            <label for=\"calibrationTime\" class=\"explanation\">Vul de tijd in die de klok nu weergeeft:</label>\n"\
		"            <input type=\"time\" id=\"calibrationTime\" name=\"calibrationTime\" value=\""); 

	client.print(paddedHours);
	client.print(":");
	client.print(paddedMinutes);
	
	client.print("\" />\n"\
		"            <button name=\"submit\" value=\"calibrationForm\" type=\"submit\">Kalibreren</button>\n"\
		"            <p class=\"explanation\">Als de klok niet de verwachte tijd aangeeft moet hij mogelijk gekalibreerd worden. Vul de tijd in die de wijzers op dit moment aangeven en klik op \"Kalibreren\".</p>\n"\
		"        </fieldset>\n"\
		"    </form>\n");

	printPageFooter(client);
}