#include "Time.h"

/**************************************************************************/
/*!
    @brief  Constructor from number of seconds since 00:00:00
        
    This builds a Time from an integer specifying the number of seconds
    elapsed since midnight.
    
    @param t Time elapsed in seconds since 00:00:00.
*/
/**************************************************************************/
Time::Time(int64_t t) {
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
    
    @param hour,min Hour (0--23), and minute (0--59).
*/
/**************************************************************************/
Time::Time(uint8_t hour, uint8_t min) {    
    hh = hour;
    mm = min;
    ss = 0;    
}

/**************************************************************************/
/*!
    @brief  Copy constructor.
    @param copy Time to copy.
*/
/**************************************************************************/
Time::Time(const Time& copy)
    : hh(copy.hh), mm(copy.mm), ss(copy.ss) {}

/**************************************************************************/
/*!
      @brief  Return the hour in 12-hour format.
      @return Hour (0--11).
*/
/**************************************************************************/
uint8_t Time::hour() const {
    if (hh >= 12) { // 1 o'clock or later
        return hh - 12;
    }
    else { // morning
        return hh;
    }
}


int32_t Time::totalSeconds(void) const {
    int32_t t = ((unsigned long)hh * 60 + mm) * 60 + ss;
    return t;
}

/**************************************************************************/
/*!
    @brief  Add a TimeSpan to the Time object
    @param span TimeSpan object
    @return New Time object with span added to it.
*/
/**************************************************************************/
Time Time::operator+(const TimeSpan& span) {
    return Time(totalSeconds() + span.totalseconds());
}

/**************************************************************************/
/*!
    @brief  Subtract a TimeSpan from the Time object
    @param span TimeSpan object
    @return New Time object with span subtracted from it.
*/
/**************************************************************************/
Time Time::operator-(const TimeSpan& span) {
    return Time(totalSeconds() - span.totalseconds());
}

/**************************************************************************/
/*!
    @brief  Subtract one Time from another

    @note Since a TimeSpan cannot be negative, the subtracted Time
        should be less (earlier) than or equal to the one it is
        subtracted from.

    @param right The Time object to subtract from self (the left object)
    @return TimeSpan of the difference between Times.
*/
/**************************************************************************/
TimeSpan Time::operator-(const Time& right) {
    return TimeSpan(totalSeconds() - right.totalSeconds());
}

/**************************************************************************/
/*!
    @author Anton Rieutskyi
    @brief  Test if one Time is less (earlier) than another.
    @warning if one or both Time objects are invalid, returned value is
        meaningless
    @param right Comparison Time object
    @return True if the left Time is earlier than the right one,
        false otherwise.
*/
/**************************************************************************/
bool Time::operator<(const Time& right) const {
    return (hh < right.hour() ||
                                (hh == right.hour() &&
                                    (mm < right.minute() ||
                                        (mm == right.minute() && ss < right.second()))));
}

/**************************************************************************/
/*!
    @author Anton Rieutskyi
    @brief  Test if two Time objects are equal.
    @warning if one or both Time objects are invalid, returned value is
        meaningless
    @param right Comparison Time object
    @return True if both Time objects are the same, false otherwise.
*/
/**************************************************************************/
bool Time::operator==(const Time& right) const {
    return (right.hour() == hh && right.minute() == mm &&
        right.second() == ss);
}

