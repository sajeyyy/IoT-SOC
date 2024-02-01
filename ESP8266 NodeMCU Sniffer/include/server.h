#ifndef SERVER_H
#define SERVER_H

class ServerHandler
{
    public:
      ServerHandler();
      void begin();
      void handleClient();

    private:
        ESP8266WebServer server;
        void handleRoot();
};


#endif