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
// =========================================================================
//  Created on: Jun 10, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "operations_test_common.hpp"
#include <mcaops/operations/scale.hpp>

using namespace pni::core;
using boost::test_tools::output_test_stream;

struct scale_test_fixture
{
    shape_t shape;
    array_type mca;
    array_type channel_1;
    array_type channel_2;
    output_test_stream stream;

    scale_test_fixture():
        shape(shape_t{48}),
        mca(array_type::create(shape,
                    storage_type{45, 13, 52, 51, 51, 62, 69, 83, 41, 41,
                                     49, 58, 84, 36, 42,  0, 50, 25, 71, 68,
                                      0,  8, 49, 34, 25, 56, 85, 80, 33, 56,
                                      3, 56, 95, 63, 33, 42, 24, 32, 92, 35,
                                     57, 38, 30, 90, 31, 75, 17, 63})),
        channel_1(array_type::create(shape)),
        channel_2(array_type::create(shape)),
        stream()
    {
        std::iota(channel_1.begin(),channel_1.end(),0.0);
        std::iota(channel_2.begin(),channel_2.end(),3.0);
    }

};


BOOST_FIXTURE_TEST_SUITE(scale_test,scale_test_fixture)

    float64 compute_axis(float64 cv,size_t i,float64 d,size_t cb)
    {
        return cv + d*(float64(i)-float64(cb));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_automax)
    {
        scale op;
        args_vector cnf_opt{"--delta=0.5","--cvalue=1.34"};
        BOOST_CHECK_NO_THROW(op.configure(cnf_opt));
        argument_type arg{{channel_1.begin(),channel_1.end()},
                          {mca.begin(),mca.end()}};
        BOOST_CHECK_NO_THROW(op(arg));
        op.stream_result(stream);




        string result = "-1.46600000000000001e+01 +4.50000000000000000e+01\n"
                        "-1.41600000000000001e+01 +1.30000000000000000e+01\n"
                        "-1.36600000000000001e+01 +5.20000000000000000e+01\n"
                        "-1.31600000000000001e+01 +5.10000000000000000e+01\n"
                        "-1.26600000000000001e+01 +5.10000000000000000e+01\n"
                        "-1.21600000000000001e+01 +6.20000000000000000e+01\n"
                        "-1.16600000000000001e+01 +6.90000000000000000e+01\n"
                        "-1.11600000000000001e+01 +8.30000000000000000e+01\n"
                        "-1.06600000000000001e+01 +4.10000000000000000e+01\n"
                        "-1.01600000000000001e+01 +4.10000000000000000e+01\n"
                        "-9.66000000000000014e+00 +4.90000000000000000e+01\n"
                        "-9.16000000000000014e+00 +5.80000000000000000e+01\n"
                        "-8.66000000000000014e+00 +8.40000000000000000e+01\n"
                        "-8.16000000000000014e+00 +3.60000000000000000e+01\n"
                        "-7.66000000000000014e+00 +4.20000000000000000e+01\n"
                        "-7.16000000000000014e+00 +0.00000000000000000e+00\n"
                        "-6.66000000000000014e+00 +5.00000000000000000e+01\n"
                        "-6.16000000000000014e+00 +2.50000000000000000e+01\n"
                        "-5.66000000000000014e+00 +7.10000000000000000e+01\n"
                        "-5.16000000000000014e+00 +6.80000000000000000e+01\n"
                        "-4.66000000000000014e+00 +0.00000000000000000e+00\n"
                        "-4.16000000000000014e+00 +8.00000000000000000e+00\n"
                        "-3.66000000000000014e+00 +4.90000000000000000e+01\n"
                        "-3.16000000000000014e+00 +3.40000000000000000e+01\n"
                        "-2.66000000000000014e+00 +2.50000000000000000e+01\n"
                        "-2.16000000000000014e+00 +5.60000000000000000e+01\n"
                        "-1.65999999999999992e+00 +8.50000000000000000e+01\n"
                        "-1.15999999999999992e+00 +8.00000000000000000e+01\n"
                        "-6.59999999999999920e-01 +3.30000000000000000e+01\n"
                        "-1.59999999999999920e-01 +5.60000000000000000e+01\n"
                        "+3.40000000000000080e-01 +3.00000000000000000e+00\n"
                        "+8.40000000000000080e-01 +5.60000000000000000e+01\n"
                        "+1.34000000000000008e+00 +9.50000000000000000e+01\n"
                        "+1.84000000000000008e+00 +6.30000000000000000e+01\n"
                        "+2.33999999999999986e+00 +3.30000000000000000e+01\n"
                        "+2.83999999999999986e+00 +4.20000000000000000e+01\n"
                        "+3.33999999999999986e+00 +2.40000000000000000e+01\n"
                        "+3.83999999999999986e+00 +3.20000000000000000e+01\n"
                        "+4.33999999999999986e+00 +9.20000000000000000e+01\n"
                        "+4.83999999999999986e+00 +3.50000000000000000e+01\n"
                        "+5.33999999999999986e+00 +5.70000000000000000e+01\n"
                        "+5.83999999999999986e+00 +3.80000000000000000e+01\n"
                        "+6.33999999999999986e+00 +3.00000000000000000e+01\n"
                        "+6.83999999999999986e+00 +9.00000000000000000e+01\n"
                        "+7.33999999999999986e+00 +3.10000000000000000e+01\n"
                        "+7.83999999999999986e+00 +7.50000000000000000e+01\n"
                        "+8.33999999999999986e+00 +1.70000000000000000e+01\n"
                        "+8.83999999999999986e+00 +6.30000000000000000e+01\n";

        BOOST_CHECK(stream.is_equal(result));
    }

    //-----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_usermax)
    {
        scale op;
        args_vector cnf_opt{"--delta=0.5","--cvalue=1.34","--center=30"};
        BOOST_CHECK_NO_THROW(op.configure(cnf_opt));
        argument_type arg{{channel_1.begin(),channel_1.end()},
                          {mca.begin(),mca.end()}};
        BOOST_CHECK_NO_THROW(op(arg));
        op.stream_result(stream);

        string result = "-1.36600000000000001e+01 +4.50000000000000000e+01\n"
                        "-1.31600000000000001e+01 +1.30000000000000000e+01\n"
                        "-1.21600000000000001e+01 +5.10000000000000000e+01\n"
                        "-1.26600000000000001e+01 +5.20000000000000000e+01\n"
                        "-1.16600000000000001e+01 +5.10000000000000000e+01\n"
                        "-1.11600000000000001e+01 +6.20000000000000000e+01\n"
                        "-1.06600000000000001e+01 +6.90000000000000000e+01\n"
                        "-1.01600000000000001e+01 +8.30000000000000000e+01\n"
                        "-9.66000000000000014e+00 +4.10000000000000000e+01\n"
                        "-9.16000000000000014e+00 +4.10000000000000000e+01\n"
                        "-8.66000000000000014e+00 +4.90000000000000000e+01\n"
                        "-8.16000000000000014e+00 +5.80000000000000000e+01\n"
                        "-7.66000000000000014e+00 +8.40000000000000000e+01\n"
                        "-7.16000000000000014e+00 +3.60000000000000000e+01\n"
                        "-6.66000000000000014e+00 +4.20000000000000000e+01\n"
                        "-6.16000000000000014e+00 +0.00000000000000000e+00\n"
                        "-5.66000000000000014e+00 +5.00000000000000000e+01\n"
                        "-5.16000000000000014e+00 +2.50000000000000000e+01\n"
                        "-4.66000000000000014e+00 +7.10000000000000000e+01\n"
                        "-4.16000000000000014e+00 +6.80000000000000000e+01\n"
                        "-3.66000000000000014e+00 +0.00000000000000000e+00\n"
                        "-3.16000000000000014e+00 +8.00000000000000000e+00\n"
                        "-2.66000000000000014e+00 +4.90000000000000000e+01\n"
                        "-2.16000000000000014e+00 +3.40000000000000000e+01\n"
                        "-1.65999999999999992e+00 +2.50000000000000000e+01\n"
                        "-1.15999999999999992e+00 +5.60000000000000000e+01\n"
                        "-6.59999999999999920e-01 +8.50000000000000000e+01\n"
                        "-1.59999999999999920e-01 +8.00000000000000000e+01\n"
                        "+3.40000000000000080e-01 +3.30000000000000000e+01\n"
                        "+8.40000000000000080e-01 +5.60000000000000000e+01\n"
                        "+1.34000000000000008e+00 +3.00000000000000000e+00\n"
                        "+1.84000000000000008e+00 +5.60000000000000000e+01\n"
                        "+2.33999999999999986e+00 +9.50000000000000000e+01\n"
                        "+2.83999999999999986e+00 +6.30000000000000000e+01\n"
                        "+3.33999999999999986e+00 +3.30000000000000000e+01\n"
                        "+3.83999999999999986e+00 +4.20000000000000000e+01\n"
                        "+4.33999999999999986e+00 +2.40000000000000000e+01\n"
                        "+4.83999999999999986e+00 +3.20000000000000000e+01\n"
                        "+5.33999999999999986e+00 +9.20000000000000000e+01\n"
                        "+5.83999999999999986e+00 +3.50000000000000000e+01\n"
                        "+6.33999999999999986e+00 +5.70000000000000000e+01\n"
                        "+6.83999999999999986e+00 +3.80000000000000000e+01\n"
                        "+7.33999999999999986e+00 +3.00000000000000000e+01\n"
                        "+7.83999999999999986e+00 +9.00000000000000000e+01\n"
                        "+8.33999999999999986e+00 +3.10000000000000000e+01\n"
                        "+8.83999999999999986e+00 +7.50000000000000000e+01\n"
                        "+9.33999999999999986e+00 +1.70000000000000000e+01\n"
                        "+9.83999999999999986e+00 +6.30000000000000000e+01\n";

        BOOST_CHECK(stream.is_equal(result));
    }


BOOST_AUTO_TEST_SUITE_END()
