#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(sensor_module, 4);
static void sample_fetch_fn(struct k_work *work);

static const struct device *dev;
static K_WORK_DELAYABLE_DEFINE(sample_work, sample_fetch_fn);

static void sample_fetch_fn(struct k_work *work){
    struct sensor_value temp, press, humidity, gas_res;

    sensor_sample_fetch(dev);
    sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
    sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
    sensor_channel_get(dev, SENSOR_CHAN_GAS_RES, &gas_res);

    LOG_DBG("T: %d.%06d; P: %d.%06d; H: %d.%06d; G: %d.%06d",
                    temp.val1, temp.val2, press.val1, press.val2,
                    humidity.val1, humidity.val2, gas_res.val1,
                    gas_res.val2);
    
    k_work_reschedule(&sample_work, K_SECONDS(1));
}

int sensor_init(void)
{
    dev = DEVICE_DT_GET_ONE(bosch_bme680);
    
    if (!device_is_ready(dev)) {
            printk("sensor: device not ready.\n");
            return ENXIO;
    }

    LOG_DBG("Device %p name is %s\n", dev, dev->name);

    k_work_reschedule(&sample_work, K_SECONDS(2));

    return 0;
}