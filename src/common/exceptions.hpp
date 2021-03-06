//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 26, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once
#include<pni/core/types.hpp>
#include<pni/core/error.hpp>

//!
//! \brief file type error
//! 
//! This exception is thrown if the input or output file format cannot be
//! handled.
//!
class file_type_error:public pni::core::exception
{
    public:
        //-----------------------------------------------------------------
        //! default constructor
        file_type_error():pni::core::exception("file_type_error"){}
        
        //-----------------------------------------------------------------
        //!
        //! \brief constructor
        //!
        //! \param r exception record
        //! \param d description
        //!
        file_type_error(const pni::core::exception_record &r,
                        const pni::core::string &d):
            exception("file_type_error",r,d)
        {}

        //-----------------------------------------------------------------
        //! destructor
        ~file_type_error() throw() {}

        //! output operator
        friend std::ostream &operator<<(std::ostream &o,const file_type_error &e);
};

//!
//! \brief program error
//!
//! This exception is thrown in all situations which would cause a program 
//! to quit. 
//!
class program_error : public pni::core::exception
{
    public:
        //--------------------------------------------------------------------
        //! default constructor
        program_error():pni::core::exception("program_error") {}

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //!
        //! \param r exception record
        //! \param d description
        //!
        program_error(const pni::core::exception_record &r,
                      const pni::core::string &d):
            exception("program_error",r,d)
        {}

        //--------------------------------------------------------------------
        //! destructor
        ~program_error() throw() {}

        //--------------------------------------------------------------------
        //! output operator
        friend std::ostream &operator<<(std::ostream &stream,
                                        const program_error &error);
};
