#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ahmed";
const char* password = "123456789";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  configureEndpoints();

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

void configureEndpoints() {
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
        <title>Car Control</title>
        <style>
          body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin: 0;
            padding: 0;
            background-image: url('لينك الصوره يتحط هنا');
            background-size: cover;
            background-position: center;
            background-attachment: fixed;
            height: 100vh;
          }
          h1 { color: #fff; }
          .container {
            margin: 50px auto;
            width: 80%;
            max-width: 300px;
          }
          button {
            width: 80px;
            height: 80px;
            margin: 5px;
            font-size: 16px;
            border: none;
            border-radius: 10px;
            color: white;
            cursor: pointer;
            background-color: #007BFF;
            transition: background-color 0.3s;
          }
          button:hover { background-color: #0056b3; }
          .grid {
            display: grid;
            grid-template-rows: auto auto auto;
            grid-template-columns: auto auto auto;
            gap: 10px;
            justify-items: center;
            align-items: center;
          }
          .slider-container { margin-top: 20px; }
          .slider {
            -webkit-appearance: none;
            width: 100%;
            height: 15px;
            background: #ddd;
            border-radius: 10px;
            outline: none;
            opacity: 0.7;
            transition: opacity 0.2s;
          }
          .slider:hover { opacity: 1; }
          .slider-value {
            color: white;
            font-size: 16px;
            margin-top: 10px;
          }
          .extra-buttons {
            margin-top: 30px;
            display: flex;
            justify-content: space-around;
          }
          .extra-button {
            width: 45%;
            height: 50px;
            font-size: 18px;
            color: white;
            border: none;
            border-radius: 25px;
            cursor: pointer;
            background-color: #007bff;
          }
          .extra-button:hover { background-color: #0056b3; }
        </style>
      </head>
      <body>
        <div class="container">
          <h1>Car Control</h1>
          <div class="grid">
            <span></span>
            <button onclick="fetch('/forward')">▲</button>
            <span></span>
            <button onclick="fetch('/left')">◀</button>
            <button></button>
            <button onclick="fetch('/right')">▶</button>
            <span></span>
            <button onclick="fetch('/backward')">▼</button>
            <span></span>
          </div>
          <div style="margin-top: 20px;">
            <button onclick="fetch('/start')" style="background-color: #28a745;">Start</button>
            <button onclick="fetch('/stop')" style="background-color: #dc3545;">Stop</button>
          </div>
          <div class="slider-container">
            <input type="range" min="0" max="100" value="0" class="slider" id="speedSlider">
            <div class="slider-value" id="speedValue">Speed: 0%</div>
          </div>
          <div class="extra-buttons">
            <button class="extra-button" onclick="fetch('/function1')">Function 1</button>
            <button class="extra-button" onclick="fetch('/function2')">Function 2</button>
          </div>
        </div>

        <script>
          const slider = document.getElementById("speedSlider");
          const speedValue = document.getElementById("speedValue");

          slider.oninput = function() {
            speedValue.innerHTML = "Speed: " + this.value + "%";
            fetch('/setSpeed?value=' + this.value);
          }
        </script>
      </body>
      </html>
    )rawliteral");
  });

  server.on("/forward", HTTP_GET, []() {
    Serial.println("MOVE FORWARD");
    server.send(200, "text/plain", "Car moving forward");
  });
  server.on("/backward", HTTP_GET, []() {
    Serial.println("MOVE BACKWARD");
    server.send(200, "text/plain", "Car moving backward");
  });
  server.on("/left", HTTP_GET, []() {
    Serial.println("TURN LEFT");
    server.send(200, "text/plain", "Car turning left");
  });
  server.on("/right", HTTP_GET, []() {
    Serial.println("TURN RIGHT");
    server.send(200, "text/plain", "Car turning right");
  });
  server.on("/start", HTTP_GET, []() {
    Serial.println("START");
    server.send(200, "text/plain", "Car started");
  });
  server.on("/stop", HTTP_GET, []() {
    Serial.println("STOP");
    server.send(200, "text/plain", "Car stopped");
  });

  server.on("/setSpeed", HTTP_GET, []() {
    String speed = server.arg("value");
    Serial.print("Speed set to: ");
    Serial.println(speed);
    server.send(200, "text/plain", "Speed set to: " + speed + "%");
  });

  server.on("/function1", HTTP_GET, []() {
    Serial.println("Function 1 Activated");
    server.send(200, "text/plain", "Function 1 activated");
  });
  server.on("/function2", HTTP_GET, []() {
    Serial.println("Function 2 Activated");
    server.send(200, "text/plain", "Function 2 activated");
  });
}
