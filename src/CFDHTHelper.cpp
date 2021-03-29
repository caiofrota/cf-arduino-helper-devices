/**
 * CFDHTHelper.cpp
 * 
 * DHT Helper for CF Arduino Devices.
 * 
 * @author  Caio Frota <caiofrota@gmail.com>
 * @version 1.0
 * @since   Mar, 2021
 */

#include <CFDHTHelper.h>                                                                            // CF DHT Helper Header.

/**
 * Constructor.
 *
 * @param pinData Pin Data.
 */
CFDHTHelper::CFDHTHelper(int dhtType, int pinData):
        _dht(dhtType, pinData), _pinReset(-1),
        _read(false),
        _temperatureC(0), _temperatureF(0), _heatIndexC(0), _heatIndexF(0), _humidity(0),
        _lastReading(0), _readingDelay(1000) {
    
}


/**
 * Constructor.
 * DHT Workaround for fail reading failure.
 *
 * @param pinData Pin Data.
 * @param pinReset Pin used for forced reset when reading is fail.
 */
CFDHTHelper::CFDHTHelper(int dhtType, int pinData, int pinReset):
        _dht(dhtType, pinData), _pinReset(pinReset),
        _read(false),
        _temperatureC(0), _temperatureF(0), _heatIndexC(0), _heatIndexF(0), _humidity(0),
        _lastReading(0), _readingDelay(1000) {
    
}

/**
 * Initial setup.
 */
void CFDHTHelper::begin() {
    if (_pinReset > -1) {
        pinMode(_pinReset, OUTPUT);                                                                 // DHT Workaround for fail reading failure.
    }
    _dht.begin();
}

/**
 * Control push button state.
 *
 * @returns True if it was read succesfully.
 */
bool CFDHTHelper::loop() {
    if (_lastReading == 0 || millis() - _lastReading > _readingDelay) {
        // Read
        _lastReading = millis();
        
        _temperatureC = _dht.readTemperature();
        _temperatureF = _dht.readTemperature(true);
        _humidity = _dht.readHumidity();
        
        // Check if it was read.
        if (isnan(_temperatureC) || isnan(_temperatureF) || isnan(_humidity)) {
            _temperatureC = 0;
            _temperatureF = 0;
            _heatIndexC = 0;
            _heatIndexF = 0;
            _humidity = 0;
            _read = false;
            
            // DHT Workaround for fail reading failure.
            digitalWrite(_pinReset, !digitalRead(_pinReset));                                       // Force pshysical power recycle.
            
            return false;
        }
        
        _temperatureC = roundf(_temperatureC * 10) / 10;
        _temperatureF = roundf(_temperatureF * 10) / 10;
        _humidity = roundf(_humidity * 10) / 10;
        _heatIndexC = roundf(_dht.computeHeatIndex(_temperatureC, _humidity, false) * 10) / 10;
        _heatIndexF = roundf(_dht.computeHeatIndex(_temperatureC, _humidity) * 10) / 10;
        
        _read = true;
    }
}

/**
 * Check if it's read.
 *
 * @returns True if it's read.
 */
bool CFDHTHelper::isRead() {
    return _read;
}

/**
 * Get Temperature in C.
 *
 * @returns Temperature in C.
 */
float CFDHTHelper::getTemperatureC() {
    return _temperatureC;
}

/**
 * Get Temperature in F.
 *
 * @returns Temperature in F.
 */
float CFDHTHelper::getTemperatureF() {
    return _temperatureF;
}

/**
 * Get Heat Index in C.
 *
 * @returns Heat Index in C.
 */
float CFDHTHelper::getHeatIndexC() {
    return _heatIndexC;
}

/**
 * Get Heat Index in F.
 *
 * @returns Heat Index in F.
 */
float CFDHTHelper::getHeatIndexF() {
    return _heatIndexF;
}

/**
 * Get Humidity.
 *
 * @returns Humidity.
 */
float CFDHTHelper::getHumidity() {
    return _humidity;
}

/**
 * Get DHT Object.
 *
 * @returns DHT.
 */
DHT CFDHTHelper::getDHT() {
    return _dht;
}