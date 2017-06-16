#!/usr/bin/env python

#
# (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
#
# This file is part of pnitools.
#
# pnitools is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# pnitools is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
#************************************************************************
#
#  Created on: Oct 02, 2013
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#
from subprocess import check_output

from subprocess import STDOUT
from subprocess import call
import unittest
import os
import os.path
import pni.io.nx.h5 as nx

here = os.path.dirname(os.path.abspath(__file__))
bin_path = os.path.join(here,"..","..","bin")


class nxls_test(unittest.TestCase):
    input_file = "nxls_test.nxs"
    nxls = os.path.join(bin_path,"nxls")

    def setUp(self):

        with open('nxls_test.xml') as f:
            xml_struct = f.read()

        f = nx.create_file(self.input_file,overwrite=True)
        nx.xml_to_nexus(xml_struct,f.root())

    def tearDown(self):
        pass

    def test_return(self):
        #there are currently three situations where the program should fail
        # 1.) no input file is given
        # 2.) the input file does not exist
        # 3.) the input file is not a Nexus/HDF5 file

        #should give a useage message and return 1
        cmd = [self.nxls]
        result = int(call(cmd))
        self.assertEqual(result,1)

        #should return 1 as the group does not exist in the file
        cmd = [self.nxls,'bla.nxs']
        result = int(call(cmd))
        self.assertEqual(result,1)

        #should return 1 as the file is not a nexus file
        cmd = [self.nxls,'xml2nx_test.py']
        result = int(call(cmd))
        self.assertEqual(result,1)

    def test_simple_list(self):
        #just produce a simple output list
        cmd = [self.nxls,self.input_file+"://"]
        result = check_output(cmd)
        self.assertEqual(result.strip(),'entry:NXentry')

        #check more lines
        output = ['instrument:NXinstrument','sample:NXsample',
                  'control:NXmonitor','data:NXdata','title',
                  'experiment_description','start_time',
                  'end_time','program_name']
        result = check_output([self.nxls,self.input_file+'://:NXentry'])
        result = result.split('\n')
        result.remove('')
        self.assertEqual(len(result),len(output))

        for r in result:
            self.assertEqual(output.count(r.strip()),1)

    def test_recursive_list(self):
        #check more lines
        output = ['entry:NXentry',
                  'entry:NXentry/title',
                  'entry:NXentry/experiment_description',
                  'entry:NXentry/start_time',
                  'entry:NXentry/end_time',
                  'entry:NXentry/program_name',
                  'entry:NXentry/sample:NXsample',
                  'entry:NXentry/control:NXmonitor',
                  'entry:NXentry/data:NXdata',
                  'entry:NXentry/data:NXdata/data_1',
                  'entry:NXentry/data:NXdata/data_2',
                  'entry:NXentry/data:NXdata/data_3',
                  'entry:NXentry/instrument:NXinstrument',
                  'entry:NXentry/instrument:NXinstrument/name',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/data',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/layout',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/description',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource/name',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource/type',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource/probe'
                ]
        result = check_output([self.nxls,'-r',self.input_file+"://"])
        result = result.split('\n')
        result.remove('')
        self.assertEqual(len(result),len(output))

        for r in result:
            self.assertEqual(output.count(r.strip()),1)

    def test_attribute_list(self):
        output = ['entry:NXentry',
                  'entry:NXentry@NX_class',
                  'entry:NXentry/title',
                  'entry:NXentry/experiment_description',
                  'entry:NXentry/start_time',
                  'entry:NXentry/end_time',
                  'entry:NXentry/program_name',
                  'entry:NXentry/program_name@version',
                  'entry:NXentry/program_name@configuration',
                  'entry:NXentry/sample:NXsample',
                  'entry:NXentry/sample:NXsample@NX_class',
                  'entry:NXentry/control:NXmonitor',
                  'entry:NXentry/control:NXmonitor@NX_class',
                  'entry:NXentry/data:NXdata',
                  'entry:NXentry/data:NXdata@NX_class',
                  'entry:NXentry/data:NXdata/data_1',
                  'entry:NXentry/data:NXdata/data_1@units',
                  'entry:NXentry/data:NXdata/data_2',
                  'entry:NXentry/data:NXdata/data_3',
                  'entry:NXentry/instrument:NXinstrument',
                  'entry:NXentry/instrument:NXinstrument@NX_class',
                  'entry:NXentry/instrument:NXinstrument/name',
                  'entry:NXentry/instrument:NXinstrument/name@short_name',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector@NX_class',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/data',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/data@units',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size@units',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size@units',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/layout',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/description',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance',
                  'entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance@units',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource@NX_class',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource/name',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource/name@short_name',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource/type',
                  'entry:NXentry/instrument:NXinstrument/source:NXsource/probe'
                ]
        result = check_output([self.nxls,'-ra',self.input_file+"://"])
        result = result.split('\n')
        result.remove('')
        for x in result: print x
        self.assertEqual(len(result),len(output))

        for r in result:
            self.assertEqual(output.count(r.strip()),1)



if __name__ == "__main__":
    unittest.main()
