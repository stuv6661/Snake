/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
 *
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include "platform.h"

#ifdef OS_WINDOWS
/* Get va_list.  */
#if __STDC__ || defined __cplusplus || defined _MSC_VER
# include <stdarg.h>
#else
# include <varargs.h>
#endif
extern int vasprintf (char **, const char *, va_list);
extern int asprintf (char **, const char *, ...);
#endif

#include "MLV_xml.h"
#include "MLV_xml_va.h"

#include "warning_error.h"

#include "memory_management.h"

#include "data_structure.h"

#include <glib.h>

#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

#include <errno.h>

extern DataMLV* MLV_data;

struct _MLV_Xml {
	xmlDocPtr doc;
//	xmlNodePtr cur;
};

MLV_Xml* MLV_load_xml( const char* xml_file_path ){
	MLV_Xml* result =  MLV_MALLOC( 1, MLV_Xml );

	result->doc = xmlParseFile( xml_file_path );
	
	if (result->doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		MLV_FREE( result, MLV_Xml );
		return NULL;
	}

//	result->cur = xmlDocGetRootElement( result->doc );
//	
//	if ( result->cur == NULL) {
//		fprintf(stderr,"empty document\n");
//		xmlFreeDoc(result->doc);
//		MLV_FREE( result, MLV_Xml );
//		return NULL;
//	}

	return result;
}

void MLV_free_xml( MLV_Xml* xml_data ){
	if( xml_data  ){
		if( xml_data->doc ){
			xmlFreeDoc( xml_data->doc );
		}
		MLV_FREE( xml_data, MLV_Xml );
	}
}


void test_if_text_is_valid( const char* text, const char* xpath ){
	if( ! text ){
		char* message;
		if(
			asprintf( 
				&message, 
				"The xml file is probably corupted. The following element is not present: \"%s\" in the xml file.", 
				xpath
			) < 0
		){
			ERROR_FULL("The error message can be constructed.");
		}
		ERROR( message );
	}
}

void internal_scan_xml(
	const MLV_Xml* xml_data, const char* xpath, va_list pile, 
	xmlXPathObjectPtr *result_search
){
	xmlXPathContextPtr context;

	char* complete_xpath;
	if( vasprintf( &complete_xpath, xpath, pile ) < 0 ){
		ERROR_FULL("Unexpected error");
	}

	context = xmlXPathNewContext( xml_data->doc );
	*result_search = xmlXPathEvalExpression( (xmlChar*) complete_xpath, context);
	MLV_FREE( complete_xpath, char );
	xmlXPathFreeContext( context );
	if( xmlXPathNodeSetIsEmpty((*result_search)->nodesetval) ){
		xmlXPathFreeObject((*result_search));
		*result_search = NULL;
	}
}


char* internal_get_string_value_from_xml(
	const MLV_Xml* xml_data, int i, const char* xpath, va_list pile
){
	char* result = NULL;
	
	xmlXPathObjectPtr result_search;
	internal_scan_xml( xml_data, xpath, pile, &result_search );
	if( !result_search ) return NULL;

	xmlNodeSetPtr nodeset;
	nodeset = result_search->nodesetval;
	if(  i < nodeset->nodeNr ){
		result = (char*) xmlNodeListGetString(
			xml_data->doc, nodeset->nodeTab[i]->xmlChildrenNode, 1
		);
	}
	xmlXPathFreeObject(result_search);
	return result; 
}

MLV_Xml_error MLV_get_string_value_from_xml_va(
	const MLV_Xml* xml_data, char** result, const char* xpath, va_list pile
){
	*result = internal_get_string_value_from_xml( xml_data, 0, xpath, pile );
	if( *result == NULL ){
		return MLV_XML_THE_FIELD_DOESNT_EXIST;
	}
	return MLV_XML_NONE;
}

MLV_Xml_error MLV_get_string_value_from_xml(
	const MLV_Xml* xml_data, char** result, const char* xpath, ...
){
	MLV_Xml_error error;

	va_list pile;
	va_start( pile, xpath );

	error = MLV_get_string_value_from_xml_va( xml_data, result, xpath, pile );

	va_end( pile );

	return error;
}

MLV_Xml_error MLV_get_integer_value_from_xml_va(
	const MLV_Xml* xml_data, int* result, const char* xpath, va_list pile
){
	long int value;
	char* text;
	MLV_Xml_error error;

	error = MLV_get_string_value_from_xml_va( xml_data, &text, xpath, pile );
	
	if( error ){
		return error;
	}	

	char* final;
	errno = 0;
	value = strtol(text, &final, 10 );
	int err_sys = errno;
	if( (final==NULL) || (*text='\0') || (*final != '\0') ){
		error = MLV_XML_THE_FIELD_IS_NOT_AN_INTEGER;
	}else if( err_sys==ERANGE ){
		error = MLV_XML_THE_FIELD_IS_TOO_BIG;
	}else if( err_sys != 0 && value == 0 ){
		ERROR_FULL("A anormal error occurs during string to int conversion in XML Parsing." );
	}else{
		error = MLV_XML_NONE;
	}
	MLV_FREE( text, char );
	
	*result = value;

	return error; 
}


