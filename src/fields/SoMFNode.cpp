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

// Important note: this sourcefile was in full generated by the
// Coin/scripts/templant script from the code in MFNodeEnginePath.tpl.

//$ BEGIN TEMPLATE MFNodeEnginePath(NODE, Node, node)

/*!
  \class SoMFNode SoMFNode.h Inventor/fields/SoMFNode.h
  \brief The SoMFNode class is a container for nodes.
  \ingroup fields

  This field container stores an array of pointers to nodes. It takes
  care of the necessary functionality for handling copy, import and
  export operations.

  Note that node pointers stored in field instances of this type may
  be \c NULL pointers.

  \sa SoNode, SoSFNode

*/

// Type-specific define to be able to do #ifdef tests on type.  (Note:
// used to check the header file wrapper define, but that doesn't work
// with --enable-compact build.)
#define COIN_INTERNAL_NODE

#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSubFieldP.h>
#include <Inventor/fields/SoSFNode.h>

#include <Inventor/SoPath.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/nodes/SoNode.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG


SO_MFIELD_REQUIRED_SOURCE(SoMFNode);
SO_MFIELD_CONSTRUCTOR_SOURCE(SoMFNode);
SO_MFIELD_MALLOC_SOURCE(SoMFNode, SoNode *);



// Override from parent class.
void
SoMFNode::initClass(void)
{
  SO_MFIELD_INTERNAL_INIT_CLASS(SoMFNode);
}


// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

//// From the SO_MFIELD_VALUE_SOURCE macro, start. ///////////////////////////

// We can't use the macro invocation, as we need to take care of doing
// ref() and unref() on the nodes in the array.

int
SoMFNode::fieldSizeof(void) const
{
  return sizeof(SoNode *);
}

void *
SoMFNode::valuesPtr(void)
{
  return (void *)this->values;
}

void
SoMFNode::setValuesPtr(void * ptr)
{
  // We don't get any ref()'ing done here, or any notification
  // mechanisms set up -- so this function should _only_ be used for
  // initial setup of array memory.  In Coin, it's only used from
  // SoMField::allocValues().
  this->values = (SoNode **)ptr;
}

int
SoMFNode::find(SoNode * value, SbBool addifnotfound)
{
  for (int i=0; i < this->num; i++) if ((*this)[i] == value) return i;

  if (addifnotfound) this->set1Value(this->num, value);
  return -1;
}

