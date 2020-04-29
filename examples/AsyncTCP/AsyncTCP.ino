#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FileStream.h"

AsyncWebServer server(80);
FileStream FileStream;

const char* ssid = "Matos Almeida";
const char* password = "628628628";

const char* PARAM_MESSAGE = "message";

namespace WebServer {
void setup();
void handleRoot(AsyncWebServerRequest* request);
void handleNotFound(AsyncWebServerRequest* request);

boolean _debug = true;
template <typename Generic>
void DEBUG_WS(Generic text);
}  // namespace WebServer

/* 
 * @brief Setup the WebServer
 */
void WebServer::setup() {
  DEBUG_WS(F("Setup"));
  server.on("/", HTTP_GET, WebServer::handleRoot);

  server.onNotFound(WebServer::handleNotFound);

  server.begin();
}  // Function setup

/* 
 * @brief handle Not Found page
 */
void WebServer::handleNotFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}  // END Function

/* 
 * @brief handle Root
 */
void WebServer::handleRoot(AsyncWebServerRequest *request) {
  FileStream.stream(request, "/js/jquery-3.2.1.slim.min.js") ? DEBUG_WS("Success to Server -> " + String(__func__)) : DEBUG_WS("Fail to serve -> " + String(__func__));
}  //END Function

/* 
 * @brief template DEBUG_WS
 */
template <typename Generic>
void WebServer::DEBUG_WS(Generic text) {
  if (_debug) {
    Serial.print("[WebServer] : ");
    Serial.println(text);
  }
}

void setup()
{
  Serial.begin(115200);
  FileStream.setup();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  WebServer::setup();
}

void loop()
{
  Serial.println("Working");
}