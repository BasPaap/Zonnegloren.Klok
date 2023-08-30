#include "DateTime.h"

/**************************************************************************/
/*!
    @brief  Constructor from number of seconds since 00:00:00
        
    This builds a DateTime from an integer specifying the number of seconds
    elapsed since midnight.
    
    @param t Time elapsed in seconds since 00:00:00.
*/
/**************************************************************************/
DateTime::DateTime(int64_t t) {
    // If this constructor is called with a negative value t, that means we want to count back from 00:00:00. Therefore, we'll add an entire day's worth
    // of seconds to t, which will get us the correct value.

    const int64_t secondsPerDay = static_cast<int64_t>(60 * 60) * 24; // static cast because sub expression 60*60 will overflow before being cast to a wider type.
    t = t % secondsPerDay;

    if (t < 0)
    {
        t = secondsPerDay + t;
    }
    
    ss = t % 60;
    t /= 60;
    mm = t % 60;
    t /= 60;
    hh = t % 24;
}

/**************************************************************************/
/*!
    @brief  Constructor from (hour, minute).
    @warning If the provided parameters are not valid (e.g. 31 February),
           the constructed DateTime will be invalid.
    
    @param hour,min Hour (0--23), and minute (0--59).
*/
/**************************************************************************/
DateTime::DateTime(uint8_t hour, uint8_t min) {    
    hh = hour;
    mm = min;
    ss = 0;    
}

/**************************************************************************/
/*!
    @brief  Copy constructor.
    @param copy DateTime to copy.
*/
/**************************************************************************/
DateTime::DateTime(const DateTime& copy)
    : hh(copy.hh), mm(copy.mm), ss(copy.ss) {}

/**************************************************************************/
/*!
      @brief  Return the hour in 12-hour format.
      @return Hour (0--11).
*/
/**************************************************************************/
uint8_t DateTime::hour() const {
    if (hh >= 12) { // 1 o'clock or later
        return hh - 12;
    }
    else { // morning
        return hh;
    }
}


int32_t DateTime::totalSeconds(void) const {
    int32_t t = ((unsigned long)hh * 60 + mm) * 60 + ss;
    return t;
}

/**************************************************************************/
/*!
    @brief  Add a TimeSpan to the DateTime object
    @param span TimeSpan object
    @return New DateTime object with span added to it.
*/
/**************************************************************************/
DateTime DateTime::operator+(const TimeSpan& span) {
    return DateTime(totalSeconds() + span.totalseconds());
}

/**************************************************************************/
/*!
    @brief  Subtract a TimeSpan from the DateTime object
    @param span TimeSpan object
    @return New DateTime object with span subtracted from it.
*/
/**************************************************************************/
DateTime DateTime::operator-(const TimeSpan& span) {
    return DateTime(totalSeconds() - span.totalseconds());
}

/**************************************************************************/
/*!
    @brief  Subtract one DateTime from another

    @note Since a TimeSpan cannot be negative, the subtracted DateTime
        should be less (earlier) than or equal to the one it is
        subtracted from.

    @param right The DateTime object to subtract from self (the left object)
    @return TimeSpan of the difference between DateTimes.
*/
/**************************************************************************/
TimeSpan DateTime::operator-(const DateTime& right) {
    return TimeSpan(totalSeconds() - right.totalSeconds());
}

/**************************************************************************/
/*!
    @author Anton Rieutskyi
    @brief  Test if one DateTime is less (earlier) than another.
    @warning if one or both DateTime objects are invalid, returned value is
        meaningless
    @param right Comparison DateTime object
    @return True if the left DateTime is earlier than the right one,
        false otherwise.
*/
/**************************************************************************/
bool DateTime::operator<(const DateTime& right) const {
    return (hh < right.hour() ||
                                (hh == right.hour() &&
                                    (mm < right.minute() ||
                                        (mm == right.minute() && ss < right.second()))));
}

/**************************************************************************/
/*!
    @author Anton Rieutskyi
    @brief  Test if two DateTime objects are equal.
    @warning if one or both DateTime objects are invalid, returned value is
        meaningless
    @param right Comparison DateTime object
    @return True if both DateTime objects are the same, false otherwise.
*/
/**************************************************************************/
bool DateTime::operator==(const DateTime& right) const {
    return (right.hour() == hh && right.minute() == mm &&
        right.second() == ss);
}

