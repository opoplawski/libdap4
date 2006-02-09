
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
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.
 
// (c) COPYRIGHT URI/MIT 1999
// Please read the full copyright statement in the file COPYRIGHT_URI.
//
// Authors:
//      jhrg,jimg       James Gallagher <jgallagher@gso.uri.edu>

// Templates for relational operations.
//
// jhrg 3/24/99

#ifndef _operators_h
#define _operators_h

#include "GNURegex.h"		// GNU Regex class used for string =~ op.

using namespace std;

static unsigned
dods_max(int i1, int i2)
{
    return (unsigned)((i1 > i2) ? i1 : i2);
}

/** Compare two numerical types, both of which are either signed or unsigned.
    This class is one implementation of the comparison policy used by
    rops.
    
    @see rops
    @see USCmp
    @see SUCmp */
template<class T1, class T2> class Cmp {
 public:
    static bool eq(T1 v1, T2 v2) {return v1 == v2;}
    static bool ne(T1 v1, T2 v2) {return v1 != v2;}
    static bool gr(T1 v1, T2 v2) {return v1 > v2;}
    static bool ge(T1 v1, T2 v2) {return v1 >= v2;}
    static bool lt(T1 v1, T2 v2) {return v1 < v2;}
    static bool le(T1 v1, T2 v2) {return v1 <= v2;}
    static bool re(T1, T2) {
	cerr << "Illegal operation" << endl;
	return false;
    }
};

/** Compare two numerical types, the first one unsigned and the second
    signed. If the signed argument is negative, zero is used in the
    comparison. This class is one implementation of the comparison policy
    used by rops.

    @see rops
    @see SUCmp
    @see Cmp */
template<class UT1, class T2> class USCmp {
 public:
    static bool eq(UT1 v1, T2 v2) {return v1 == dods_max(0, v2);}
    static bool ne(UT1 v1, T2 v2) {return v1 != dods_max(0, v2);}
    static bool gr(UT1 v1, T2 v2) {return v1 > dods_max(0, v2);}
    static bool ge(UT1 v1, T2 v2) {return v1 >= dods_max(0, v2);}
    static bool lt(UT1 v1, T2 v2) {
	return v1 < dods_max(0, v2);
    }
    static bool le(UT1 v1, T2 v2) {return v1 <= dods_max(0, v2);}
    static bool re(UT1, T2) {
	cerr << "Illegal operation" << endl;
	return false;
    }
};

/** Compare two numerical types, the first one signed and the second
    unsigned. If the signed argument is negative, zero is used in the
    comparison. This class is one implementation of the comparison policy
    used by rops. This class is here to make writing the Byte::ops, ...
    member functions simpler. It is not necessary since the functions could
    twiddle the order of arguments to rops and use <tt>USCmp</tt>. Having 
    this class make Byte:ops, ... simper to read and write.

    @see Byte::ops
    @see USCmp
    @see Cmp
    @see ops */
template<class T1, class UT2> class SUCmp {
 public:
    static bool eq(T1 v1, UT2 v2) {return dods_max(0, v1) == v2;}
    static bool ne(T1 v1, UT2 v2) {return dods_max(0, v1) != v2;}
    static bool gr(T1 v1, UT2 v2) {return dods_max(0, v1) > v2;}
    static bool ge(T1 v1, UT2 v2) {return dods_max(0, v1) >= v2;}
    static bool lt(T1 v1, UT2 v2) {return dods_max(0, v1) < v2;}
    static bool le(T1 v1, UT2 v2) {return dods_max(0, v1) <= v2;}
    static bool re(T1, UT2) {
	cerr << "Illegal operation" << endl;
	return false;
    }
};

/** Compare two string types.
    This class is one implementation of the comparison policy used by
    rops.
    
    @see rops */
template<class T1, class T2> class StrCmp {
 public:
    static bool eq(T1 v1, T2 v2) {return v1 == v2;}
    static bool ne(T1 v1, T2 v2) {return v1 != v2;}
    static bool gr(T1 v1, T2 v2) {return v1 > v2;}
    static bool ge(T1 v1, T2 v2) {return v1 >= v2;}
    static bool lt(T1 v1, T2 v2) {return v1 < v2;}
    static bool le(T1 v1, T2 v2) {return v1 <= v2;}
    static bool re(T1 v1, T2 v2) {
	Regex r(v2.c_str());
	return r.match(v1.c_str(), v1.length()) > 0;
    }
};

