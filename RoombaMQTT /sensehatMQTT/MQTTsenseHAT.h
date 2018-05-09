#ifndef MQTTSENSEHAT_H
#define MQTTSENSEHAT_H

#include "CommandProcessor.h"
#include "ParLoop.h"
#include "SenseHAT.h"

using parameters_t = std::vector<std::string>;

class MQTTsenseHAT: public CommandProcessor
{
public:
   MQTTsenseHAT(const std::string& appname,
                const std::string& clientname,
                const std::string& host,
                int port);
   MQTTsenseHAT() = delete;
   MQTTsenseHAT(const MQTTsenseHAT& other) = delete;
   MQTTsenseHAT& operator=(const MQTTsenseHAT& other) = delete;
   virtual ~MQTTsenseHAT();

   SenseHAT senseHAT_;
protected:
   const std::string mqttID_;
   int x_;
   int y_;
   const int min_x_ = 0;
   const int min_y_ = 0;
   const int max_x_ = 7;
   const int max_y_ = 7;

   ParLoop publishSensorData_;

   // SensorHAT Sensors
   void getTemp(const parameters_t& commandParameters);
   void getPres(const parameters_t& commandParameters);
   void getHum(const parameters_t& commandParameters);

   // SensorHAT LED matrix display
   void clear(const parameters_t& commandParameters);
   void blank(const parameters_t& commandParameters);
   void invert(const parameters_t& commandParameters);
   void setPixel(const parameters_t& commandParameters);
   void getPixel(const parameters_t& commandParameters);
   void invertPixel(const parameters_t& commandParameters);
   void cylonPar(const parameters_t& commandParameters);
   void cylon(const parameters_t& commandParameters);

   // SensorHAT joystick event handlers
   void jsup();
   void jsdown();
   void jsright();
   void jsleft();
   void jspressed();
   void jsany();

   void handleSensorData();
};

#endif
