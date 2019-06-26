#ifndef _EMONESP_H
#define _EMONESP_H

// -------------------------------------------------------------------
// General support code used by all modules
// -------------------------------------------------------------------

#include "debug.h"
#include "profile.h"

#ifndef RAPI_PORT
#ifdef ESP32
#include "HardwareSerial.h"
extern HardwareSerial Serial1;
#define RAPI_PORT Serial1
#elif defined(ESP8266)
#define RAPI_PORT Serial
#else
#error Platform not supported
#endif
#endif

// https://stackoverflow.com/questions/4415524/common-array-length-macro-for-c
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#endif // _EMONESP_H
