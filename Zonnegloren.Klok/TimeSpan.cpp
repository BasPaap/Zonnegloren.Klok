// 
// 
// 

#include "TimeSpan.h"


/**************************************************************************/
/*!
    @brief  Create a new TimeSpan object in seconds
    @param seconds Number of seconds
*/
/**************************************************************************/
Bas::TimeSpan::TimeSpan(int32_t seconds) : _seconds(seconds) {}

/**************************************************************************/
/*!
    @brief  Copy constructor, make a new TimeSpan using an existing one
    @param copy The TimeSpan to copy
*/
/**************************************************************************/
Bas::TimeSpan::TimeSpan(const TimeSpan& copy) : _seconds(copy._seconds) {}

/**************************************************************************/
/*!
    @brief  Add two TimeSpans
    @param right TimeSpan to add
    @return New TimeSpan object, sum of left and right
*/
/**************************************************************************/
Bas::TimeSpan Bas::TimeSpan::operator+(const TimeSpan& right) {
    return TimeSpan(_seconds + right._seconds);
}

/**************************************************************************/
/*!
    @brief  Subtract a TimeSpan
    @param right TimeSpan to subtract
    @return New TimeSpan object, right subtracted from left
*/
/**************************************************************************/
Bas::TimeSpan Bas::TimeSpan::operator-(const TimeSpan& right) {
    return TimeSpan(_seconds - right._seconds);
}