/** This template function is used to compare two values of two instances of
    the DAP2 simple types (Byte, ..., Str). The function does not take the
    DAP2 objects as arguments; the caller must access the values of those
    objects and pass them to this function. The reason for this is that all
    the possible functions that could be generated from this template would
    have to be explicitly listed as friend functions in each of the DAP2
    simple type classes. In the current implementation, only the simple type
    classes must be friends - to see why, look at Byte::ops and note that it
    accesses the <tt>_buf</tt> member of Int16, ..., Float64 and thus must be a
    friend of those classes.

    NB: This would all be simpler if: 1) g++ supported template friend
    functions (without explicit listing of all the template's arguments). 2)
    we did not have unsigned types.

    T1 The type of <tt>a</tt>.
    
    T2 The type of <tt>b</tt>.
    
    C A class which implements the policy used for comparing <tt>a</tt> 
    and <tt>b</tt>. 

    @param a The first argument.
    @param b The second argument.
    @param op The relational operator.
    @see Byte::ops */

template<class T1, class T2, class C>
bool rops(T1 a, T2 b, int op)
{
    switch (op) {
      case SCAN_EQUAL:
	return C::eq(a, b);
      case SCAN_NOT_EQUAL:
	return C::ne(a, b);
      case SCAN_GREATER:
	return C::gr(a, b);
      case SCAN_GREATER_EQL:
	return C::ge(a, b);
      case SCAN_LESS:
	return C::lt(a, b);
      case SCAN_LESS_EQL:
	return C::le(a, b);
      case SCAN_REGEXP:
	return C::re(a, b);
      default:
	cerr << "Unknown operator" << endl;
	return false;
    }
}

// $Log: Operators.h,v $
// Revision 1.15  2005/02/08 21:31:57  jimg
// Merged with release-3-4-10.
//
// Revision 1.13.2.2  2005/02/03 01:26:44  jimg
// Changes from Karl Benedict (added using namespace std;).
//
// Revision 1.14  2003/12/08 18:02:29  edavis
// Merge release-3-4 into trunk
//
// Revision 1.13.2.1  2003/09/06 22:47:13  jimg
// Updated the documentation.
//
// Revision 1.13  2003/04/22 19:40:28  jimg
// Merged with 3.3.1.
//
// Revision 1.12  2003/02/21 00:14:24  jimg
// Repaired copyright.
//
// Revision 1.11.2.1  2003/02/21 00:10:07  jimg
// Repaired copyright.
//
// Revision 1.11  2003/01/23 00:22:24  jimg
// Updated the copyright notice; this implementation of the DAP is
// copyrighted by OPeNDAP, Inc.
//
// Revision 1.10  2003/01/10 19:46:40  jimg
// Merged with code tagged release-3-2-10 on the release-3-2 branch. In many
// cases files were added on that branch (so they appear on the trunk for
// the first time).
//
// Revision 1.6.4.3  2002/08/08 06:54:57  jimg
// Changes for thread-safety. In many cases I found ugly places at the
// tops of files while looking for globals, et c., and I fixed them up
// (hopefully making them easier to read, ...). Only the files RCReader.cc
// and usage.cc actually use pthreads synchronization functions. In other
// cases I removed static objects where they were used for supposed
// improvements in efficiency which had never actually been verifiied (and
// which looked dubious).
//
// Revision 1.9  2002/06/18 15:36:24  tom
// Moved comments and edited to accommodate doxygen documentation-generator.
//
// Revision 1.8  2001/09/28 17:50:07  jimg
// Merged with 3.2.7.
//
// Revision 1.6.4.2  2001/09/25 20:30:38  jimg
// Removed debug.h
//
// Revision 1.7  2001/06/15 23:49:02  jimg
// Merged with release-3-2-4.
//
// Revision 1.6.4.1  2001/06/07 20:32:34  jimg
// Fixed a simple (but costly) error in dods_max().
// Added some instrumentation (which lead to fixing the error).
//
// Revision 1.6  2000/09/22 02:17:21  jimg
// Rearranged source files so that the CVS logs appear at the end rather than
// the start. Also made the ifdef guard symbols use the same naming scheme and
// wrapped headers included in other headers in those guard symbols (to cut
// down on extraneous file processing - See Lakos).
//
// Revision 1.5  2000/07/09 21:57:09  rmorris
// Mods's to increase portability, minimuze ifdef's in win32 and account
// for differences between the Standard C++ Library - most notably, the
// iostream's.
//
// Revision 1.4  2000/06/07 18:06:59  jimg
// Merged the pc port branch
//
// Revision 1.3.20.1  2000/06/02 18:29:31  rmorris
// Mod's for port to Win32.
//
// Revision 1.3  1999/05/04 19:47:21  jimg
// Fixed copyright statements. Removed more of the GNU classes.
//
// Revision 1.2  1999/04/29 02:29:31  jimg
// Merge of no-gnu branch
//
// Revision 1.1  1999/03/24 23:37:37  jimg
// Added

#endif // _operators_h
