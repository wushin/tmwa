#include "zstring.hpp"
//    strings/zstring.cpp - Functions for zstring.hpp
//
//    Copyright © 2013 Ben Longbons <b.r.longbons@gmail.com>
//
//    This file is part of The Mana World (Athena server)
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "xstring.hpp"

namespace strings
{
    ZString::ZString()
    {
        *this = ZString("");
    }
    ZString::ZString(const FString& s)
    : _b(&*s.begin()), _e(&*s.end()), _base(s.base())
    {}
    ZString::ZString(const TString& s)
    : _b(&*s.begin()), _e(&*s.end()), _base(s.base())
    {}
    ZString::ZString(const char *b, const char *e, const FString *base_)
    : _b(b), _e(e), _base(base_)
    {}
    ZString::ZString(decltype(really_construct_from_a_pointer), const char *s, const FString *base_)
    : _b(s), _e(s + strlen(s)), _base(base_)
    {}

    ZString::iterator ZString::begin() const
    {
        return _b;
    }
    ZString::iterator ZString::end() const
    {
        return _e;
    }
    const FString *ZString::base() const
    {
        return _base;
    }
    const char *ZString::c_str() const
    {
        return &*begin();
    }

    ZS ZS::oslice_t(size_t o) const
    { return ZS(really_construct_from_a_pointer, &begin()[o], base()); }
    XS ZS::oslice_h(size_t o) const
    { return XS(&*begin(), &begin()[o], base()); }
    ZS ZS::orslice_t(size_t no) const
    { return ZS(really_construct_from_a_pointer, &end()[-no], base()); }
    XS ZS::orslice_h(size_t no) const
    { return XS(&*begin(), &end()[-no], base()); }
    ZS ZS::oislice_t(iterator it) const
    { return ZS(really_construct_from_a_pointer, &*it, base()); }
    XS ZS::oislice_h(iterator it) const
    { return XS(&*begin(), &*it, base()); }
    XS ZS::olslice(size_t o, size_t l) const
    { return XS(&begin()[o], &begin()[o + l], base()); }
    XS ZS::opslice(size_t b, size_t e) const
    { return XS(&begin()[b], &begin()[e], base()); }
    XS ZS::oislice(iterator b, iterator e) const
    { return XS(&*b, &*e, base()); }

    const char *decay_for_printf(const ZString& zs)
    {
        return zs.c_str();
    }

    __attribute__((format(scanf, 2, 0)))
    int do_vscan(ZString in, const char *fmt, va_list ap)
    {
        return vsscanf(in.c_str(), fmt, ap);
    }
} // namespace strings
