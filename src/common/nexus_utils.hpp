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
 * Created on: Jun 7, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

#include "nexus_object_utils.hpp"
#include "nexus_path_utils.hpp"
#include "nexus_group_utils.hpp"
#include "nexus_field_utils.hpp"
#include "nxvariant_traits.hpp"

using namespace pni::core;
using namespace pni::io::nx;


//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get object by name

Return an object specified by a Nexus path. From the nature of a nexus file we
can assume that every object in the path except the last one has to be a group
as it must hold other objects 
*/
template<typename PTYPE> typename nxvariant_traits<PTYPE>::object_types 
find_object(const PTYPE &p,const nxpath &path)
{
    nxpath group_path;
    nxpath target_path;

    split_last(path,group_path,target_path);

    //try to fetch the groups 
    PTYPE t_group;
    if(!is_valid(t_group = get_group(p,group_pathfalse))) return PTYPE();

    /*now we need to fetch the target object. This can be either a group or a
     * field - need to take this into account
     */
    //first we try to fetch a group
    if(get_group(t_group,target_path,object)) return true;

    return true;
}

//-----------------------------------------------------------------------------
template<typename PTYPE,typename OTYPE>
bool find_object_by_name(const PTYPE &p,const string &name,OTYPE &o)
{
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //check name
        if(iter->name() == name) 
        {
            o = *iter;
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
template<typename PTYPE,typename OTYPE>
bool find_object_by_class(const PTYPE &p,const string &oclass,OTYPE &o)
{

    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        if(is_class(*iter,oclass))
        {
            o = *iter;
            return true;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
template<typename PTYPE,typename OTYPE>
bool find_object_by_name_and_class(const PTYPE &p,const string &name,
                                   const string &oclass,OTYPE &o)
{
    if(!find_object_by_name(p,name,o))
        return false;

    if(!is_class(o,oclass)) return false;

    return true;
}


