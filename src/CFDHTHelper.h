/**
 * CFDHTHelper.h
 * 
 * DHT Helper for CF Arduino Devices.
 * 
 * @author  Caio Frota <caiofrota@gmail.com>
 * @version 1.0
 * @since   Mar, 2021
 */
 
#include <Arduino.h>
#include <DHT.h>

#ifndef CFDHTHelper_h
#define CFDHTHelper_h

class CFDHTHelper {
    private:
        // Attributes.
        DHT _dht;
        int _pinReset;                                                                              // DHT Workaround for fail reading failure.
        unsigned long _lastReading;
        unsigned long _readingDelay;
        bool _read;
        float _temperatureC;
        float _temperatureF;
        float _heatIndexC;
        float _heatIndexF;
        float _humidity;
    public:
        // Constructors.
        CFDHTHelper(int dhtType, int pinData);
        CFDHTHelper(int dhtType, int pinData, int pinReset);                                        // DHT Workaround for fail reading failure.
        
        // Methods.
        void begin();                                                                               // Initial Setup.
        bool loop();                                                                                // Control.
        
        // Accessors.
        void setReadingDelay();
        bool isRead();
        float getTemperatureC();
        float getTemperatureF();
        float getHeatIndexC();
        float getHeatIndexF();
        float getHumidity();
        DHT getDHT();
};

#endif