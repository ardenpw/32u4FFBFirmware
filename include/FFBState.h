#ifndef FFBState_h
#define FFBState_h

#include <stdint.h>

void FFB_handleControl(uint8_t cmd);

void FFB_enableActuators(void);
void FFB_effectStop(void);
void FFB_deviceReset(void);

#endif // #ifndef FFBState_h