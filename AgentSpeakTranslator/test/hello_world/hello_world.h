/* File hello_world.h generated from hello_world.asl using AgentSpeakTranslator */

#ifndef __HELLO_WORLD_H
#define __HELLO_WORLD_H
#include <stdbool.h>
#include "types.h"


/* "public" interface */
void init(void);
void next_step(void);
bool can_add_event(void);
void clear(void);
void updateBeliefs(void);

/* "public" trigger functions */
void achieve_start(void);
void achieve_count(void);

 /* setters for belief base */
void set_testSetable(int);
#endif /* __HELLO_WORLD_H */
