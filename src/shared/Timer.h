/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2016 AscEmu Team <http://www.ascemu.org>
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TIMER_H
#define TIMER_H
/*
#include "Common.h"

#include <Util.h>

inline uint32 getMSTime()
{
    using namespace std::chrono;

    static const system_clock::time_point ApplicationStartTime = system_clock::now();

    return uint32(duration_cast<milliseconds>(system_clock::now() - ApplicationStartTime).count());
}
ARCEMU_INLINE uint32 getMSTime()
{
    uint32 MSTime = 0;
#ifdef WIN32
    MSTime = GetTickCount();
#else
    timeval tv;
    gettimeofday(&tv, NULL);
    MSTime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
    return MSTime;
}

inline uint32 getMSTimeDiff(uint32 oldMSTime, uint32 newMSTime)
{
    // getMSTime() have limited data range and this is case when it overflow in this tick
    if (oldMSTime > newMSTime)
        return (0xFFFFFFFF - oldMSTime) + newMSTime;
    else
        return newMSTime - oldMSTime;
}

inline uint32 GetMSTimeDiffToNow(uint32 oldMSTime)
{
    return getMSTimeDiff(oldMSTime, getMSTime());
}

struct IntervalTimer
{
    public:

    IntervalTimer()
        : _interval(0), _current(0)
    {}

    void Update(time_t diff)
    {
        _current += diff;
        if (_current < 0)
            _current = 0;
    }

    bool Passed()
    {
        return _current >= _interval;
    }

    void Reset()
    {
        if (_current >= _interval)
            _current %= _interval;
    }

    void SetCurrent(time_t current)
    {
        _current = current;
    }

    void SetInterval(time_t interval)
    {
        _interval = interval;
    }

    time_t GetInterval() const
    {
        return _interval;
    }

    time_t GetCurrent() const
    {
        return _current;
    }

    private:

    time_t _interval;
    time_t _current;
};

struct TimeTracker
{
    public:

    TimeTracker(time_t expiry)
        : i_expiryTime(expiry)
    {}

    void Update(time_t diff)
    {
        i_expiryTime -= diff;
    }

    bool Passed() const
    {
        return i_expiryTime <= 0;
    }

    void Reset(time_t interval)
    {
        i_expiryTime = interval;
    }

    time_t GetExpiry() const
    {
        return i_expiryTime;
    }

    private:

    time_t i_expiryTime;
};

struct TimeTrackerSmall
{
    public:

    TimeTrackerSmall(uint32 expiry = 0)
        : i_expiryTime(expiry)
    {}

    void Update(int32 diff)
    {
        i_expiryTime -= diff;
    }

    bool Passed() const
    {
        return i_expiryTime <= 0;
    }

    void Reset(uint32 interval)
    {
        i_expiryTime = interval;
    }

    int32 GetExpiry() const
    {
        return i_expiryTime;
    }

    private:

    int32 i_expiryTime;
};

struct PeriodicTimer
{
    public:

    PeriodicTimer(int32 period, int32 start_time)
        : i_period(period), i_expireTime(start_time)
    {}

    bool Update(const uint32 diff)
    {
        if ((i_expireTime -= diff) > 0)
            return false;

        i_expireTime += i_period > int32(diff) ? i_period : diff;
        return true;
    }

    void SetPeriodic(int32 period, int32 start_time)
    {
        i_expireTime = start_time;
        i_period = period;
    }

    // Tracker interface
    void TUpdate(int32 diff) { i_expireTime -= diff; }
    bool TPassed() const { return i_expireTime <= 0; }
    void TReset(int32 diff, int32 period) { i_expireTime += period > diff ? period : diff; }

    private:

    int32 i_period;
    int32 i_expireTime;
};
*/
#endif
