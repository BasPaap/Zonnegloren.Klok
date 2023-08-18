#pragma once
const char* config_html = "<!DOCTYPE html>"\
""\
"<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">"\
"<head>"\
"    <meta charset=\"utf-8\" />"\
"    <title>Sanatorium Zonnegloren: De Klok - Configuratie</title>"\
""\
"    <style>"\
"        body {"\
"            background-color: darkslategray;"\
"            color: white;"\
"            font-size: 16px;"\
"            font-family:Verdana, Geneva, Tahoma, sans-serif;"\
"        }"\
""\
"        #domainName {"\
"            text-align:right;"\
"        }"\
"    </style>"\
"</head>"\
"<body>"\
"    <h3>Sanatorium Zonnegloren</h3>"\
"    <h1>De Klok</h1>"\
"    <h2>Configuratie</h2>"\
"    <form action=\"\" method=\"post\">"\
"        <fieldset>"\
"            <legend>Wi-Fi</legend>"\
"            <p>"\
"                <label for=\"ssid\">Kies een Wi-Fi netwerk:</label>"\
"                <select name=\"ssid\" id=\"ssid\">"\
"                    <option value=\"foo\">foo</option>"\
"                    <option value=\"bar\">bar</option>"\
"                </select>"\
"            </p>"\
"            <p>"\
"                <label for=\"password\">Wachtwoord:</label>"\
"                <input type=\"password\" name=\"password\" id=\"password\" />"\
"            </p>"\
"            <p>"\
"                <label for=\"keyIndex\">Key Index (alleen voor WEP)</label>"\
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
"                <input type=\"text\" maxlength=\"247\" name=\"domainName\" id=\"domainName\" value=\"klok\" />"\
"                .local"\
"            </p>"\
"        </fieldset>"\
""\
"        <input type=\"submit\" value=\"Opslaan\" />"\
"    </form>"\
"</body>"\
"</html>";