#include "MQTTconfig.h"
#include "MQTTsenseHAT.h"
#include "ParWait.h"
#include "Pixel.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

MQTTsenseHAT::MQTTsenseHAT(const std::string& appname,
                           const std::string& clientname,
                           const std::string& host,
                           int port) :
   CommandProcessor(appname, clientname, host, port),
   senseHAT_{},
   mqttID_{HOSTNAME + appname + clientname},
   x_{0},
   y_{0},
   publishSensorData_(std::bind(&MQTTsenseHAT::handleSensorData, this), 60)
{
   std::cerr << "---- CTOR MQTTsenseHAT host = '" << host
        << "'  port = " << port
        << "  id = " << mqttID_
        << "  topic root = "<< MQTT_TOPIC_ROOT << std::endl;

   senseHAT_.leds.clear(Pixel{0, 50, 0});

   // Sensor commands
   registerCommand("getTemp", bind(&MQTTsenseHAT::getTemp, this,
                                   placeholders::_1));
   registerCommand("getPres", bind(&MQTTsenseHAT::getPres, this,
                                   placeholders::_1));
   registerCommand("getHum", bind(&MQTTsenseHAT::getHum, this,
                                  placeholders::_1));

   // LEDs display commands
   registerCommand("clear", bind(&MQTTsenseHAT::clear, this,
                                 placeholders::_1));
   registerCommand("blank", bind(&MQTTsenseHAT::blank, this,
                                 placeholders::_1));
   registerCommand("invert", bind(&MQTTsenseHAT::invert, this,
                                  placeholders::_1));
   registerCommand("setPixel", bind(&MQTTsenseHAT::setPixel, this,
                                    placeholders::_1));
   registerCommand("getPixel", bind(&MQTTsenseHAT::getPixel, this,
                                    placeholders::_1));
   registerCommand("invertPixel", bind(&MQTTsenseHAT::invertPixel, this,
                                       placeholders::_1));
   registerCommand("cylon", bind(&MQTTsenseHAT::cylon, this,
                                 placeholders::_1));

   senseHAT_.stick.directionUP = std::bind(&MQTTsenseHAT::jsup, this);
   senseHAT_.stick.directionDOWN = std::bind(&MQTTsenseHAT::jsdown, this);
   senseHAT_.stick.directionLEFT = std::bind(&MQTTsenseHAT::jsleft, this);
   senseHAT_.stick.directionRIGHT = std::bind(&MQTTsenseHAT::jsright, this);
   senseHAT_.stick.directionPRESSED = std::bind(&MQTTsenseHAT::jspressed, this);
   senseHAT_.stick.directionANY = std::bind(&MQTTsenseHAT::jsany, this);

   senseHAT_.leds.setPixel(x_, y_, Pixel{200, 100, 100});
}

MQTTsenseHAT::~MQTTsenseHAT()
{
   senseHAT_.leds.clear(Pixel{50, 0, 0});
}

void MQTTsenseHAT::getTemp(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 0)
   {
      publishError("getTemp", "number of parameters != 0");
   }
   else
   {
      publishInfo("getTemp", "Hello SenseHAT");
      double temperature = senseHAT_.get_temperature();
      publishReturn("getTemp", std::to_string(temperature));
   }
}

void MQTTsenseHAT::getPres(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 0)
   {
      publishError("getPres", "number of parameters != 0");
   }
   else
   {
      publishInfo("getPres", "Hello SenseHAT");
      double temperature = senseHAT_.get_pressure();
      publishReturn("getPres", std::to_string(temperature));
   }
}

void MQTTsenseHAT::getHum(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 0)
   {
      publishError("getHum", "number of parameters != 0");
   }
   else
   {
      publishInfo("getHum", "Hello SenseHAT");
      int humidity = senseHAT_.get_humidity();
      publishReturn("getHum", std::to_string(humidity));
   }
}

void MQTTsenseHAT::blank(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 0)
   {
      publishError("setPixel", "number of parameters != 0");
   }
   else
   {
      senseHAT_.leds.clear();
   }
}

