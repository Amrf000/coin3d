/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use Coin with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

/*!
  \class SoArray SoArray.h Inventor/nodes/SoArray.h
  \brief The SoArray class ...
  \ingroup nodes

  FIXME: write class doc
*/



#include <Inventor/nodes/SoArray.h>
#include <Inventor/nodes/SoSubNodeP.h>


#include <Inventor/misc/SoState.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <Inventor/elements/SoSwitchElement.h>
#include <Inventor/actions/SoCallbackAction.h>

/*!
  \enum SoArray::Origin
  FIXME: write documentation for enum
*/
/*!
  \var SoArray::Origin SoArray::FIRST
  FIXME: write documentation for enum definition
*/
/*!
  \var SoArray::Origin SoArray::CENTER
  FIXME: write documentation for enum definition
*/
/*!
  \var SoArray::Origin SoArray::LAST
  FIXME: write documentation for enum definition
*/


/*!
  \var SoSFEnum SoArray::origin
  FIXME: write documentation for field
*/
/*!
  \var SoSFShort SoArray::numElements1
  FIXME: write documentation for field
*/
/*!
  \var SoSFShort SoArray::numElements2
  FIXME: write documentation for field
*/
/*!
  \var SoSFShort SoArray::numElements3
  FIXME: write documentation for field
*/
/*!
  \var SoSFVec3f SoArray::separation1
  FIXME: write documentation for field
*/
/*!
  \var SoSFVec3f SoArray::separation2
  FIXME: write documentation for field
*/
/*!
  \var SoSFVec3f SoArray::separation3
  FIXME: write documentation for field
*/

// *************************************************************************

SO_NODE_SOURCE(SoArray);

/*!
  Constructor.
*/
SoArray::SoArray()
{
  SO_NODE_INTERNAL_CONSTRUCTOR(SoArray);

  SO_NODE_ADD_FIELD(origin, (SoArray::FIRST));
  SO_NODE_ADD_FIELD(numElements1, (1));
  SO_NODE_ADD_FIELD(numElements2, (1));
  SO_NODE_ADD_FIELD(numElements3, (1));
  SO_NODE_ADD_FIELD(separation1, (SbVec3f(1, 0, 0)));
  SO_NODE_ADD_FIELD(separation2, (SbVec3f(0, 1, 0)));
  SO_NODE_ADD_FIELD(separation3, (SbVec3f(0, 0, 1)));


  SO_NODE_DEFINE_ENUM_VALUE(Origin, FIRST);
  SO_NODE_DEFINE_ENUM_VALUE(Origin, CENTER);
  SO_NODE_DEFINE_ENUM_VALUE(Origin, LAST);
  SO_NODE_SET_SF_ENUM_TYPE(origin, Origin);
}

/*!
  Destructor.
*/
SoArray::~SoArray()
{
}

// doc in super
void
SoArray::initClass(void)
{
  SO_NODE_INTERNAL_INIT_CLASS(SoArray);
}

/*!
  FIXME: write function documentation
*/
void
SoArray::getBoundingBox(SoGetBoundingBoxAction * action)
{
#if 0 // mortene's old (buggy ?) code (removed 19990423, pederb)
  // store incoming modelmatrix
  SbMatrix mat = SoModelMatrixElement::get(action->getState());

  // get reference to the box
  SbXfBox3f & box = action->getXfBoundingBox();

  // store current bbox
  SbXfBox3f incomingbox = box;

  // accumulation variables
  SbVec3f acccenter(0.0f, 0.0f, 0.0f);
  int numCenters = 0;
  SbXfBox3f totalbox;

  for (int i=0; i < numElements3.getValue(); i++) {
    for (int j=0; j < numElements2.getValue(); j++) {
      for (int k=0; k < numElements1.getValue(); k++) {

        float multfactor_i = float(i);
        float multfactor_j = float(j);
        float multfactor_k = float(k);

        switch (origin.getValue()) {
        case SoArray::FIRST:
          break;
        case SoArray::CENTER:
          multfactor_i = -float(numElements3.getValue()-1.0f)/2.0f + float(i);
          multfactor_j = -float(numElements2.getValue()-1.0f)/2.0f + float(j);
          multfactor_k = -float(numElements1.getValue()-1.0f)/2.0f + float(k);
          break;
        case SoArray::LAST:
          multfactor_i = -multfactor_i;
          multfactor_j = -multfactor_j;
          multfactor_k = -multfactor_k;
          break;

        default: assert(0); break;
        }

        SbVec3f instance_pos =
          separation3.getValue() * multfactor_i +
          separation2.getValue() * multfactor_j +
          separation1.getValue() * multfactor_k;

#if 0 // debug
        SoDebugError::postInfo("SoArray::getBoundingBox",
                               "instance_pos: <%f, %f, %f>",
                               instance_pos[0],
                               instance_pos[1],
                               instance_pos[2]);
#endif // debug

        SbMatrix mat;
        mat.setTranslate(instance_pos);

        action->getState()->push();

        SoSwitchElement::set(action->getState(),
                             i * numElements2.getValue() *
                             numElements1.getValue() +
                             j * numElements1.getValue() + k);

        // make current box empty to calculate bbox of this separator
        box.makeEmpty();
        box.setTransform(SbMatrix::identity());

        // set local matrix to identity
        SoBBoxModelMatrixElement::set(action->getState(), this, mat);

        // traverse all children, calculate the local bbox
        inherited::getBoundingBox(action);

        // If center point is set, accumulate center.
        if (action->isCenterSet()) {
          acccenter += action->getCenter();
          numCenters++;
          action->resetCenter();
        }

        // expand box by stored bbox
        if (!totalbox.isEmpty()) box.extendBy(totalbox);
        totalbox = box;

        action->getState()->pop();
      }
    }
  }

  // transform the local bbox by stored model matrix
  if (!box.isEmpty()) box.transform(mat);
  if (!incomingbox.isEmpty()) box.extendBy(incomingbox);

  if (numCenters != 0)
    action->setCenter(acccenter / numCenters, FALSE);

#else // "new" code, 19990423, pederb

  float curri = 0.0f;
  float currj = 0.0f;
  float currk = 0.0f;

  float inci = 1.0f;
  float incj = 1.0f;
  float inck = 1.0f;

  // accumulation variables
  SbVec3f acccenter(0.0f, 0.0f, 0.0f);
  int numCenters = 0;

  switch (origin.getValue()) {
  case SoArray::FIRST:
    break;
  case SoArray::CENTER:
    curri = -(numElements3.getValue()-1.0f)/2.0f;
    currj = -(numElements2.getValue()-1.0f)/2.0f;
    currk = -(numElements1.getValue()-1.0f)/2.0f;
    break;
  case SoArray::LAST:
    inci = -1.0f;
    incj = -1.0f;
    inck = -1.0f;
    break;
  default: assert(0); break;
  }

  float initj = currj;
  float initk = currk;

  int N = 0;
  for (int i=0; i < numElements3.getValue(); i++) {
    currj = initj;
    for (int j=0; j < numElements2.getValue(); j++) {
      currk = initk;
      for (int k=0; k < numElements1.getValue(); k++) {

        SbVec3f instance_pos =
          separation3.getValue() * curri +
          separation2.getValue() * currj +
          separation1.getValue() * currk;

        action->getState()->push();

        // translate bbox matrix
        SoBBoxModelMatrixElement::translateBy(action->getState(),
                                              this, instance_pos);
        SoSwitchElement::set(action->getState(),++N);

        inherited::getBoundingBox(action);

        // If center point is set, accumulate center.
        if (action->isCenterSet()) {
          acccenter += action->getCenter();
          numCenters++;
          action->resetCenter();
        }
        // pop back to the original bboxmatrix
        action->getState()->pop();
        currk += inck;
      }
      currj += incj;
    }
    curri += inci;
  }

  if (numCenters != 0)
    action->setCenter(acccenter / float(numCenters), FALSE);
#endif // end of new code by pederb
}

