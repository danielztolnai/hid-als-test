#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include "AmbientLightSensor.h"

AmbientLightSensor ambient_light_sensor;
BH1750 bh1750{0x23};

void setup()
{
    Wire.begin();
    bh1750.begin();
}

void loop()
{
    if (bh1750.measurementReady()) {
        auto lux = bh1750.readLightLevel();
        ambient_light_sensor.update(static_cast<uint32_t>(lux * 10));
    }

    ambient_light_sensor.handle();
}
