#include <IO.h>
#include <eers.h>
#include <version.h>

bool indicator_value = true;
pin_t indicator_pin = hw_pin(D, 3);
void indicator_toggle(eer_t *indicator) {
    indicator_value = !indicator_value;
}

IO_new(indicator, _({
                      .io   = &hw(gpio),
                      .pin  = &indicator_pin,
                      .mode = IO_OUTPUT,
                      .on = { .change = indicator_toggle }
                  }));

int main(void)
{

    loop()
    {
        apply(IO, indicator,
              _({
                  .level = indicator_value,
              }));
    }
}
