#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <stdio.h>

#include "sensor.h"

LOG_MODULE_REGISTER(main_module, 4);

int main(void)
{
        int err = 0;

        err = sensor_init();
        if (err) {
                LOG_ERR("sensor_init failed with error code %d\n", err);
                return err;
        }

        return err;
}
 