MLV_Xml_error MLV_get_integer_value_from_xml(
	const MLV_Xml* xml_data, int* result, const char* xpath, ...
){
	MLV_Xml_error error;

	va_list pile;
	va_start( pile, xpath );
	
	error = MLV_get_integer_value_from_xml_va( xml_data, result, xpath, pile );

	va_end( pile );
	return error; 
}

MLV_Xml_error MLV_get_double_value_from_xml_va(
	const MLV_Xml* xml_data, double* result, const char* xpath, va_list pile
){
	double value;
	char* text;
	MLV_Xml_error error;
	
	error = MLV_get_string_value_from_xml_va( xml_data, &text, xpath, pile );
	
	if( error ){
		return error;
	}	

	char* final;
	errno = 0;
	value = strtod(text, &final );
	int err_sys = errno;
	if( (final==NULL) || (*text='\0') || (*final != '\0') ){
		error = MLV_XML_THE_FIELD_IS_NOT_A_REAL;
	}else if( err_sys==ERANGE ){
		error = MLV_XML_THE_FIELD_IS_TOO_BIG;
	}else if( err_sys != 0 && value == 0 ){
		ERROR_FULL("A anormal error occurs during string to double conversion in XML Parsing." );
	}else{
		error = MLV_XML_NONE;
	}
	MLV_FREE( text, char );
	
	*result = value;

	return error; 
}

MLV_Xml_error MLV_get_double_value_from_xml(
	const MLV_Xml* xml_data, double* result, const char* xpath, ...
){
	MLV_Xml_error error;

	va_list pile;
	va_start( pile, xpath );
	
	error = MLV_get_double_value_from_xml_va( xml_data, result, xpath, pile );

	va_end( pile );
	
	return error; 
}

MLV_Xml_error MLV_get_float_value_from_xml_va(
	const MLV_Xml* xml_data, float* result, const char* xpath, va_list pile
){
	float value;
	char* text;
	MLV_Xml_error error;
	
	error = MLV_get_string_value_from_xml_va( xml_data, &text, xpath, pile );
	
	if( error ){
		return error;
	}	

	char* final;
	errno = 0;
	value = strtof(text, &final);
	int err_sys = errno;
	if( (final==NULL) || (*text='\0') || (*final != '\0') ){
		error = MLV_XML_THE_FIELD_IS_NOT_A_REAL;
	}else if( err_sys==ERANGE ){
		error = MLV_XML_THE_FIELD_IS_TOO_BIG;
	}else if( err_sys != 0 && value == 0 ){
		ERROR_FULL("A anormal error occurs during string to double conversion in XML Parsing." );
	}else{
		error = MLV_XML_NONE;
	}
	MLV_FREE( text, char );
	
	*result = value;

	return error; 
}

MLV_Xml_error MLV_get_float_value_from_xml(
	const MLV_Xml* xml_data, float* result, const char* xpath, ...
){
	MLV_Xml_error error;

	va_list pile;
	va_start( pile, xpath );
	
	error = MLV_get_float_value_from_xml_va( xml_data, result, xpath, pile );

	va_end( pile );

	return error; 
}

int MLV_get_number_of_objects_from_xml_va(
	const MLV_Xml* xml_data, const char* xpath, va_list pile
){
	int result;

	xmlXPathObjectPtr result_search;
	internal_scan_xml( xml_data, xpath, pile, &result_search );

	if( !result_search ) return 0;
	result = result_search->nodesetval->nodeNr;

	xmlXPathFreeObject(result_search);
	return result; 
}

int MLV_get_number_of_objects_from_xml(
	const MLV_Xml* xml_data, const char* xpath, ...
){
	int result;
	
	va_list pile;
	va_start( pile, xpath );

	result = MLV_get_number_of_objects_from_xml_va( xml_data, xpath, pile );

	va_end( pile );
	
	return result; 
}

MLV_Xml* MLV_get_xml_object_of_va(
	const MLV_Xml* xml_data, const char* xpath, va_list pile
){
	MLV_Xml* result = NULL;
	ERROR_FULL("Not implemented.");
	return result;
}

MLV_Xml* MLV_get_xml_object_of(
	const MLV_Xml* xml_data, const char* xpath, ...
){
	MLV_Xml* result;

	va_list pile;
	va_start( pile, xpath );

	result = MLV_get_xml_object_of_va( xml_data, xpath, pile );

	va_end( pile );

	return result;
}

void MLV_print_xml( const MLV_Xml* xml_data ){
	ERROR_FULL("Not implemented.");
}