/*!
  FIXME: write function documentation
*/
void
SoArray::GLRender(SoGLRenderAction * action)
{
  SoArray::doAction(action);
}

/*!
  FIXME: write doc
*/
SbBool
SoArray::affectsState(void) const
{
  return FALSE; // state is pushed/popped for each traversal
}

/*!
  FIXME: write doc
*/
void
SoArray::doAction(SoAction *action)
{
  int N = 0;
  for (int i=0; i < numElements3.getValue(); i++) {
    for (int j=0; j < numElements2.getValue(); j++) {
      for (int k=0; k < numElements1.getValue(); k++) {

        float multfactor_i = float(i);
        float multfactor_j = float(j);
        float multfactor_k = float(k);

        switch (origin.getValue()) {
        case SoArray::FIRST:
          break;
        case SoArray::CENTER:
          multfactor_i = -float(numElements3.getValue()-1.0f)/2.0f + float(i);
          multfactor_j = -float(numElements2.getValue()-1.0f)/2.0f + float(j);
          multfactor_k = -float(numElements1.getValue()-1.0f)/2.0f + float(k);
          break;
        case SoArray::LAST:
          multfactor_i = -multfactor_i;
          multfactor_j = -multfactor_j;
          multfactor_k = -multfactor_k;
          break;

        default: assert(0); break;
        }

        SbVec3f instance_pos =
          separation3.getValue() * multfactor_i +
          separation2.getValue() * multfactor_j +
          separation1.getValue() * multfactor_k;

        action->getState()->push();

        SoSwitchElement::set(action->getState(),
                             ++N);

        SoModelMatrixElement::translateBy(action->getState(), this,
                                          instance_pos);

        inherited::doAction(action);
        action->getState()->pop();
      }
    }
  }
}

/*!
  FIXME: write doc
*/
void
SoArray::callback(SoCallbackAction *action)
{
  SoArray::doAction((SoAction*)action);
}

/*!
  We came across what we think is a bug in TGS/SGI OIV when
  implementing picking for this node. The SoPickedPoint class can
  return the object space point, normal and texture
  coordinates. TGS/SGI OIV do not consider the translation inside this
  node before returning the object space data from SoPickedPoint,
  since the path in SoPickedPoint does not say anything about on which
  copy the pick occured. We solved this simply by storing both world
  space and object space data in SoPickedPoint.
*/
void
SoArray::pick(SoPickAction *action)
{
  SoArray::doAction((SoAction*)action);
}

/*!
  FIXME: write doc
*/
void
SoArray::handleEvent(SoHandleEventAction *action)
{
  SoNode::handleEvent(action);
  inherited::handleEvent(action);
}

/*!
  FIXME: write doc
*/
void
SoArray::getMatrix(SoGetMatrixAction *action)
{
  // path does not specify which copy to traverse
  inherited::getMatrix(action);
}

/*!
  FIXME: write doc
*/
void
SoArray::search(SoSearchAction * action)
{
  SoNode::search(action);
  inherited::search(action);
}

/*!
  FIXME: write doc
*/
void
SoArray::getPrimitiveCount(SoGetPrimitiveCountAction *action)
{
  SoArray::doAction((SoAction*)action);
}
