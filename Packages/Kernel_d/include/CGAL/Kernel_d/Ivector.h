// ============================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision$
// release_date  : $CGAL_Date$
//
// file          : include/CGAL/Ivector.h
// package       : Kernel_d
// chapter       : Kernel
//
// source        : ddgeo/Linear_algebra.lw
// revision      : $Revision$
// revision_date : $Date$
//
// author(s)     : Michael Seel <seel@mpi-sb.mpg.de>
// maintainer    : Michael Seel <seel@mpi-sb.mpg.de>
// coordinator   : Susan Hert <hert@mpi-sb.mpg.de>
//
// implementation: Higher dimensional geometry
// ============================================================================
//---------------------------------------------------------------------
// file generated by notangle from Linear_algebra.lw
// please debug or modify noweb file
// based on LEDA architecture by S. Naeher, C. Uhrig
// coding: K. Mehlhorn, M. Seel
// debugging and templatization: M. Seel
//---------------------------------------------------------------------

#ifndef CGAL_IVECTOR_H
#define CGAL_IVECTOR_H

#include <CGAL/basic.h>
#include <CGAL/memory.h>
#include <CGAL/Kernel_d/d_utils.h>

#include <cmath>
#include <memory>
#include <new>
#include <iostream>
#include <vector>

CGAL_BEGIN_NAMESPACE

template <class NT, class A = CGAL_ALLOCATOR(NT) > 
  class Imatrix;
template <class NT, class A = CGAL_ALLOCATOR(NT) > 
  class Ivector;

#define CGAL_LA_PRECOND(cond,s) CGAL_assertion_msg((cond),s);
#define ERROR_HANDLER(n,s) CGAL_assertion_msg(!(n),s)

/*{\Msubst
<>#
<_NT,_ALLOC>#<NT>
Ivector#Vector
Imatrix#Matrix
}*/
/*{\Moptions print_title=yes}*/
/*{\Moptions outfile=Ivector.man}*/

/*{\Mtext \headerline{Common Notation}
The following data types use the concept of iterator ranges as an
abstraction of tuples and sets. For an iterator range |[first,last)|
we define |S = set [first,last)| as the ordered tuple $(|S[0]|,|S[1]|,
\ldots |S[d-1]|)$ where $|S[i]| = |*| |++|^{(i)}|first|$ (the element
obtained by forwarding the iterator by operator |++| $i$ times and
then dereferencing it to get the value to which it points). We write
|d = size [first,last)|.  This extends the syntax of random access
iterators to input iterators.  If we index the tuple as above then we
require that $|++|^{(d)}|first == last|$ (note that |last| points
beyond the last element to be accepted).}*/

/*{\Manpage {Vector}{NT}{Vectors with NT Entries}{v}}*/

template <class _NT, class _ALLOC> 
class Ivector
{
/*{\Mdefinition An instance of data type |Ivector| is a vector of
variables of number type |NT|.  Together with the type |Imatrix| it
realizes the basic operations of linear algebra. Internal correctness
tests are executed if compiled with the flag [[CGAL_LA_SELFTEST]].}*/

public:

/*{\Mtypes 5.5}*/
typedef _NT*       pointer;
typedef const _NT* const_pointer;

typedef _NT    NT;
/*{\Mtypemember the ring type of the components.}*/ 

typedef pointer iterator;
/*{\Mtypemember the iterator type for accessing components.}*/ 

typedef const_pointer const_iterator;
/*{\Mtypemember the const iterator type for accessing components.}*/ 

class Initialize {};
/*{\Mtypemember a tag class for homogeneous initialization}*/

protected:
  friend class Imatrix<_NT,_ALLOC>;
  NT* v;
  int dim;
  typedef _ALLOC allocator_type;
  static allocator_type MM;

  inline void allocate_vec_space(NT*& vi, int di)
  {
  /* We use this procedure to allocate memory. We first get an appropriate 
     piece of memory from the allocator and then initialize each cell 
     by an inplace new. */

    vi = MM.allocate(di);
    NT* p = vi + di - 1;
    while (p >= vi) { new (p) NT(0);  p--; }   
  }

