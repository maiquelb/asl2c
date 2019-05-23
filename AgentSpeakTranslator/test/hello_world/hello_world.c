/* File hello_world.c generated from hello_world.asl using AgentSpeakTranslator */

#include <stdbool.h>
#include "types.h"
#include "hello_world.h"
#include "actions.h"

/* belief base */
static bool started_set = false;

static bool testSetable_set = false;
static int testSetable_param0;

void set_testSetable(int param0)
{
  testSetable_set = true;
  testSetable_param0 = param0;
}

/* triggers */
typedef enum
{
  NONE,
  ADD_ACHIEVE_START,
  ADD_ACHIEVE_COUNT
} triggert;

/* events */
typedef struct
{
  triggert trigger;
} eventt;

/* returns true if the event is triggering */
static bool is_triggering(eventt event)
{
  bool triggering = false;
  switch (event.trigger)
  {
    case ADD_ACHIEVE_START:
      triggering = true;
      break;
    case ADD_ACHIEVE_COUNT:
      triggering = true;
      break;
    default:  // nothing to do
      break;
  }
  return triggering;
}

/* changes belief base according to triggering event */
static void handle_percept(eventt event)
{
  switch (event.trigger)
  {
    default:  // nothing to do
      break;
  }
}

/* in the event-queue-less version, we have potentially two events:
 * 1) an event that needs to be completed, this one will always be given
 *    preference, if set
 * 2) a deferred event, this one will be used, if no event to complete
 *    is set
 */
static bool rtc_event_set;
static eventt rtc_event;
static bool deferred_event_set;
static eventt deferred_event;

/* initialise the events, there's not much to do here... */
static void init_events(void)
{
  rtc_event_set = false;
  deferred_event_set = false;
}

/* indicate whether another event can be generated */
bool can_add_event(void)
{
  return !rtc_event_set;
}

/* add deferred event */
static bool add_event_new_focus(eventt event)
{
  if (!deferred_event_set)
  {
    deferred_event = event;
    deferred_event_set = true;
    return true;
  }
  // TODO: This should not happen
  return false;
}

/* add event to complete */
static bool add_event_to_complete(eventt event)
{
  if (!rtc_event_set)
  {
    rtc_event = event;
    rtc_event_set = true;
    return true;
  }
  // TODO: This should not happen
  return false;  
}

/* without an event queue, we handle external events immediately, as they are supposed
   to be only added when can_add_event() returns true, i.e., no event_to_complete is set */
static bool add_external_event(eventt event)
{
  return add_event_to_complete(event);
}

/* get next event: event_to_complete is given preference over deferred_event */
static eventt get_next_event(void)
{
  eventt event = { NONE };
  if (rtc_event_set) 
  {
    event = rtc_event;
    rtc_event_set = false;
  }
  else if (deferred_event_set)
  {
    event = deferred_event;
    deferred_event_set = false;
  }
  return event;
}

/* internal trigger functions */
static void internal_achieve_count(void)
{
  eventt event;
  event.trigger = ADD_ACHIEVE_COUNT;
  add_event_to_complete(event);
}

/* "public" trigger functions */
void achieve_start(void)
{
  eventt event;
  event.trigger = ADD_ACHIEVE_START;
  add_external_event(event);
}

void achieve_count(void)
{
  eventt event;
  event.trigger = ADD_ACHIEVE_COUNT;
  add_external_event(event);
}

/* applicable plan selection declarations */
static void add_achieve_start(void);

static void add_achieve_count(void);

/* plans */
/*
+!start()
   : not started()
   <- print("starting...");
      +started();
      +testSetable(0);
      !count()
*/
static bool add_achieve_start_plan0(void)
{
  /* instantiate trigger parameters */
  /* plan context, i.e., guards */
  if (started_set)
  {
    return false;
  }
  /* plan body */
  print("starting...");
  started_set = true;
  testSetable_set = true;
  testSetable_param0 = 0;
  internal_achieve_count();
  return true;
}

/*
+!count()
   : testSetable(X)
   <- print("counting...");
      ?testSetable(Y);
      +testSetable(Y);
      !count()
*/
static bool add_achieve_count_plan0(void)
{
  /* instantiate trigger parameters */
  /* plan context, i.e., guards */
  if (!testSetable_set)
  {
    return false;
  }
  int X = testSetable_param0;
  /* plan body */
  print("counting...");
  if (!testSetable_set)
  {
    // TODO: this case needs to be specified
  }
  int Y = testSetable_param0;
  testSetable_set = true;
  testSetable_param0 = Y;
  internal_achieve_count();
  return true;
}

/* applicable plan selection */
static void add_achieve_start(void)
{
  if (add_achieve_start_plan0())
  {
    return;
  }
  // TODO: Handle the case where no plan is applicable
  return;
}

static void add_achieve_count(void)
{
  if (add_achieve_count_plan0())
  {
    return;
  }
  // TODO: Handle the case where no plan is applicable
  return;
}

/* init */
void init(void)
{
  // initialise event queue
  init_events();
  // set initial beliefs
  // initial goal: !start()
  add_achieve_start();
}

/* clear */
void clear(void)
{
  // clear event queue
  init_events();
  // restart with initial goal: !start()
  add_achieve_start();
}

/* do one step */
void next_step(void)
{
  updateBeliefs();
  eventt event = get_next_event();
  handle_percept(event);
  if (!is_triggering(event))
  {
    event = get_next_event();
    handle_percept(event);
  }
  switch (event.trigger)
  {
    case ADD_ACHIEVE_START:
      add_achieve_start();
      break;
    case ADD_ACHIEVE_COUNT:
      add_achieve_count();
      break;
    default:  // nothing to do
      break;
  }
}
