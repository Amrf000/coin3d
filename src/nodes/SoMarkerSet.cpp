/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2000 by Systems in Motion. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation. See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition license.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/

/*!
  \class SoMarkerSet SoMarkerSet.h Inventor/nodes/SoMarkerSet.h
  \brief The SoMarkerSet class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoMarkerSet.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <coindefs.h> // COIN_STUB()



/*!
  \enum SoMarkerSet::MarkerType
  FIXME: write documentation for enum
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CROSS_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PLUS_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::MINUS_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SLASH_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::BACKSLASH_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::BAR_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::STAR_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::Y_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::LIGHTNING_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::WELL_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CIRCLE_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SQUARE_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::DIAMOND_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::TRIANGLE_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::RHOMBUS_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::HOURGLASS_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SATELLITE_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PINE_TREE_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CAUTION_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SHIP_LINE_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CIRCLE_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SQUARE_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::DIAMOND_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::TRIANGLE_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::RHOMBUS_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::HOURGLASS_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SATELLITE_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PINE_TREE_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CAUTION_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SHIP_FILLED_5_5
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CROSS_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PLUS_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::MINUS_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SLASH_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::BACKSLASH_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::BAR_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::STAR_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::Y_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::LIGHTNING_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::WELL_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CIRCLE_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SQUARE_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::DIAMOND_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::TRIANGLE_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::RHOMBUS_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::HOURGLASS_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SATELLITE_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PINE_TREE_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CAUTION_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SHIP_LINE_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CIRCLE_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SQUARE_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::DIAMOND_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::TRIANGLE_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::RHOMBUS_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::HOURGLASS_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SATELLITE_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PINE_TREE_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CAUTION_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SHIP_FILLED_7_7
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CROSS_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PLUS_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::MINUS_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SLASH_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::BACKSLASH_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::BAR_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::STAR_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::Y_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::LIGHTNING_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::WELL_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CIRCLE_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SQUARE_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::DIAMOND_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::TRIANGLE_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::RHOMBUS_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::HOURGLASS_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SATELLITE_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PINE_TREE_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CAUTION_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SHIP_LINE_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CIRCLE_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SQUARE_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::DIAMOND_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::TRIANGLE_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::RHOMBUS_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::HOURGLASS_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SATELLITE_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::PINE_TREE_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::CAUTION_FILLED_9_9
  FIXME: write documentation for enum definition
*/
/*!
  \var SoMarkerSet::MarkerType SoMarkerSet::SHIP_FILLED_9_9
  FIXME: write documentation for enum definition
*/


/*!
  \var SoMFInt32 SoMarkerSet::markerIndex
  FIXME: write documentation for field
*/


// *************************************************************************

SO_NODE_SOURCE(SoMarkerSet);

/*!
  Constructor.
*/
SoMarkerSet::SoMarkerSet()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoMarkerSet);

  SO_NODE_ADD_FIELD(markerIndex, (0));
}

/*!
  Destructor.
*/
SoMarkerSet::~SoMarkerSet()
{
}

/*!
  Does initialization common for all objects of the
  SoMarkerSet class. This includes setting up the
  type system, among other things.
*/
void
SoMarkerSet::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoMarkerSet);
}


/*!
  FIXME: write doc
 */
void
SoMarkerSet::GLRender(SoGLRenderAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoMarkerSet::getPrimitiveCount(SoGetPrimitiveCountAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
int
SoMarkerSet::getNumDefinedMarkers(void)
{
  COIN_STUB();
  return 0;
}

/*!
  FIXME: write doc
 */
void
SoMarkerSet::addMarker(int /* markerIndex */, const SbVec2s & /* size */,
                       const unsigned char * /* bytes */, SbBool /* isLSBFirst */,
                       SbBool /* isUpToDown */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
SbBool
SoMarkerSet::getMarker(int /* markerIndex */, SbVec2s & /* size */,
                       const unsigned char *& /* bytes */, SbBool & /* isLSBFirst */)
{
  COIN_STUB();
  return FALSE;
}

/*!
  FIXME: write doc
 */
SbBool
SoMarkerSet::removeMarker(int /* markerIndex */)
{
  COIN_STUB();
  return FALSE;
}

/*!
  FIXME: write doc
 */
SbBool
SoMarkerSet::isMarkerBitSet(int /* markerIndex */, int /* bitNumber */)
{
  COIN_STUB();
  return FALSE;
}

// Need some perl-magic from Larsa

//$ INSERT MARKER CROSS_5_5
// "x...x"
// ".x.x."
// "..x.."
// ".x.x."
// "x...x"

//$ INSERT MARKER PLUS_5_5
// "..x.."
// "..x.."
// "xxxxx"
// "..x.."
// "..x.."

//$ INSERT MARKER MINUS_5_5
// "..x.."
// "....."
// "xxxxx"
// "....."
// "..x.."
