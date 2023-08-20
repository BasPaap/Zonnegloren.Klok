#pragma once
const char* first_calibration_html = "<!DOCTYPE html>\n"\
"\n"\
"<html lang=\"en\" xmlns=\"http://www.w3.org/1999/xhtml\">\n"\
"<head>\n"\
"    <meta charset=\"utf-8\" />\n"\
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"    <title>Sanatorium Zonnegloren: De Klok - Eerste Kalibratie</title>\n"\
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
"    </style>\n"\
"</head>\n"\
"<body>\n"\
"    <h3>Sanatorium Zonnegloren</h3>\n"\
"    <h1>De Klok</h1>\n"\
"    <h2>Eerste Kalibratie</h2>\n"\
"    \n"\
"    <form action=\"\" method=\"post\">\n"\
"        <fieldset>\n"\
"            <legend>Kalibratie</legend>\n"\
"            <p class=\"explanation\">De klok is zojuist voor het eerst opgestart. Vul de tijd in die de wijzers <em>op dit moment</em> aangeven en klik op \"Kalibreren\".</p>\n"\
"            <input type=\"time\" id=\"time\" name=\"time\" value=\"00:00\">\n"\
"            <button name=\"submit\" value=\"firstCalibrationForm\" type=\"submit\">Kalibreren</button>\n"\
"        </fieldset>\n"\
"    </form>\n"\
"</body>\n"\
"</html>";