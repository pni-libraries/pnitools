//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: May 27, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "max.hpp"
#include <pni/io/formatters.hpp>

//----------------------------------------------------------------------------
max::max(): operation(),_value(0)
{}

//----------------------------------------------------------------------------
max::~max(){}

//----------------------------------------------------------------------------
operation::args_vector max::configure(const args_vector &args)
{
    return args;
}

//----------------------------------------------------------------------------
void max::operator()(const argument_type &data)
{
    auto &mca_range = data.second;

    auto iter = std::max_element(mca_range.first,mca_range.second);
    _value = *iter;
}

//----------------------------------------------------------------------------
std::ostream &max::stream_result(std::ostream &o) const
{
    o<<pni::io::format(_value);
    return o;
}
