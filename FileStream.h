#ifndef FileStream_H
#define FileStream_H

#include "SPIFFS.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class FileStream {
 public:
  AsyncWebServer* server;
  FileStream();
  bool setup();
  bool stream(AsyncWebServerRequest* request, String path, bool gzip = true);

 private:
  boolean _debug = true;

  bool isFile(String path);
  template <typename Generic>
  void DEBUG_FS(Generic text);
};

#endif