//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 28, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <pni/io/parsers.hpp>
#include "utils.hpp"
#include "../common/roi.hpp"
#include "io/data_provider_factory.hpp"

using namespace pni::core;
using namespace pni::io;

configuration create_global_config()
{
    configuration config;

    //----------------setting up the program options---------------------------
    //these options do not show up in the help text
    config.add_argument(config_argument<std::vector<string>>("input-files",-1));

    //-------------------------------------------------------------------------
    //global options valid for all commands
    config.add_option(config_option<bool>("help","h","show help text",false));
    config.add_option(config_option<bool>("verbose","v","show verbose output",
                                          false));
    config.add_option(config_option<bool>(
                "header","","write headers before output",false));

    config.add_option(config_option<string>("channels","c",
                "name of the column with bin center values"));
    config.add_option(config_option<string>("bins","b",
                "name of the column with the center values"));
    config.add_option(config_option<string>("mca","m",
                "name of the MCA columns"));
    config.add_option(config_option<size_t>("auto-index-offset","",
                "offset for automatic channel index",size_t(0)));
    
    config.add_option(config_option<size_t>("mca-size","s",
                "number of channels of a single MCA spectrum",size_t(0)));

    config.add_option(config_option<roi_type>("roi","r",
                "ROI for the input data"));
    config.add_option(config_option<string>("base","",
                "base path for Nexus objects",""));

    config.add_option(config_option<string>("channel-sep","",
                "channel separator","\n"));
    config.add_option(config_option<bool>("no-channel-output","",
                "Supress channel data output",false));

    return config;
}

//------------------------------------------------------------------------------
bool check_argument_count(int argc)
{
    if(argc<2)
    {
        std::cerr<<usage_string<<std::endl;
        std::cerr<<"\nuse mcaops -h for more information"<<std::endl;
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
bool manage_help_request(const configuration &c)
{
    if(c.value<bool>("help"))
    {
        std::cerr<<usage_string<<std::endl<<std::endl;
        std::cerr<<command_string<<std::endl;
        std::cerr<<c<<std::endl;
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------
bool get_file_queue(const pni::core::configuration &c,file_queue &q)
{
    try
    {
        if(c.has_option("input-files"))
            q = fill_file_queue(c.value<std::vector<string>>("input-files"));
        else
            q.push(file());
    }
    catch(file_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return false;
    }
    return true;
}

//----------------------------------------------------------------------------
bool get_roi(const pni::core::configuration &c,roi_type &r)
{
    try
    {
        if(c.has_option("roi")) 
        {
            r = c.value<roi_type>("roi");
            //duplicate ROI for the channel data
            r.push_back(r.back());
        }
    }
    catch(range_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return false;
    }

    return true;
}

//----------------------------------------------------------------------------
bool get_provider(const string &path,const configuration &c,
                  provider_ptr &provider)
{
    try
    {
        provider = data_provider_factory::create(path,c);
    }
    catch(file_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return false;
    }
    catch(cli_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return false;
    }
    catch(type_error &error)
    {
        std::cerr<<error<<std::endl;
        return false;
    }

    return true;
}
