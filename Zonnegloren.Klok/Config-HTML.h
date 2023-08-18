#pragma once
const char* config_html1 = "<!DOCTYPE html>"\
""\
"<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">"\
"<head>"\
"    <meta charset=\"utf-8\" />"\
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"\
"    <title>Sanatorium Zonnegloren: De Klok - Configuratie</title>"\
""\
"    <style>"\
"        body {"\
"            background-color: darkslategray;"\
"            color: white;"\
"            font-size: 16px;"\
"            font-family: Verdana, Geneva, Tahoma, sans-serif;"\
"            margin-left: 5%;"\
"            margin-right: 5%;"\
"        }"\
""\
"        .centered {"\
"            text-align: center;"\
"        }"\
""\
"        h1, h2, h3 {"\
"            text-align: center;"\
"        }"\
""\
"        h3 {"\
"            margin-bottom: 0px;"\
"        }"\
""\
"        h1 {"\
"            margin-top: 0px;"\
"            margin-bottom: 5px;"\
"        }"\
""\
"        #domainName {"\
"            text-align: right;"\
"        }"\
""\
"        .domainElements {"\
"            white-space: nowrap;"\
"        }"\
""\
"        .submitButton {"\
"            padding: 10px;"\
"        }"\
""\
"        fieldset {"\
"            margin-top: 5px;"\
"            margin-bottom: 5px;"\
"        }"\
""\
"        .hidden {"\
"            display: none;"\
"        }"\
""\
"        .visible {"\
"            display: block;"\
"        }"\
"    </style>"\
"</head>"\
"<body onload=\"onLoad()\">"\
"    <h3>Sanatorium Zonnegloren</h3>"\
"    <h1>De Klok</h1>"\
"    <h2>Configuratie</h2>"\
"    <form action=\"\" method=\"post\">"\
"        <fieldset>"\
"            <legend>Wi-Fi</legend>"\
"            <p>"\
"                <label for=\"ssid\">Kies een Wi-Fi netwerk:</label>"\
"                <select name=\"ssid\" id=\"ssid\">";

const char* config_html2 = "                </select>"\
"            </p>"\
"            <p id=\"passwordBlock\">"\
"                <label for=\"password\">Wachtwoord:</label>"\
"                <input type=\"password\" name=\"password\" id=\"password\" />"\
"            </p>"\
"            <p id=\"keyIndexBlock\">"\
"                <label for=\"keyIndex\">Key index:</label>"\
"                <select name=\"keyIndex\" id=\"keyIndex\">"\
"                    <option value=\"1\">1</option>"\
"                    <option value=\"2\">2</option>"\
"                    <option value=\"3\">3</option>"\
"                    <option value=\"4\">4</option>"\
"                </select>"\
"            </p>"\
"        </fieldset>"\
""\
"        <fieldset>"\
"            <legend>Domeinnaam</legend>"\
"            <p>"\
"                <label for=\"domainName\">Domeinnaam waarop de klok te bereiken is:</label>"\
"                <span class=\"domainElements\">"\
"                    http://"\
"                    <input type=\"text\" maxlength=\"247\" name=\"domainName\" id=\"domainName\" value=\"klok\" />"\
"                    .local"\
"                </span>"\
"            </p>"\
"        </fieldset>"\
""\
"        <input type=\"hidden\" name=\"encryption\" id=\"encryption\" />"\
""\
"        <p class=\"centered\">"\
"            <input class=\"submitButton\" type=\"submit\" value=\"Opslaan\" />"\
"        </p>"\
"    </form>"\
""\
"    <script type=\"text/javascript\">"\
""\
"        function hide(element) {"\
"            element.classList.add(\"hidden\");"\
"            element.classList.remove(\"visible\");"\
"        }"\
""\
"        function show(element) {"\
"            element.classList.remove(\"hidden\");"\
"            element.classList.add(\"visible\");"\
"        }"\
""\
"        function onEncryptionTypeChanged(encryptionType) {"\
"            var passwordBlock = document.getElementById('passwordBlock');"\
"            var keyIndexBlock = document.getElementById('keyIndexBlock');"\
""\
"            var encryptionElement = document.getElementById('encryption');"\
""\
"            encryptionElement.value = encryptionType;"\
""\
"            switch (encryptionType) {"\
"                case \"WPA\":                    "\
"                    show(passwordBlock);"\
"                    hide(keyIndexBlock);"\
"                    break;"\
"                case \"WEP\":"\
"                    show(passwordBlock);"\
"                    show(keyIndexBlock);"\
"                    break;"\
"                case \"none\":"\
"                    hide(passwordBlock);"\
"                    hide(keyIndexBlock);"\
"                default:"\
"                    break;"\
"            }"\
"        }"\
""\
"        function onLoad() {"\
"            var ssidElement = document.getElementById('ssid');"\
"            var encryptionType = ssidElement.options[ssidElement.selectedIndex].dataset.encryption;"\
""\
"            onEncryptionTypeChanged(encryptionType);"\
"        }"\

""\
"        document.getElementById('ssid').onchange = function () {"\
"            var encryptionType = this.options[this.selectedIndex].dataset.encryption;"\
""\
"            onEncryptionTypeChanged(encryptionType);"\
"        }"\
"    </script>"\
"</body>"\
"</html>";