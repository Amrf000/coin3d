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
  \class SoGetBoundingBoxAction SoGetBoundingBoxAction.h Inventor/actions/SoGetBoundingBoxAction.h
  \brief The SoGetBoundingBoxAction class calculates bounding boxes for nodes and subgraphs.
  \ingroup actions

  The use of bounding boxes is ubiquitous within the Coin library. It
  is needed for the correct execution of and for performance
  enhancements during rendering, picking, caching, culling, etc.

  Apply this action to a path or scene graph root to calculate the
  bounding box and the center point of the geometry contained within
  the scene.


  SoSeparator nodes are aggressively caching the results of bounding
  box calculations, so that they are really only re-calculated
  whenever the scenegraph rooted below any SoSeparator node has been
  modified. This means that applying this action to scenegraphs, or
  parts of scenegraphs, should be very quick on successive runs for
  "static" parts of the scene.

  \sa SoSeparator::boundingBoxCaching
*/

#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoSubActionP.h>

#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <Inventor/elements/SoLocalBBoxMatrixElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/lists/SoEnabledElementsList.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/nodes/SoNode.h>

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

// *************************************************************************

/*!
  \enum SoGetBoundingBoxAction::ResetType
  \internal
*/


SO_ACTION_SOURCE(SoGetBoundingBoxAction);


// Overridden from parent class.
void
SoGetBoundingBoxAction::initClass(void)
{
  SO_ACTION_INIT_CLASS(SoGetBoundingBoxAction, SoAction);

  SO_ENABLE(SoGetBoundingBoxAction, SoViewportRegionElement);
}

/*!
  Constructor.

  Some node types need to know the viewport region to calculate their
  bounding box.
*/
SoGetBoundingBoxAction::SoGetBoundingBoxAction(const SbViewportRegion & vp)
  : center(0, 0, 0),
    vpregion(vp),
    resetpath(NULL),
    flags(SoGetBoundingBoxAction::RESET_BEFORE)
{
  SO_ACTION_CONSTRUCTOR(SoGetBoundingBoxAction);
}

/*!
  Destructor.
*/
SoGetBoundingBoxAction::~SoGetBoundingBoxAction()
{
}

// *************************************************************************

/*!
  Set a new viewport region with this method, if it has changed from
  the oned passed in with the constructor.
*/
void
SoGetBoundingBoxAction::setViewportRegion(const SbViewportRegion & newregion)
{
  this->vpregion = newregion;
}

/*!
  Returns the viewport region used by the action instance.
*/
const SbViewportRegion &
SoGetBoundingBoxAction::getViewportRegion(void) const
{
  return this->vpregion;
}

/*!
  Returns the projected bounding box after (or during) traversal.
*/
SbBox3f
SoGetBoundingBoxAction::getBoundingBox(void) const
{
  return this->bbox.project();
}

/*!
  Returns the bounding box and transformation matrix to global
  coordinates. Use after (or during) traversal.
*/
SbXfBox3f &
SoGetBoundingBoxAction::getXfBoundingBox(void)
{
  return this->bbox;
}

/*!
  Returns center point of scene after the action has been applied.

  This might differ from the geometric center of the bounding box, as
  shape nodes may "weight" the center point according to various
  criteria (i.e. a faceset could for instance weight the center point
  according to the area within its bounding box where there are more
  polygons).
*/
const SbVec3f &
SoGetBoundingBoxAction::getCenter(void) const
{
  if (!this->isCenterSet()) {
    // Cast away constness and set.
    SoGetBoundingBoxAction * action = (SoGetBoundingBoxAction *)this;
    action->center.setValue(0.0f, 0.0f, 0.0f);
  }
  // Center point should not be affected by the current
  // transformation.
  return this->center;
}

/*!
  Sets whether the returned bounding box should be calculated in the
  coordinate system of the camera space or not.
*/
void
SoGetBoundingBoxAction::setInCameraSpace(const SbBool on)
{
  if (on) this->flags |= SoGetBoundingBoxAction::CAMERA_SPACE;
  else this->flags &= ~SoGetBoundingBoxAction::CAMERA_SPACE;
}

/*!
  Returns whether the bounding box returned is to be in camera space.
*/
SbBool
SoGetBoundingBoxAction::isInCameraSpace(void) const
{
  return (this->flags & SoGetBoundingBoxAction::CAMERA_SPACE) != 0;
}

/*!
  Forces the computed bounding box to be reset and the transformation
  to be identity before or after the tail node of \a path, depending
  on the \a resetbefore argument.  \c NULL can be specified for the \a
  path argument to disable this behavior.

  \sa getResetPath(), isResetPath(), isResetBefore(), getWhatReset()
*/

void
SoGetBoundingBoxAction::setResetPath(const SoPath * path,
                                     const SbBool resetbefore,
                                     const ResetType what)
{
  this->resetpath = path;
  this->resettype = what;
  if (resetbefore) this->flags |= SoGetBoundingBoxAction::RESET_BEFORE;
  else this->flags &= ~SoGetBoundingBoxAction::RESET_BEFORE;
}

/*!
  Returns the reset path (or \c NULL).

  \sa setResetPath(), isResetPath(), isResetBefore(), getWhatReset()
*/
const SoPath *
SoGetBoundingBoxAction::getResetPath(void) const
{
  return this->resetpath;
}

/*!
  Returns whether a reset path is set or not.

  \sa setResetPath(), getResetPath(), isResetBefore(), getWhatReset()
*/
SbBool
SoGetBoundingBoxAction::isResetPath(void) const
{
  return this->resetpath != NULL;
}

