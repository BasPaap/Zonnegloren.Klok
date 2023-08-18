#pragma once
const char* config_html1 = "<!DOCTYPE html>\n"\
"\n"\
"<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">\n"\
"<head>\n"\
"    <meta charset=\"utf-8\" />\n"\
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"    <title>Sanatorium Zonnegloren: De Klok - Configuratie</title>\n"\
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
"    </style>\n"\
"</head>\n"\
"<body>\n"\
"    <h3>Sanatorium Zonnegloren</h3>\n"\
"    <h1>De Klok</h1>\n"\
"    <h2>Configuratie</h2>\n"\
"    <form action=\"\" method=\"post\">\n"\
"        <fieldset>\n"\
"            <legend>Wi-Fi</legend>\n"\
"            <p>\n"\
"                <label for=\"ssid\">Kies een Wi-Fi netwerk:</label>\n"\
"                <select name=\"ssid\" id=\"ssid\">\n";

const char* config_html2 = "                </select>\n"\
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
"                    <input type=\"text\" maxlength=\"247\" name=\"domainName\" id=\"domainName\" value=\"klok\" />\n"\
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
"    </script>\n"\
"</body>\n"\
"</html>";