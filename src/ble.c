#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include <zephyr/logging/log.h>

#include "ble.h"

LOG_MODULE_REGISTER(ble_module, 4);

static bool notify_enabled = false;
static bool button_state = false;

#define DEVICE_NAME             CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN         (sizeof(DEVICE_NAME) - 1)

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};


static void ccc_cfg_changed(const struct bt_gatt_attr *attr,
    uint16_t value)
{
    notify_enabled = (value == BT_GATT_CCC_NOTIFY);
}

static ssize_t read_button(struct bt_conn *conn,
    const struct bt_gatt_attr *attr,
    void *buf,
    uint16_t len,
    uint16_t offset)
{
    const char *value = attr->user_data;

    LOG_DBG("Attribute read, handle: %u, conn: %p", attr->handle,
    (void *)conn);


    return bt_gatt_attr_read(conn, attr, buf, len, offset, value, sizeof(*value));
}

/* Gas Service Declaration */
BT_GATT_SERVICE_DEFINE(gas_svc,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_GAS_SRV),
        BT_GATT_CHARACTERISTIC(BT_UUID_DATA_CHAR,
                       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                       BT_GATT_PERM_READ, read_button, NULL, &button_state),
        BT_GATT_CCC(ccc_cfg_changed,
                BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
    );

int ble_init(void)
{
    int err = 0;

    err = bt_enable(NULL);
    if (err) {
        LOG_ERR("Bluetooth init failed with error code %d\n", err);
        return err;
    }

    LOG_DBG("Bluetooth initialized\n");

    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err){
        LOG_ERR("Advertising failed to start (err %d)\n", err);
        return err;
    }

    return err;
}