// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
// 
// release       :
// release_date  :
// 
// file          : include/CGAL/Arithmetic_filter/predicates/in_smallest_orthogonalcircle_ftC2.h
// package       : Interval_arithmetic
// author(s)     : Sylvain Pion <Sylvain.Pion@sophia.inria.fr>
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec@sophia.inria.fr>)
// ======================================================================

// This file is automatically generated by the script
// examples/Interval_arithmetic/filtered_predicate_converter.

#ifndef CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H
#define CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H

#include <CGAL/determinant.h>
#include <CGAL/enum.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
/* CGAL_MEDIUM_INLINE */
Oriented_side
in_smallest_orthogonalcircleC2(
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pw,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qw,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tx,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ty,
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tw)
{
  CGAL::FPU_CW_t backup = CGAL::FPU_get_and_set_cw(CGAL::FPU_cw_up);
  try
  {
    Oriented_side result = in_smallest_orthogonalcircleC2(
		px.interval(),
		py.interval(),
		pw.interval(),
		qx.interval(),
		qy.interval(),
		qw.interval(),
		tx.interval(),
		ty.interval(),
		tw.interval());
    CGAL::FPU_set_cw(backup);
    return result;
  } 
  catch (CGAL::Interval_nt_advanced::unsafe_comparison)
  {
    CGAL::FPU_set_cw(backup);
    return in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
  }
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_IN_SMALLEST_ORTHOGONALCIRCLEC2_H