void MQTTsenseHAT::clear(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 3)
   {
      publishError("clear", "number of parameters != 3");
   }
   else
   {
      auto r = stoi(commandParameters[0]);
      auto g = stoi(commandParameters[1]);
      auto b = stoi(commandParameters[2]);
      senseHAT_.leds.clear(Pixel(r, g, b));
   }
}

void MQTTsenseHAT::invert(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 0)
   {
      publishError("clear", "number of parameters != 0");
   }
   else
   {
     senseHAT_.leds.invert();
   }
}

void MQTTsenseHAT::setPixel(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 5)
   {
      publishError("setPixel", "number of parameters != 5");
   }
   else
   {
      auto y = stoi(commandParameters[0]);
      auto x = stoi(commandParameters[1]);
      auto r = stoi(commandParameters[2]);
      auto g = stoi(commandParameters[3]);
      auto b = stoi(commandParameters[4]);
      senseHAT_.leds.setPixel(x, y, Pixel(r, g, b));
   }
}

void MQTTsenseHAT::getPixel(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 2)
   {
      publishError("getPixel", "number of parameters != 2");
   }
   else
   {
      auto y = stoi(commandParameters[0]);
      auto x = stoi(commandParameters[1]);
      Pixel pixel = senseHAT_.leds.getPixel(x, y);
      publishReturn("getPixel", std::to_string(pixel[Pixel::RGB::R])
                                + " " + std::to_string(pixel[Pixel::RGB::G])
                                + " " + std::to_string(pixel[Pixel::RGB::B]));
   }
}

void MQTTsenseHAT::invertPixel(const parameters_t& commandParameters)
{
   if (commandParameters.size() != 2)
   {
      publishError("invertPixel", "number of parameters != 2");
   }
   else
   {
      auto y = stoi(commandParameters[0]);
      auto x = stoi(commandParameters[1]);

      Pixel pixel{senseHAT_.leds.getPixel(x, y)};
      pixel.invert();
      senseHAT_.leds.setPixel(x, y, pixel);
   }
}


void MQTTsenseHAT::cylonPar(const parameters_t& commandParameters)
{
   auto putDot = [this] (int x, const Pixel& pixel)
   {
      senseHAT_.leds.setPixel(x, 3, pixel);
      senseHAT_.leds.setPixel(x, 4, pixel);
      senseHAT_.leds.setPixel(x+1, 3, pixel);
      senseHAT_.leds.setPixel(x+1, 4, pixel);
   };

   auto show = [putDot] {
      int x{0};
	   int i{1};
      int count{13};

	   while (count >0) {
	      putDot(x, Pixel::RED);
         std::this_thread::sleep_for(std::chrono::milliseconds{200});
		   putDot(x, Pixel::BLANK);
		   x += i;
		   if (x < 0) {
		      i = 1;
			   x = 1;
		   }
		   if (x > 6) {
			   i = -1;
			   x = 5;
		   }
         --count;
	   }
   };

   show();
}

void MQTTsenseHAT::cylon(const parameters_t& commandParameters)
{
   new ParWait {std::bind(&MQTTsenseHAT::cylonPar, this, commandParameters)};
}

void MQTTsenseHAT::jsup()
{
   if (y_ > 0)  {
      --y_;
   }
}

void MQTTsenseHAT::jsdown()
{
   if (y_ < max_y_)  {
      ++y_;
   }
}

void MQTTsenseHAT::jsright()
{
   if (x_ < max_x_) {
      ++x_;
   }
}

void MQTTsenseHAT::jsleft()
{
   if (x_ > 0) {
      --x_;
   }
}

void MQTTsenseHAT::jspressed()
{
   x_ = 0;
   y_ = 0;
   publishAddition("pixel", "back to 0 0");
}

void MQTTsenseHAT::jsany()
{
   senseHAT_.leds.clear();
   senseHAT_.leds.setPixel(x_, y_, Pixel{100, 100, 200});
}

void MQTTsenseHAT::handleSensorData()
{
   std::string message{
      std::to_string(static_cast<int>(senseHAT_.get_humidity()))};
   publishAddition("humidity", message);
}
