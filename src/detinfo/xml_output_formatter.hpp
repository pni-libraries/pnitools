//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Oct 10,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "output_formatter.hpp"

class xml_output_formatter : public output_formatter
{
    static const string detector_indent;
    static const string data_indent;
    public:
        virtual void header(std::ostream &stream);
        virtual void footer(std::ostream &stream);
        virtual void detector_header(std::ostream &stream);
        virtual void detector_footer(std::ostream &stream);
        virtual void write(std::ostream &stream,const detector_info &info);
};
    
