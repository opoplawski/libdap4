
// (c) COPYRIGHT URI/MIT 1994-1999
// Please read the full copyright statement in the file COPYRIGHT.
//
// Authors:
//      jhrg,jimg       James Gallagher (jgallagher@gso.uri.edu)

// Implementation for Array.
//
// jhrg 9/13/94

// $Log: Array.cc,v $
// Revision 1.47  2000/09/21 16:22:06  jimg
// Merged changes from Jose Garcia that add exceptions to the software.
// Many methods that returned error codes now throw exectptions. There are
// two classes which are thrown by the software, Error and InternalErr.
// InternalErr is used to report errors within the library or errors using
// the library. Error is used to reprot all other errors. Since InternalErr
// is a subclass of Error, programs need only to catch Error.
//
// Revision 1.46  2000/07/09 22:05:35  rmorris
// Changes to increase portability, minimize ifdef's for win32 and account
// for differences in the iostreams implementations.
//
// Revision 1.45  2000/06/16 18:14:59  jimg
// Merged with 3.1.7
//
// Revision 1.43.6.1  2000/06/14 16:59:00  jimg
// Added instrumentation for the dtor.
//
// Revision 1.44  2000/06/07 18:06:57  jimg
// Merged the pc port branch
//
// Revision 1.43.20.1  2000/06/02 18:11:19  rmorris
// Mod's for Port to Win32.
//
// Revision 1.43.14.2  2000/02/17 05:03:12  jimg
// Added file and line number information to calls to InternalErr.
// Resolved compile-time problems with read due to a change in its
// parameter list given that errors are now reported using exceptions.
//
// Revision 1.43.14.1  2000/01/28 22:14:03  jgarcia
// Added exception handling and modify add_var to get a copy of the object
//
// Revision 1.43  1999/04/29 02:29:26  jimg
// Merge of no-gnu branch
//
// Revision 1.42  1998/12/15 20:50:23  jimg
// Added fix for strides <= 0 (which results in division by zero).
//
// Revision 1.41.4.1  1999/02/02 21:56:54  jimg
// String to string version
//
// Revision 1.41  1997/12/15 18:10:19  jimg
// Changed check_semantics() so that it returns an error message instead of
// printing one (thus it now works like all the other implementations of
// check_semantics().
//
// Revision 1.40  1997/03/08 19:01:52  jimg
// Changed default param to check_semantics() from  to String()
// and removed the default from the argument list in the mfunc definition
//
// Revision 1.39  1997/02/28 01:28:01  jimg
// Changed check_semantics() so that it now returns error messages in a String
// object (passed by reference).
//
// Revision 1.38  1996/09/12 21:02:35  jimg
// Fixed a nasty bug in print_array (private member function) where recursive
// calls were made in the wrong order causing 3+ dimension arrays to print many
// more values than actually exist in the array.
//
// Revision 1.37  1996/08/26 21:12:48  jimg
// Changes for version 2.07
//
// Revision 1.36  1996/08/13 16:46:14  jimg
// Added bounds checking to the add_constraint member function.
// add_constraint() now returns false when a bogus constraint is used.
//
// Revision 1.35  1996/06/11 17:21:31  jimg
// Fixed a bug in clear_constraint(); the dimension variables in the list
// _SHAPE were not correctly `cleared', now they are.
//
// Revision 1.34  1996/05/31 23:29:17  jimg
// Updated copyright notice.
//
// Revision 1.33  1996/05/29 22:08:32  jimg
// Made changes necessary to support CEs that return the value of a function
// instead of the value of a variable. This was done so that it would be
// possible to translate Sequences into Arrays without first reading the
// entire sequence over the network.
//
// Revision 1.32  1996/05/14 06:41:17  jimg
// Update for
//
// Revision 1.32  1996/05/10 21:18:16  jimg
// Fixed off-by-one error in add_constraint().
//
// Revision 1.31  1996/05/06 21:15:58  jimg
// Added the member functions dimension_start, _stop and _stride to this class.
// Changed the first argument of add_constraint from Pix &p to Pix p (the
// member function does not change its argument).
//
// Revision 1.30  1996/04/05 00:21:17  jimg
// Compiled with g++ -Wall and fixed various warnings.
//
// Revision 1.29  1996/03/05 18:48:24  jimg
// Fixed bugs in the print_array software.
// Fixed the ctor and related CE member functions (so that projections work).
//
// Revision 1.28  1996/02/01 22:22:42  jimg
// Merged changes between DODS-1.1 and DODS 2.x.
//
// Revision 1.27  1995/12/09  01:06:29  jimg
// Added changes so that relational operators will work properly for all the
// datatypes (including Sequences). The relational ops are evaluated in
// DDS::eval_constraint() after being parsed by DDS::parse_constraint().
//
// Revision 1.26  1995/12/06  21:40:58  jimg
// Added reset_constraint(), clear_constraint() and add_constraint() to manage
// the new constraint-related members (in struct dimension).
// Fixed variour member functions to return information about sizes,
// ... correctly both before and after constraints are set.
//
// Revision 1.25  1995/11/22  22:31:02  jimg
// Modified so that the Vector class is now the parent class.
//
// Revision 1.24  1995/10/23  23:20:44  jimg
// Added _send_p and _read_p fields (and their accessors) along with the
// virtual mfuncs set_send_p() and set_read_p().
//
// Revision 1.23  1995/08/26  00:31:21  jimg
// Removed code enclosed in #ifdef NEVER #endif.
//
// Revision 1.22  1995/08/22  23:45:33  jimg
// Removed DBMALLOC code.
// Added set_vec/vec mfuncs so that non-Array software can access the
// BaseType * vector.
// Changed names read_val and store_val to buf2val and val2buf. The old names
// remain.
// removed the card member function: used the new _type enum with a switch in
// its place.
//
// Revision 1.21.2.4  1995/09/27 21:49:03  jimg
// Fixed casts.
//
// Revision 1.21.2.3  1995/09/27  19:06:56  jimg
// Add casts to `cast away' const and unsigned in places where we call various
// xdr functions (which don't know about, or use, const or unsigned.
//
// Revision 1.21.2.2  1995/09/14  20:59:50  jimg
// Fixed declaration of, and calls to, _duplicate() by changing the formal
// param from a pointer to a reference.
//
// Revision 1.21.2.1  1995/07/11  18:17:09  jimg
// Added cast of xdr_array (used in BaseType's constructor) to xdrproc_t.
//
// Revision 1.21  1995/07/09  21:28:48  jimg
// Added copyright notice.
//
// Revision 1.20  1995/05/10  15:33:52  jimg
// Failed to change `config.h' to `config_dap.h' in these files.
//
// Revision 1.19  1995/05/10  13:45:01  jimg
// Changed the name of the configuration header file from `config.h' to
// `config_dap.h' so that other libraries could have header files which were
// installed in the DODS include directory without overwriting this one. Each
// config header should follow the convention config_<name>.h.
//
// Revision 1.18  1995/04/28  19:53:46  reza
// First try at adding constraints capability.
// Enforce a new size calculated from constraint expression.
//
// Revision 1.17  1995/03/16  17:22:58  jimg
// Added include of config_dap.h before all other includes.
// Fixed deletes of buffers in read_val().
// Added initialization of _buf in ctor.
//
// Revision 1.16  1995/03/04  14:34:40  jimg
// Major modifications to the transmission and representation of values:
// Added card() virtual function which is true for classes that
// contain cardinal types (byte, int float, string).
// Changed the representation of Str from the C rep to a C++
// class represenation.
// Chnaged read_val and store_val so that they take and return
// types that are stored by the object (e.g., inthe case of Str
// an URL, read_val returns a C++ String object).
// Modified Array representations so that arrays of card()
// objects are just that - no more storing strings, ... as
// C would store them.
// Arrays of non cardinal types are arrays of the DODS objects (e.g.,
// an array of a structure is represented as an array of Structure
// objects).
//
// Revision 1.15  1995/02/10  02:22:54  jimg
// Added DBMALLOC includes and switch to code which uses malloc/free.
// Private and protected symbols now start with `_'.
// Added new accessors for name and type fields of BaseType; the old ones
// will be removed in a future release.
// Added the store_val() mfunc. It stores the given value in the object's
// internal buffer.
// Made both List and Str handle their values via pointers to memory.
// Fixed read_val().
// Made serialize/deserialize handle all malloc/free calls (even in those
// cases where xdr initiates the allocation).
// Fixed print_val().
//
// Revision 1.14  1995/01/19  20:05:21  jimg
// ptr_duplicate() mfunc is now abstract virtual.
// Array, ... Grid duplicate mfuncs were modified to take pointers, not
// referenves.
//
// Revision 1.13  1995/01/11  15:54:39  jimg
// Added modifications necessary for BaseType's static XDR pointers. This
// was mostly a name change from xdrin/out to _xdrin/out.
// Removed the two FILE pointers from ctors, since those are now set with
// functions which are friends of BaseType.
//
// Revision 1.12  1994/12/19  20:52:45  jimg
// Minor modifications to the print_val mfunc.
//
// Revision 1.11  1994/12/16  20:13:31  dan
// Fixed serialize() and deserialize() for arrays of strings.
//
// Revision 1.10  1994/12/14  20:35:36  dan
// Added dimensions() member function to return number of dimensions
// contained in the array.
// Removed alloc_buf() and free_buf() member functions and placed them
// in util.cc.
//
// Revision 1.9  1994/12/14  17:50:34  dan
// Modified serialize() and deserialize() member functions to special
// case BaseTypes 'Str' and 'Url'.  These special cases do not call
// xdr_array, but iterate through the arrays using calls to XDR_STR.
// Modified print_val() member function to handle arrays of different
// BaseTypes.
// Modified append_dim() member function for initializing its dimension
// components.
// Removed dim() member function.
//
// Revision 1.7  1994/12/09  21:36:33  jimg
// Added support for named array dimensions.
//
// Revision 1.6  1994/12/08  15:51:41  dan
// Modified size() member to return cumulative size of all dimensions
// given the variable basetype.
// Modified serialize() and deserialize() member functions for data
// transmission using XDR.
//
// Revision 1.5  1994/11/22  20:47:45  dan
// Modified size() to return total number of elements.
// Fixed errors in deserialize (multiple returns).
//
// Revision 1.4  1994/11/22  14:05:19  jimg
// Added code for data transmission to parts of the type hierarchy. Not
// complete yet.
// Fixed erros in type hierarchy headers (typos, incorrect comments, ...).
//
// Revision 1.3  1994/10/17  23:34:42  jimg
// Added code to print_decl so that variable declarations are pretty
// printed.
// Added private mfunc duplicate().
// Added ptr_duplicate().
// Added Copy ctor, dtor and operator=.
//
// Revision 1.2  1994/09/23  14:31:36  jimg
// Added check_semantics mfunc.
// Added sanity checking for access to shape list (is it empty?).
// Added cvs log listing to Array.cc.
//

