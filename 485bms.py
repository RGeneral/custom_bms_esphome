from esphome.components import sensor
import esphome.config_validation as cv
import esphome.codegen as cg

DEPENDENCIES = ['uart']

bms_battery_ns = cg.esphome_ns.namespace('bms_battery')
BmsBattery = bms_battery_ns.class_('BmsBattery', cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BmsBattery),
    cv.Required('uart_parent'): cv.use_id(cg.UARTDevice),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    parent = yield cg.get_variable(config['uart_parent'])
    cg.add(var.set_uart_parent(parent))
