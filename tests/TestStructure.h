
// -*- mode: c++; c-basic-offset:4 -*-

// This file is part of libdap, A C++ implementation of the OPeNDAP Data
// Access Protocol.

// Copyright (c) 2002,2003 OPeNDAP, Inc.
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.
 
// (c) COPYRIGHT URI/MIT 1995-1999
// Please read the full copyright statement in the file COPYRIGHT_URI.
//
// Authors:
//      jhrg,jimg       James Gallagher <jgallagher@gso.uri.edu>

// Interface for the class TestStructure. See TestByte.h
//
// jhrg 1/12/95

#ifndef _teststructure_h
#define _teststructure_h 1

#include "Structure.h"
#include "TestCommon.h"

using namespace libdap ;

class TestStructure: public Structure, public TestCommon {
    bool d_series_values;
    void m_duplicate(const TestStructure &ts);

public:
    TestStructure(const string &n);
    TestStructure(const string &n, const string &d);
    TestStructure(const TestStructure &rhs);

    virtual ~TestStructure();

    TestStructure &operator=(const TestStructure &rhs);

    virtual BaseType *ptr_duplicate();

    virtual bool read();
    
    virtual void output_values(std::ostream &out);

    void set_series_values(bool);
    bool get_series_values() { return d_series_values; }
};

#endif // _teststructure_h
