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
  \class SoWWWInline SoWWWInline.h Inventor/nodes/SoWWWInline.h
  \brief The SoWWWInline class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoWWWInline.h>
#include <Inventor/nodes/SoSubNodeP.h>

#include <coindefs.h> // COIN_STUB()
#include <Inventor/SbColor.h>


#include <Inventor/actions/SoGetBoundingBoxAction.h>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <GL/gl.h>

/*!
  \enum SoWWWInline::BboxVisibility
  FIXME: write documentation for enum
*/
/*!
  \var SoWWWInline::BboxVisibility SoWWWInline::NEVER
  FIXME: write documentation for enum definition
*/
/*!
  \var SoWWWInline::BboxVisibility SoWWWInline::UNTIL_LOADED
  FIXME: write documentation for enum definition
*/
/*!
  \var SoWWWInline::BboxVisibility SoWWWInline::ALWAYS
  FIXME: write documentation for enum definition
*/


/*!
  \var SoSFString SoWWWInline::name
  FIXME: write documentation for field
*/
/*!
  \var SoSFVec3f SoWWWInline::bboxCenter
  FIXME: write documentation for field
*/
/*!
  \var SoSFVec3f SoWWWInline::bboxSize
  FIXME: write documentation for field
*/
/*!
  \var SoSFNode SoWWWInline::alternateRep
  FIXME: write documentation for field
*/


// *************************************************************************

SO_NODE_SOURCE(SoWWWInline);

/*!
  Constructor.
*/
SoWWWInline::SoWWWInline()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoWWWInline);

  SO_NODE_ADD_FIELD(name, ("<Undefined file>"));
  SO_NODE_ADD_FIELD(bboxCenter, (0.0f, 0.0f, 0.0f));
  SO_NODE_ADD_FIELD(bboxSize, (0.0f, 0.0f, 0.0f));
  SO_NODE_ADD_FIELD(alternateRep, (NULL));
}

/*!
  Destructor.
*/
SoWWWInline::~SoWWWInline()
{
}

/*!
  Does initialization common for all objects of the
  SoWWWInline class. This includes setting up the
  type system, among other things.
*/
void
SoWWWInline::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoWWWInline);
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::setFullURLName(const SbString & /* url */)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
const SbString &
SoWWWInline::getFullURLName(void)
{
  COIN_STUB();
  static SbString s;
  return s;
}

/*!
  FIXME: write function documentation
*/
SoGroup *
SoWWWInline::copyChildren(void) const
{
  COIN_STUB();
  return NULL;
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::requestURLData(void)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
SbBool
SoWWWInline::isURLDataRequested(void) const
{
  COIN_STUB();
  return FALSE;
}

/*!
  FIXME: write function documentation
*/
SbBool
SoWWWInline::isURLDataHere(void) const
{
  COIN_STUB();
  return FALSE;
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::cancelURLDataRequest(void)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::setChildData(SoNode * /* urlData */)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
SoNode *
SoWWWInline::getChildData(void) const
{
  COIN_STUB();
  return NULL;
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::setFetchURLCallBack(SoWWWInlineFetchURLCB * /* f */,
                                 void * /* userData */)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::setBoundingBoxVisibility(BboxVisibility /* b */)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
SoWWWInline::BboxVisibility
SoWWWInline::getBoundingBoxVisibility(void)
{
  COIN_STUB();
  return NEVER;
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::setBoundingBoxColor(SbColor & /* c */)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
const SbColor &
SoWWWInline::getBoundingBoxColor(void)
{
  COIN_STUB();
  static SbColor col;
  return col;
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::setReadAsSoFile(SbBool /* onOff */)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
SbBool
SoWWWInline::getReadAsSoFile(void)
{
  COIN_STUB();
  return FALSE;
}


/*!
  FIXME: write function documentation
*/
void
SoWWWInline::GLRender(SoGLRenderAction * /* action */)
{
  // FIXME: quick hack implementation until someone does it 100%
  // correct. NB: loadsofstuff missing. 19990404 mortene.

  GLboolean lightenabled = glIsEnabled(GL_LIGHTING);
  glDisable(GL_LIGHTING);

  float cx, cy, cz;
  this->bboxCenter.getValue().getValue(cx, cy, cz);

  float x0, y0, z0;
  this->bboxSize.getValue().getValue(x0, y0, z0);
  x0 = -x0/2.0f + cx;
  y0 = -y0/2.0f + cy;
  z0 = -z0/2.0f + cz;
  float x1, y1, z1;
  this->bboxSize.getValue().getValue(x1, y1, z1);
  x1 = x1/2.0f + cx;
  y1 = y1/2.0f + cy;
  z1 = z1/2.0f + cz;

  glBegin(GL_LINE_LOOP);
  glVertex3f(x0, y0, z0);
  glVertex3f(x1, y0, z0);
  glVertex3f(x1, y1, z0);
  glVertex3f(x0, y1, z0);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(x0, y0, z1);
  glVertex3f(x1, y0, z1);
  glVertex3f(x1, y1, z1);
  glVertex3f(x0, y1, z1);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(x0, y0, z0);
  glVertex3f(x0, y0, z1);
  glVertex3f(x0, y1, z0);
  glVertex3f(x0, y1, z1);
  glVertex3f(x1, y0, z0);
  glVertex3f(x1, y0, z1);
  glVertex3f(x1, y1, z0);
  glVertex3f(x1, y1, z1);
  glEnd();

  if (lightenabled) glEnable(GL_LIGHTING);
}

/*!
  FIXME: write function documentation
*/
void
SoWWWInline::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SbVec3f halfsize = bboxSize.getValue()/2.0f;
  SbVec3f center = bboxCenter.getValue();

  action->extendBy(SbBox3f(-halfsize[0] + center[0],
                           -halfsize[1] + center[1],
                           -halfsize[2] + center[2],
                           halfsize[0] + center[0],
                           halfsize[1] + center[1],
                           halfsize[2] + center[2]));

  assert(! action->isCenterSet());
  action->setCenter(center, TRUE);
}

/*!
  FIXME: write doc
 */
SoChildList *
SoWWWInline::getChildren(void) const
{
  COIN_STUB();
  return NULL;
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::doAction(SoAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::doActionOnKidsOrBox(SoAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::callback(SoCallbackAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::getMatrix(SoGetMatrixAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::handleEvent(SoHandleEventAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::search(SoSearchAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::pick(SoPickAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::getPrimitiveCount(SoGetPrimitiveCountAction * /* action */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::addBoundingBoxChild(SbVec3f /* center */, SbVec3f /* size */)
{
  COIN_STUB();
}

/*!
  FIXME: write doc
 */
SbBool
SoWWWInline::readInstance(SoInput * in, unsigned short /* flags */)
{
  COIN_STUB();
  return FALSE;
}

/*!
  FIXME: write doc
 */
void
SoWWWInline::copyContents(const SoFieldContainer * /* fromFC */,
                          SbBool /* copyConnections */)
{
  COIN_STUB();
}
