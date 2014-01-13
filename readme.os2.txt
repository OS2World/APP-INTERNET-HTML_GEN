HTML_GEN v1.0

Generates HTML files out of source files and macros

This is a little program I programmed to help me in maintaining my web sites. I had a lot of
pages that contained the same or nearly the same code on them and if I had to change one
thing I had to go through nearly all the pages.

The trick with this program is that I don't write HTML files directly. The pages contain HTML
code but also MACRO calls. They end in .SOURCE and are read by the program. By that
the source code is scanned for M!A!C!R!O followed by the macro name. Each macro can
take parameters too. They have to be given in brackets after the macro name and must be
seperated by a comma, e.g:

	M!A!C!R!Obody(#FFFFFF,#550000,#00FFCC)

The program substitutes the macro call with the content of the macro file which should be
named <macro name>.MACRO, e.g:

	body.macro

The parameters of the macro are filled into the places marked with !A!A!. The rest of the source
and macro file are stored in the resulting HTML file as given in the source.

To generate the example file:	html_gen index

This will generate the file index.html out of the index.source.

Requirements: The executable program requires at least a 386 cpu with OS/2.

Files Included

    HTML_GEN.C	C source code
    HTML_GEN.EXE	OS/2 executable
    BODY.MACRO	example of a macro
    DOCTYPE.MACRO	another macro example
    INDEX.SOURCE	example source file
    README.OS2	this file

Compiling source

The source code has been compiled and tested with

   Borland C++ v2.1 for OS/2

Disclaimer:

The author assumes no responsibility for the use of the program, source
code, documentation, sample data, and etc. 

Have fun.

U. A. Mueller
email: sicota.country@usa.net

comments welcome