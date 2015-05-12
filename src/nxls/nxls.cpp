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
// Created on: 30.06.2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "config.hpp"
#include "utils.hpp"
#include "output_config.hpp"
#include "output.hpp"
#include <iostream>
#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/flat_group.hpp>
#include <pni/io/nx/algorithms/is_field.hpp>
#include <pni/io/nx/algorithms/is_attribute.hpp>


using namespace pni::core;
using namespace pni::io::nx;


//!
//! \ingroup nxls_devel
//! \brief main program
//! 
//! The main program sequence of nxls.
//!
int main(int argc,char **argv)
{
    //create configuration
    configuration config = get_config(argc,argv);

    nxpath path = get_path(config);

    h5::nxfile file = get_file(path);

    h5::nxobject root = get_root(file,path);

    //generate output configuraiton
    output_config out_config = make_output_config(config);

    //in the case that the root object is a single field or attribute
    //we have to adjust the trim level - but only if it is not 0.
    if(is_field(root) || is_attribute(root))
    {
        if(out_config.trim_level()) 
            out_config.trim_level(out_config.trim_level()-1);
    }

    //generat output class
    output o(std::cout,out_config);

    try
    {
        if(is_field(root) || is_attribute(root))
            o.write_object(root);
        else
        {
            if(config.value<bool>("recursive"))
                o(make_flat(root));
            else
                o(h5::nxgroup(root));
        }

    }
    catch(pni::core::type_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::io::parser_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::core::size_mismatch_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::io::object_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }


	return 0;
}
