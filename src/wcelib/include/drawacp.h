// drawacp.h
//

#if !defined(DRAWACP_H__13CEEEFE_DB6E_4918_B4DB_D78A97363E17__INCLUDED_)
#define DRAWACP_H__13CEEEFE_DB6E_4918_B4DB_D78A97363E17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

BOOL CeArc(
   HDC hdc,         // handle to device context
   int nLeftRect,   // x-coord of upper-left corner of rectangle
   int nTopRect,    // y-coord of upper-left corner of rectangle
   int nRightRect,  // x-coord of lower-right corner of rectangle
   int nBottomRect, // y-coord of lower-right corner of rectangle
   int nXStartArc,  // x-coord of first radial's endpoint
   int nYStartArc,  // y-coord of first radial's endpoint
   int nXEndArc,    // x-coord of second radial's endpoint
   int nYEndArc     // y-coord of second radial's endpoint
);

BOOL CeChord(
   HDC hdc,         // handle to device context
   int nLeftRect,   // x-coord of upper-left corner of rectangle
   int nTopRect,    // y-coord of upper-left corner of rectangle
   int nRightRect,  // x-coord of lower-right corner of rectangle
   int nBottomRect, // y-coord of lower-right corner of rectangle
   int nXRadial1,   // x-coord of first radial's endpoint
   int nYRadial1,   // y-coord of first radial's endpoint
   int nXRadial2,   // x-coord of second radial's endpoint
   int nYRadial2    // y-coord of second radial's endpoint
);

BOOL CePie(
   HDC hdc,         // handle to device context
   int nLeftRect,   // x-coord of upper-left corner of rectangle
   int nTopRect,    // y-coord of upper-left corner of rectangle
   int nRightRect,  // x-coord of lower-right corner of rectangle
   int nBottomRect, // y-coord of lower-right corner of rectangle
   int nXRadial1,   // x-coord of first radial's endpoint
   int nYRadial1,   // y-coord of first radial's endpoint
   int nXRadial2,   // x-coord of second radial's endpoint
   int nYRadial2    // y-coord of second radial's endpoint
);

#endif // !defined(DRAWACP_H__13CEEEFE_DB6E_4918_B4DB_D78A97363E17__INCLUDED_)