  inline void deallocate_vec_space(NT*& vi, int di)
  {
  /* We use this procedure to deallocate memory. We have to free it by
     the allocator scheme. We first call the destructor for type NT for each
     cell of the array and then return the piece of memory to the memory
     manager. */

    NT* p = vi + di - 1;
    while (p >= vi)  { p->~NT(); p--; }
    MM.deallocate(vi, di);
    vi = (NT*)0;
  }

  inline void 
  check_dimensions(const Ivector<_NT,_ALLOC>& vec) const
  { 
    CGAL_LA_PRECOND((dim == vec.dim), "Ivector::check_dimensions:\
    object dimensions disagree.")
  }

public:

/*{\Mcreation v 3}*/

Ivector(int d = 0) 
/*{\Mcreate creates an instance |\Mvar| of type |\Mname|. 
|\Mvar| is initialized to a vector of dimension $d$.}*/ 
{ 
  CGAL_LA_PRECOND( d >= 0 , 
    "Ivector::constructor: negative dimension.") 
  dim = d; 
  v = (NT*)0;
  if (dim > 0){ 
    allocate_vec_space(v,dim);
    while (d--) v[d] = NT(0);
  }
}

Ivector(int d, const Initialize&, const NT& x) 
/*{\Mcreate creates an instance |\Mvar| of type |\Mname|. 
|\Mvar| is initialized to a vector of dimension $d$ with entries |x|.}*/ 
{ 
  CGAL_LA_PRECOND( d >= 0 , "Ivector::constructor: negative dimension.") 
  dim = d; 
  v = (NT*)0;
  if (dim > 0){ 
    allocate_vec_space(v,dim);
    while (d--) v[d] = x;
  }
}

template <class Forward_iterator>
Ivector(Forward_iterator first, Forward_iterator last)
/*{\Mcreate creates an instance |\Mvar| of type |\Mname|; 
|\Mvar| is initialized to the vector with entries
|set [first,last)|. \precond |Forward_iterator| has value type |NT|.}*/
{ dim = std::distance(first,last);
  allocate_vec_space(v,dim);
  iterator it = begin();
  while (first != last) { *it = *first; ++it; ++first; }
}

private:
void init(int d, const NT& x0, const NT& x1, const NT& x2=0, const NT& x3=0)
{ dim = d; allocate_vec_space(v,dim);
  v[0]=x0; v[1]=x1; ( d>2 ? (v[2]=x2) : 0); ( d>3 ? (v[3]=x3) : 0);
}
public:

Ivector(const NT& a, const NT& b) { init(2,a,b); }
/*{\Mcreate creates an instance |\Mvar| of type |\Mname|.
|\Mvar| is initialized to the two-dimensional vector $(a,b)$.}*/

Ivector(const NT& a, const NT& b, const NT& c) { init(3,a,b,c); }
/*{\Mcreate creates an instance |\Mvar| of type |\Mname|. 
|\Mvar| is initialized to the three-dimensional vector 
$(a,b,c)$.}*/

Ivector(const NT& a, const NT& b, const NT& c, const NT& d) 
/*{\Mcreate creates an instance |\Mvar| of type |\Mname|; 
|\Mvar| is initialized to the four-dimensional vector 
$(a,b,c,d)$.}*/
{ init(4,a,b,c,d); }

Ivector(int a, int b) { init(2,a,b); }
Ivector(int a, int b, int c) { init(3,a,b,c); }
Ivector(int a, int b, int c, int d) { init(4,a,b,c,d); }

 
Ivector(const Ivector<_NT,_ALLOC>& p)
{ dim = p.dim;
  if (dim > 0) allocate_vec_space(v,dim);
  else         v = (NT*)0;
  for(int i=0; i<dim; i++) { v[i] = p.v[i]; }
}


Ivector<_NT,_ALLOC>& operator=(const Ivector<_NT,_ALLOC>& vec)
{ 
  register int n = vec.dim;
  if (n != dim) { 
    if (dim > 0) deallocate_vec_space(v,dim);
    dim=n;
  }
  if (n > 0) allocate_vec_space(v,n);
  else       v = (NT*)0;

  while (n--) v[n] = vec.v[n];
  return *this;
}

~Ivector() 
{ if (dim > 0) deallocate_vec_space(v,dim); }

/*{\Moperations 3 3}*/

int  dimension() const { return dim; }
/*{\Mop returns the dimension of |\Mvar|.}*/ 

bool is_zero() const 
/*{\Mop returns true iff |\Mvar| is the zero vector.}*/ 
{ for(int i=0; i<dim; ++i) if (v[i]!=NT(0)) return false; 
  return true; }
  
NT& operator[](int i)
/*{\Marrop returns $i$-th component of |\Mvar|.\\
           \precond $0\le i \le |v.dimension()-1|$. }*/
{ CGAL_LA_PRECOND((0<=i && i<dim), 
    "Ivector::operator[]: index out of range.")
  return v[i];
}
  
NT operator[](int i) const
{ CGAL_LA_PRECOND((0<=i && i<dim), 
    "Ivector::operator[]: index out of range.")
  return v[i];
}

inline Ivector<_NT,_ALLOC>& operator+=(const Ivector<_NT,_ALLOC>& v1);
/*{\Mbinop Addition plus assignment. \precond\\
|v.dimension() == v1.dimension()|.}*/

inline Ivector<_NT,_ALLOC>& operator-=(const Ivector<_NT,_ALLOC>& v1);
/*{\Mbinop Subtraction plus assignment. \precond\\ 
|v.dimension() == v1.dimension()|.}*/

inline Ivector<_NT,_ALLOC>& operator*=(const NT& s);
/*{\Mbinop Scalar multiplication plus assignment.}*/

inline Ivector<_NT,_ALLOC>& operator/=(const NT& s);
/*{\Mbinop Scalar division plus assignment.}*/
 
Ivector<_NT,_ALLOC>  operator+(const Ivector<_NT,_ALLOC>& v1) const;
/*{\Mbinop Addition. \precond\\ 
|v.dimension() == v1.dimension()|.}*/

Ivector<_NT,_ALLOC>  operator-(const Ivector<_NT,_ALLOC>& v1) const;
/*{\Mbinop Subtraction. \precond\\ 
|v.dimension() = v1.dimension()|.}*/

NT operator*(const Ivector<_NT,_ALLOC>& v1) const;
/*{\Mbinop Inner Product. \precond\\ 
|v.dimension() = v1.dimension()|.}*/

Ivector<_NT,_ALLOC> compmul(const NT& r) const;

Ivector<_NT,_ALLOC>  operator-() const;
/*{\Munopfunc Negation.}*/

/*{\Mtext We provide component access via |iterator| and |const_iterator|
by the standard iterator range access operations |begin()|, |end()|.}*/
iterator begin() { return v; }
iterator end() { return v+dim; }
const_iterator begin() const { return v; }
const_iterator end() const { return v+dim; }


bool     operator==(const Ivector<_NT,_ALLOC>& w) const;
bool     operator!=(const Ivector<_NT,_ALLOC>& w) const 
{ return !(*this == w); }

static int  compare(const Ivector<_NT,_ALLOC>&, 
                    const Ivector<_NT,_ALLOC>&);

};


