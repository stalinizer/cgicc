/*
 *  $Id: HTMLAttributes.cpp,v 1.3 2001/09/02 19:53:17 sbooth Exp $
 *
 *  Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001 Stephen F. Booth
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef __GNUG__
#  pragma implementation
#endif

#include "cgicc/HTMLAttributes.h"
#include "cgicc/CgiUtils.h"

// ============================================================
// Class HTMLAttribute
// ============================================================
CGICCNS HTMLAttribute::HTMLAttribute()
{}

CGICCNS HTMLAttribute::HTMLAttribute(const STDNS string& name)
  : fName(name),
    fValue(name)
{}

CGICCNS HTMLAttribute::HTMLAttribute(const STDNS string& name, 
				     const STDNS string& value)
  : fName(name), 
    fValue(value)
{}

CGICCNS HTMLAttribute::HTMLAttribute(const HTMLAttribute& attribute)
  : MStreamable(),
    fName(attribute.fName), 
    fValue(attribute.fValue)
{}

CGICCNS HTMLAttribute::~HTMLAttribute()
{}

bool
CGICCNS HTMLAttribute::operator== (const HTMLAttribute& att) 	const
{
  return (stringsAreEqual(fName, att.fName) 
	  && stringsAreEqual(fValue, att.fValue));
}

CGICCNS HTMLAttribute& 
CGICCNS HTMLAttribute::operator= (const HTMLAttribute& att) 
{
  fName 	= att.fName;
  fValue 	= att.fValue;

  return *this;
}

void 
CGICCNS HTMLAttribute::render(STDNS ostream& out) 		const
{
  out << getName() << "=\"" << getValue() << "\"";
}

// ============================================================
// Class HTMLAttributeList
// ============================================================
CGICCNS HTMLAttributeList::HTMLAttributeList()
{
  fAttributes.reserve(5);
}

CGICCNS HTMLAttributeList::HTMLAttributeList(const HTMLAttribute& head) 
{
  fAttributes.reserve(5);
  fAttributes.push_back(head);
}

CGICCNS HTMLAttributeList::HTMLAttributeList(const HTMLAttributeList& list)
{
  this->operator=(list);
}

CGICCNS HTMLAttributeList::~HTMLAttributeList()
{}

CGICCNS HTMLAttributeList&
CGICCNS HTMLAttributeList::operator= (const HTMLAttributeList& list)
{
  fAttributes = list.fAttributes;
  return *this;
}

CGICCNS HTMLAttributeList&
CGICCNS HTMLAttributeList::set(const STDNS string& name)
{ 
  fAttributes.push_back(HTMLAttribute(name));
  return *this;
}

CGICCNS HTMLAttributeList&
CGICCNS HTMLAttributeList::set(const STDNS string& name, 
			       const STDNS string& value)
{ 
  fAttributes.push_back(HTMLAttribute(name, value));
  return *this;
}

void 
CGICCNS HTMLAttributeList::render(STDNS ostream& out) 	const
{
  STDNS vector<HTMLAttribute>::const_iterator iter;
  for(iter = fAttributes.begin(); iter != fAttributes.end(); ++iter) {
    out << *iter << ' ';
  }
}
