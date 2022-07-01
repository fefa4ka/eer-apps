#include <IO.h>
#include <Clock.h>
#include <Button.h>
#include <eers.h>

Clock(clk, &hw(timer), TIMESTAMP);


bool indicator_value = true;
pin_t indicator_pin = hw_pin(B, 12);
void indicator_toggle(eer_t *indicator) {
    indicator_value = !indicator_value;
}
IO_new(indicator, _({
                      .io   = &hw(gpio),
                      .pin  = &indicator_pin,
                      .mode = IO_OUTPUT
                  }));

/* Seatbelt Fastened Sensor */
pin_t belt_sensor_pin = hw_pin(A, 4);
Button(belt_sensor, _({
                   .io  = &hw(gpio),
                   .pin = &belt_sensor_pin,

                   .clock = &clk.state.time,

                   .type            = BUTTON_PUSH_PULLUP,
                   .bounce_delay_ms = 100,
               }));

int main(void)
{
    clk.props.onSecond = &indicator_toggle;

    loop(clk, belt_sensor)
    {
        apply(IO, indicator,
              _({
                  .level = Button_is_pressed(&belt_sensor),
              }));
    }
}
