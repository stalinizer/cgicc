/* $Id: FormEntry.cc,v 1.6 1998/09/24 01:37:58 sbooth Exp $ */

#include "FormEntry.hh"

/* Create a new FormEntry */
FormEntry::FormEntry(const char	*name,
		     const char	*value,
		     int valueLen) throw (Exception)
  : fName(NULL), fValue(NULL)
{
  fName = new char[strlen(name) + 1];
  if(fName == NULL)
    throw Exception("new failed", ERRINFO);
  strcpy(fName, name);
  
  if(valueLen == -1) {
    fValue = new char[strlen(value) + 1];
    if(fValue == NULL)
      throw Exception("new failed", ERRINFO);
    strcpy(fValue, value);  
  }
  else {
    fValue = new char[valueLen + 1];
    if(fValue == NULL)
      throw Exception("new failed", ERRINFO);
    strncpy(fValue, value, valueLen);
    fValue[valueLen] = '\0';
  }

  fLength = strlen(fValue);
}

FormEntry::FormEntry(const FormEntry& entry) throw (Exception)
  : fName(NULL), fValue(NULL)
{
  fName = new char[strlen(entry.getName()) + 1];
  if(fName == NULL)
    throw Exception("new failed", ERRINFO);
  strcpy(fName, entry.getName());

  fValue = new char[strlen(entry.getValue()) + 1];
  if(fValue == NULL)
    throw Exception("new failed", ERRINFO);
  strcpy(fValue, entry.getValue());

  fLength = entry.length();
}

/* Delete this FormEntry */
FormEntry::~FormEntry()
{
  delete [] fName;
  delete [] fValue;
}

void
FormEntry::render(ostream& out) const {
  out << getName() << '=' << getValue();
}

void 
FormEntry::getValue(int maxChars,
		    char* &value) const throw(Exception) 
{
  value = new char[ length() + 1 ];
  if( ! value )
    throw Exception("new failed", ERRINFO);
  int result = makeString(value, maxChars, true);
  if( ! result ) {
    delete [] value;
    value = NULL;
  }
}

void 
FormEntry::getStrippedValue(char* &value) const throw(Exception) {
  getStrippedValue(INT_MAX, value);
}

void 
FormEntry::getStrippedValue(int maxChars,
			    char* &value) const throw(Exception) 
{
  value = new char[ length() + 1 ];
  if( ! value )
    throw Exception("new failed", ERRINFO);
  int result = makeString(value, maxChars, false);
  if( ! result) {
    delete [] value;
    value = NULL;
  }
}

int
FormEntry::getIntegerValue(int min, int max) const {
  int value = atoi(getValue());
  if(value > max)
    value = max;
  else if(value < min)
    value = min;
  
  return value;
}

double
FormEntry::getDoubleValue(double min, double max) const {
  double value = atof(getValue());
  if(value > max)
    value = max;
  else if(value < min)
    value = min;
  
  return value;
}

int 
FormEntry::makeString(char*	&result, 
		      int 	maxLen, 
		      int 	allowNewlines) const
{
  char *dest, *s;
  int truncated = 0;
  int len 	= 0;
  int avail 	= maxLen - 1;
  int crCount 	= 0;
  int lfCount 	= 0;	

  dest 	= result;
  s 	= (char*) getValue();	

  while(true) {
    char c = *s;

    if( len == avail ) {
      truncated = true;
      break;
    }	 
		
    // Fix the CR/LF, LF, CR nightmare: watch for
    // consecutive bursts of CRs and LFs in whatever
    // pattern, then actually output the larger number 
    // of LFs. Consistently sane, yet it still allows
    // consecutive blank lines when the user
    // actually intends them.
    if( ( c == 13 ) || ( c == 10 ) ) 
      if( c == 13 ) 
	crCount++;
      else 
	lfCount++;
    else {
      if( crCount || lfCount ) {
	int lfsAdd = crCount;
	if( lfCount > crCount ) 
	  lfsAdd = lfCount;
	
	// Stomp all newlines if desired
	if ( ! allowNewlines ) 
	  lfsAdd = 0;
	
	while( lfsAdd ) {
	  if( len == avail ) {
	    truncated = true;
	    break;
	  }
	  *dest++ = 10;
	  lfsAdd--;
	  len++;		
	}
	crCount = 0;
	lfCount = 0;
      }
      if( c == '\0' ) {
	// The end of the source string
	break;				
      }
      *dest++ = c;
      len++;
    }
    s++;	
  }
  *dest = '\0';
  
  if( truncated ) 
    return -1;
  else if( ! len) 
    return 0;
  else 
    return 1;
}
