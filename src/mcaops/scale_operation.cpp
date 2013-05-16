/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: May 08,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "scale_operation.hpp"


//-----------------------------------------------------------------------------
scale_operation::scale_operation():
    operation(),
    _search_max(true),
    _center(0),
    _delta(1),
    _cvalue(0)
{ }

//-----------------------------------------------------------------------------
scale_operation::~scale_operation() 
{}

//-----------------------------------------------------------------------------
void scale_operation::operator()(const array_type &channels,
                                 const array_type &data)
{
    _channels = array_type(channels);
    _data = array_type(data);

    if(_search_max)
        _center = pni::core::max_offset(data);

#ifdef NOFOREACH
    for(auto iter=_channels.begin();iter!=_channels.end();iter++)
    {
        float64 &v = *iter;
#else
    for(float64 &v: _channels)
    {
#endif
        v = _cvalue + _delta*(v - _center); 
    }
    
}

//-----------------------------------------------------------------------------
void scale_operation::use_data_maximum(bool v)
{
    _search_max = v;
}

//-----------------------------------------------------------------------------
size_t scale_operation::center_bin() const
{
    return _center;
}

//-----------------------------------------------------------------------------
void scale_operation::center_bin(size_t v)
{
    _center = v;
}

//-----------------------------------------------------------------------------
float64 scale_operation::center_value() const
{
    return _cvalue;
}

//-----------------------------------------------------------------------------
void scale_operation::center_value(float64 v) 
{
    _cvalue = v;
}

//-----------------------------------------------------------------------------
float64 scale_operation::delta() const
{
    return _delta;
}

//-----------------------------------------------------------------------------
void scale_operation::delta(float64 v) 
{
    _delta = v;
}

//-----------------------------------------------------------------------------
std::ostream &scale_operation::stream_result(std::ostream &o) const
{
    for(size_t i=0;i<_channels.size();i++)
    {
        o<<_channels[i]<<"\t"<<_data[i]<<std::endl;
    }
    return o;
}