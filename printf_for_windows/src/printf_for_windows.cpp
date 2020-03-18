//////////////////////////////////////////////////////////////////////////////
//
//  printf_for_windows.cpp
//
//  Description:
//      Contains Unigraphics entry points for the application.
//
//////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE 1

//  Include files
#include <uf.h>
#include <uf_exit.h>
#include <uf_ui.h>

#if ! defined ( __hp9000s800 ) && ! defined ( __sgi ) && ! defined ( __sun )
#	include <strstream>
	using std::ostrstream;
	using std::endl;
	using std::ends;
#else
#	include <strstream.h>
#endif
#include <iostream.h>

#include "printf_for_windows.h"

#include <windows.h>
#include <fstream.h>
#include <stdio.h>
#include <uf_exit.h>

static filebuf coutbuf;

int printf_for_windows(void);
int printf_for_windows_file(void);

//----------------------------------------------------------------------------
//  Activation Methods
//----------------------------------------------------------------------------

//  Unigraphics Startup
//      This entry point activates the application at Unigraphics startup
extern "C" DllExport void ufsta( char *param, int *returnCode, int rlen )
{
    /* Initialize the API environment */
    int errorCode = UF_initialize();

    if ( 0 == errorCode )
    {
        /* TODO: Add your application code here */
        printf_for_windows();
        //printf_for_windows_file();

        /* Terminate the API environment */
        errorCode = UF_terminate();
    }

    /* Print out any error messages */
    PrintErrorMessage( errorCode );
    *returnCode=0;
}

//----------------------------------------------------------------------------
//  Utilities
//----------------------------------------------------------------------------

// Unload Handler
//     This function specifies when to unload your application from Unigraphics.
//     If your application registers a callback (from a MenuScript item or a
//     User Defined Object for example), this function MUST return
//     "UF_UNLOAD_UG_TERMINATE".
extern "C" int ufusr_ask_unload( void )
{
    return( UF_UNLOAD_UG_TERMINATE );
}

/* PrintErrorMessage
**
**     Prints error messages to standard error and the Unigraphics status
**     line. */
static void PrintErrorMessage( int errorCode )
{
    if ( 0 != errorCode )
    {
        /* Retrieve the associated error message */
        char message[133];
        UF_get_fail_message( errorCode, message );

        /* Print out the message */
        UF_UI_set_status( message );

        // Construct a buffer to hold the text.
        ostrstream error_message;

        // Initialize the buffer with the required text.
        error_message << endl
                      << "Error:" << endl
                      << message
                      << endl << endl << ends;

	    // Write the message to standard error
        cerr << error_message.str();
    }
}

int printf_for_windows(void)
{

    ostream coutstr(&coutbuf);

    // allocate console window conout$
    AllocConsole();

    // reopen stdout on conout$ for fprintf and printf
    FILE *fp;
    fp = freopen("conout$", "w", stdout);

    // open filebuf on conout$, create ostream, and assign to cout
    coutbuf.open("conout$", ios::out);
    cout = coutstr;

    printf( "printf's , puts ");
    cout << "and cout's will go here now" << endl;

	return(0);
}

int printf_for_windows_file(void)
{

    // allocate console window conout$
    AllocConsole();

  // ============================================================
  char *mes="Output log...";
  UF_UI_message_buttons_t buttons1 = { TRUE, FALSE, TRUE, "stdout", NULL, "file", 1, 0, 2 };
  int response;

  response=0;
  UF_UI_message_dialog("file or stdout ?", UF_UI_MESSAGE_QUESTION, &mes, 1, TRUE, &buttons1, &response);
  if (response!=1) {
    char *path , envpath[255]="";
    path = (char *) malloc(255+10);
    UF_translate_variable("UGII_TMP_DIR", &path);
    if (path!=NULL) {
    	envpath[0]='\0';
      strcpy(envpath,path); strcat(envpath,"\\printf_for_windows.log\0");
      FILE *ffile;
      ffile = freopen(envpath, "w+", stdout);
    }
  }
  // ============================================================

  printf( "printf_for_windows_file - load \n");

	return(0);
}
