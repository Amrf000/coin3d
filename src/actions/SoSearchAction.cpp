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
  \class SoSearchAction SoSearchAction.h Inventor/actions/SoSearchAction.h
  \brief The SoSearchAction class provides methods for searching through scene graphs.
  \ingroup actions

  Nodes can be searched for by pointer, type, and name, or a
  combination of those criteria.  Types can be interpreted as exact
  types, or the type can match nodes derived from it.  Every single
  node can be searched, or normal traversal rules can be followed when
  searching (this is especially important to note with regard to
  switch nodes).

  When using more than one of the setNode(), setType() and setName()
  calls, note that the action will search for node(s) with an \c "AND"
  combination of the given search criteria.

  Be aware that if you do search operations on an SoSearchAction
  created on the stack, you can get some unfortunate side effects if
  you're not careful. Since SoSearchAction keeps a list of the path(s)
  found in the latest search, the nodes in these paths will be
  unref'ed when the SoSearchAction stack instance is destructed at the
  end of your function. If the root of your scene-graph then has
  ref-count zero (it is often useful to do a unrefNoDelete() before
  returning a node from a function to leave the referencing to the
  caller), the root node will be destructed! It might be better to
  create a heap instance of the search action in those cases, since
  you'll then be able to destruct the search action before calling
  unrefNoDelete(). Another solution would be to call reset() before
  calling unrefNoDelete() on your object, since reset() truncates
  the path list.
*/

#include <Inventor/actions/SoSearchAction.h>

#include <Inventor/actions/SoSubActionP.h>
#include <Inventor/nodes/SoNode.h>

// *************************************************************************

/*!
  \enum SoSearchAction::LookFor

  Specify the search criterion. This can be a bitwise combination of
  the available values.
*/

/*!
  \enum SoSearchAction::Interest

  Values used when specifiying what node(s) we are interested in: the
  first one found, the last one or all of them.
*/

/*!
  \var SbBool SoSearchAction::duringSearchAll

  Obsoleted global flag, only present for compatibility reasons
  with old SGI / TGS Inventor application code.

  It's set to \c TRUE when an SoSearchAction traversal with
  SoSearchAction::isSearchingAll() equal to \c TRUE is started, and is
  reset to \c FALSE again after traversal has finished.

  (The flag is used by SGI / TGS Inventor in SoSwitch::affectsState()
  to know when SoSwitch::whichChild should behave as
  SoSwitch::SO_SWITCH_ALL. We have a better solution for this problem
  in Coin.)
*/

SO_ACTION_SOURCE(SoSearchAction);

SbBool SoSearchAction::duringSearchAll = FALSE;


// Overridden from parent class.
void
SoSearchAction::initClass(void)
{
  SO_ACTION_INIT_CLASS(SoSearchAction, SoAction);
}


/*!
  Initializes internal settings with default values. With the default
  settings, the SoSearchAction will ignore all nodes.
*/
SoSearchAction::SoSearchAction(void)
  : lookfor(0), interest(FIRST), searchall(FALSE),
    node(NULL), type(SoType::badType()), name(""),
    path(NULL) // paths(0)
{
  SO_ACTION_CONSTRUCTOR(SoSearchAction);
}

/*!
  Destructor.
*/
SoSearchAction::~SoSearchAction()
{
  this->reset(); // clears everything
}

// *************************************************************************

/*!
  Sets the \a node pointer to search for.

  The action is also automatically configured to set the search
  "interest" to LookFor \c NODE, so there is no need to call
  SoSearchAction::setFind() in anything but special cases. This is
  also the case for the setType() and setName() calls.
*/
void
SoSearchAction::setNode(SoNode * const node)
{
  this->node = node;
  this->lookfor |= NODE;
}

/*!
  Returns the node the SoSearchAction instance is configured
  to search for.
*/
SoNode *
SoSearchAction::getNode(void) const
{
  return this->node;
}

/*!
  Configures the SoSearchAction instance to search for nodes of the
  given \a type, and nodes of classes derived from the given \a type
  if \a chkderived is \c TRUE.
*/
void
SoSearchAction::setType(const SoType type, const SbBool chkderived)
{
  this->type = type;
  this->chkderived = chkderived;
  this->lookfor |= TYPE;
}

/*!
  Returns the node type which is searched for, and whether derived
  classes of that type also returns a match.
*/
SoType
SoSearchAction::getType(SbBool & chkderived) const
{
  chkderived = this->chkderived;
  return this->type;
}

/*!
  Configures the SoSearchAction instance to search for nodes with the
  given \a name.
*/
void
SoSearchAction::setName(const SbName name)
{
  this->name = name;
  this->lookfor |= NAME;
}

/*!
  Returns the name the SoSearchAction instance is configured to search
  for.
*/
SbName
SoSearchAction::getName(void) const
{
  return this->name;
}

