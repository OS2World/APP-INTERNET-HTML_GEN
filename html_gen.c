/************************************************************************
*  HTML generation - Main file
*
*  Author:      U.A.Mueller
*  Last update: 27.12.1997
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define prog_version "1.0"
#define prog_date    "27. Dec. 1997"

FILE  *fout,
      *fp,
      *fmac;

int strpos (const char *source, const char *comp)
{
  char temp[255] = "",
       walk[255] = "";
  int  i = 0;

  strcpy (temp, comp);
  strcpy (walk, source);

  while (walk[i] != temp[0])
    i++;

  return (i);
}

char *substr (const char *source, int first, int second)
{
  char temp[255] = "",
       *temp2;

  strcpy (temp, source);
  temp[second - first + 1] = '\0';
  temp2 = &temp[first - 1];
  return (temp2);
}

FILE *openFile (char *fname, char *extend, char *mode)
{
  char *buffer = "";
  FILE *fpp;

  strcpy (buffer, fname);
  strcat (buffer, extend);
  fpp = fopen (buffer, mode);

  if (fpp == NULL)
  {
    printf ("Error opening file %s\n\n", buffer);
    exit (1);
  }

  return (fpp);
}

void insertMacro (char *macroWithPar)
{
  char buffer[255],
       mfline[255];
  char *macline,
       *param,
       *macpar;

  macline = macroWithPar;
  param = strstr (macline, "(");

  if (param != NULL)
  {
    param++;                              /* remove opening parathesis */
    param[strlen (param) - 2] = '\0';     /* remove closing parathesis */
  }

  /* get macro name and open macro file */
  if (strcspn (macline, "(") == strlen (macline))
    strcpy (buffer, substr (macline, 1, strlen (macline) - 1));
  else
    strcpy (buffer, substr (macline, 1, strcspn (macline, "(")));

  fmac = openFile (buffer, ".macro", "rt");
  fseek (fmac, 0, SEEK_SET);

  while (NULL != fgets (mfline, 255, fmac))
  {
    macpar = strstr (mfline, "!A!A!");
    strcpy (buffer, "");

    if (macpar != NULL)
    { /* line contains parameter wilcard */
      while (macpar != NULL)  /* repeat until line contains no wildcards anymore */
      {
        if (param == NULL)
        { /* no parameter left from macro call */
          printf ("Error in macro %s (no parameters)\n\n", macline);
          exit (1);
        }

        strcat (buffer, substr (mfline, 1, strpos (mfline, "!A!A!")));  /* copy line till wildcard to buffer */
        strcat (buffer, substr (param, 1, strcspn (param, ",")));       /* insert parameter */
        param = strstr (param, ",");               /* remove used parameter and comma from param line */

        if (param != NULL)
         param++;

        macpar += 5;
        strcpy (mfline, macpar);             /* skip wildcard string from input line */
        macpar = strstr (mfline , "!A!A!");  /* test for further wildcards */
    }

    strcat (buffer, mfline);                 /* add remainder of line to translated line */
    fputs (buffer, fout);
    }
    else
      fputs (mfline, fout);
  }

  fputs ("\n", fout);
  fclose (fmac);
}

void parse_file (char *fname)
{
  char fline[255] = "";
  char *macline;

  fp   = openFile (fname, ".source", "rt");
  fout = openFile (fname, ".html", "wt");
  fseek (fp, 0, SEEK_SET);
  fseek (fout, 0, SEEK_SET);

  while (NULL != fgets (fline, 255, fp))
  {
    macline = strstr (fline, "M!A!C!R!O");

    if (macline != NULL)                       /* line contains macro */
    {
      macline += 9;                            /* remove macro sign */
      insertMacro (macline);
    }
    else
      fputs (fline, fout);
  }

  fclose (fp);
  fclose (fout);
}

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    printf ("HTML parser v%s by U.A.Mueller %s\n", prog_version, prog_date);
    printf ("Usage: %s <file name>\n\n", argv[0]);
  }
  else
    parse_file (argv[1]);

  return (0);
}