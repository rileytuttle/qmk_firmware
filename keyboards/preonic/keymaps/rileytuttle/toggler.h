#include "timer.h"

const uint16_t DOUBLE_TAP_THRESHOLD = 90;

typedef struct {
  bool prev;
  bool toggle;
  uint16_t timer;
} TogglerData;

void toggle_reset(TogglerData *data)
{
  data->prev = false;
  data->toggle = false;
  data->timer = 0;
}

/**
 * this toggler will toggle on with a quick double tap
 * and toggle off with a single tap
 */
bool toggle_update(TogglerData *data, const bool current)
{
  if (!data->toggle)
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
      data->toggle = true;
    }
  }
  else
  {
    if (!data->prev && current)
    {
      data->toggle = false;
    }
  }
  data->prev = current;
  return data->toggle;
}
