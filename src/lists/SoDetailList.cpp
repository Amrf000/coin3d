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
  \class SoDetailList SoDetailList.h Inventor/lists/SoDetailList.h
  \brief The SoDetailList class is a container for pointers to SoDetail objects.
  \ingroup details

  \sa SbList
*/

// SoDetailList was moved from being a subclass of SbPList to being a
// subclass of SbList. This removed the need to do lots of ugly casts
// in overloaded methods, with the subsequent removal of all code in
// this file. 20000228 mortene.

/*!
  \fn SoDetailList::SoDetailList(void)

  Default constructor.
*/

/*!
  \fn SoDetailList::SoDetailList(const int sizehint)

  This constructor initializes the internal allocated size for the
  list to \a sizehint. Note that the list will still initially contain
  zero items.

  \sa SbList::SbList(const int sizehint)
*/

/*!
  \fn SoDetailList::SoDetailList(const SoDetailList & l)

  Copy constructor.

  \sa SbList::SbList(const SbList<Type> & l)
*/

/*!
  \fn void SoDetailList::set(const int index, SoDetail * item)

  This method sets the element at \a index to \a item. Does the same
  thing as SbList::operator[](). This method is only present for
  compatibility with the original Inventor API.
*/
