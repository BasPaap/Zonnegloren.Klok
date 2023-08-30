// TimeSpan.h

#ifndef _DATETIME_h
#define _DATETIME_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include "TimeSpan.h"

/**************************************************************************/
/*!
    @brief  Simple general-purpose date/time class (no TZ / DST / leap
            seconds).

    This class stores date and time information in a broken-down form, as a
    tuple (year, month, day, hour, minute, second). The day of the week is
    not stored, but computed on request. The class has no notion of time
    zones, daylight saving time, or
    [leap seconds](http://en.wikipedia.org/wiki/Leap_second): time is stored
    in whatever time zone the user chooses to use.

    The class supports dates in the range from 1 Jan 2000 to 31 Dec 2099
    inclusive.
*/
/**************************************************************************/

#define SECONDS_FROM_1970_TO_2000                                              \
  946684800 ///< Unixtime for 2000-01-01 00:00:00, useful for initialization                 

class DateTime {

public:
    DateTime(uint32_t t = SECONDS_FROM_1970_TO_2000);
    DateTime(uint8_t hour, uint8_t min);
    DateTime(const DateTime& copy);
    
    /*!
        @brief  Return the hour        
    */
    uint8_t hour() const;

    /*!
        @brief  Return the minute.
        @return Minute (0--59).
    */
    uint8_t minute() const { return mm; }
    /*!
        @brief  Return the second.
        @return Second (0--59).
    */
    uint8_t second() const { return ss; }

    /* 32-bit times as seconds since 1970-01-01. */
    uint32_t unixtime(void) const;

    DateTime operator+(const TimeSpan& span);
    DateTime operator-(const TimeSpan& span);
    TimeSpan operator-(const DateTime& right);
    bool operator<(const DateTime& right) const;

    /*!
        @brief  Test if one DateTime is greater (later) than another.
        @warning if one or both DateTime objects are invalid, returned value is
          meaningless
        @param right DateTime object to compare
        @return True if the left DateTime is later than the right one,
          false otherwise
    */
    bool operator>(const DateTime& right) const { return right < *this; }

    /*!
        @brief  Test if one DateTime is less (earlier) than or equal to another
        @warning if one or both DateTime objects are invalid, returned value is
          meaningless
        @see use `isValid()` method to check if DateTime object is valid
        @param right DateTime object to compare
        @return True if the left DateTime is earlier than or equal to the
          right one, false otherwise
    */
    bool operator<=(const DateTime& right) const { return !(*this > right); }

    /*!
        @brief  Test if one DateTime is greater (later) than or equal to another
        @warning if one or both DateTime objects are invalid, returned value is
          meaningless
        @see use `isValid()` method to check if DateTime object is valid
        @param right DateTime object to compare
        @return True if the left DateTime is later than or equal to the right
          one, false otherwise
    */
    bool operator>=(const DateTime& right) const { return !(*this < right); }
    bool operator==(const DateTime& right) const;

    /*!
        @brief  Test if two DateTime objects are not equal.
        @warning if one or both DateTime objects are invalid, returned value is
          meaningless
        @see use `isValid()` method to check if DateTime object is valid
        @param right DateTime object to compare
        @return True if the two objects are not equal, false if they are
    */
    bool operator!=(const DateTime& right) const { return !(*this == right); }

protected:
    uint8_t hh;   ///< Hours 0-23
    uint8_t mm;   ///< Minutes 0-59
    uint8_t ss;   ///< Seconds 0-59
};



#endif