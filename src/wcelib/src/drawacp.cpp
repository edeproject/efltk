// drawacp.cpp
//

#include <windows.h>
#include <math.h>               // abs, sin, cos, atan2

static LPPOINT GetArcPoints(
   int nLeftRect,   // [IN] x-coord of upper-left corner of rectangle
   int nTopRect,    // [IN] y-coord of upper-left corner of rectangle
   int nRightRect,  // [IN] x-coord of lower-right corner of rectangle
   int nBottomRect, // [IN] y-coord of lower-right corner of rectangle
   int nXStartArc,  // [IN] x-coord of first radial's endpoint
   int nYStartArc,  // [IN] y-coord of first radial's endpoint
   int nXEndArc,    // [IN] x-coord of second radial's endpoint
   int nYEndArc,    // [IN] y-coord of second radial's endpoint
   int &nPoints     // [IN] zero: Arc, Chord; nonzero: Pie. [OUT] number of points
)
{
   // drawing a pie?
   const bool bPie = nPoints != 0;

   // PI * 2
   const double PI2 = 3.14159265358979 * 2;

   // delta angle
   const double dDeltaAngle = 0.01;

   // rectangle center
   const int nCX = (nLeftRect + nRightRect) / 2,
             nCY = (nTopRect + nBottomRect) / 2;

   // ellipse radius 
   const int nRX = ::abs(nLeftRect - nRightRect) / 2,
             nRY = ::abs(nTopRect - nBottomRect) / 2;

   // begin and end angles
   const double dBeginAngle = ::atan2((nYEndArc - nCY) * nRX / nRY, nXEndArc - nCX);
   double dEndAngle = ::atan2((nYStartArc - nCY) * nRX / nRY, nXStartArc - nCX);

   // normalization 
   if (dBeginAngle >= dEndAngle)
   {
       dEndAngle += PI2;
   }

   ASSERT(dBeginAngle < dEndAngle);

   // number of points
   nPoints = static_cast<int>((dEndAngle - dBeginAngle) / dDeltaAngle) + 1;

   if (nPoints < 2)
       return NULL;

   // array of points
   const LPPOINT lppt = new POINT[nPoints + (bPie ? 1 : 0)];

   if (lppt == NULL)
       return NULL;

   double dCurAngle = dBeginAngle;
   for (int ni = 0; ni < nPoints; ni++)
   {
       lppt[ni].x = static_cast<int>(nRX * ::cos(dCurAngle)) + nCX;
       lppt[ni].y = static_cast<int>(nRY * ::sin(dCurAngle)) + nCY;

       dCurAngle += dDeltaAngle;
   }

   if (bPie)
   {
       // a pie's last point is the center.
       lppt[nPoints].x = nCX;
       lppt[nPoints].y = nCY;
       nPoints++;
   }

   return lppt;
}

static void ReleaseArcPoints(LPPOINT lppt)
{
   if (lppt != NULL)
   {
       delete []lppt;
   }
}

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
)
{
   int nPoints = 0;  // Arc
   const LPPOINT lppt = ::GetArcPoints(nLeftRect, nTopRect, nRightRect, nBottomRect,
                                       nXStartArc, nYStartArc,
                                       nXEndArc, nYEndArc,
                                       nPoints);

   if (lppt != NULL)
   {
       ASSERT(nPoints >= 2);

       // drawing 
       const BOOL bRet = ::Polyline(hdc, lppt, nPoints);

       ::ReleaseArcPoints(lppt);

       return bRet;
   }
   else
   {
       return FALSE;
   }
}

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
)
{
   int nPoints = 0;  // Chord
   const LPPOINT lppt = ::GetArcPoints(nLeftRect, nTopRect, nRightRect, nBottomRect,
                                       nXRadial1, nYRadial1,
                                       nXRadial2, nYRadial2,
                                       nPoints);

   if (lppt != NULL)
   {
       ASSERT(nPoints >= 2);

       // drawing 
       const BOOL bRet = ::Polygon(hdc, lppt, nPoints);

       ::ReleaseArcPoints(lppt);

       return bRet;
   }
   else
   {
       return FALSE;
   }
}

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
)
{
   int nPoints = 1;  // Pie
   const LPPOINT lppt = ::GetArcPoints(nLeftRect, nTopRect, nRightRect, nBottomRect,
                                       nXRadial1, nYRadial1,
                                       nXRadial2, nYRadial2,
                                       nPoints);

   if (lppt != NULL)
   {
       ASSERT(nPoints >= 2);

       // drawing 
       const BOOL bRet = ::Polygon(hdc, lppt, nPoints);

       ::ReleaseArcPoints(lppt);

       return bRet;
   }
   else
   {
       return FALSE;
   }
}
