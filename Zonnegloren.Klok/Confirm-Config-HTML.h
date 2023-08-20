#pragma once
const char* confirm_config_html1 = "<!DOCTYPE html>\n"\
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
"        progress {\n"\
"            width: 80%;\n"\
"            margin-top: 30px;\n"\
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
"        h4 {\n"\
"            margin-top: 40px;\n"\
"        }\n"\
"\n"\
"        .setting {\n"\
"            font-weight: bold;\n"\
"            font-family: monospace, monospace\n"\
"        }\n"\
"    </style>\n"\
"</head>\n"\
"<body>\n"\
"    <h3>Sanatorium Zonnegloren</h3>\n"\
"    <h1>De Klok</h1>\n"\
"    <h2>Configuratie</h2>\n"\
"\n"\
"    <h4>Opnieuw opstarten</h4>\n"\
"    <p>De configuratie is opgeslagen, de klok wordt nu opnieuw opgestart en zal over enkele seconden beschikbaar zijn op <span class=\"setting\" id=\"urlText\"></span> zolang je verbonden bent met het Wi-Fi netwerk <span class=\"setting\">\n";

const char* confirm_config_html2 = "</span>.</p>\n"\
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
"        var url = \"http://";


const char* confirm_config_html3 = ".local\";\n"\
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
"    </script>\n"\
"</body>\n"\
"</html>";