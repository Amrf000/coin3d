/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

/*!
  \class SoLocateHighlight SoLocateHighlight.h Inventor/nodes/SoLocateHighlight.h
  \brief The SoLocateHighlight class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/SbName.h>
#include <Inventor/nodes/SoLocateHighlight.h>
#include <Inventor/nodes/SoSubNode.h>

/*!
  \enum SoLocateHighlight::Modes
  FIXME: write documentation for enum
*/
/*!
  \var SoLocateHighlight::Modes SoLocateHighlight::AUTO
  FIXME: write documentation for enum definition
*/
/*!
  \var SoLocateHighlight::Modes SoLocateHighlight::ON
  FIXME: write documentation for enum definition
*/
/*!
  \var SoLocateHighlight::Modes SoLocateHighlight::OFF
  FIXME: write documentation for enum definition
*/
/*!
  \enum SoLocateHighlight::Styles
  FIXME: write documentation for enum
*/
/*!
  \var SoLocateHighlight::Styles SoLocateHighlight::EMISSIVE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoLocateHighlight::Styles SoLocateHighlight::EMISSIVE_DIFFUSE
  FIXME: write documentation for enum definition
*/


/*!
  \var SoSFColor SoLocateHighlight::color
  FIXME: write documentation for field
*/
/*!
  \var SoSFEnum SoLocateHighlight::style
  FIXME: write documentation for field
*/
/*!
  \var SoSFEnum SoLocateHighlight::mode
  FIXME: write documentation for field
*/


// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoLocateHighlight)
SoType SoLocateHighlight::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoLocateHighlight node class.
*/
void *
SoLocateHighlight::createInstance(void)
{
  return new SoLocateHighlight;
}

/*!
  Returns the unique type identifier for the SoLocateHighlight class.
*/
SoType
SoLocateHighlight::getClassTypeId(void)
{
  return SoLocateHighlight::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoLocateHighlight::getTypeId(void) const
{
  return SoLocateHighlight::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoLocateHighlight::SoLocateHighlight()
{
//$ BEGIN TEMPLATE NodeConstructor(SoLocateHighlight)
  // Make sure the class has been initialized.
  assert(SoLocateHighlight::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor

  SO_NODE_ADD_FIELD(color, (SbColor(0.3f, 0.3f, 0.3f)));
  SO_NODE_ADD_FIELD(style, (EMISSIVE));
  SO_NODE_ADD_FIELD(mode, (AUTO));

  SO_NODE_DEFINE_ENUM_VALUE(Styles, EMISSIVE);
  SO_NODE_DEFINE_ENUM_VALUE(Styles, EMISSIVE_DIFFUSE);
  SO_NODE_SET_SF_ENUM_TYPE(style, Styles);

  SO_NODE_DEFINE_ENUM_VALUE(Modes, AUTO);
  SO_NODE_DEFINE_ENUM_VALUE(Modes, ON);
  SO_NODE_DEFINE_ENUM_VALUE(Modes, OFF);
  SO_NODE_SET_SF_ENUM_TYPE(mode, Modes);
}

/*!
  Destructor.
*/
SoLocateHighlight::~SoLocateHighlight()
{
}

/*!
  Does initialization common for all objects of the
  SoLocateHighlight class. This includes setting up the
  type system, among other things.
*/
void
SoLocateHighlight::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(LocateHighlight)
  // Make sure we only initialize once.
  assert(SoLocateHighlight::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoLocateHighlight::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "LocateHighlight",
                       &SoLocateHighlight::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoLocateHighlight::cleanClass(void)
{
}

/*!
  FIXME: write function documentation
*/
void
SoLocateHighlight::turnOffCurrentHighlight(SoGLRenderAction * action)
{
  // FIXME: stub. 19990224 mortene.
}


#if !defined(COIN_EXCLUDE_SOHANDLEEVENTACTION)
/*!
  FIXME: write doc
 */
void
SoLocateHighlight::handleEvent(SoHandleEventAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOHANDLEEVENTACTION

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
/*!
  FIXME: write doc
 */
void
SoLocateHighlight::GLRenderBelowPath(SoGLRenderAction * action)
{
  assert(0 && "FIXME: not implemented");
}

/*!
  FIXME: write doc
 */
void
SoLocateHighlight::GLRenderInPath(SoGLRenderAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write doc
 */
void
SoLocateHighlight::redrawHighlighted(SoAction * act, SbBool  flag)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOACTION
