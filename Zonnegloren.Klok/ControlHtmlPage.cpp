#include "WebServer.h"

void Bas::WebServer::printControlPage(WiFiClient& client, IPAddress localIpAddress, uint8_t hours, uint8_t minutes, float constantSpeed, uint8_t startHours, uint8_t startMinutes, float variableStartSpeed, uint8_t endHours, uint8_t endMinutes, float variableEndSpeed)
{
	printPageHeader(client, "Sanatorium Zonnegloren: De Klok");

	client.print("\n"\
		"    <table class=\"deviceData\">\n"\
		"        <tr>\n"\
		"            <td>IP-adres:</td>\n"\
		"            <td>127.0.0.1</td>\n"\
		"        </tr>\n"\
		"        <tr>\n"\
		"            <td>Huidige tijd:</td>\n"\
		"            <td>04:20</td>\n"\
		"        </tr>\n"\
		"        <tr>\n"\
		"            <td>Huidige snelheid:</td>\n"\
		"            <td>1</td>\n"\
		"        </tr>\n"\
		"\n"\
		"        <tr>\n"\
		"            <td>Variabele snelheid:</td>\n"\
		"            <td>tussen <strong>4:20</strong> en <strong>4:20</strong> van <strong>1</strong> naar <strong>0.5</strong>.</td>\n"\
		"        </tr>\n"\
		"    </table>\n"\
		"\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Tijd</legend>\n"\
		"            <input type=\"time\" id=\"time\" name=\"time\" value=\"04:20\">\n"\
		"            <button name=\"submit\" value=\"timeForm\" type=\"submit\">Tijd aanpassen</button>\n"\
		"        </fieldset>\n"\
		"    </form>\n"\
		"\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Snelheid</legend>\n"\
		"            <input type=\"number\" maxlength=\"10\" id=\"speed\" name=\"speed\" class=\"speed\" value=\"1\">\n"\
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
		"                <input type=\"time\" id=\"startTime\" name=\"startTime\" value=\"04:20\" title=\"eindtijd\" placeholder=\"4:20\">\n"\
		"                tot\n"\
		"                <input type=\"time\" id=\"endTime\" name=\"endTime\" value=\"04:20\" title=\"starttijd\" placeholder=\"4:20\">\n"\
		"                moet de snelheid lineair aangepast worden van\n"\
		"                <input type=\"number\" maxlength=\"10\" id=\"startSpeed\" name=\"startSpeed\" class=\"speed\" value=\"1\" title=\"startsnelheid\" placeholder=\"1\">\n"\
		"                naar\n"\
		"                <input type=\"number\" maxlength=\"10\" id=\"endSpeed\" name=\"endSpeed\" class=\"speed\" value=\"0.5\" title=\"eindsnelheid\" placeholder=\"0.5\">.\n"\
		"                <button name=\"submit\" value=\"variableSpeedForm\" type=\"submit\">Snelheid aanpassen</button>\n"\
		"            </p>\n"\
		"        </fieldset>\n"\
		"    </form>\n"\
		"\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Kalibratie</legend>\n"\
		"            <label for=\"calibrationTime\" class=\"explanation\">Vul de tijd in die de klok nu weergeeft:</label>\n"\
		"            <input type=\"time\" id=\"calibrationTime\" name=\"calibrationTime\" value=\"04:20\" />\n"\
		"            <button name=\"submit\" value=\"calibrationForm\" type=\"submit\">Kalibreren</button>\n"\
		"            <p class=\"explanation\">Als de klok niet de verwachte tijd aangeeft moet hij mogelijk gekalibreerd worden. Vul de tijd in die de wijzers op dit moment aangeven en klik op \"Kalibreren\".</p>\n"\
		"        </fieldset>\n"\
		"    </form>\n");

	printPageFooter(client);
}