void
SoMFNode::setValues(const int start, const int num, const SoNode ** newvals)
{
  // Disable temporarily, so we under any circumstances will not send
  // more than one notification about the changes.
  SbBool notificstate = this->enableNotify(FALSE);

  // ref() new nodes before unref()-ing old ones, in case there are
  // common nodes (we don't want any premature destruction to happen).
  { for (int i=0; i < num; i++) if (newvals[i]) newvals[i]->ref(); }

  // We favor simplicity of code over performance here.
  { for (int i=0; i < num; i++)
    this->set1Value(start+i, (SoNode *)newvals[i]); }

  // unref() to match the initial ref().
  { for (int i=0; i < num; i++) if (newvals[i]) newvals[i]->unref(); }

  // Finally, send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

void
SoMFNode::set1Value(const int idx, SoNode * newval)
{
  // Disable temporarily, so we under no circumstances will send more
  // than one notification about the change.
  SbBool notificstate = this->enableNotify(FALSE);

  // Expand array if necessary.
  if (idx >= this->getNum()) {
#ifdef COIN_INTERNAL_PATH
    for (int i = this->getNum(); i <= idx; i++) this->pathheads.append(NULL);
#endif // COIN_INTERNAL_PATH
    this->setNum(idx + 1);
  }

  // Don't use getValues() or operator[[] to find oldptr, since this
  // might trigger a recursive evaluation call if the field is connected.
  SoNode * oldptr = this->values[idx];
  if (oldptr == newval) return;

  if (oldptr) {
    oldptr->removeAuditor(this, SoNotRec::FIELD);
    oldptr->unref();
#ifdef COIN_INTERNAL_PATH
    SoNode * h = oldptr->getHead();
    // The path should be audited by us at all times. So don't use
    // SoMFPath to wrap SoTempPath or SoLightPath, for instance.
    assert(h==this->pathheads[idx] &&
           "Path head changed without notification!");
    if (h) {
      h->removeAuditor(this, SoNotRec::FIELD);
      h->unref();
    }
#endif // COIN_INTERNAL_PATH
  }

  if (newval) {
    newval->addAuditor(this, SoNotRec::FIELD);
    newval->ref();
#ifdef COIN_INTERNAL_PATH
    SoNode * h = newval->getHead();
    if (h) {
      h->addAuditor(this, SoNotRec::FIELD);
      h->ref();
    }
#endif // COIN_INTERNAL_PATH
  }

  this->values[idx] = newval;
#ifdef COIN_INTERNAL_PATH
  this->pathheads[idx] = newval ? newval->getHead() : NULL;
#endif // COIN_INTERNAL_PATH

  // Finally, send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

void
SoMFNode::setValue(SoNode * value)
{
  this->deleteAllValues();
  this->set1Value(0, value);
}

SbBool
SoMFNode::operator==(const SoMFNode & field) const
{
  if (this == &field) return TRUE;
  if (this->getNum() != field.getNum()) return FALSE;

  const SoNode ** const lhs = this->getValues(0);
  const SoNode ** const rhs = field.getValues(0);
  for (int i = 0; i < num; i++) if (lhs[i] != rhs[i]) return FALSE;
  return TRUE;
}

void
SoMFNode::deleteAllValues(void)
{
  if (this->getNum()) this->deleteValues(0);
}

// Overloaded to handle unref() and removeAuditor().
void
SoMFNode::deleteValues(int start, int num)
{
  if (num == -1) num = this->getNum() - 1 - start;
  for (int i=start; i < start+num; i++) {
    SoNode * n = this->values[i];
    if (n) {
      n->removeAuditor(this, SoNotRec::FIELD);
      n->unref();
    }
#ifdef COIN_INTERNAL_PATH
    SoNode * h = this->pathheads[start];
    this->pathheads.remove(start);
    if (h) {
      h->removeAuditor(this, SoNotRec::FIELD);
      h->unref();
    }
#endif // COIN_INTERNAL_PATH
  }

  inherited::deleteValues(start, num);
}

// Overloaded to insert NULL pointers in new array slots.
void
SoMFNode::insertSpace(int start, int num)
{
  // Disable temporarily so we don't send notification prematurely
  // from inherited::insertSpace().
  SbBool notificstate = this->enableNotify(FALSE);

  inherited::insertSpace(start, num);
  for (int i=start; i < start+num; i++) {
#ifdef COIN_INTERNAL_PATH
    this->pathheads.insert(NULL, start);
#endif // COIN_INTERNAL_PATH
    this->values[i] = NULL;
  }

  // Initialization done, now send notification.
  (void)this->enableNotify(notificstate);
  if (notificstate) this->valueChanged();
}

// This is the "memmove replacement" to use copy constructors where
// they are defined.
void
SoMFNode::copyValue(int to, int from)
{
  this->values[from] = this->values[to];
}

//// From the SO_MFIELD_VALUE_SOURCE macro, end. /////////////////////////////


// Import a single node.
SbBool
SoMFNode::read1Value(SoInput * in, int index)
{
  SoSFNode sfnode;
  SbBool result = sfnode.readValue(in);
  if (result) this->set1Value(index, sfnode.getValue());
  return result;
}

// Export a single node.
void
SoMFNode::write1Value(SoOutput * out, int idx) const
{
  SoSFNode sfnode;
  sfnode.setValue((*this)[idx]);
  sfnode.writeValue(out);
}

#endif // DOXYGEN_SKIP_THIS


// Overridden from parent to propagate write reference counting to
// node.
void
SoMFNode::countWriteRefs(SoOutput * out) const
{
  inherited::countWriteRefs(out);

  for (int i=0; i < this->getNum(); i++) {
    SoNode * n = (*this)[i];
    // Set the "from field" flag as FALSE, as that flag is meant to be
    // used for references through field-to-field connections.
    if (n) n->addWriteReference(out, FALSE);
#ifdef COIN_INTERNAL_PATH
    if (this->pathheads[i]) this->pathheads[i]->addWriteReference(out, FALSE);
#endif // COIN_INTERNAL_PATH
  }
}

// Override from parent to update our node pointer references. This is
// necessary so 1) we're added as an auditor to the copied nodes (they
// have so far only been copied as pointer bits), and 2) so we
// increase the reference count.
void
SoMFNode::fixCopy(SbBool copyconnections)
{
  for (int i=0; i < this->getNum(); i++) {
    SoNode * n = (*this)[i];
    if (n) {
      // There's only been a bitwise copy of the pointer; no auditing
      // has been set up, no increase in the reference count. So we do
      // that by setting the value to NULL and then re-setting with
      // setValue().
      this->values[i] = NULL;
#if defined(COIN_INTERNAL_NODE) || defined(COIN_INTERNAL_ENGINE)
      SoFieldContainer * fc = SoFieldContainer::findCopy(n, copyconnections);
      this->set1Value(i, (SoNode *)fc);
#endif // COIN_INTERNAL_NODE || COIN_INTERNAL_ENGINE

#ifdef COIN_INTERNAL_PATH
      this->set1Value(i, n->copy());
#endif // COIN_INTERNAL_PATH
    }
  }
}

// Override from SoField to check node pointer.
SbBool
SoMFNode::referencesCopy(void) const
{
  if (inherited::referencesCopy()) return TRUE;

  for (int i=0; i < this->getNum(); i++) {
    SoNode * item = (*this)[i];
    if (item) {
#if defined(COIN_INTERNAL_NODE) || defined(COIN_INTERNAL_ENGINE)
      if (SoFieldContainer::checkCopy((SoFieldContainer *)item)) return TRUE;
#endif // COIN_INTERNAL_NODE || COIN_INTERNAL_ENGINE
#ifdef COIN_INTERNAL_PATH
      if (item->getHead() && SoFieldContainer::checkCopy(item->getHead())) return TRUE;
#endif // COIN_INTERNAL_PATH
    }
  }

  return FALSE;
}

// Kill the type-specific define.
#undef COIN_INTERNAL_NODE
//$ END TEMPLATE MFNodeEnginePath
