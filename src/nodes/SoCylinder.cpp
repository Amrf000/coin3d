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
  \class SoCylinder SoCylinder.h Inventor/nodes/SoCylinder.h
  \brief The SoCylinder class ...
  \ingroup nodes

  FIXME: write class doc
*/

#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/SbName.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/misc/SoGL.h>
#endif // !COIN_EXCLUDE_SOGLRENDERACTION

#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION

#if !defined(COIN_EXCLUDE_SOGLSHAPEHINTSELEMENT)
#include <Inventor/elements/SoGLShapeHintsElement.h>
#endif // !COIN_EXCLUDE_SOGLSHAPEHINTSELEMENY

#if !defined(COIN_EXCLUDE_SOGLSHADEMODELELEMENT)
#include <Inventor/elements/SoGLShadeModelElement.h>
#endif // ! COIN_EXCLUDE_SOGLSHADEMODELELEMENT

#if !defined(COIN_EXCLUDE_SOMATERIALBINDINGELEMENT)
#include <Inventor/elements/SoMaterialBindingElement.h>
#endif

#if !defined(COIN_EXCLUDE_SOCOMPLEXITYTYPEELEMENT)
#include <Inventor/elements/SoComplexityTypeElement.h>
#endif

#if !defined(COIN_EXCLUDE_SOCOMPLEXITYELEMENT)
#include <Inventor/elements/SoComplexityElement.h>
#endif

/*!
  \enum SoCylinder::Part
  FIXME: write documentation for enum
*/
/*!
  \var SoCylinder::Part SoCylinder::SIDES
  FIXME: write documentation for enum definition
*/
/*!
  \var SoCylinder::Part SoCylinder::TOP
  FIXME: write documentation for enum definition
*/
/*!
  \var SoCylinder::Part SoCylinder::BOTTOM
  FIXME: write documentation for enum definition
*/
/*!
  \var SoCylinder::Part SoCylinder::ALL
  FIXME: write documentation for enum definition
*/


/*!
  \var SoSFFloat SoCylinder::radius
  FIXME: write documentation for field
*/
/*!
  \var SoSFFloat SoCylinder::height
  FIXME: write documentation for field
*/
/*!
  \var SoSFBitMask SoCylinder::parts
  FIXME: write documentation for field
*/


// *************************************************************************

//$ BEGIN TEMPLATE NodeSource(SoCylinder)
SoType SoCylinder::classTypeId = SoType::badType();

/*!
  Returns a new instance of the SoCylinder node class.
*/
void *
SoCylinder::createInstance(void)
{
  return new SoCylinder;
}

/*!
  Returns the unique type identifier for the SoCylinder class.
*/
SoType
SoCylinder::getClassTypeId(void)
{
  return SoCylinder::classTypeId;
}

/*!
  Returns type identifier for an object.
*/
SoType
SoCylinder::getTypeId(void) const
{
  return SoCylinder::classTypeId;
}
//$ END TEMPLATE NodeSource

/*!
  Constructor.
*/
SoCylinder::SoCylinder()
{
//$ BEGIN TEMPLATE NodeConstructor(SoCylinder)
  // Make sure the class has been initialized.
  assert(SoCylinder::classTypeId != SoType::badType());
//$ END TEMPLATE NodeConstructor

  SO_NODE_ADD_FIELD(radius, (1.0f));
  SO_NODE_ADD_FIELD(height, (2.0f));
  SO_NODE_ADD_FIELD(parts, (SoCylinder::ALL));

  SO_NODE_DEFINE_ENUM_VALUE(Part, SIDES);
  SO_NODE_DEFINE_ENUM_VALUE(Part, TOP);
  SO_NODE_DEFINE_ENUM_VALUE(Part, BOTTOM);
  SO_NODE_DEFINE_ENUM_VALUE(Part, ALL);
  SO_NODE_SET_SF_ENUM_TYPE(parts, Part);
}

/*!
  Destructor.
*/
SoCylinder::~SoCylinder()
{
}

/*!
  Does initialization common for all objects of the
  SoCylinder class. This includes setting up the
  type system, among other things.
*/
void
SoCylinder::initClass(void)
{
//$ BEGIN TEMPLATE InitNodeSource(Cylinder)
  // Make sure we only initialize once.
  assert(SoCylinder::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  SoCylinder::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "Cylinder",
                       &SoCylinder::createInstance,
                       SoNode::nextActionMethodIndex++);
//$ END TEMPLATE InitNodeSource
}

/*!
  Clean out all statically allocated resources.
  This method is only useful for debugging purposes.
*/
void
SoCylinder::cleanClass(void)
{
}

#if !defined(COIN_EXCLUDE_SOGETBOUNDINGBOXACTION)
/*!
  FIXME: write function documentation
*/
void
SoCylinder::computeBBox(SoAction * action, SbBox3f & box, SbVec3f & center)
{

  float r = this->radius.getValue();
  float h = this->height.getValue();

  // Either the SIDES are present, or we've at least got both the TOP
  // and BOTTOM caps -- so just find the middle point and enclose
  // everything.
  if (this->parts.getValue() & SoCylinder::SIDES ||
      (this->parts.getValue() & SoCylinder::BOTTOM &&
       this->parts.getValue() & SoCylinder::TOP)) {
    center.setValue(0.0f, 0.0f, 0.0f);
    box.setBounds(SbVec3f(-r, -h/2.0f, -r), SbVec3f(r, h/2.0f, r));
  }
  // ..not a "full" cylinder, but we've got the BOTTOM cap.
  else if(this->parts.getValue() & SoCylinder::BOTTOM) {
    center.setValue(0.0f, -h/2.0f, 0.0f);
    box.setBounds(SbVec3f(-r, -h/2.0f, -r), SbVec3f(r, -h/2.0f, r));
  }
  // ..not a "full" cylinder, but we've got the TOP cap.
  else if(this->parts.getValue() & SoCylinder::TOP) {
    center.setValue(0.0f, h/2.0f, 0.0f);
    box.setBounds(SbVec3f(-r, h/2.0f, -r), SbVec3f(r, h/2.0f, r));
  }
  // ..no parts present. My confidence is shot -- I feel very small.
  else {
    center.setValue(0.0f, 0.0f, 0.0f);
    box.setBounds(SbVec3f(0.0f, 0.0f, 0.0f), SbVec3f(0.0f, 0.0f, 0.0f));
  }
}
#endif // !COIN_EXCLUDE_SOGETBOUNDINGBOXACTION

