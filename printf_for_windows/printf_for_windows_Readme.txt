
/*HEAD MAKE_WINDOW_FOR_PRINTF CCC UFUN */
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

Для отладки программ

 вывод сообщений printf|cout|puts на консоль