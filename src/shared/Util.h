/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org/>
 * Copyright (C) 2008-2012 ArcEmu Team <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _UTIL_H
#define _UTIL_H

#include "Common.h"

#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// String Functions ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> StrSplit(const std::string & src, const std::string & sep);

// This HAS to be called outside the threads __try / __except block!
void SetThreadName(const char* format, ...);
time_t convTimePeriod(uint32 dLength, char dType);


// Searcher for map of structs
template<typename T, class S> struct Finder
{
    T val_;
    T S::* idMember_;

    Finder(T val, T S::* idMember) : val_(val), idMember_(idMember) {}
    bool operator()(const std::pair<int, S> &obj) { return obj.second.*idMember_ == val_; }
};

struct Tokens: public std::vector<char*>
{
    Tokens(const std::string &src, const char sep, uint32 vectorReserve = 0);
    ~Tokens() { delete[] m_str; }

    char* m_str;
};

inline uint32 secsToTimeBitFields(time_t secs)
{
    tm* lt = localtime(&secs);
    return (lt->tm_year - 100) << 24 | lt->tm_mon  << 20 | (lt->tm_mday - 1) << 14 | lt->tm_wday << 11 | lt->tm_hour << 6 | lt->tm_min;
}


extern SERVER_DECL const char* _StringToUTF8(const char* pASCIIBuf);
extern SERVER_DECL const char* _StringToANSI(const char* pUtf8Buf);
extern SERVER_DECL bool _IsStringUTF8(const char* str);

volatile long Sync_Add(volatile long* value);

volatile long Sync_Sub(volatile long* value);

#ifdef WIN32

typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // must be 0x1000
    LPCSTR szName; // pointer to name (in user addr space)
    DWORD dwThreadID; // thread ID (-1=caller thread)
    DWORD dwFlags; // reserved for future use, must be zero
} THREADNAME_INFO;

#endif

namespace Arcemu
{
    SERVER_DECL float round(float f);
    SERVER_DECL double round(double d);
    SERVER_DECL long double round(long double ld);

    /////////////////////////////////////////////////////////////////////////
    //void Sleep( unsigned long timems );
    //  Puts the calling thread to sleep for the specified miliseconds
    //
    //Parameter(s)
    //  unsigned long timemes  -  time interval to put the thread to sleep for
    //
    //Return Value
    //  None
    //
    //
    /////////////////////////////////////////////////////////////////////////
    void Sleep(unsigned long timems);
}


/////////////////////////////////////////////////////////
//uint32 getMSTime()
//  Returns the time elapsed in milliseconds
//
//Parameter(s)
//  None
//
//Return Value
//  Returns the time elapsed in milliseconds
//
//
/////////////////////////////////////////////////////////
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
#ifndef _FLAG96
#define _FLAG96

#ifndef PAIR64_HIPART
#define PAIR64_HIPART(x)   (uint32)((uint64(x) >> 32) & uint64(0x00000000FFFFFFFF))
#define PAIR64_LOPART(x)   (uint32)(uint64(x)         & uint64(0x00000000FFFFFFFF))
#endif

class flag96
{
private:
    uint32 part[3];
public:
    flag96(uint32 p1 = 0, uint32 p2 = 0, uint32 p3 = 0)
    {
        part[0] = p1;
        part[1] = p2;
        part[2] = p3;
    }

    flag96(uint64 p1, uint32 p2)
    {
        part[0] = PAIR64_LOPART(p1);
        part[1] = PAIR64_HIPART(p1);
        part[2] = p2;
    }

    inline bool IsEqual(uint32 p1 = 0, uint32 p2 = 0, uint32 p3 = 0) const
    {
        return (
            part[0] == p1 &&
            part[1] == p2 &&
            part[2] == p3);
    };

    inline bool HasFlag(uint32 p1 = 0, uint32 p2 = 0, uint32 p3 = 0) const
    {
        return (
            part[0] & p1 ||
            part[1] & p2 ||
            part[2] & p3);
    };

    inline void Set(uint32 p1 = 0, uint32 p2 = 0, uint32 p3 = 0)
    {
        part[0] = p1;
        part[1] = p2;
        part[2] = p3;
    };

    template<class type>
    inline bool operator < (type & right)
    {
        for (uint8 i = 3; i > 0; --i)
        {
            if (part[i - 1]<right.part[i - 1])
                return 1;
            else if (part[i - 1]>right.part[i - 1])
                return 0;
        }
        return 0;
    };

    template<class type>
    inline bool operator < (type & right) const
    {
        for (uint8 i = 3; i > 0; --i)
        {
            if (part[i - 1]<right.part[i - 1])
                return 1;
            else if (part[i - 1]>right.part[i - 1])
                return 0;
        }
        return 0;
    };

