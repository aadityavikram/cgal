//---------------------------------------------------------------------
// file generated by notangle from noweb/Aff_transformationHd.lw
// please debug or modify noweb file
// coding: K. Mehlhorn, M. Seel
//---------------------------------------------------------------------

#ifndef CGAL_AFF_TRANSFORMATIONHD_H
#define CGAL_AFF_TRANSFORMATIONHD_H

#ifndef NOCGALINCL
#include <CGAL/basic.h>
#include <CGAL/Handle_for.h>
#endif
#include <CGAL/Kernel_d/PointHd.h>
#include <CGAL/Kernel_d/VectorHd.h>
#include <CGAL/Kernel_d/DirectionHd.h>
#include <CGAL/Kernel_d/HyperplaneHd.h>

CGAL_BEGIN_NAMESPACE

template <class RT, class LA > class Aff_transformationHd;
template <class RT, class LA > class Aff_transformationHd_rep;

template <class RT, class LA>
class Aff_transformationHd_rep : 
  private LA::Matrix, public Ref_counted {
  typedef typename LA::Matrix Matrix;
  friend class Aff_transformationHd<RT,LA>;
public:
  Aff_transformationHd_rep(int d) : Matrix(d+1) {}
  Aff_transformationHd_rep(const Matrix& M_init) : Matrix(M_init) {}
  ~Aff_transformationHd_rep() {}
}; 


/*{\Moptions outfile=Aff_transformation_d.man}*/ 
/*{\Manpage{Aff_transformation_d}{R}{Affine Transformations}{t}}*/
/*{\Msubst 
Hd<RT,LA>#_d<R>
Aff_transformationHd#Aff_transformation_d
Quotient<RT>#FT
}*/

