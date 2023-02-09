#include <Button.h>
#include <Chip.h>
#include <Clock.h>
#include <IO.h>
#include <eer_app.h>
#include <sys.h>


Chip(sys,
    _({}),
    _({
        .frequency = {.cpu = CPU_FREQUENCY},
        .sys       = &hw(sys),
    })
);

Clock(clk, &hw(timer), TIMESTAMP);


bool  indicator_value = true;
pin_t indicator_pin   = hw_pin(INDICATOR_PORT, INDICATOR_PIN);
IO_new(indicator,
       _({.io = &hw(gpio), .pin = &indicator_pin, .mode = IO_OUTPUT}));

/* Seatbelt Fastened Sensor */
pin_t belt_sensor_pin = hw_pin(SENSOR_PORT, SENSOR_PIN);
Button(belt_sensor, _({
                        .io  = &hw(gpio),
                        .pin = &belt_sensor_pin,

                        .clock = &clk.state.time,

                        .type            = BUTTON_PUSH_PULLUP,
                        .bounce_delay_ms = 100,
                    }));

int main(void)
{
    ignite(sys, clk);

    with(belt_sensor)
    {
        apply(IO, indicator,
              _({
                  .level = Button_is_pressed(&belt_sensor),
              }));
    }

    halt(0);
}
