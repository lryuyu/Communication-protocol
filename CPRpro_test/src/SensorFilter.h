#ifndef SENSORFILTER_H
#define SENSORFILTER_H
#include <Arduino.h>
#include <freertos/semphr.h>

#define FILTER_MAX 100
struct SimpleFilter {
    int buffer[FILTER_MAX] = {0};
    int index = 0;
    long sum = 0;
    int filled = 0;
};
struct SensorConfig {
    int pin;
    SimpleFilter filterState;
    volatile int latesValue;
    SemaphoreHandle_t mutex;
};

int simpleFilter(int pin, SimpleFilter& state) ;
[[noreturn]]void sensorTask(void *pvParameters);

#endif //SENSORFILTER_H