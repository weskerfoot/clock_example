#include "pgmspace.h"
#include <stdlib.h>
#include <Adafruit_SI5351.h>
#include "esp32-hal-log.h"

extern "C"
void
setupClock() {
  ESP_LOGI("setupClock", "setupClock being called");
  initArduino();
  ESP_LOGI("setupClock", "arduino initialized");

  Adafruit_SI5351 clockgen = Adafruit_SI5351();

  ESP_LOGI("setupClock", "class initialized");

  //clockgen.setClockBuilderData();

  ESP_LOGI("setupClock", "setClockBuilderData called");

  if (clockgen.begin() != ERROR_NONE) {
    ESP_LOGI("setupClock", "clockgen.begin ERROR!! XXX");
    while(1);
  }
  ESP_LOGI("setupClock", "clockgen.begin called without errors");

  clockgen.setupPLL(SI5351_PLL_A, 35, 3493, 15625);
  //clockgen.setupPLLInt(SI5351_PLL_A, 35);

  ESP_LOGI("setupClock", "SHOULD be at 11.28 mhz");

  clockgen.setupMultisynth(0, SI5351_PLL_A, 78, 0, 1);
  //clockgen.setupMultisynth(0, SI5351_PLL_A, 78, 0, 1);

  clockgen.enableOutputs(true);
}
