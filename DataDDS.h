
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
 
// (c) COPYRIGHT URI/MIT 1997-1999
// Please read the full copyright statement in the file COPYRIGHT_URI.
//
// Authors:
//      jhrg,jimg       James Gallagher <jgallagher@gso.uri.edu>

// Specialize DDS for returned data. This currently means adding version
// information about the source of the data. Was it from a version 1, 2 or
// later server?
// 
// jhrg 9/19/97

#ifndef _datadds_h
#define _datadds_h 1

#include <iostream>
#include <string>

#ifndef _dds_h
#include "DDS.h"
#endif

/** This class adds some useful state information to the DDS
    structure.  It is for use on the client side of the connection. 
    
    @note Update: I removed the DEFAULT_BASETYPE_FACTORY switch because it
    caused more confusion than it avoided. See Trac #130.

    @note The compile-time symbol DEFAULT_BASETYPE_FACTORY controls whether
    the old (3.4 and earlier) DDS and DataDDS constructors are supported.
    These constructors now use a default factory class (BaseTypeFactory,
    implemented by this library) to instantiate Byte, ..., Grid variables. To
    use the default ctor in your code you must also define this symbol. If
    you \e do choose to define this and fail to provide a specialization of
    BaseTypeFactory when your software needs one, you code may not link or
    may fail at run time. In addition to the older ctors for DDS and DataDDS,
    defining the symbol also makes some of the older methods in Connect
    available (because those methods require the older DDS and DataDDS ctors.

    @brief Holds a DAP2 DDS.
    @see Connect
    */

class DataDDS : public DDS {
private:
    string d_server_version;
    int d_server_version_major;
    int d_server_version_minor;

    string d_protocol_version;
    int d_server_protocol_major;
    int d_server_protocol_minor;

    void m_version_string_to_numbers();
    void m_protocol_string_to_numbers();

public:
    DataDDS(BaseTypeFactory *factory, const string &n = "",
	    const string &v = "", const string &p = "");
    // #ifdef DEFAULT_BASETYPE_FACTORY
    // DataDDS(const string &n = "", const string &v = "");
    // #endif
    virtual ~DataDDS() {}

    /** Sets the version string.  This typically looks something like:
    <tt>DODS/2.15</tt>, where ``2'' is the major version number, and ``15''
    the minor number. */
    void set_version(const string &v) {
        d_server_version = v;
        m_version_string_to_numbers();
    }
    /** @brief Get the server version string, unparsed. */
    string get_version() const { return d_server_version; }
    /** @brief Returns the major version number. */
    int get_version_major() const { return d_server_version_major; }
    /** @brief Returns the minor version number. */
    int get_version_minor() const { return d_server_version_minor; }

    void set_protocol(const string &p) {
        d_protocol_version = p;
        m_protocol_string_to_numbers();
    }
    string get_protocol() const { return d_protocol_version; }
    int get_protocol_major() const { return d_server_protocol_major; }
    int get_protocol_minor() const { return d_server_protocol_minor; }
};

// Revision 1.8.4.1  2002/09/05 22:52:54  pwest
// Replaced the GNU data structures SLList and DLList with the STL container
// class vector<>. To maintain use of Pix, changed the Pix.h header file to
// redefine Pix to be an IteratorAdapter. Usage remains the same and all code
// outside of the DAP should compile and link with no problems. Added methods
// to the different classes where Pix is used to include methods to use STL
// iterators. Replaced the use of Pix within the DAP to use iterators instead.
// Updated comments for documentation, updated the test suites, and added some
// unit tests. Updated the Makefile to remove GNU/SLList and GNU/DLList.
//
// $Log: DataDDS.h,v $
// Revision 1.18  2005/03/30 21:25:43  jimg
// Added DEFAULT_BASETYPE_FACTORY define; use this to control whether
// the DDS objects suppy the BaseTypeFactory by default.
//
// Revision 1.17  2005/01/28 17:25:12  jimg
// Resolved conflicts from merge with release-3-4-9
//
// Revision 1.14.2.4  2004/12/23 21:11:32  jimg
// Removed the sequence level method declarations.
//
// Revision 1.16  2004/07/07 21:08:47  jimg
// Merged with release-3-4-8FCS
//
// Revision 1.14.2.3  2004/07/02 20:41:51  jimg
// Removed (commented) the pragma interface/implementation lines. See
// the ChangeLog for more details. This fixes a build problem on HP/UX.
//
// Revision 1.15  2003/12/08 18:02:29  edavis
// Merge release-3-4 into trunk
//
// Revision 1.14.2.2  2003/11/18 22:05:31  jimg
// Removed old Sequence level code. Added string get_version() method.
//
// Revision 1.14.2.1  2003/06/23 11:49:18  rmorris
// The // #pragma interface directive to GCC makes the dynamic typing functionality
// go completely haywire under OS X on the PowerPC.  We can't use that directive
// on that platform and it was ifdef'd out for that case.
//
// Revision 1.14  2003/04/22 19:40:27  jimg
// Merged with 3.3.1.
//
// Revision 1.13  2003/02/21 00:14:24  jimg
// Repaired copyright.
//
// Revision 1.12.2.1  2003/02/21 00:10:07  jimg
// Repaired copyright.
//
// Revision 1.12  2003/01/23 00:22:24  jimg
// Updated the copyright notice; this implementation of the DAP is
// copyrighted by OPeNDAP, Inc.
//
// Revision 1.11  2003/01/10 19:46:40  jimg
// Merged with code tagged release-3-2-10 on the release-3-2 branch. In many
// cases files were added on that branch (so they appear on the trunk for
// the first time).
//
// Revision 1.10  2002/06/18 15:36:24  tom
// Moved comments and edited to accommodate doxygen documentation-generator.
//
// Revision 1.9  2002/06/03 22:21:15  jimg
// Merged with release-3-2-9
//
// Revision 1.8  2000/09/22 02:17:19  jimg
// Rearranged source files so that the CVS logs appear at the end rather than
// the start. Also made the ifdef guard symbols use the same naming scheme and
// wrapped headers included in other headers in those guard symbols (to cut
// down on extraneous file processing - See Lakos).
//
// Revision 1.7  2000/08/02 22:46:49  jimg
// Merged 3.1.8
//
// Revision 1.4.6.1  2000/08/02 21:10:07  jimg
// Removed the header config.h. If this file uses the dods typedefs for
// cardinal datatypes, then it gets those definitions from the header
// dods-datatypes.h.
//
// Revision 1.6  2000/07/09 21:57:09  rmorris
// Mods's to increase portability, minimuze ifdef's in win32 and account
// for differences between the Standard C++ Library - most notably, the
// iostream's.
//
// Revision 1.5  2000/06/07 18:06:58  jimg
// Merged the pc port branch
//
// Revision 1.4.20.1  2000/06/02 18:21:26  rmorris
// Mod's for port to Win32.
//
// Revision 1.4  1999/04/29 02:29:29  jimg
// Merge of no-gnu branch
//
// Revision 1.3.6.1  1999/02/02 21:56:58  jimg
// String to string version
//
// Revision 1.3  1998/02/05 20:13:52  jimg
// DODS now compiles with gcc 2.8.x
//
// Revision 1.2  1998/01/12 14:27:57  tom
// Second pass at class documentation.
//
// Revision 1.1  1997/09/22 22:19:27  jimg
// Created this subclass of DDS to hold version information in the data DDS
//

#endif // _datadds_h
