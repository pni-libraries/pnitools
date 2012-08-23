/*
 * main.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: Eugen Wintersberger
 */

#include<iostream>
#include<vector>

#include "../common/Exceptions.hpp"
#include "../common/ProgramConfig.hpp"

typedef std::vector<String> strlist;

int main(int argc,char **argv)
{
    ProgramConfig config;

    //---------------------setup program configuration-------------------------
    config.add_option(ConfigOption<Bool>("verbose","v","be verbose"));
    config.add_argument(ConfigArgument<strlist>("input-files",-1));

    //------------------managing command line parsing--------------------------
    try
    {
        config.parse(argc,argv);
    }
    catch(CLIHelpRequest &error)
    {
        std::cerr<<config<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Error parsing command line - aborting!"<<std::endl;
        std::cerr<<"For useage information use: "<<std::endl<<std::endl;
        std::cerr<<"    detinfo -h"<<std::endl<<std::endl;

        return 1;
    }

    //-------------------obtain input files------------------------------------
    auto file_list = config.value<strlist>("input-files");
    for(auto f: file_list) std::cout<<f<<std::endl;


    return 0;
}