/*!
  Configures what to search for in the scene graph.  \a what is a
  bitmask of LookFor flags.

  Default find configuration is to ignore all nodes, but the setFind()
  configuration is updated automatically when any one of
  SoSearchAction::setNode(), SoSearchAction::setType() or
  SoSearchAction::setName() is called.
*/
void
SoSearchAction::setFind(const int what)
{
  this->lookfor = what;
}

/*!
  Returns the search configuration of the action instance.
*/
int
SoSearchAction::getFind(void) const
{
  return this->lookfor;
}

/*!
  Configures whether only the first, the last, or all the searching
  matches are of interest.  Default configuration is \c FIRST.
*/
void
SoSearchAction::setInterest(const Interest interest)
{
  this->interest = interest;
}

/*!
  Returns whether only the first, the last, or all the searching
  matches will be saved.
*/
SoSearchAction::Interest
SoSearchAction::getInterest(void) const
{
  return this->interest;
}

/*!
  Specifies whether normal graph traversal should be done (\a
  searchall is \c FALSE) (which is the default setting), or if every
  single node should be searched (\a searchall is \c TRUE).

  If the \a searchall flag is \c TRUE, even nodes considered "hidden"
  by other actions are searched (like for instance the disabled
  children of SoSwitch nodes).
*/
void
SoSearchAction::setSearchingAll(const SbBool searchall)
{
  this->searchall = searchall;
}

/*!
  Returns the traversal method configuration of the action.
*/
SbBool
SoSearchAction::isSearchingAll(void) const
{
  return this->searchall;
}

/*!
  Returns the path to the node of interest that matched the search
  criterions. If no match was found, \c NULL is returned.

  Note that if \c ALL matches are of interest, the result of a search
  action must be fetched through SoSearchAction::getPaths().


  There is one frequently asked question about the paths that are
  returned from either this method or the getPaths() method below:
  "why am I not getting the complete path as expected?"

  Well, then you probably have to cast the path to a SoFullPath, since
  certain nodes (nodekits, many VRML97 nodes) have hidden
  children. SoPath::getTail() will return the first node that has
  hidden children, or the tail if none of the nodes have hidden
  children. SoFullPath::getTail() will always return the actual
  tail. Just do like this:
 
  \code
    SoFullPath * path = (SoFullPath *) searchaction->getPath();
    SoVRMLCoordinate * vrmlcord = (SoVRMLCoordinate *) path->getTail();
  \endcode
*/
SoPath *
SoSearchAction::getPath(void) const
{
  return this->path;
}

/*!
  Returns a pathlist of all nodes that matched the search criterions.

  Note that if interest were only \c FIRST or \c LAST,
  SoSearchAction::getPath() should be used instead of this method.

  \sa getPath()
*/
SoPathList &
SoSearchAction::getPaths(void)
{
  return this->paths;
}

/*!
  Resets all the SoSearchAction internals back to their default
  values.
*/
void
SoSearchAction::reset(void)
{
  this->lookfor = 0;
  this->interest = SoSearchAction::FIRST;
  this->searchall = FALSE;
  this->chkderived = TRUE;
  this->node = NULL;
  this->type = SoType::badType();
  this->name = SbName("");
  if (this->path) this->path->unref();
  this->path = NULL;
  this->paths.truncate(0);
}

/*!
  \COININTERNAL

  Marks the SoSearchAction instance as terminated.
*/
void
SoSearchAction::setFound(void)
{
  this->setTerminated(TRUE);
}

/*!
  \COININTERNAL

  Returns whether the search action was terminated.

  Note that this value does not reflect whether the node(s) that
  was searched for was found or not.
*/
SbBool
SoSearchAction::isFound(void) const
{
  return this->hasTerminated();
}

/*!
  \COININTERNAL

  Sets the path, or adds the path to the path list, depending on the
  interest configuration.  The path is not copied, so it can not be
  modified after being added without side effects.
*/
void
SoSearchAction::addPath(SoPath * const path)
{
  assert(! this->isFound()); // shouldn't try to add path if found

  switch (this->interest) {
  case FIRST:
    assert(! this->path); // should be NULL
    this->path = path;
    this->path->ref();
    this->setFound();
    break;

  case LAST:
    if (this->path)
      this->path->unref(); // should delete it if possible
    this->path = path;
    this->path->ref();
    break;

  case ALL:
    this->paths.append(path);
    break;

  default:
    assert(FALSE && "Interest setting is invalid");
    break;
  }
}

// *************************************************************************

// Documented in superclass. Overridden from superclass to initialize
// internal data.
void
SoSearchAction::beginTraversal(SoNode * node)
{
  this->paths.truncate(0);
  if (this->path) this->path->unref();
  this->path = NULL;

  // For compatibility with older application code which is using this
  // flag.
  SoSearchAction::duringSearchAll = this->isSearchingAll();

  this->traverse(node); // begin traversal at root node

  SoSearchAction::duringSearchAll = FALSE;
}
