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
//************************************************************************
//
//  Created on: Jun 1, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

#include <common/file_type.hpp>


BOOST_AUTO_TEST_SUITE(file_type_test)

BOOST_AUTO_TEST_CASE(tif_test)
{
    fs::path s = "../../data/tif/detector_013.tif";
    BOOST_CHECK_EQUAL(get_file_type(s.string()),file_type::TIFF_FILE);
    BOOST_CHECK_EQUAL(get_file_type(file(s.string())),file_type::TIFF_FILE);
}

BOOST_AUTO_TEST_CASE(cbf_test)
{
    fs::path s = "../../data/cbf/LAOS3_05461.cbf";
    BOOST_CHECK_EQUAL(get_file_type(s.string()),file_type::CBF_FILE);
    BOOST_CHECK_EQUAL(get_file_type(file(s.string())),file_type::CBF_FILE);
}

BOOST_AUTO_TEST_CASE(nexus_test)
{
    fs::path s1 = "../../data/nexus/CSP93065.nxs";
    BOOST_CHECK_EQUAL(get_file_type(s1.string()),file_type::NEXUS_FILE);
    BOOST_CHECK_EQUAL(get_file_type(file(s1.string())),file_type::NEXUS_FILE);

    fs::path s2 = "../../data/nexus/tstfile_00012.h5";
    BOOST_CHECK_EQUAL(get_file_type(s2.string()),file_type::NEXUS_FILE);
    BOOST_CHECK_EQUAL(get_file_type(file(s2.string())),file_type::NEXUS_FILE);
}

BOOST_AUTO_TEST_CASE(fio_test)
{
    fs::path s = "../../data/fio/scan_mca_00007.fio";
    BOOST_CHECK_EQUAL(get_file_type(s.string()),file_type::FIO_FILE);
    BOOST_CHECK_EQUAL(get_file_type(file(s.string())),file_type::FIO_FILE);
}

BOOST_AUTO_TEST_CASE(unkown_test)
{
    BOOST_CHECK_EQUAL(get_file_type("cmake_install.cmake"),file_type::UNKNOWN);
    BOOST_CHECK_EQUAL(get_file_type(file("cmake_install.cmake")),file_type::UNKNOWN);
}

BOOST_AUTO_TEST_SUITE_END()
