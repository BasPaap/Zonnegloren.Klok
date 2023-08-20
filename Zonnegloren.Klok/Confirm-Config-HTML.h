#pragma once
const char* confirm_config_html1 = "<!DOCTYPE html>"\
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
"        progress {"\
"            width: 80%;"\
"            margin-top: 30px;"\
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
"        h4 {"\
"            margin-top: 40px;"\
"        }"\
""\
"        .setting {"\
"            font-weight: bold;"\
"            font-family: monospace, monospace"\
"        }"\
"    </style>"\
"</head>"\
"<body>"\
"    <h3>Sanatorium Zonnegloren</h3>"\
"    <h1>De Klok</h1>"\
"    <h2>Configuratie</h2>"\
""\
"    <h4>Opnieuw opstarten</h4>"\
"    <p>De configuratie is opgeslagen, de klok wordt nu opnieuw opgestart en zal over enkele seconden beschikbaar zijn op <span class=\"setting\" id=\"urlText\"></span> zolang je verbonden bent met het Wi-Fi netwerk <span class=\"setting\">";

const char* confirm_config_html2 = "</span>.</p>"\
"    <p>Even geduld a.u.b.</p>"\
""\
"    <p class=\"centered\">"\
"        <progress id=\"progressBar\" max=\"100\" value=\"0\"></progress>"\
"    </p>"\
"    <p class=\"centered\">Nog <span id=\"numSecondsRemainingText\"></span> seconde<span id=\"pluralityCharacter\">n</span>...</p>"\
""\
"    <script type=\"text/javascript\">"\
"        var intervalId;"\
"        var progressbar = document.getElementById('progressBar');"\
"        var numSecondsRemainingText = document.getElementById('numSecondsRemainingText');"\
"        var pluralityCharacter = document.getElementById('pluralityCharacter');"\
"        var urlText = document.getElementById('urlText');"\
"        var url = \"http://";


const char* confirm_config_html3 = "\";"\
""\
"        var timeoutInSeconds = 30;"\
"        var numSecondsRemaining = timeoutInSeconds;"\
""\
"        window.onload = function () {"\
"            intervalId = setInterval(updateProgress, 10);"\
"            progressbar.max = timeoutInSeconds;"\
"            urlText.textContent = url;"\
"        }"\
""\
"        function updateProgress() {"\
"            numSecondsRemaining -= 0.01;"\
"            "\
"            progressbar.value = timeoutInSeconds - numSecondsRemaining;"\
"            "\
"            //progressBar.value = percentage;"\
"            var numRoundedSecondsRemaining = Math.round(numSecondsRemaining);"\
"            numSecondsRemainingText.textContent = numRoundedSecondsRemaining;"\
""\
"            if (numRoundedSecondsRemaining == 1) {"\
"                pluralityCharacter.style.display = 'none';"\
"            }"\
"            else {"\
"                pluralityCharacter.style.display = 'inline';"\
"            }"\
""\
"            if (numSecondsRemaining <= 0) {"\
"                clearInterval(intervalId);"\
"                location.href = url;"\
"            }"\
"        }"\
""\
"    </script>"\
"</body>"\
"</html>";