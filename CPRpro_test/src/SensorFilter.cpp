#include "SensorFilter.h"

int simpleFilter(const int pin ,SimpleFilter& state) {
    const int new_val = analogRead(pin);
    const int old_val = state.buffer[state.index];
    state.sum = state.sum + new_val - old_val;
    state.buffer[state.index] = new_val;
    state.index = (state.index + 1) % FILTER_MAX;
    if (state.filled < FILTER_MAX) state.filled++;
    return state.sum /state.filled;
}

[[noreturn]]void sensorTask(void *pvParameters) {
    auto* sensor = static_cast<SensorConfig *>(pvParameters);
    while (true) {
        const int val = simpleFilter(sensor->pin,sensor->filterState);
        if (xSemaphoreTake(sensor->mutex, (TickType_t)10) == pdTRUE) {
            sensor -> latesValue = val;
            xSemaphoreGive(sensor->mutex);
        }
        vTaskDelay(pdMS_TO_TICKS(2));
    }
}
