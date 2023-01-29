/**************************************************************************/
/*!
 * @file     Adafruit_SI5351.cpp
 *
 * @mainpage Adafruit Si5351 Library
 *
 * @author   K. Townsend (Adafruit Industries)
 *
 * @brief    Driver for the SI5351 160MHz Clock Gen
 *
 * @section  REFERENCES
 *
 * Si5351A/B/C Datasheet:
 * http://www.silabs.com/Support%20Documents/TechnicalDocs/Si5351.pdf
 *
 * Manually Generating an Si5351 Register Map:
 * http://www.silabs.com/Support%20Documents/TechnicalDocs/AN619.pdf
 *
 * @section license License
 *
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2014, Adafruit Industries
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**************************************************************************/
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
