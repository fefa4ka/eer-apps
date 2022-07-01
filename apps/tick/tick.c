//#include <Button.h>
#include <Clock.h>
#include <IO.h>
#include <eers.h>
#include <sys.h>

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
    enum ch573_clock_source clock = CPU_FREQUENCY;
    eer_hw_sys.clock.set(&clock);
    clk.props.onSecond = &indicator_toggle;

    loop(clk)
    {
        apply(IO, indicator,
              _({
                  .level = indicator_value,
              }));
    }
}