#ifdef __GNUG__
#pragma implementation
#endif

#include "config_dap.h"

#include <assert.h>

#include "Array.h"
#include "util.h"
#include "debug.h"
#include "InternalErr.h"

#ifdef TRACE_NEW
#include "trace_new.h"
#endif

#ifdef WIN32
using std::endl;
#endif

void
Array::_duplicate(const Array &a)
{
    Vector::_duplicate(a);

    _shape = a._shape;
}

void
Array::update_length(int size)
{
    if (length() == -1)
	set_length(size);
    else
	set_length(length() * size);
}

// Construct an instance of Array. The (BaseType *) is assumed to be
// allocated using new - The dtor for Vector will delete this object.

Array::Array(const string &n, BaseType *v) : Vector(n, v, dods_array_c)
{
}

Array::Array(const Array &rhs)
{
    _duplicate(rhs);
}

Array::~Array()
{
    DBG(cerr << "Entering ~Array (" << this << ")" << endl);
    DBG(cerr << "Exiting ~Array" << endl);
}

const Array &
Array::operator=(const Array &rhs)
{
    if (this == &rhs)
	return *this;
    
    _duplicate(rhs);

    return *this;
}

// Add the dimension DIM to the list of dimensions for this array. If NAME is
// given, set it to the name of this dimension. NAME defaults to "".
//
// Sets Vector's length member as a side effect.
//
// Returns: void

