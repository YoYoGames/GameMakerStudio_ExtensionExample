// **********************************************************************************************************************
// 
// Copyright (c)2014, YoYo Games Ltd. All Rights reserved.
// 
// File:	    	ExampleExtension.cpp
// Created:	        23/06/2014
// Author:    		Mike.Dailly
// Project:		    Example GameMaker: Studio Extension
// Description:   	Show the basics of creating an extension
//
//					Please also take not of the POST build event. Once added to a project, get the full name+path
//					and make sure you copy over it every time you build - debug AND release!!
// 
// Date				Version		BY		Comment
// ----------------------------------------------------------------------------------------------------------------------
// 23/06/2014		V1.0		MJD		1st verison
// 
// **********************************************************************************************************************
#include <stdio.h>
#include <string.h>

#if !defined( _MSC_VER)
#define EXPORTED_FN __attribute__((visibility("default")))
#else
#define EXPORTED_FN __declspec(dllexport)
#define snprintf sprintf_s
#define strdup _strdup
#endif

 
// ensure that the symbols are undercorated in the dynamic lib
extern "C" {

static bool g_Initialised = false;


// #############################################################################################
/// Function:<summary>
///             Initialsie the DLL
///          </summary>
// #############################################################################################
EXPORTED_FN double MyExtension_Init( void )
{
	g_Initialised = true;
	return 0.0;
}

// #############################################################################################
/// Function:<summary>
///             Shutdown the DLL
///          </summary>
// #############################################################################################
EXPORTED_FN double  MyExtension_Quit( void )
{
	g_Initialised = false;
	return 0.0;
}

// #############################################################################################
/// Function:<summary>
///             An actual function, takes a double... returns a double
///          </summary>
///
/// In:		 <param name="_value">A user value</param>
/// Out:	 <returns>
///				_value*100.0
///			 </returns>
// #############################################################################################
EXPORTED_FN double MyExtension_Function( double _value )
{
	if( !g_Initialised ) return 0.0;
	return _value*100.0;
}


// #############################################################################################
/// Function:<summary>
///             An actual function, takes a string and a double... returns a combined string
//				NOTE: strings are UTF8 ( demo is in ASCI, All chars <128 )
///          </summary>
///
/// In:		 <param name="_text">A heading prefix</param>
/// 		 <param name="_value">A user value</param>
/// Out:	 <returns>
///				_value*100.0
///			 </returns>
// #############################################################################################
EXPORTED_FN char*  MyExtension_StringReturn( char* _text, double _value )
{
	if( !g_Initialised ) return NULL;

	char s[1024];
	snprintf(&s[0], 1023, "%s%f", _text, (float)_value);
	char* pString = strdup(s);
	return pString;
}

// #############################################################################################
/// Function:<summary>
///             This example takes a GML buffer pointer, adds up the data contained in it,
//				then fills in some NEW data. Please note never go beyond the bounds
//				of the buffer, and never free/realloc it. GML controls it's life
///          </summary>
///
/// In:		 <param name="_pBuffer">Buffer pointer</param>
/// 		 <param name="_size">size of buffer in bytes</param>
/// Out:	 <returns>
///				a string holding the total of the data.
///				Buffer data is also changed
///			 </returns>
// #############################################################################################
EXPORTED_FN  char*  MyExtension_BufferPointer( void* _pBuffer, double _size)
{
	if( !g_Initialised ) return NULL;

	unsigned char* pBuffer = (unsigned char*)_pBuffer;
	int i,total = 0;
	for(i=0;i<_size;i++){
		total+=pBuffer[i];					// buffer read example
		pBuffer[i] = (unsigned char)i;		// buffer write example
	}


	char s[1024];
	snprintf(&s[0], 1023, "Total = %d", total);
	char* pString = strdup(s);
	return pString;
}


}

