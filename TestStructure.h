
// -*- C++ -*-

// (c) COPYRIGHT URI/MIT 1995-1999
// Please read the full copyright statement in the file COPYRIGHT.
//
// Authors:
//      jhrg,jimg       James Gallagher (jgallagher@gso.uri.edu)

// Interface for the class TestStructure. See TestByte.h
//
// jhrg 1/12/95

/* 
 * $Log: TestStructure.h,v $
 * Revision 1.13  2000/09/21 16:22:09  jimg
 * Merged changes from Jose Garcia that add exceptions to the software.
 * Many methods that returned error codes now throw exectptions. There are
 * two classes which are thrown by the software, Error and InternalErr.
 * InternalErr is used to report errors within the library or errors using
 * the library. Error is used to reprot all other errors. Since InternalErr
 * is a subclass of Error, programs need only to catch Error.
 *
 * Revision 1.12.14.1  2000/02/17 05:03:15  jimg
 * Added file and line number information to calls to InternalErr.
 * Resolved compile-time problems with read due to a change in its
 * parameter list given that errors are now reported using exceptions.
 *
 * Revision 1.12  1999/04/29 02:29:33  jimg
 * Merge of no-gnu branch
 *
 * Revision 1.11.10.1  1999/02/02 21:57:04  jimg
 * String to string version
 *
 * Revision 1.11  1997/08/11 18:19:28  jimg
 * Fixed comment leaders for new CVS version
 *
 * Revision 1.10  1996/05/31 23:30:35  jimg
 * Updated copyright notice.
 *
 * Revision 1.9  1996/05/16 22:50:24  jimg
 * Dan's changes for version 2.0. Added a parameter to read that returns
 * an error code so that EOF can be distinguished from an actual error when
 * reading sequences. This *may* be replaced by an error member function
 * in the future.
 *
 * Revision 1.8  1996/04/05 00:22:02  jimg
 * Compiled with g++ -Wall and fixed various warnings.
 *
 * Revision 1.7  1995/12/09  01:07:29  jimg
 * Added changes so that relational operators will work properly for all the
 * datatypes (including Sequences). The relational ops are evaluated in
 * DDS::eval_constraint() after being parsed by DDS::parse_constraint().
 *
 * Revision 1.6  1995/12/06  19:55:46  jimg
 * Changes read() member function from three arguments to two.
 *
 * Revision 1.5  1995/08/26  00:32:02  jimg
 * Removed code enclosed in #ifdef NEVER #endif.
 *
 * Revision 1.4  1995/08/23  00:44:38  jimg
 * Updated to use the newer member functions.
 *
 * Revision 1.3  1995/02/10  02:34:01  jimg
 * Modified Test<class>.h and .cc so that they used to new definitions of
 * read_val().
 * Modified the classes read() so that they are more in line with the
 * class library's intended use in a real subclass set.
 *
 * Revision 1.2  1995/01/19  21:59:45  jimg
 * Added read_val from dummy_read.cc to the sample set of sub-class
 * implementations.
 * Changed the declaration of readVal in BaseType so that it names the
 * mfunc read_val (to be consistant with the other mfunc names).
 * Removed the unnecessary duplicate declaration of the abstract virtual
 * mfuncs read and (now) read_val from the classes Byte, ... Grid. The
 * declaration in BaseType is sufficient along with the decl and definition
 * in the *.cc,h files which contain the subclasses for Byte, ..., Grid.
 *
 * Revision 1.1  1995/01/19  20:20:57  jimg
 * Created as an example of subclassing the class hierarchy rooted at
 * BaseType.
 *
 */

#ifndef _TestStructure_h
#define _TestStructure_h 1

#ifdef _GNUG_
#pragma interface
#endif

#include "Structure.h"

class TestStructure: public Structure {
public:
    TestStructure(const string &n = "");
    virtual ~TestStructure();

    virtual BaseType *ptr_duplicate();

    virtual bool read(const string &dataset);
};

#endif
