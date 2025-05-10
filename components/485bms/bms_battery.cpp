#include "bms_battery.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bms_battery {

static const char *TAG = "bms_battery";

void BmsBattery::setup() {
  ESP_LOGI(TAG, "Setting up BMS Battery component...");
}

void BmsBattery::update() {
  static uint8_t request[] = {0x5A, 0xA5, 0xA1, 0xB0, 0x0D, 0x00, 0x00, 0x2E, 0xDA};
  this->parent_->write_array(request, sizeof(request));
}

void BmsBattery::loop() {
  if (this->parent_->available()) {
    size_t available = this->parent_->read_array(cell_data_, 20);
    if (available == 20) {
      float voltages[10];
      float total = 0;

      for (int i = 0; i < 10; i++) {
        uint16_t raw = (cell_data_[i*2 + 1] << 8) | cell_data_[i*2];
        voltages[i] = raw / 1000.0f;
        total += voltages[i];
      }

      this->total_voltage_sensor_->publish_state(total);

      this->cell_1_sensor_->publish_state(voltages[0]);
      this->cell_2_sensor_->publish_state(voltages[1]);
      this->cell_3_sensor_->publish_state(voltages[2]);
      this->cell_4_sensor_->publish_state(voltages[3]);
      this->cell_5_sensor_->publish_state(voltages[4]);
      this->cell_6_sensor_->publish_state(voltages[5]);
      this->cell_7_sensor_->publish_state(voltages[6]);
      this->cell_8_sensor_->publish_state(voltages[7]);
      this->cell_9_sensor_->publish_state(voltages[8]);
      this->cell_10_sensor_->publish_state(voltages[9]);

      float soc = calculate_soc_(total / 10.0f);
      this->soc_sensor_->publish_state(soc);
    }
  }
}

float BmsBattery::calculate_soc_(float avg_voltage) {
  static const float soc_table[][2] = {
    {3.0f, 0.0f},
    {3.3f, 10.0f},
    {3.4f, 20.0f},
    {3.5f, 30.0f},
    {3.6f, 50.0f},
    {3.7f, 60.0f},
    {3.8f, 70.0f},
    {3.9f, 80.0f},
    {4.0f, 90.0f},
    {4.2f, 100.0f}
  };

  for (size_t i = 0; i < sizeof(soc_table)/sizeof(soc_table[0]) - 1; i++) {
    if (avg_voltage <= soc_table[i+1][0]) {
      float v0 = soc_table[i][0], s0 = soc_table[i][1];
      float v1 = soc_table[i+1][0], s1 = soc_table[i+1][1];
      return s0 + (avg_voltage - v0) * (s1 - s0) / (v1 - v0);
    }
  }

  return 100.0f;
}

}  // namespace bms_battery
}  // namespace esphomebms_battery.cpp