void 
Array::append_dim(int size, string name)
{ 
    dimension d;

    // This is invariant
    d.size = size;
    d.name = name;

    // this information changes with each constraint expression
    d.start = 0; 
    d.stop = size -1;
    d.stride = 1;
    d.c_size = size;
    d.selected = true;		// assume all dims selected.

    _shape.append(d); 

    update_length(size);
}

// Reset the dimension contraint information so that the entire array is
// `selected'

void
Array::reset_constraint()
{
    set_length(-1);

    for (Pix p = _shape.first(); p; _shape.next(p)) {
	dimension d = _shape(p);
	
	d.start = 0;
	d.stop = d.size;
	d.stride = 1;
	d.c_size = d.size;

	d.selected = true;

	update_length(d.size);
    }
}

// Tell the Array object to clear the constraint information about
// dimensions. Do this *once* before calling add_constraint() for each new 
// constraint expression. Only the dimensions explicitly selected using
// Array::add_constraint(...) will be sent.

void
Array::clear_constraint()
{
    for (Pix p = _shape.first(); p; _shape.next(p)) {
	dimension &d = _shape(p);
	
	d.start = 0;
	d.stop = 0;
	d.stride = 0;
	d.c_size = 0;
	d.selected = false;
    }

    set_length(-1);
}

