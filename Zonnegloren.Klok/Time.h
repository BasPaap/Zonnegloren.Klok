// Time.h

#ifndef _TIME_h
#define _TIME_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include "TimeSpan.h"

/**************************************************************************/
/*!
    @brief  Simple general-purpose time class 

    Derived from RTCLib's DateTime class
*/
/**************************************************************************/

class Time {

public:
    Time(int64_t t = 0);
    Time(uint8_t hour, uint8_t min);
    Time(const Time& copy);
    
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

    int32_t totalSeconds(void) const;

    Time operator+(const TimeSpan& span);
    Time operator-(const TimeSpan& span);
    TimeSpan operator-(const Time& right);
    bool operator<(const Time& right) const;

    /*!
        @brief  Test if one Time is greater (later) than another.
        @warning if one or both Time objects are invalid, returned value is
          meaningless
        @param right Time object to compare
        @return True if the left Time is later than the right one,
          false otherwise
    */
    bool operator>(const Time& right) const { return right < *this; }

    /*!
        @brief  Test if one Time is less (earlier) than or equal to another
        @warning if one or both Time objects are invalid, returned value is
          meaningless
        @see use `isValid()` method to check if Time object is valid
        @param right Time object to compare
        @return True if the left Time is earlier than or equal to the
          right one, false otherwise
    */
    bool operator<=(const Time& right) const { return !(*this > right); }

    /*!
        @brief  Test if one Time is greater (later) than or equal to another
        @warning if one or both Time objects are invalid, returned value is
          meaningless
        @see use `isValid()` method to check if Time object is valid
        @param right Time object to compare
        @return True if the left Time is later than or equal to the right
          one, false otherwise
    */
    bool operator>=(const Time& right) const { return !(*this < right); }
    bool operator==(const Time& right) const;

    /*!
        @brief  Test if two Time objects are not equal.
        @warning if one or both Time objects are invalid, returned value is
          meaningless
        @see use `isValid()` method to check if Time object is valid
        @param right Time object to compare
        @return True if the two objects are not equal, false if they are
    */
    bool operator!=(const Time& right) const { return !(*this == right); }

protected:
    uint8_t hh;   ///< Hours 0-23
    uint8_t mm;   ///< Minutes 0-59
    uint8_t ss;   ///< Seconds 0-59
};

#endif