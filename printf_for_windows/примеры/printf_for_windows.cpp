//  Include files
#include <uf.h>
#include <uf_exit.h>
#include <uf_ui.h>
#include <ug_session.hxx>
#include <ug_exception.hxx>
#include <ug_info_window.hxx>
#if ! defined ( __hp9000s800 ) && ! defined ( __sgi ) && ! defined ( __sun )
#	include <strstream>
	using std::ostrstream;
	using std::endl;	
	using std::ends;
#else
#	include <strstream.h>
#endif
#include <iostream.h>
#include <fstream.h>
//#include <wincon.h>
#include "printf_for_windows.h"

static filebuf coutbuf;

extern "C" DllExport void ufusr( char *param, int *returnCode, int rlen )
{
//	      filebuf coutbuf;

	ostream coutstr(&coutbuf);

  //   AllocConsole();


     FILE *fp;
     fp = freopen("conout$", "w", stdout);

     // open filebuf on conout$, create ostream, and assign to cout
     coutbuf.open("conout$", ios::out);
     cout = coutstr;

     printf( "printf's ");
     cout << "and cout's will go here now" << endl;
}


extern "C" int ufusr_ask_unload( void )
{
    return( UF_UNLOAD_UG_TERMINATE );
}

void processException( const UgException &exception )
{
    // Construct a buffer to hold the text.
    ostrstream error_message;

    // Initialize the buffer with the required text.
    error_message << endl
                  << "Error:" << endl
                  << ( exception.askErrorText() ).c_str()
                  << endl << endl << ends;

    // Open the UgInfoWindow
    UgInfoWindow::open ( );

    // Write the message to the UgInfoWindow.  The str method
    // freezes the buffer, so it must be unfrozen afterwards.
    UgInfoWindow::write( error_message.str() );

	// Write the message to standard error
    cerr << error_message.str();
    error_message.rdbuf()->freeze( 0 );
}






