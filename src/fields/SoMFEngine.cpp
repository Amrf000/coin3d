/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/*!
  \class SoMFEngine SoMFEngine.h Inventor/fields/SoMFEngine.h
  \brief The SoMFEngine class ...
  \ingroup fields

  FIXME: write class doc
*/

#include <Inventor/fields/SoMFEngine.h>
#include <Inventor/fields/SoSubFieldP.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG
#include <coindefs.h> // COIN_STUB()



SO_MFIELD_SOURCE_MALLOC(SoMFEngine, SoEngine *, SoEngine *);


// Doc from superclass
void
SoMFEngine::initClass(void)
{
  SO_MFIELD_INTERNAL_INIT_CLASS(SoMFEngine);
}


#ifndef DOXYGEN_SKIP_THIS

/* FIXME: write function documentation */
SbBool
SoMFEngine::read1Value(SoInput * /* in */, int /* idx */)
{
  COIN_STUB();
  return FALSE;
}

/* FIXME: write function documentation */
void
SoMFEngine::write1Value(SoOutput * /* out */, int /* idx */) const
{
  COIN_STUB();
}

#endif // DOXYGEN_SKIP_THIS


/*!
  FIXME: write function documentation
*/
void
SoMFEngine::fixCopy(SbBool /* copyConnections */)
{
  COIN_STUB();
}

/*!
  FIXME: write function documentation
*/
SbBool
SoMFEngine::referencesCopy(void) const
{
  COIN_STUB();
  return FALSE;
}

// Overridden from parent to propagate write reference counting to
// value members.
void
SoMFEngine::countWriteRefs(SoOutput * out) const
{
  inherited::countWriteRefs(out);
  COIN_STUB();
}
