/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion. All rights reserved.
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
  \class SoExtSelection SoExtSelection.h Inventor/nodes/SoExtSelection.h
  \brief The SoExtSelection class ...
  \ingroup nodes

  FIXME: write class doc
*/


#include <Inventor/nodes/SoExtSelection.h>
#include <Inventor/nodes/SoSubNodeP.h>
#include <coindefs.h> // COIN_STUB()


/*!
  \enum SoExtSelection::LassoType
  FIXME: write documentation for enum
*/
/*!
  \var SoExtSelection::LassoType SoExtSelection::NOLASSO
  FIXME: write documentation for enum definition
*/
/*!
  \var SoExtSelection::LassoType SoExtSelection::LASSO
  FIXME: write documentation for enum definition
*/
/*!
  \var SoExtSelection::LassoType SoExtSelection::RECTANGLE
  FIXME: write documentation for enum definition
*/

/*!
  \enum SoExtSelection::LassoPolicy
  FIXME: write documentation for enum
*/
/*!
  \var SoExtSelection::LassoPolicy SoExtSelection::FULL_BBOX
  FIXME: write documentation for enum definition
*/
/*!
  \var SoExtSelection::LassoPolicy SoExtSelection::PART_BBOX
  FIXME: write documentation for enum definition
*/
/*!
  \var SoExtSelection::LassoPolicy SoExtSelection::FULL
  FIXME: write documentation for enum definition
*/
/*!
  \var SoExtSelection::LassoPolicy SoExtSelection::PART
  FIXME: write documentation for enum definition
*/


/*!
  \var SoSFEnum SoExtSelection::lassoType
  FIXME: write documentation for field
*/
/*!
  \var SoSFEnum SoExtSelection::lassoPolicy
  FIXME: write documentation for field
*/

// *************************************************************************

SO_NODE_SOURCE(SoExtSelection);

/*!
  Constructor.
*/
SoExtSelection::SoExtSelection()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoExtSelection);

  SO_NODE_ADD_FIELD(lassoType, (SoExtSelection::NOLASSO));
  SO_NODE_ADD_FIELD(lassoPolicy, (SoExtSelection::FULL_BBOX));

  SO_NODE_DEFINE_ENUM_VALUE(LassoType, NOLASSO);
  SO_NODE_DEFINE_ENUM_VALUE(LassoType, LASSO);
  SO_NODE_DEFINE_ENUM_VALUE(LassoType, RECTANGLE);
  SO_NODE_SET_SF_ENUM_TYPE(lassoType, LassoType);

  SO_NODE_DEFINE_ENUM_VALUE(LassoPolicy, FULL_BBOX);
  SO_NODE_DEFINE_ENUM_VALUE(LassoPolicy, PART_BBOX);
  SO_NODE_DEFINE_ENUM_VALUE(LassoPolicy, FULL);
  SO_NODE_DEFINE_ENUM_VALUE(LassoPolicy, PART);
  SO_NODE_SET_SF_ENUM_TYPE(lassoPolicy, LassoPolicy);
}

/*!
  Destructor.
*/
SoExtSelection::~SoExtSelection()
{
}

/*!
  Does initialization common for all objects of the
  SoExtSelection class. This includes setting up the
  type system, among other things.
*/
void
SoExtSelection::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoExtSelection);
}


/*!
  FIXME: write doc
 */
void
SoExtSelection::useOverlay(SbBool /* flg */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
SbBool
SoExtSelection::isUsingOverlay(void)
{
  COIN_STUB();
  return FALSE;
}

/*!
  FIXME: write doc
 */
SoSeparator *
SoExtSelection::getOverlaySceneGraph(void)
{
  COIN_STUB();
  return NULL;
}

/*!
  FIXME: write doc
 */
void
SoExtSelection::setOverlayLassoColorIndex(int /* index */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
int
SoExtSelection::getOverlayLassoColorIndex(void)
{
  COIN_STUB();
  return 0;
}

/*!
  FIXME: write doc
 */
void
SoExtSelection::setLassoColor(SbColor /* c */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
SbColor
SoExtSelection::getLassoColor(void)
{
  COIN_STUB();
  static SbColor col;
  return col;
}

/*!
  FIXME: write doc
 */
void
SoExtSelection::setLassoWidth(float /* width */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
float
SoExtSelection::getLassoWidth(void)
{
  COIN_STUB();
  return 0.0f;
}

/*!
  FIXME: write doc
 */
void
SoExtSelection::setOverlayLassoPattern(unsigned short /* pattern */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
unsigned short
SoExtSelection::getOverlayLassoPattern(void)
{
  COIN_STUB();
  return 0;
}

/*!
  FIXME: write doc
 */
void
SoExtSelection::animateOverlayLasso(SbBool /* flg */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
SbBool
SoExtSelection::isOverlayLassoAnimated(void)
{
  COIN_STUB();
  return FALSE;
}