/*{\Mimplementation Vectors are implemented by arrays of type
|NT|. All operations on a vector |v| take time $O(|v.dimension()|)$,
except for |dimension()| and $[\ ]$ which take constant time. The space
requirement is $O(|v.dimension()|)$. }*/


template <class NT, class A> 
Ivector<NT,A> operator*(const NT& r, const Ivector<NT,A>& v)
/*{\Mbinopfunc Componentwise multiplication with number $r$.}*/
{ return v.compmul(r); }

template <class NT, class A> 
Ivector<NT,A> operator*(const Ivector<NT,A>& v, const NT& r)
/*{\Mbinopfunc Componentwise multiplication with number $r$.}*/
{ return v.compmul(r); }

template <class NT, class A> 
Ivector<NT,A> operator*(int r, const Ivector<NT,A>& v)
{ return v.compmul(r); } 

template <class NT, class A> 
Ivector<NT,A> operator*(const Ivector<NT,A>& v, int r)
{ return v.compmul(r); }

template <class NT, class A> 
Ivector<NT,A>& Ivector<NT,A>::
operator+=(const Ivector<NT,A>& vec)
{ 
  check_dimensions(vec);
  register int n = dim;
  while (n--) v[n] += vec.v[n];
  return *this;
}

template <class NT, class A> 
Ivector<NT,A>& Ivector<NT,A>::
operator-=(const Ivector<NT,A>& vec)
{ 
  check_dimensions(vec);
  register int n = dim;
  while (n--) v[n] -= vec.v[n];
  return *this;
}

