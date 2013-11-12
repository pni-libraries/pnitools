/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Nov 12, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "io_utils.hpp"


//-----------------------------------------------------------------------------
reader_ptr reader_from_file(const file &infile)
{
    //determine the reader type from the file extension
    string type;
    try
    {
        string extension = infile.extension();
        std::transform(extension.begin(),extension.end(),extension.begin(),
                       std::ptr_fun<int,int>(std::tolower));
        type = type_extension_map[extension];
    }
    catch(...)
    {
        throw file_error(EXCEPTION_RECORD,
                "Unable to determine file type for file "+infile.path()+ "!");
    }

    try
    {
        if(type == "cbf")
            return reader_ptr(new cbf_reader(infile.path()));
        else if(type == "tif")
            return reader_ptr(new tiff_reader(infile.path()));
    }
    catch(...)
    {
        throw file_error(EXCEPTION_RECORD,
                "Unable to construct reader for file "+infile.path()+"!");
    }

}

//------------------------------------------------------------------------------
image_type read_image(const file &f)
{
    reader_ptr reader = reader_from_file(f);

    //get image information
    type_id_t tid = reader->info(0).get_channel(0).type_id();

    if(tid == type_id_t::UINT8)       return read_data<uint8>  (reader);
    else if(tid == type_id_t::INT8)   return read_data<int8>   (reader);
    else if(tid == type_id_t::UINT16) return read_data<uint16> (reader);
    else if(tid == type_id_t::INT16)  return read_data<int16>  (reader);
    else if(tid == type_id_t::UINT32) return read_data<uint32> (reader);
    else if(tid == type_id_t::INT32)  return read_data<int32>  (reader);
    else if(tid == type_id_t::UINT64) return read_data<uint64> (reader);
    else if(tid == type_id_t::INT64)  return read_data<int64>  (reader);
}

