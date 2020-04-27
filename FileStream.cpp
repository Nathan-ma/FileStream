#include "FileStream.h"

/*
 * @brief Class Constructor creating a new object 
 */
FileStream::FileStream() {
  this->server = new AsyncWebServer(80);
}

/*
 * @brief Setup  the FileStream
 */
bool FileStream::setup() {
  if (SPIFFS.begin(true)) {
    DEBUG_FS(F("SPIFFS Started"));
    return true;
  } else {
    DEBUG_FS(F("SPIFFS Fail"));
  }
}  // END Function

/*
 * @brief check if the file exists
 * @param path: to the file 
 */
bool FileStream::isFile(String path) {
  if (SPIFFS.exists(path)) {
    //DEBUG_FS(F("File Found"));
    return true;
  } else {
    DEBUG_FS(F("File Missing"));
    return false;
  }
}  // END Function

/* 
 * @brief Stream a file depending on it's extension
 * @param path: to file gzip: compacted?
 */
bool FileStream::stream(AsyncWebServerRequest* request, String path, bool gzip) {
  if (isFile(path)) {
    File file = SPIFFS.open(path, "r");
  } else {
    DEBUG_FS(F("Fail to Server File"));
    return false;
  }
  AsyncWebServerResponse* response;

  if (path.endsWith(".js")) {
    response = request->beginResponse(SPIFFS, path, "application/javascript");
  } else if (path.endsWith(".css")) {
    response = request->beginResponse(SPIFFS, path, "text/css");
  } else if (path.endsWith(".html")) {
    response = request->beginResponse(SPIFFS, path, "text/html");
  } else if (path.endsWith(".png")) {
    response = request->beginResponse(SPIFFS, path, "img/png");
  } else if (path.endsWith(".jpg")) {
    response = request->beginResponse(SPIFFS, path, "img/jpeg");
  } else if (path.endsWith(".json")) {
    response = request->beginResponse(SPIFFS, path, "application/json");
  }

  if (gzip)
    response->addHeader("Content-Encoding", "gzip");

  request->send(response);
  return true;
}  // END Function

/* 
 * @brief Debug template
 */
template <typename Generic>
void FileStream::DEBUG_FS(Generic text) {
  if (_debug) {
    Serial.print("[FileStream] : ");
    Serial.println(text);
  }
}  // template DEBUG_FS