template <class _RT, class _LA>
class Aff_transformationHd : 
  public Handle_for< Aff_transformationHd_rep<_RT,_LA> > { 

  typedef Aff_transformationHd_rep<_RT,_LA> Rep;
  typedef Handle_for<Rep> Base;
  typedef Aff_transformationHd<_RT,_LA> Self;

/*{\Mdefinition 
An instance of the data type |\Mname| is an affine transformation of
$d$-dimensional space. It is specified by a square matrix
$M$ of dimension $d + 1$. All entries in the last row of |M| except
the diagonal entry must be zero; the diagonal entry must be non-zero.
A point $p$ with homogeneous coordinates $(p[0], \ldots, p[d])$ can be
transformed into the point |p.transform(A)|, where |A| is an affine
transformation created from |M| by the constructors below. }*/

public: 
/*{\Mtypes 4}*/

typedef _RT RT;
/*{\Mtypemember the ring type.}*/
typedef Quotient<_RT> FT;
/*{\Mtypemember the field type.}*/
typedef _LA LA;
/*{\Mtypemember the linear algebra layer.}*/

/*{\Mcreation 3}*/

Aff_transformationHd(int d = 0, bool identity=false) : Base( Rep(d) )
/*{\Mcreate introduces a transformation in $d$-dimensional space. 
If identity is true then the transformation is the identity 
transformation.}*/
{ if (identity) for (int i = 0; i <= d; ++i) (*ptr)(i,i) = RT(1); }

Aff_transformationHd(const typename LA::Matrix& M) : Base( Rep(M) )
/*{\Mcreate introduces the transformation of $d$ - space specified by
matrix $M$. \precond |M| is a square matrix of dimension $d + 1$. }*/
{ CGAL_assertion_msg((M.row_dimension()==M.column_dimension()),
  "Aff_transformationHd::\
   construction: initialization matrix is not quadratic.");
}

template <typename Forward_iterator>
Aff_transformationHd(Forward_iterator start, Forward_iterator end) :
  Base( Rep(std::distance(start,end)-1) )
/*{\Mcreate introduces the transformation of $d$-space specified by a
diagonal matrix with entries |set [start,end)| on the diagonal 
(a scaling of the space). \precond |set [start,end)| is a vector of 
dimension $d+1$.}*/
{ int i=0; while (start != end) { (*ptr)(i,i) = *start++;++i; } }

Aff_transformationHd(const VectorHd<RT,LA>& v) :
  Base( Rep(v.dimension()) )
/*{\Mcreate introduces the translation by vector $v$.}*/ 
{ register int d = v.dimension();
  for (int i = 0; i < d; ++i) {
    (*ptr)(i,i) = v.homogeneous(d);
    (*ptr)(i,d) = v.homogeneous(i);
  }
  (*ptr)(d,d) = v.homogeneous(d);
}

Aff_transformationHd(int d, const RT& num, const RT& den) : Base( Rep(d) ) 
/*{\Mcreate returns a scaling by a scale factor $\mathit{num}/
\mathit{den}$.}*/
{ typename LA::Matrix& M(*ptr);
  for (int i = 0; i < d; ++i) M(i,i) = num;  
  M(d,d) = den;
}

Aff_transformationHd(int d, 
  const RT& sin_num, const RT& cos_num, const RT& den, 
  int e1 = 0, int e2 = 1); 
/*{\Mcreate returns a planar rotation with sine and cosine values
|sin_num/den| and |cos_num/den| in the plane spanned by
the base vectors $b_{e1}$ and $b_{e2}$ in $d$-space. Thus
the default use delivers a planar rotation in the $x$-$y$
plane. \precond $|sin_num|^2 + |cos_num|^2 = |den|^2$
and $0 \leq e_1 < e_2 < d$}*/

Aff_transformationHd(int d, const DirectionHd<RT,LA>& dir, 
  const RT& num, const RT& den, int e1 = 0, int e2 = 1); 
/*{\Mcreate returns a planar rotation within the plane spanned by
the base vectors $b_{e1}$ and $b_{e2}$ in $d$-space.  The rotation
parameters are given by the $2$-dimensional direction |dir|, such that
the difference between the sines and cosines of the rotation given by
|dir| and the approximated rotation are at most |num/den| each.\\
\precond |dir.dimension()==2|, |!dir.is_degenerate()| and |num < den|
is positive and $0 \leq e_1 < e_2 < d$ }*/

/*{\Moperations 5 3}*/

int dimension() const 
{ return (*ptr).row_dimension()-1; }
/*{\Mop the dimension of the underlying space }*/

const typename LA::Matrix& matrix() const 
{ return static_cast<const typename LA::Matrix&>(*ptr); }
/*{\Mop returns the transformation matrix }*/

typename LA::Vector operator()(const typename LA::Vector& iv) const
// transforms the ivector by a matrix multiplication
{ return matrix()*iv; }


Aff_transformationHd<RT,LA> inverse() const
/*{\Mop returns the inverse transformation.
\precond |\Mvar.matrix()| is invertible.}*/
{ Aff_transformationHd<RT,LA> Inv; RT D; 
  typename LA::Vector dummy;
  if (!LA::inverse((*ptr),(*Inv.ptr),D,dummy)) 
  CGAL_assertion_msg(0,"Aff_transformationHd::inverse: not invertible."); 
  return Inv;
}
  
Aff_transformationHd<RT,LA>  
operator*(const Aff_transformationHd<RT,LA>& s) const
/*{\Mbinop composition of transformations. Note that transformations
are not necessarily commutative. |t*s| is the transformation
which transforms first by |t| and then by |s|.}*/
{ CGAL_assertion_msg((dimension()==s.dimension()),
  "Aff_transformationHd::operator*: dimensions disagree.");
  return Aff_transformationHd<RT,LA>(matrix()*s.matrix()); 
}

bool operator==(const Aff_transformationHd<RT,LA>& a1) const
{ if (identical(a1)) return true;
  return (matrix() == a1.matrix());
}
bool operator!=(const Aff_transformationHd<RT,LA>& a1) const
{ return !operator==(a1); }

}; // Aff_transformationHd

template <class RT, class LA>
std::ostream& operator<<(
  std::ostream& os, const Aff_transformationHd<RT,LA>& t) 
{ os << t.matrix(); return os; }

template <class RT, class LA>
std::istream& operator>>(
  std::istream& is, Aff_transformationHd<RT,LA>& t)
{ typename LA::Matrix M(t.dimension());
  is >> M; t = Aff_transformationHd<RT,LA>(M); 
  return is;
}

/*{\Mimplementation 
Affine Transformations are implemented by matrices of integers as an
item type.  All operations like creation, initialization, input and
output on a transformation $t$ take time $O(|t.dimension()|^2)$. |dimension()|
takes constant time.  The operations for inversion and composition
have the cubic costs of the used matrix operations. The space
requirement is $O(|t.dimension()|^2)$. }*/

// ----------------------------- end of file ----------------------------


CGAL_END_NAMESPACE
#endif // CGAL_AFF_TRANSFORMATIONHD_H