    template<class type>
    inline bool operator != (type & right)
    {
        if (part[0] != right.part[0]
            || part[1] != right.part[1]
            || part[2] != right.part[2])
            return true;
        return false;
    }

    template<class type>
    inline bool operator != (type & right) const
    {
        if (part[0] != right.part[0]
            || part[1] != right.part[1]
            || part[2] != right.part[2])
            return true;
        return false;
    };

    template<class type>
    inline bool operator == (type & right)
    {
        if (part[0] != right.part[0]
            || part[1] != right.part[1]
            || part[2] != right.part[2])
            return false;
        return true;
    };

    template<class type>
    inline bool operator == (type & right) const
    {
        if (part[0] != right.part[0]
            || part[1] != right.part[1]
            || part[2] != right.part[2])
            return false;
        return true;
    };

    template<class type>
    inline void operator = (type & right)
    {
        part[0] = right.part[0];
        part[1] = right.part[1];
        part[2] = right.part[2];
    };

    template<class type>
    inline flag96 operator & (type & right)
    {
        flag96 ret(part[0] & right.part[0], part[1] & right.part[1], part[2] & right.part[2]);
        return
            ret;
    };
    template<class type>
    inline flag96 operator & (type & right) const
    {
        flag96 ret(part[0] & right.part[0], part[1] & right.part[1], part[2] & right.part[2]);
        return
            ret;
    };

    template<class type>
    inline void operator &= (type & right)
    {
        *this = *this & right;
    };

    template<class type>
    inline flag96 operator | (type & right)
    {
        flag96 ret(part[0] | right.part[0], part[1] | right.part[1], part[2] | right.part[2]);
        return
            ret;
    };

    template<class type>
    inline flag96 operator | (type & right) const
    {
        flag96 ret(part[0] | right.part[0], part[1] | right.part[1], part[2] | right.part[2]);
        return
            ret;
    };

    template<class type>
    inline void operator |= (type & right)
    {
        *this = *this | right;
    };

    inline void operator ~ ()
    {
        part[2] = ~part[2];
        part[1] = ~part[1];
        part[0] = ~part[0];
    };

    template<class type>
    inline flag96 operator ^ (type & right)
    {
        flag96 ret(part[0] ^ right.part[0], part[1] ^ right.part[1], part[2] ^ right.part[2]);
        return
            ret;
    };

    template<class type>
    inline flag96 operator ^ (type & right) const
    {
        flag96 ret(part[0] ^ right.part[0], part[1] ^ right.part[1], part[2] ^ right.part[2]);
        return
            ret;
    };

    template<class type>
    inline void operator ^= (type & right)
    {
        *this = *this^right;
    };

    inline operator bool() const
    {
        return(
            part[0] != 0 ||
            part[1] != 0 ||
            part[2] != 0);
    };

    inline operator bool()
    {
        return(
            part[0] != 0 ||
            part[1] != 0 ||
            part[2] != 0);
    };

    inline bool operator ! () const
    {
        return(
            part[0] == 0 &&
            part[1] == 0 &&
            part[2] == 0);
    };

    inline bool operator ! ()
    {
        return(
            part[0] == 0 &&
            part[1] == 0 &&
            part[2] == 0);
    };

    inline uint32 & operator[](uint8 el)
    {
        return (part[el]);
    };

    inline uint32 operator[](uint8 el) const
    {
        return (part[el]);
    };
};
#endif

template <class T>
inline T CalculatePctF(T base, float pct)
{
    return T(base * pct / 100.0f);
}

template <class T>
inline T CalculatePctN(T base, int32 pct)
{
    return T(base * float(pct) / 100.0f);
}

template <class T>
inline T CalculatePctU(T base, uint32 pct)
{
    return T(base * float(pct) / 100.0f);
}

template <class T>
inline T AddPctF(T& base, float pct)
{
    return base += CalculatePctF(base, pct);
}

template <class T>
inline T AddPctN(T& base, int32 pct)
{
    return base += CalculatePctN(base, pct);
}

template <class T>
inline T AddPctU(T& base, uint32 pct)
{
    return base += CalculatePctU(base, pct);
}

template <class T>
inline T ApplyPctF(T& base, float pct)
{
    return base = CalculatePctF(base, pct);
}

template <class T>
inline T ApplyPctN(T& base, int32 pct)
{
    return base = CalculatePctN(base, pct);
}

template <class T>
inline T ApplyPctU(T& base, uint32 pct)
{
    return base = CalculatePctU(base, pct);
}

template <class T>
inline T RoundToInterval(T& num, T floor, T ceil)
{
    return num = std::min(std::max(num, floor), ceil);
}
#endif
