
// -*- mode: c++; c-basic-offset:4 -*-

// This file is part of libdap, A C++ implementation of the OPeNDAP Data
// Access Protocol.

// Copyright (c) 2006 OPeNDAP, Inc.
// Author: James Gallagher <jgallagher@opendap.org>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.

// Tests for the AISResources class.

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

//#define DODS_DEBUG

#include "BaseType.h"
#include "Int32.h"
#include "Float64.h"
#include "Str.h"
#include "Array.h"
#include "Grid.h"
#include "DDS.h"
#include "DAS.h"
#include "ce_functions.h"
#include <test_config.h>

#include "../tests/TestTypeFactory.h"

#include "debug.h"

#if 1
#define TWO_GRID_DDS "ce-functions-testsuite/two_grid.dds"
#define TWO_GRID_DAS "ce-functions-testsuite/two_grid.das"
#else
#define TWO_GRID_DDS "unit-tests/ce-functions-testsuite/two_grid.dds"
#define TWO_GRID_DAS "unit-tests/ce-functions-testsuite/two_grid.das"
#endif

using namespace CppUnit;
using namespace libdap;
using namespace std;

int test_variable_sleep_interval = 0;

class KeywordsTest:public TestFixture
{
private:
    Keywords *k;
public:
    KeywordsTest()
    {}

    ~KeywordsTest()
    {}

    void setUp()
    {
	k = new Keyword();
    }

    void tearDown()
    {
        delete k; k = 0;
    }

    CPPUNIT_TEST_SUITE( KeywordsTest );

    CPPUNIT_TEST(no_keywords_test);
    CPPUNIT_TEST(one_keyword_test_1);
    CPPUNIT_TEST(one_keyword_test_1);
    CPPUNIT_TEST(two_keyword_test);

    CPPUNIT_TEST_SUITE_END();

    void no_keywords_test()
    {
	string ce = k->parse_keywords("");
	CPPUNIT_ASSERT(ce == "");
	CPPUNIT_ASSERT(k->get_keywords()->count() == 0);
    }

    void one_keyword_test_1()
    {
	string ce = k->parse_keywords("dap2");
	CPPUNIT_ASSERT(ce == "");
	CPPUNIT_ASSERT(k->get_keywords()->count() == 1);
	CPPUNIT_ASSERT(k->is_known_keyword("dap2"));
    }

    void one_keyword_test_2()
    {
	string ce = k->parse_keywords("dap2,u,v&v<7");
	CPPUNIT_ASSERT(ce == "u,v&v<7");
	CPPUNIT_ASSERT(k->get_keywords()->count() == 1);
	CPPUNIT_ASSERT(k->is_known_keyword("dap2"));
    }

    void two_keyword_test()
    {

    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(KeywordsTest);

int
main( int, char** )
{
    CppUnit::TextTestRunner runner;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );

    bool wasSuccessful = runner.run( "", false ) ;

    return wasSuccessful ? 0 : 1;
}
