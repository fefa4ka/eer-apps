#include <Chip.h>
#include <Clock.h>
#include <IO.h>
#include <eers.h>
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
void  indicator_toggle(eer_t *indicator) { indicator_value = !indicator_value; }
IO_new(indicator, _({
                      .io = &hw(gpio),
                      .pin = &indicator_pin,
                      .mode = IO_OUTPUT,
                  }));

int main(void)
{
    clk.props.onSecond = &indicator_toggle;

    loop(sys, clk)
    {
        apply(IO, indicator,
              _({
                  .level = indicator_value,
              }));
    }
}
