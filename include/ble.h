#ifndef __BLE_H
#define __BLE_H

/** @brief Gas Service UUID. */
#define BT_UUID_GAS_SRV_VAL \
	BT_UUID_128_ENCODE(0x00000001, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief Data Characteristic UUID. */
#define BT_UUID_DATA_CHAR_VAL \
	BT_UUID_128_ENCODE(0x00000002, 0x1212, 0xefde, 0x1523, 0x785feabcd123)


#define BT_UUID_GAS_SRV           BT_UUID_DECLARE_128(BT_UUID_GAS_SRV_VAL)
#define BT_UUID_DATA_CHAR    BT_UUID_DECLARE_128(BT_UUID_DATA_CHAR_VAL)


int ble_init(void);

#endif // __BLE_H