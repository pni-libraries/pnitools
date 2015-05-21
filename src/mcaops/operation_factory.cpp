//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 10,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <limits>
#include <ios>
#include <iomanip>
#include "operation.hpp"


//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const operation &op)
{
    typedef operation::array_type::value_type value_type;
    o<<std::setprecision(std::numeric_limits<value_type>::digits10)
     <<std::scientific;
    return op.stream_result(o);
}