#!/usr/bin/env python

#this is the master script running all the CLI tests for pnitools

from unittest import main
from unittest import TestLoader
from unittest import TestSuite
from det2nx_test  import det2nx_test
from detinfo_test import detinfo_test
from nxcat_test   import nxcat_test
from nxls_test    import nxls_test
from xml2nx_test  import xml2nx_test
from mcaops_test  import mcaops_test

suite = TestSuite()
suite.addTest(TestLoader().loadTestsFromTestCase(det2nx_test))
suite.addTest(TestLoader().loadTestsFromTestCase(detinfo_test))
suite.addTest(TestLoader().loadTestsFromTestCase(nxcat_test))
suite.addTest(TestLoader().loadTestsFromTestCase(nxls_test))
suite.addTest(TestLoader().loadTestsFromTestCase(xml2nx_test))
suite.addTest(TestLoader().loadTestsFromTestCase(mcaops_test))

main()