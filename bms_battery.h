#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace bms_battery {

class BmsBattery : public PollingComponent {
 public:
  sensor::Sensor *total_voltage_sensor_{new sensor::Sensor()};
  sensor::Sensor *soc_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_1_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_2_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_3_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_4_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_5_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_6_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_7_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_8_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_9_sensor_{new sensor::Sensor()};
  sensor::Sensor *cell_10_sensor_{new sensor::Sensor()};

  void setup() override;
  void update() override;
  void loop() override;

 protected:
  UARTDevice *parent_;
  uint8_t cell_data_[20]{};
};

}  // namespace bms_battery
}  // namespace esphome
