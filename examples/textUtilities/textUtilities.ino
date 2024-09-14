
#include <IoLogging.h>
#include <TextUtilities.h>

char sz[32] = {0};

void setup() {
    // This example logs using IoLogging, see the following guide to enable
    // https://www.thecoderscorner.com/products/arduino-libraries/io-abstraction/arduino-logging-with-io-logging/
    IOLOG_START_SERIAL

    // convert 102934 to 8 decimal places not padded.
    // the clrBuff version also clears the sz buffer first
    // IE does not concatenate.
    ltoaClrBuff(sz, 102934, 8, NOT_PADDED, sizeof sz);
    serlogF2(SER_DEBUG, "Str is: ", sz);

    // concatenate 00102934 (to 8 decimal places zero padded).
    // this variant concatenates to a zero terminated string
    fastltoa(sz, 102934, 8, '0', sizeof sz);
    serlogF2(SER_DEBUG, "Str is: ", sz);

    // clear the string
    sz[0] = 0;

    // convert a float into sz string to 4 places.
    fastftoa(sz, 1024.512F, 4, sizeof sz);
    serlogF2(SER_DEBUG, "Float: ", sz);

    // find a power of ten for decimal place calculation
    serlogF2(SER_DEBUG, "Dp To Div: ", dpToDivisor(5));

    // find the significant places needed to represent a value
    serlogF2(SER_DEBUG, "Dp To Div: ", valueToSignificantPlaces(50123, false));

    // get the single hex character of a digit between 0..15 and vice versa
    serlogF2(SER_DEBUG, "Hexchar: ", hexChar(12));
    serlogF2(SER_DEBUG, "HexVal: ", hexValueOf('D'));

    // convert a number into a hex string
    sz[0]=0;

    // convert a int into hex string
    intToHexString(sz, sizeof sz, 0xFACE, 4, true);
    serlogF2(SER_DEBUG, "Hex str: ", sz);
}

void loop() {
    delay(1000);
    // convert the time into seconds and then print via logging to 3dp.
    float now = millis() / 1000.0F;
    sz[0]=0;
    fastftoa(sz, now, 3, sizeof sz);
    serlogF2(SER_DEBUG, "Time = ", sz);
}