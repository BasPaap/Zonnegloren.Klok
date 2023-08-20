#include "WebServer.h"

void Bas::WebServer::printConfirmConfigurationPage(WiFiClient& client, const char* ssid, const char* domainName)
{
	printPageHeader(client, "Sanatorium Zonnegloren : De Klok - Configuratie");

	client.print("    <h2>Configuratie</h2>\n"\
		"\n"\
		"    <h4>Opnieuw opstarten</h4>\n"\
		"    <p>De configuratie is opgeslagen, de klok wordt nu opnieuw opgestart en zal over enkele seconden beschikbaar zijn op <span class=\"setting\" id=\"urlText\"></span> zolang je verbonden bent met het Wi-Fi netwerk <span class=\"setting\">\n");

	client.print(ssid);

	client.print("</span>.</p>\n"\
		"    <p>Even geduld a.u.b.</p>\n"\
		"\n"\
		"    <p class=\"centered\">\n"\
		"        <progress id=\"progressBar\" max=\"100\" value=\"0\"></progress>\n"\
		"    </p>\n"\
		"    <p class=\"centered\">Nog <span id=\"numSecondsRemainingText\"></span> seconde<span id=\"pluralityCharacter\">n</span>...</p>\n"\
		"\n"\
		"    <script type=\"text/javascript\">\n"\
		"        function updateProgress() {\n"\
		"            numSecondsRemaining -= 0.01;\n"\
		"            \n"\
		"            progressbar.value = timeoutInSeconds - numSecondsRemaining;\n"\
		"            var numRoundedSecondsRemaining = Math.round(numSecondsRemaining);\n"\
		"            numSecondsRemainingText.textContent = numRoundedSecondsRemaining;\n"\
		"\n"\
		"            if (numRoundedSecondsRemaining == 1) {\n"\
		"                pluralityCharacter.style.display = 'none';\n"\
		"            }\n"\
		"            else {\n"\
		"                pluralityCharacter.style.display = 'inline';\n"\
		"            }\n"\
		"\n"\
		"            if (numSecondsRemaining <= 0) {\n"\
		"                clearInterval(intervalId);\n"\
		"                location.href = url;\n"\
		"            }\n"\
		"        }\n"\
		"\n"\
		"        var intervalId;\n"\
		"        var progressbar = document.getElementById('progressBar');\n"\
		"        var numSecondsRemainingText = document.getElementById('numSecondsRemainingText');\n"\
		"        var pluralityCharacter = document.getElementById('pluralityCharacter');\n"\
		"        var urlText = document.getElementById('urlText');\n"\
		"        var url = \"http://");

	client.print(domainName);

	client.print(".local\";\n"\
		"\n"\
		"        var timeoutInSeconds = 30;\n"\
		"        var numSecondsRemaining = timeoutInSeconds;\n"\
		"\n"\
		"        window.onload = function () {\n"\
		"            intervalId = setInterval(updateProgress, 10);\n"\
		"            progressbar.max = timeoutInSeconds;\n"\
		"            urlText.textContent = url;\n"\
		"        }\n"\
		"\n"\
		"    </script>\n");

	printPageFooter(client);
}