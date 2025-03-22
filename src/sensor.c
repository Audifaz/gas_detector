#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(sensor_module, 4);

static const struct device *dev;

int sensor_fetch(){
    struct sensor_value temp, press, humidity, gas_res;

    sensor_sample_fetch(dev);
    sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
    sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
    sensor_channel_get(dev, SENSOR_CHAN_GAS_RES, &gas_res);

    LOG_DBG("T: %d.%06d; P: %d.%06d; H: %d.%06d; G: %d.%06d\n",
                    temp.val1, temp.val2, press.val1, press.val2,
                    humidity.val1, humidity.val2, gas_res.val1,
                    gas_res.val2);
    
    return 0;
}

int sensor_init(void)
{
    dev = DEVICE_DT_GET_ONE(bosch_bme680);
    
    if (!device_is_ready(dev)) {
            printk("sensor: device not ready.\n");
            return ENXIO;
    }

    LOG_DBG("Device %p name is %s\n", dev, dev->name);

    return 0;
}