#if !defined(COIN_EXCLUDE_SOGLRENDERACTION)
/*!
  FIXME: write function documentation
*/
void
SoCylinder::GLRender(SoGLRenderAction * action)
{
  if (!shouldGLRender(action)) return;

  SoState *state = action->getState();

  SoCylinder::Part p = (SoCylinder::Part) this->parts.getValue();
  SoMaterialBundle mb(action);
  mb.sendFirst();

  // FIXME: test if we really need normals and texcoords
  unsigned int flags = SOGL_NEED_NORMALS | SOGL_NEED_TEXCOORDS;
  if (p & SIDES) flags |= SOGL_RENDER_SIDE;
  if (p & TOP) flags |= SOGL_RENDER_TOP;
  if (p & BOTTOM) flags |= SOGL_RENDER_BOTTOM;

#if !defined(COIN_EXCLUDE_SOMATERIALBINDINGELEMENT)
  SoMaterialBindingElement::Binding bind =
    SoMaterialBindingElement::get(state);
  if (bind == SoMaterialBindingElement::PER_PART ||
      bind == SoMaterialBindingElement::PER_PART_INDEXED)
    flags |= SOGL_MATERIAL_PER_PART;
#endif

#if !defined(COIN_EXCLUDE_SOGLSHAPEHINTSELEMENT)
  const SoGLShapeHintsElement * sh = (SoGLShapeHintsElement *)
    state->getConstElement(SoGLShapeHintsElement::getClassStackIndex());
  if (p == ALL) sh->forceSend(TRUE, TRUE);
  else sh->forceSend(TRUE, FALSE, TRUE);
#endif


  float complexity = 1.0f;

#if !defined(COIN_EXCLUDE_SOCOMPLEXITYELEMENT)
#if !defined(COIN_EXCLUDE_SOCOMPLEXITYTYPEELEMENT)

  // FIXME: check for OBJECT_SPACE or SCREEN_SPACE
  if (SoComplexityTypeElement::get(state) !=
      SoComplexityTypeElement::BOUNDING_BOX) {
    complexity = SoComplexityElement::get(state);
  }

#endif
#endif

#if !defined(COIN_EXCLUDE_SOGLSHADEMODELELEMENT)
  const SoGLShadeModelElement * sm = (SoGLShadeModelElement *)
    state->getConstElement(SoGLShadeModelElement::getClassStackIndex());
  if (!(p & SIDES)) 
    sm->forceSend(TRUE); // flatshading
  else
    sm->forceSend(FALSE); // smooth
  
#endif // ! COIN_EXCLUDE_SOGLSHADEMODELELEMENT
  
  sogl_render_cylinder(this->radius.getValue(),
		       this->height.getValue(),
		       (int)(40.0f * complexity),
		       &mb,
		       flags);
}

/*!
  FIXME: write function documentation
*/
SbBool 
SoCylinder::willSetShadeModel(void) const
{
  return TRUE;
}

/*!
  FIXME: write function documentation
*/
SbBool 
SoCylinder::willSetShapeHints(void) const
{
  return TRUE;
}

#endif // !COIN_EXCLUDE_SOGLRENDERACTION


/*!
  Add a part to the cylinder.

  \sa removePart(), hasPart()
*/
void
SoCylinder::addPart(SoCylinder::Part part)
{
  if (this->hasPart(part)) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoCylinder::addPart", "part already set");
#endif // COIN_DEBUG
    return;
  }

  this->parts.setValue(this->parts.getValue() | part);
}

/*!
  Remove a part from the cylinder.

  \sa addPart(), hasPart()
*/
void
SoCylinder::removePart(SoCylinder::Part part)
{
  if (!this->hasPart(part)) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoCylinder::removePart", "part was not set");
#endif // COIN_DEBUG
    return;
  }

  this->parts.setValue(this->parts.getValue() & ~part);
}

/*!
  Returns \a TRUE if rendering of the given part is currently turned on.

  \sa addPart(), removePart()
*/
SbBool
SoCylinder::hasPart(SoCylinder::Part part) const
{
  return (this->parts.getValue() & part) ? TRUE : FALSE;
}

#if !defined(COIN_EXCLUDE_SORAYPICKACTION)
/*!
  FIXME: write doc
*/
void
SoCylinder::rayPick(SoRayPickAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SORAYPICKACTION

#if !defined(COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION)
/*!
  FIXME: write doc
*/
void
SoCylinder::getPrimitiveCount(SoGetPrimitiveCountAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOGETPRIMITIVECOUNTACTION

#if !defined(COIN_EXCLUDE_SOACTION)
/*!
  FIXME: write doc
*/
void
SoCylinder::generatePrimitives(SoAction * action)
{
  assert(0 && "FIXME: not implemented");
}
#endif // !COIN_EXCLUDE_SOACTION
