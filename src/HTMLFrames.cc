/* $Id: HTMLFrames.cc,v 1.1 1998/02/12 05:31:41 sbooth Exp $ */

#include "HTMLFrames.hh"

// ============================================================
// Statics
// ============================================================
bool frameset::sState = false;
bool noframes::sState = false;
bool iframe::sState = false;

// ============================================================
// Class frameset
// ============================================================
frameset::frameset(const char *text) 
	: HTMLBooleanElement(text, NULL, NULL)
{}

frameset::frameset(const HTMLAttributeList& attributes)
	: HTMLBooleanElement(NULL, &attributes, NULL)
{}

frameset::frameset(const HTMLSimpleElement& embed)
	: HTMLBooleanElement(NULL, NULL, &embed)
{}

frameset::frameset(const char *text, const HTMLAttributeList& attributes) 
	: HTMLBooleanElement(text, &attributes, NULL)
{}

frameset::frameset(const HTMLAttributeList& attributes, const HTMLSimpleElement& embed)
	: HTMLBooleanElement(NULL, &attributes, &embed)
{}

frameset::~frameset()
{}

// ============================================================
// Class frame
// ============================================================
frame::frame() 
{}

frame::frame(const HTMLAttributeList& attributes)
	: HTMLElement(&attributes)
{}

frame::~frame()
{}

// ============================================================
// Class noframes
// ============================================================
noframes::noframes(const char *text) 
	: HTMLBooleanElement(text, NULL, NULL)
{}

noframes::noframes(const HTMLAttributeList& attributes)
	: HTMLBooleanElement(NULL, &attributes, NULL)
{}

noframes::noframes(const HTMLSimpleElement& embed)
	: HTMLBooleanElement(NULL, NULL, &embed)
{}

noframes::noframes(const char *text, const HTMLAttributeList& attributes) 
	: HTMLBooleanElement(text, &attributes, NULL)
{}

noframes::noframes(const HTMLAttributeList& attributes, const HTMLSimpleElement& embed)
	: HTMLBooleanElement(NULL, &attributes, &embed)
{}

noframes::~noframes()
{}

// ============================================================
// Class iframe
// ============================================================
iframe::iframe(const char *text) 
	: HTMLBooleanElement(text, NULL, NULL)
{}

iframe::iframe(const HTMLAttributeList& attributes)
	: HTMLBooleanElement(NULL, &attributes, NULL)
{}

iframe::iframe(const HTMLSimpleElement& embed)
	: HTMLBooleanElement(NULL, NULL, &embed)
{}

iframe::iframe(const char *text, const HTMLAttributeList& attributes) 
	: HTMLBooleanElement(text, &attributes, NULL)
{}

iframe::iframe(const HTMLAttributeList& attributes, const HTMLSimpleElement& embed)
	: HTMLBooleanElement(NULL, &attributes, &embed)
{}

iframe::~iframe()
{}
