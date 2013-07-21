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
 * Created on: Jul 19, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "nx2xml.hpp"

//-------------------------------------------------------------------------
configuration create_config()
{
    configuration config;

    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<string>("output","o",
                "name of the output file","output.xml"));
    config.add_argument(config_argument<string>("input-file",-1));

    return config;
}