// the start and stop indeces are inclusive.

static char *array_sss = \
"Invalid constraint parameters: At least one of the start, stride or stop 
specified do not match the array variable.";

void
Array::add_constraint(Pix p, int start, int stride, int stop)
{
    dimension &d = _shape(p);

    // Check for bad constraints.
    // Jose Garcia
    // Usually invalid data for a constraint is the user's mistake
    // because they build a wrong URL in the client side.
    if (start >= d.size || stop >= d.size || stride > d.size || stride <= 0)
	throw Error(malformed_expr, array_sss);

    if (((stop - start) / stride + 1) > d.size)
	throw Error(malformed_expr, array_sss);

    d.start = start;
    d.stop = stop;
    d.stride = stride;

    d.c_size = (stop - start) / stride + 1;
    
    DBG(cerr << "add_constraint: c_size = " << d.c_size << endl);

    d.selected = true;

    update_length(d.c_size);

}

Pix 
Array::first_dim() 
{ 
    return _shape.first();
}

void 
Array::next_dim(Pix &p) 
{ 
    if (!_shape.empty() && p)
	_shape.next(p); 
}

// Return the number of dimensions contained in the array. When CONSTRAINED
// is true, return the number of dimensions given the most recently evaluated
// constraint expression. By default, constraint is false.

unsigned int
Array::dimensions(bool constrained)
{
    unsigned int dim = 0;
    for(Pix p = first_dim(); p; next_dim(p)) 
	if (constrained) {
	    if (_shape(p).selected)
		dim++;
	}
	else
	    dim++;

    return dim;
}

// Return the size of the array dimension referred to by P. If CONSTRAINED is
// true, return the size of this dimension giventhe current
// constraint. CONSTRAINED is false by default.

int 
Array::dimension_size(Pix p, bool constrained) 
{ 
    int size = 0;

    if (!_shape.empty() && p)
	if (constrained) {
	    if (_shape(p).selected)
		size = _shape(p).c_size;
	    else
		size = 0;
	}
	else
	    size = _shape(p).size; 

    return size;
}

int 
Array::dimension_start(Pix p, bool constrained) 
{ 
    int start = 0;

    if (!_shape.empty() && p)
	if (constrained) {
	    if (_shape(p).selected)
		start = _shape(p).start;
	    else
		start= 0;
	}
	else
	    start = _shape(p).start; 

    return start;
}

int 
Array::dimension_stop(Pix p, bool constrained) 
{ 
    int stop = 0;

    if (!_shape.empty() && p)
	if (constrained) {
	    if (_shape(p).selected)
		stop = _shape(p).stop;
	    else
		stop= 0;
	}
	else
	    stop = _shape(p).stop; 

    return stop;
}

