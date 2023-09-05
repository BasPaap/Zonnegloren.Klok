#include "WebServer.h"

void Bas::WebServer::printWiFiOption(WiFiClient& client, const char* ssid, int32_t rssi, Bas::NetworkInfo::encryptionType_t encryptionType)
{
	client.print("<option value=\"");
	client.print(ssid);
	client.print("\" data-encryption=\"");

	switch (encryptionType)
	{
	case Bas::NetworkInfo::encryptionType_t::wpa:
		client.print("WPA");
		break;
	case Bas::NetworkInfo::encryptionType_t::wep:
		client.print("WEP");
		break;
	case Bas::NetworkInfo::encryptionType_t::none:
	default:
		client.print("none");
		break;
	}

	client.print("\">");
	client.print(ssid);
	client.print(" (");

	switch (encryptionType)
	{
	case Bas::NetworkInfo::encryptionType_t::wpa:
		client.print("WPA");
		break;
	case Bas::NetworkInfo::encryptionType_t::wep:
		client.print("WEP");
		break;
	case Bas::NetworkInfo::encryptionType_t::none:
	default:
		client.print("public");
		break;
	}

	client.print(")</option>");
}

void Bas::WebServer::printConfigurationPage(WiFiClient& client)
{
	printPageHeader(client,"Sanatorium Zonnegloren: De Klok - Configuratie");
	client.print("    <h2>Configuratie</h2>\n"\
		"    <form action=\"\" method=\"post\">\n"\
		"        <fieldset>\n"\
		"            <legend>Wi-Fi</legend>\n"\
		"            <p>\n"\
		"                <label for=\"ssid\">Kies een Wi-Fi netwerk:</label>\n"\
		"                <select name=\"ssid\" id=\"ssid\">\n");

	for (size_t i = 0; i < scannedNetworksLength; i++)
	{
		printWiFiOption(client, scannedNetworks[i].ssid, scannedNetworks[i].rssi, scannedNetworks[i].encryptionType);
	}

	client.print("                </select>\n"\
		"            </p>\n"\
		"            <p id=\"passwordBlock\">\n"\
		"                <label for=\"password\">Wachtwoord:</label>\n"\
		"                <input type=\"password\" name=\"password\" id=\"password\" />\n"\
		"            </p>\n"\
		"            <p id=\"keyIndexBlock\">\n"\
		"                <label for=\"keyIndex\">Key index:</label>\n"\
		"                <select name=\"keyIndex\" id=\"keyIndex\">\n"\
		"                    <option value=\"1\">1</option>\n"\
		"                    <option value=\"2\">2</option>\n"\
		"                    <option value=\"3\">3</option>\n"\
		"                    <option value=\"4\">4</option>\n"\
		"                </select>\n"\
		"            </p>\n"\
		"        </fieldset>\n"\
		"\n"\
		"        <fieldset>\n"\
		"            <legend>Domeinnaam</legend>\n"\
		"            <p>\n"\
		"                <label for=\"domainName\">Domeinnaam waarop de klok te bereiken is:</label>\n"\
		"                <span class=\"domainElements\">\n"\
		"                    http://\n"\
		"                    <input type=\"text\" maxlength=\"63\" name=\"domainName\" id=\"domainName\" value=\"klok\" />\n"\
		"                    .local\n"\
		"                </span>\n"\
		"            </p>\n"\
		"        </fieldset>\n"\
		"\n"\
		"        <input type=\"hidden\" name=\"encryption\" id=\"encryption\" />\n"\
		"\n"\
		"        <p class=\"centered\">\n"\
		"            <input class=\"submitButton\" type=\"submit\" value=\"Opslaan\" />\n"\
		"        </p>\n"\
		"    </form>\n"\
		"\n"\
		"    <script type=\"text/javascript\">\n"\
		"\n"\
		"        function hide(element) {\n"\
		"            element.classList.add(\"hidden\");\n"\
		"            element.classList.remove(\"visible\");\n"\
		"        }\n"\
		"\n"\
		"        function show(element) {\n"\
		"            element.classList.remove(\"hidden\");\n"\
		"            element.classList.add(\"visible\");\n"\
		"        }\n"\
		"\n"\
		"        function onEncryptionTypeChanged(encryptionType) {\n"\
		"            var passwordBlock = document.getElementById('passwordBlock');\n"\
		"            var keyIndexBlock = document.getElementById('keyIndexBlock');\n"\
		"\n"\
		"            var encryptionElement = document.getElementById('encryption');\n"\
		"            \n"\
		"            switch (encryptionType) {\n"\
		"                case \"WPA\":                    \n"\
		"                    show(passwordBlock);\n"\
		"                    hide(keyIndexBlock);\n"\
		"                    encryptionElement.value = 1;\n"\
		"                    break;\n"\
		"                case \"WEP\":\n"\
		"                    show(passwordBlock);\n"\
		"                    show(keyIndexBlock);\n"\
		"                    encryptionElement.value = 2;\n"\
		"                    break;\n"\
		"                case \"none\":\n"\
		"                default:\n"\
		"                    hide(passwordBlock);\n"\
		"                    hide(keyIndexBlock);\n"\
		"                    encryptionElement.value = 0;                \n"\
		"                    break;\n"\
		"            }\n"\
		"        }\n"\
		"\n"\
		"        window.onload = function() {\n"\
		"            var ssidElement = document.getElementById('ssid');\n"\
		"            var encryptionType = ssidElement.options[ssidElement.selectedIndex].dataset.encryption;\n"\
		"\n"\
		"            onEncryptionTypeChanged(encryptionType);\n"\
		"        }\n"\
		"\n"\
		"        document.getElementById('ssid').onchange = function () {\n"\
		"            var encryptionType = this.options[this.selectedIndex].dataset.encryption;\n"\
		"\n"\
		"            onEncryptionTypeChanged(encryptionType);\n"\
		"        }\n"\
		"\n"\
		"        \n"\
		"    </script>\n");

	printPageFooter(client);
}