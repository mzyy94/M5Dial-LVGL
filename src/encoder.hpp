// SPDX-License-Identifier: MIT

#include <driver/pulse_cnt.h>
#include <driver/gpio.h>

class Encoder
{
private:
    gpio_num_t _pin_a;
    gpio_num_t _pin_b;

    pcnt_unit_handle_t _pcnt_unit;
    pcnt_channel_handle_t _pcnt_chan_a;
    pcnt_channel_handle_t _pcnt_chan_b;

public:
    Encoder();
    ~Encoder();
    void setup(gpio_num_t pin_a = GPIO_NUM_40, gpio_num_t pin_b = GPIO_NUM_41);
    int getCount(bool clear = false);
    void reset();
};