int 
Array::dimension_stride(Pix p, bool constrained) 
{ 
    int stride = 0;

    if (!_shape.empty() && p)
	if (constrained) {
	    if (_shape(p).selected)
		stride = _shape(p).stride;
	    else
		stride= 0;
	}
	else
	    stride = _shape(p).stride; 

    return stride;
}

// Return the name of the array dimension referred to by P.

string
Array::dimension_name(Pix p) 
{ 
  // Jose Garcia
  // Since this method is public, it is possible for a user
  // to call it before the Array object has been properly set
  // this will cause an exception which is the user's fault.
  // User in thins context is the developer of the surrogate library.
  if (_shape.empty())
      throw  InternalErr(__FILE__, __LINE__, 
			 "*This* array has no dimensions.");
  if (!p)
      throw  InternalErr(__FILE__, __LINE__, 
			 "The pointer indicating the dimesion is null.");

  return _shape(p).name; 
}

void
Array::print_decl(ostream &os, string space, bool print_semi,
		  bool constraint_info, bool constrained)
{
    if (constrained && !send_p())
	return;

    // print it, but w/o semicolon
    var()->print_decl(os, space, false, constraint_info, constrained); 

    for (Pix p = _shape.first(); p; _shape.next(p)) {
	if (constrained && !_shape(p).selected)
	    continue;
	os << "[";
	if (_shape(p).name != "")
	    os << _shape(p).name << " = ";
	if (constrained)
	    os << _shape(p).c_size << "]";
	else
	    os << _shape(p).size << "]";
    }

    if (print_semi)
	os << ";" << endl;
}

// Print an array. This is a private member function.
//
// OS is the stream used for writing
// INDEX is the index of VEC to start printing
// DIMS is the number of dimensions in the array
// SHAPE holds the size of the dimensions of the array. This is really a
// hold-over from an old version of this which was a plain function; I could
// use Array mfuncs to find out the size of the dimensions...
//
// Returns: the number of elements written.

unsigned int
Array::print_array(ostream &os, unsigned int index, unsigned int dims, 
		   unsigned int shape[])
{
    if (dims == 1) {
	os << "{";
	for (unsigned i = 0; i < shape[0]-1; ++i) {
	    var(index++)->print_val(os, "", false);
	    os << ", ";
	}
	var(index++)->print_val(os, "", false);
	os << "}";

	return index;
    }
    else {
	os << "{";
	// Fixed an off-by-one error in the following loop. Since the array
	// length is shape[dims-1]-1 *and* since we want one less dimension
	// than that, the correct limit on this loop is shape[dims-2]-1. From
	// Todd Karakasian.
	// The saga continues; the loop test should be `i < shape[0]-1'. jhrg
	// 9/12/96.
	for (unsigned i = 0; i < shape[0]-1; ++i) {
	    index = print_array(os, index, dims - 1, shape + 1);
	    os << ",";		// Removed the extra `}'. Also from Todd
	}
	index = print_array(os, index, dims - 1, shape + 1);
	os << "}";

	return index;
    }
}

// print the value given the current constraint.

void 
Array::print_val(ostream &os, string space, bool print_decl_p)
{
    // print the declaration if print decl is true.
    // for each dimension,
    //   for each element, 
    //     print the array given its shape, number of dimensions.
    // Add the `;'
    
    if (print_decl_p) {
	print_decl(os, space, false, false, false);
	os << " = ";
    }

    unsigned int dims = dimensions(true);
    unsigned int *shape = new unsigned int[dims];
    unsigned int i = 0;
    for (Pix p = first_dim(); p; next_dim(p))
	shape[i++] = dimension_size(p, true);

    print_array(os, 0, dims, shape);
    delete [] shape;

    if (print_decl_p) {
	os << ";" << endl;
    }
}

bool
Array::check_semantics(string &msg, bool)
{
    bool sem = BaseType::check_semantics(msg) && !_shape.empty();

    if (!sem)
	msg = "An array variable must have dimensions";

    return sem;
}
