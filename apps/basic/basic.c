#include <IO.h>
#include <Button.h>
#include <eers.h>
#include <version.h>

pin_t sensor_pin = hw_pin(D, 2);
IO_new(sensor, _({
                   .io = &hw.io,
                   .pin = &sensor_pin,
                   .mode = IO_INPUT,
               }));

pin_t indicator_pin = hw_pin(D, 2);
IO_new(indicator, _({
                   .io = &hw.io,
                   .pin = &indicator_pin,
                   .mode = IO_OUTPUT,
               }));

int main(void) {
  bool debug = false;

  // Event-loop
  loop(sensor) {
    // Debug Step
    debug = !debug;

    apply(IO, indicator,
          _({
              .level = debug,
          }));
  }
}
