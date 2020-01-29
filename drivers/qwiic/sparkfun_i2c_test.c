#include <print.h>
#include "sparkfun_i2c_test.h"
#include "i2c_master.h"

static const uint8_t first = 0x01;

void sparkfun_i2c_test_init(void) {
    i2c_init();
    sparkfun_i2c_send_test();
}

void sparkfun_i2c_send_test(void) {
    i2c_transmit(0x04, &first, 1, 100);
}
