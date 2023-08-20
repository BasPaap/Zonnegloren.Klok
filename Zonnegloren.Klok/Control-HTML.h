#pragma once
const char* control_html = "<!DOCTYPE html>\n"\
"\n"\
"<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">\n"\
"<head>\n"\
"    <meta charset=\"utf-8\" />\n"\
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"    <title>Sanatorium Zonnegloren: De Klok</title>\n"\
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
"        h1, h3 {\n"\
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
"        fieldset {\n"\
"            margin-top: 5px;\n"\
"            margin-bottom: 5px;\n"\
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
"    <h1>De Klok</h1>\n"\
"\n"\
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
"            <input type=\"number\" id=\"speed\" name=\"speed\" class=\"speed\" value=\"1\">\n"\
"            <button name=\"submit\" value=\"speedForm\" type=\"submit\">Snelheid aanpassen</button>\n"\
"            <p class=\"explanation\">Het aantal seconden per seconde, mag negatief zijn. 1 = normaal, -1 is normaal maar achteruit, 0.5 is half zo snel als normaal, enzovoort.</p>\n"\
"            <p class=\"explanation\">Deze snelheid wordt niet gebruikt als een variabele snelheid (zie hieronder) actief is!</p>\n"\
"        </fieldset>\n"\
"    </form>\n"\
"\n"\
"    <form action=\"\" method=\"post\">\n"\
"        <fieldset>\n"\
"            <legend>Variabele snelheid</legend>\n"\
"            <p class=\"explanation\">\n"\
"                Van\n"\
"                <input type=\"time\" id=\"startTime\" name=\"startTime\" value=\"04:20\" title=\"eindtijd\" placeholder=\"4:20\">\n"\
"                tot\n"\
"                <input type=\"time\" id=\"endTime\" name=\"endTime\" value=\"04:20\" title=\"starttijd\" placeholder=\"4:20\">\n"\
"                moet de snelheid lineair aangepast worden van\n"\
"                <input type=\"number\" id=\"startSpeed\" name=\"startSpeed\" class=\"speed\" value=\"1\" title=\"startsnelheid\" placeholder=\"1\">\n"\
"                naar\n"\
"                <input type=\"number\" id=\"endSpeed\" name=\"endSpeed\" class=\"speed\" value=\"0.5\" title=\"eindsnelheid\" placeholder=\"0.5\">.\n"\
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
"    </form>\n"\
"</body>\n"\
"</html>";