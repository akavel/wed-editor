//////////////////////////////////////////////////////////////////////
// String search routines for wild card
//

#include "stdafx.h"
#include "wed.h"

#include "MainFrm.h"
#include "StrList.h"

#include "wedDoc.h"
#include "wedView.h"

#include "FileInfo.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "mxpad.h"
#include "holdhead.h"
#include "editor.h"
#include "undo.h"
#include "diff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int     wild_str_cmp(const char *name, const char *muster)

{
    //int n;

    while(*muster != '\0')
        {
        //if(*muster == '\\' && *(muster-1) != '\\')      /* skip backslash */
        //    muster++;

        // Wild card
        if(*muster == '*')
            {
            if(*name == '\0')
                {
                muster++; break;
                }
            if(*name == *(muster+1))
                muster++;
            else
                name++;
            continue;
            }
        // One char wild card
        if(*muster == '?')
            {
            name++;  muster++;
            continue;
            }
        // Mismatch -- exit now
        if(*name != *muster)
            break;

        name++;  muster++;
        }

    if(*muster == '\0')
        return(0);
    else
        return(*name - *muster);
}


const char    *strstr_normal(const char *buffer, const char *muster)

{
    const  char *found_ptr = buffer;

    while((found_ptr = strchr(found_ptr, *muster)) != NULL)
        {
        if(strncmp(found_ptr, muster, strlen(muster)) == 0)
            return(found_ptr);
        found_ptr++;                        /* go away from this character */
        }
    return(NULL);
}

const char    *strstr_wild(const char *buffer, const char *muster)

{
    const char    *found_ptr = buffer;
    int     back = 0;

    //if(*muster == '\\' && *(muster-1) != '\\')           /* skip backslash */
    //        back = 1;

    while(TRUE)
        {
        if(wild_str_cmp(found_ptr, muster + 1 + back) == 0)
            return(found_ptr);

        found_ptr = strchr(found_ptr, *muster);

        if(!found_ptr)
            break;

        found_ptr++;                        /* go away from this character */
        }
    return(NULL);
}

// Search for matching string in another.
// If found, returns a pointer to the match,
//  else return NULL.


const char  *str_search(const char *buffer, const char *muster, int wild)

{
    if(wild)
        return(strstr_wild(buffer, muster));
    else
        return(strstr_normal(buffer, muster));
}