/*!
  Returns whether the bounding box and transformation is reset before
  or after the tail node of the reset path.

  \sa setResetPath(), getResetPath(), isResetPath(), getWhatReset()
*/
SbBool
SoGetBoundingBoxAction::isResetBefore(void) const
{
  return (this->flags & SoGetBoundingBoxAction::RESET_BEFORE) != 0;
}

/*!
  Returns what type of reset has been specified for the reset path.

  \sa setResetPath(), getResetPath(), isResetPath(), isResetBefore()
*/
SoGetBoundingBoxAction::ResetType
SoGetBoundingBoxAction::getWhatReset(void) const
{
  return this->resettype;
}

/*!
  \internal
  Called before node traversal of each node (from SoNode action method).
*/
void
SoGetBoundingBoxAction::checkResetBefore(void)
{
  if (this->resetpath && this->isResetBefore()) {
    const SoFullPath * curpath = (const SoFullPath *) this->getCurPath();
    const SoFullPath * resetpath = (const SoFullPath *) this->resetpath;
    if ((curpath->getTail() == resetpath->getTail()) &&
        curpath->containsPath(resetpath)) {
      if (this->resettype & SoGetBoundingBoxAction::TRANSFORM) {
        SoBBoxModelMatrixElement::reset(this->getState(), curpath->getTail());
      }
      if (this->resettype & SoGetBoundingBoxAction::BBOX) {
        this->bbox.makeEmpty();
        this->bbox.setTransform(SbMatrix::identity());
        this->resetCenter();
      }
    }
  }
}

/*!
  \internal
  Called after node traversal of each node (from SoNode action method).
*/
void
SoGetBoundingBoxAction::checkResetAfter(void)
{
  if (this->resetpath && !this->isResetBefore()) {
    const SoFullPath * curpath = (const SoFullPath *) this->getCurPath();
    const SoFullPath * resetpath = (const SoFullPath *) this->resetpath;
    if ((curpath->getTail() == resetpath->getTail()) &&
        curpath->containsPath(resetpath)) {
      if (this->resettype & SoGetBoundingBoxAction::TRANSFORM) {
        SoBBoxModelMatrixElement::reset(this->getState(), curpath->getTail());
      }
      if (this->resettype & SoGetBoundingBoxAction::BBOX) {
        this->bbox.makeEmpty();
        this->bbox.setTransform(SbMatrix::identity());
        this->resetCenter();
      }
    }
  }
}

/*!
  Extend bounding box by the given \a box. Called from nodes during
  traversal.

  Should usually not be of interest to application programmers, unless
  you're extending Coin with your own shapenode extension classes.
*/
void
SoGetBoundingBoxAction::extendBy(const SbBox3f & box)
{
  if (box.isEmpty()) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoGetBoundingBoxAction::extendBy", "empty box");
#endif // COIN_DEBUG
    return;
  }

  SbXfBox3f xfbox = box;
  SbMatrix transform = SoLocalBBoxMatrixElement::get(this->getState());
  if (this->isInCameraSpace()) {
    transform.multRight(SoViewingMatrixElement::get(this->getState()));
  }

  xfbox.transform(transform);
  this->bbox.extendBy(xfbox);
}

/*! \overload */
void
SoGetBoundingBoxAction::extendBy(const SbXfBox3f & box)
{
  if (box.isEmpty()) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoGetBoundingBoxAction::extendBy", "empty box");
#endif // COIN_DEBUG
    return;
  }

  SbXfBox3f lbox = box;
  SbMatrix transform = SoLocalBBoxMatrixElement::get(this->state);
  if (this->isInCameraSpace()) {
    transform.multRight(SoViewingMatrixElement::get(this->state));
  }
  lbox.transform(transform);
  this->bbox.extendBy(lbox);
}

/*!
  \internal
  Set a new center point during traversal.
*/
void
SoGetBoundingBoxAction::setCenter(const SbVec3f & center,
                                  const SbBool transformcenter)
{
  assert(!this->isCenterSet());
  this->flags |= SoGetBoundingBoxAction::CENTER_SET;

  if (transformcenter) {
    SbMatrix lmat = SoLocalBBoxMatrixElement::get(this->state);
    if (this->isInCameraSpace()) {
      lmat.multRight(SoViewingMatrixElement::get(this->state));
    }
    lmat.multVecMatrix(center, this->center);
  }
  else {
    this->center = center;
  }

#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoGetBoundingBoxAction::setCenter",
                         "center: <%f, %f, %f>, transformcenter: %s, "
                         "this->center: <%f, %f, %f>",
                         center[0], center[1], center[2],
                         transformcenter ? "TRUE" : "FALSE",
                         this->center[0], this->center[1], this->center[2]);
#endif // debug
}

/*!
  \internal
  Query about the center point during traversal.
*/
SbBool
SoGetBoundingBoxAction::isCenterSet(void) const
{
  return (this->flags & SoGetBoundingBoxAction::CENTER_SET) != 0;
}

/*!
  \internal
  Reset the scene center point during traversal.
*/
void
SoGetBoundingBoxAction::resetCenter(void)
{
  this->flags &= ~SoGetBoundingBoxAction::CENTER_SET;
  this->center.setValue(0.0f, 0.0f, 0.0f);
}

// Documented in superclass. Overridden to reset center point and
// bounding box before traversal starts.
void
SoGetBoundingBoxAction::beginTraversal(SoNode * node)
{
  this->resetCenter();
  this->bbox.makeEmpty();

  SoViewportRegionElement::set(this->getState(), this->vpregion);
  inherited::beginTraversal(node);
}
