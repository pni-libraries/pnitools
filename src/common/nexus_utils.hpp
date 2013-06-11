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

using namespace pni::core;
using namespace pni::io::nx;

/*!
\ingroup common_devel
\brief search for group by class

Search for a child group below p for a group with a particular class name
and return the group if found. The function returs false if not successful
and true otherwise. 

\code
nxgroup g = file["/"];
nxgroup e;

if(!find_group_by_class(g,"NXentry",e))
{
    //no entry found - do something here.
}

\endcode

\tparam PTYPE parent type 
\tparam GTYPE group type
\param p parent group whose childs to search
\param gclass name of the class
\param g resulting group
\return true if group has been found, false otherwise
*/
template<typename PTYPE, typename GTYPE> 
bool find_group_by_class(const PTYPE &p,const string &gclass,GTYPE &g)
{
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //continue the loop if the object is not a group
        if(iter->object_type() != nxobject_type::NXGROUP) continue;

        //if the group object has no NX_class attribute just go ahead
        if(!iter->has_attr("NX_class")) continue;

        //here we can do the check
        string buffer;
        iter->attr("NX_class").read(buffer);
        if(buffer == gclass) 
        {
            g = *iter;
            return true;
        }
    }

    return false;
}


//-------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief search for group names

Search for a child group with a particular name. The function returns true
if the search was successful, false otherwise. 
A typical application would look like this:
\code
nxgroup inst = file["/entry/instrument"];
nxgruop detector;
if(!find_group_by_name(inst,"detector_channel_1",detector))
{
    std::cerr<<"Cannot find detector!"<<std::endl;
    return -1;
}
\endcode

\tparam PTYPE parent group type
\tparam GTYPE target group type
\param p parent group 
\param gname name of the group to look for
\param g target group
\return true if group has been found, false otherwise
*/
template<typename PTYPE,typename GTYPE>
bool find_group_by_name(const PTYPE &p,const string &gname,GTYPE &g)
{
    auto iter = p.begin();
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //continue with the loop of the object is not a group
        if(iter->object_type() != nxobject_type::NXGROUP) continue;

        //check name
        if(iter->name() == gname) 
        {
            g = *iter;
            return true;
        }
    }

    return false;
}

//-------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief find group by class and name

Find a child group with a particular name and class. If the search succeeds 
the function returns true, false otherwise. 

\tparam PTYPE parent type
\tparam GTYPE target group type
\param p parent instance
\param gname group name
\param gclass class name
\param g target group
\return true if found, false otherwise
*/
template<typename PTYPE,typename GTYPE>
bool find_group_by_name_and_class(const PTYPE &p,const string &gname,
                                  const string &gclass,GTYPE &g)
{
    if(!find_group_by_name(p,gname,g))
        return false;

    if(g.has_attr("NX_class"))
    {
        string buffer;
        g.attr("NX_class").read(buffer);
        if(buffer == gclass) return true;
    }

    return false;
}

//-------------------------------------------------------------------------
/*!
\brief common_devel
\brief create a group

Creates a group of type GTYPE below a group of type GTYPE. 

\throws pni::io::nx::nxgroup_error 
\throws pni::io::nx::nxattribute_error
\tparam PTYPE type of parent group
\tparam GTYPE type of target group
\param p parent groupt
\param gname name of the new group
\param gclass class of the new group
\param g target group
*/
template<typename PTYPE,typename GTYPE>
void create_group(const PTYPE &p,const string &gname,const string &gclass,
                  GTYPE &g)
{
    g=p.create_group(gname,gclass);
}

//-----------------------------------------------------------------------------
template<typename PTYPE,typename GTYPE>
void create_group(const PTYPE &p,const string &gname,GTYPE &g)
{
    g=p.create_group(gname);
}

//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get a group

