#include "timer.h"

const uint16_t DOUBLE_TAP_THRESHOLD = 100;

typedef struct {
  bool prev;
  bool toggle;
  uint16_t timer;
} TogglerData;

bool toggle_update(TogglerData *data, const bool current)
{
  if (data->prev && !current)
  {
    // on a falling edge start a timer
    data->timer = timer_read();
  }
  else if (!data->prev && current && timer_elapsed(data->timer) < DOUBLE_TAP_THRESHOLD)
  {
    // if we have a rising edge shortly after the previous falling edge
    // toggle the layer hold
    data->toggle = !data->toggle;
  }
  data->prev = current;
  return data->toggle;
}
