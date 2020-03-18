/*  Include files */
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

// static filebuf coutbuf;

//extern "C" DllExport void ufsta( char *param, int *returnCode, int rlen )
void ufsta( char *param, int *returnCode, int rlen )
{
//	static filebuf coutbuf;

	ostream coutstr(&coutbuf);
// allocate console window conout$
//     AllocConsole();

// reopen stdout on conout$ for fprintf and printf
//     FILE *fp;
//     fp = freopen("conout$", "w", stdout);

// open filebuf on conout$, create ostream, and assign to cout
//     coutbuf.open("conout$", ios::out);
//     cout = coutstr;

//	  printf( "printf's ");
//     cout << "and cout's will go here now" << endl;
}