template <class NT, class A> 
Ivector<NT,A>& Ivector<NT,A>::
operator*=(const NT& s)
{ register int n = dim;
  while (n--) v[n] *= s;
  return *this;
}

template <class NT, class A>
Ivector<NT,A>& Ivector<NT,A>::
operator/=(const NT& s)
{ register int n = dim;
  while (n--) v[n] /= s;
  return *this;
}

template <class NT, class A> 
Ivector<NT,A> Ivector<NT,A>::
operator+(const Ivector<NT,A>& vec) const
{ 
  check_dimensions(vec);
  register int n = dim;
  Ivector<NT,A> result(n);
  while (n--) result.v[n] = v[n]+vec.v[n];
  return result;
}

template <class NT, class A> 
Ivector<NT,A> Ivector<NT,A>::
operator-(const Ivector<NT,A>& vec) const
{ 
  check_dimensions(vec);
  register int n = dim;
  Ivector<NT,A> result(n);
  while (n--) result.v[n] = v[n]-vec.v[n];
  return result;
}

template <class NT, class A> 
Ivector<NT,A> Ivector<NT,A>::
operator-() const  // unary minus
{ 
  register int n = dim;
  Ivector<NT,A> result(n);
  while (n--) result.v[n] = -v[n];
  return result;
}


template <class NT, class A> 
Ivector<NT,A> Ivector<NT,A>::
compmul(const NT& x) const
{ 
  int n = dim;
  Ivector<NT,A> result(n);
  while (n--) result.v[n] = v[n] * x;
  return result;
}


template <class NT, class A> 
NT Ivector<NT,A>::
operator*(const Ivector<NT,A>& vec) const
{ 
  check_dimensions(vec);
  NT result=0;
  register int n = dim;
  while (n--) result = result+v[n]*vec.v[n];
  return result;
}

template <class NT, class A> 
bool Ivector<NT,A>::
operator==(const Ivector<NT,A>& vec)  const
{ 
  if (vec.dim != dim) return false;
  int i = 0;
  while ((i<dim) && (v[i]==vec.v[i])) i++;
  return (i==dim);
}

template <class NT, class A> 
int Ivector<NT,A>::
compare(const Ivector<NT,A>& v1, const Ivector<NT,A>& v2)
{ 
  register int i;
  v1.check_dimensions(v2);
  for(i=0; i < v1.dimension() && v1[i]==v2[i]; i++);
  if (i == v1.dimension()) return 0;
  return (v1[i] < v2[i]) ?  -1 : 1;
}

template <class _NT, class _ALLOC> 
std::ostream& operator<<(std::ostream& os, const Ivector<_NT,_ALLOC>& v)
/*{\Xbinopfunc  writes |\Mvar| componentwise to the output stream $O$.}*/
{
  /* syntax: d x_0 x_1 ... x_d-1 */
  CGAL::print_d<_NT> prt(&os);
  if (os.iword(IO::mode)==IO::PRETTY) os << "LA::Vector(";
  prt(v.dimension());
  if (os.iword(IO::mode)==IO::PRETTY) { os << " ["; prt.reset(); }
  std::for_each(v.begin(),v.end(),prt);
  if (os.iword(IO::mode)==IO::PRETTY) os << "])";
  return os;
}

template <class _NT, class _ALLOC> 
std::istream& operator>>(std::istream& is, Ivector<_NT,_ALLOC>& v)
/*{\Xbinopfunc  reads |\Mvar| componentwise from the input stream $I$.}*/
{ 
  /* syntax: d x_0 x_1 ... x_d-1 */
  int dim;
  switch (is.iword(IO::mode)) {
    case IO::ASCII :
    case IO::BINARY :
      is >> dim;
      v = Ivector<_NT,_ALLOC>(dim);
      copy_n(std::istream_iterator<_NT>(is),dim,v.begin());
      break;
    default:
      std::cerr<<"\nStream must be in ascii or binary mode"<<std::endl;
      break;
  }
  return is;
}


template <class NT, class A>
Ivector<NT,A>::allocator_type Ivector<NT,A>::MM;


CGAL_END_NAMESPACE
#endif // CGAL_IVECTOR_H