Check if a group exists below a parent group and return it. The function handles
several special cases. If the group does not exist it will be created as long as
at least its name is given and the create flag is set to true. If the groups
name is an empty string one can still search for the group by its Nexus class.
However, if the function cannot find a group of appropriate class it throws an
exception.
\thows group_error in case of errors
\tparam PTYPE parent type
\tparam GTYPE group type
\param p parent group
\param name name of the searched group
\param gclass nexus class of the searched group
\param g reference to the group
\param create true of the group should be created 
*/
template<typename PTYPE,typename GTYPE>
void get_group(const PTYPE &p,const string &name, const string &gclass,
               GTYPE &g,bool create=true)
{
    if(!name.empty())
    {
        //groups can only be created if we at least have a name
        if(!gclass.empty())
        {
            if(!find_group_by_name_and_class(p,name,gclass,g))
            {
                //if group not found - either create it or throw an exception
                if(create) create_group(p,name,gclass,g);
                else
                    throw nxgroup_error(EXCEPTION_RECORD,
                            "("+name+":"+gclass+"does not exist!");
            }
        }
        else
        {
            if(!find_group_by_name(p,name,g))
            {
                //if group not found - either create it or throw an exception
                if(create) create_group(p,name,g);
                else
                    throw nxgroup_error(EXCEPTION_RECORD,
                            "("+name+":"+gclass+"does not exist!");
            }
        }
    }
    else if(!gclass.empty())
    {
        if(!find_group_by_class(p,gclass,g))
            throw nxgroup_error(EXCEPTION_RECORD,
                "::group_path_tcannot find group of class "+gclass+"!");
    }
    else
    {
        throw nxgroup_error(EXCEPTION_RECORD,
                "Error retrieving group!");
    }
}

//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get a group

This function  is an extension of the get_group. It walks through a Nexus path
and returns the last group of the path. Non-existing groups are automatically
created if the create flag is set to true. 
\throws nxgroup_error in case of errors
\tparam GTYPE group type
\param p parent group
\param path Nexus path object
\param g resulting group
\param create true if missing elements should be created
*/
template<typename GTYPE>
void get_group(const GTYPE &p,const nxpath &path,GTYPE &g,bool create=true)
{
    g = p;
    for(auto element: path)
        get_group(g,element.first,element.second,g,create);
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get an existing field

Return an existing field according to a path object. 
\tparam GTYPE group type
\tparam FTYPE field type
\param p parent group 
\param path the field path relative to the parent
\param f field instance
*/
template<typename GTYPE,typename FTYPE>
void get_field(const GTYPE &p,const nxpath &path,FTYPE &f)
{
    //here we assume that all elements in the path except the last one refer to
    //groups - create a new path with one element less
    nxpath::group_path_t groups(path.size()-1);
    nxpath::group_path_t::const_iterator fielditer = path.begin();
    std::advance(fielditer,path.size()-1);
    std::copy(path.begin(),fielditer,groups.begin());
    nxpath groups_only("",groups,"");

    GTYPE parent; 
    get_group(p,groups_only,parent,false);

    f = parent[fielditer->first];

}

//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create a field

Create a field from a type_id_t and a shape object. 
\throws type_error if data type is not supported
\tparam PTYPE parent type
\tparam FTYPE field type
\tparam STYPE shape type
\param parent instance of PTYPE - there parent object
\param name the name of the new field
\param tid type_id of the field
\param shape instance of STYPE - the shape of the field
\param field reference to the new field
*/
template<typename PTYPE,typename FTYPE,typename STYPE,typename ...FILTERT>
void create_field(const PTYPE &parent,const string &name,type_id_t tid,
                  const STYPE shape,FTYPE &field,FILTERT ...filters)
{
    STYPE cshape(shape.size());
    std::copy(shape.begin(),shape.end(),cshape.begin());
    *cshape.begin() = 1;

    if(tid == type_id_t::UINT8)
        field = parent.create_field<uint8>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT8)
        field = parent.create_field<int8>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT16)
        field = parent.create_field<uint16>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT16)
        field = parent.create_field<int16>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT32)
        field = parent.create_field<uint32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT32)
        field = parent.create_field<int32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT64)
        field = parent.create_field<uint64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT64)
        field = parent.create_field<int64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT32)
        field = parent.create_field<float32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT64)
        field = parent.create_field<float64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT128)
        field = parent.create_field<float128>(name,shape,cshape,filters...);
    else
        throw type_error(EXCEPTION_RECORD,
                "Unkown data type!");
}
                  