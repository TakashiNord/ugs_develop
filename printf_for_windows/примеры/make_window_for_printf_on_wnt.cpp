/*HEAD MAKE_WINDOW_FOR_PRINTF_ON_WNT.CPP CCC UFUN */
/*
    The output from the C command "printf" is no longer
    displayed in any window onthe WNT platform starting in UG
    V16.0.

    V16.0 UG is a Windows Application and no longer has a
    console tied to the process so there is no place to view the
    "printf" output.

    To work around this problem, build a shared library using
    this code and place the resulting .dll in the
    "startup" or "udo" subdirectory of a directory listed in
    %UGII_CUSTOM_DIRECTORY_FILE%.  This program will create a
    window each time UG starts up which can then be used to view
    stdout for the remainder of the session.

    For more information on the "startup" or "udo"
    subdirectories or the UGII_CUSTOM_DIRECTORY_FILE environment
    variable, consult the UG/Open Menuscript documentation.
*/

#include <windows.h>
#include <fstream.h>
#include <stdio.h>
#include <uf_exit.h>

static filebuf coutbuf;

void ufsta(char *param, int *retcode, int paramLen)
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

    printf( "printf's ");
    cout << "and cout's will go here now" << endl;

}
