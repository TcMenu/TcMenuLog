
/**
 * @file IoLogging.h
 *
 * Some very basic logging utilities for any IoAbstraction user that log to a chosen serial interface. Turned on
 * by un-commenting the define. Should NOT be used in production.
 */

#include "IoLogging.h"

#ifdef IO_LOGGING_DEBUG

unsigned int enabledLevels = IO_LOGGING_DEFAULT_LEVEL;

void serlogHexDump(SerLoggingLevel level, const char *title, const void* data, size_t strlen) {
    if(!serLevelEnabled(level)) return;

    logTimeAndLevel(title, level);
    LoggingPort.println();

    const auto str = (const uint8_t *) data;
    static const  char hexChar[] = { "0123456789ABCDEF" };
    for (size_t ii = 0; ii < strlen; ii++) {
        char sz[4];
        sz[0] = hexChar[str[ii] >> 4];
        sz[1] = hexChar[str[ii] & 0x0f];
        sz[2] = ((ii % 8) == 7) ? '\n' : ' ';
        sz[3] = 0;
        LoggingPort.print(sz);
    };
    LoggingPort.println();
}

const char* prettyLevel(SerLoggingLevel level) {
    switch(level) {
        case SER_WARNING: return "WRN";
        case SER_ERROR: return "ERR";
        case SER_DEBUG: return "DBG";
        case SER_TCMENU_INFO: return "TCM";
        case SER_TCMENU_DEBUG: return "TCD";
        case SER_NETWORK_INFO: return "NET";
        case SER_NETWORK_DEBUG: return "NTD";
        case SER_IOA_INFO: return "IOA";
        case SER_IOA_DEBUG: return "IOD";
        case SER_USER_1: return "U01";
        case SER_USER_2: return "U02";
        case SER_USER_3: return "U03";
        case SER_USER_4: return "U04";
        case SER_USER_5: return "U05";
        case SER_USER_6: return "U06";
        default: return "???";
    }
}

#ifdef BUILD_FOR_PICO_CMAKE
PrintfLogger LoggingPort;
unsigned long millis() {
    return to_ms_since_boot(get_absolute_time());
}

unsigned long micros() {
    return to_us_since_boot(get_absolute_time());
}
#endif

#ifdef LOGGING_USES_MBED
volatile bool timingStarted = false;
Timer ioaTimer;
unsigned long millis() {
    if(!timingStarted) {
        timingStarted = true;
        ioaTimer.start();
    }
    return ioaTimer.read_ms();
}

unsigned long micros() {
    if(!timingStarted) {
        timingStarted = true;
        ioaTimer.start();
    }
    return (unsigned long) ioaTimer.read_high_resolution_us();
}
#endif

#endif
