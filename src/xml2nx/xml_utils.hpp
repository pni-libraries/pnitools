#ifndef __XMLUTILS_HPP__
#define __XMLUTILS_HPP__

#include<sstream>
#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;
namespace tree = boost::property_tree;

//-----------------------------------------------------------------------------
/*!

\brief create shape form dimensions tag

Create a shape container from the dimensions tag in the XML file. 
\param dims ptree instance to the dimensions tag
\return instance of shape_t with the shapea
*/
shape_t dimensions2shape(const tree::ptree &dims);

//-----------------------------------------------------------------------------
/*!
\brief create a field from xml data

Create a field from the information provided by the XML file. 
\tparam PTYPE parent type
\param parent instance of PTYPE - the parent of the field
\param name the fields name
\param tc type code 
\param s shape of the field
\return instance of NXField
*/
template<typename PTYPE>
NXField create_field(const PTYPE &parent,const String &name,
                     const String &tc,const shape_t &s)
{
    if(tc == "uint8")
        return parent.template create_field<UInt8>(name,s);
    if(tc == "int8")
        return parent.template create_field<Int8>(name,s);
    if(tc == "uint16")
        return parent.template create_field<UInt16>(name,s);
    if(tc == "int16")
        return parent.template create_field<Int16>(name,s);
    if(tc == "uint32")
        return parent.template create_field<UInt32>(name,s);
    if(tc == "int32")
        return parent.template create_field<Int32>(name,s);
    if(tc == "uint64")
        return parent.template create_field<UInt64>(name,s);
    if(tc == "int64")
        return parent.template create_field<Int64>(name,s);
    if(tc == "float32")
        return parent.template create_field<Float32>(name,s);
    if(tc == "float64")
        return parent.template create_field<Float64>(name,s);
    if(tc == "float128")
        return parent.template create_field<Float128>(name,s);
    if(tc == "complex32")
        return parent.template create_field<Complex32>(name,s);
    if(tc == "complex64")
        return parent.template create_field<Complex64>(name,s);
    if(tc == "complex128")
        return parent.template create_field<Complex128>(name,s);
    if(tc == "bool")
        return parent.template create_field<Bool>(name,s);
    if(tc == "binary")
        return parent.template create_field<Binary>(name,s);
    if(tc == "string")
        return parent.template create_field<String>(name,s);

    std::stringstream ss;
    ss<<"Error creating field - type code "<<tc<<" is not supported!";
    throw pni::nx::NXFieldError(EXCEPTION_RECORD,ss.str());

    return NXField(); //just to make the compiler happy
}

//-----------------------------------------------------------------------------
/*!
\brief create objects from XML

Recursively creates the objects as described in the XML file below parent.
\tparam PTYPE parent type
\param parent instance of PTYPE
\param t ptree instance with the XML data
*/
template<typename PTYPE>
void create_objects(const PTYPE &parent,tree::ptree &t)
{
    for(auto child: t)
    {
        if(child.first == "group")
        {
            //create the group and call the function recursively
            auto name = child.second.template get<String>("<xmlattr>.name");
            auto type = child.second.template get<String>("<xmlattr>.type");

            NXGroup g = parent.create_group(name,type);
            create_objects(g,child.second);

        }
        else if(child.first == "field")
        {
            auto name = child.second.template get<String>("<xmlattr>.name");
            auto type = child.second.template get<String>("<xmlattr>.type");

            shape_t shape;
            //obtain the shape
            tree::ptree dim_node;
            try
            {
                tree::ptree dim_node = child.second.get_child("dimensions");
                shape = dimensions2shape(dim_node);
            }
            catch(...)
            {}

            NXField f = create_field(parent,name,type,shape);

            auto units = child.second.template get<String>("<xmlattr>.units");
            auto lname = child.second.template get<String>("<xmlattr>.long_name");
            f.attr<String>("units").write(units);
            f.attr<String>("long_name").write(lname);

        }
    }
}
#endif
