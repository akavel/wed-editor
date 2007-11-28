// diff.cpp : implementation of the diff routines
//
//

#include "stdafx.h"
#include "wed.h"
#include "MainFrm.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "FileInfo.h"
#include "notepad.h"
#include "holdhead.h"
#include "editor.h"
#include "diff.h"
#include "misc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int maxscore = 3;
int maxdeviate = 200;

CWordArray 	diffh1;
CWordArray 	diffh2;

/////////////////////////////////////////////////////////////////////////////
// Fast diff

int	dodiff(CWedView *v1, CWedView *v2)

{
	static int in_diff;

	if(in_diff)
		return (0);

    //PrintToNotepad("dodiff: %d  %d\r\n",  (int)doc1, (int)doc2);
    ASSERT_VALID(v1); ASSERT_VALID(v2);

    CWedDoc *doc1 = v1->GetDocument();  ASSERT_VALID(doc1);
    CWedDoc *doc2 = v2->GetDocument();  ASSERT_VALID(doc2);

	in_diff = TRUE;
    v1->Busy(TRUE);
    v2->Busy(TRUE);

    CString str1, str2;

    int score = 0;
    int idx1   = 0, idx2 = 0;
    int idx11  = 0, idx22 = 0;
    int idx111 = 0, idx222 = 0;

    int len1 = doc1->strlist.GetCount();
    int len2 = doc2->strlist.GetCount();
    int diff = 0;
    int deviate = 0;
    int deviate2 = 0;

    // Prepare diff arrays:
    v1->diffa.RemoveAll();  v1->diffa.SetSize(len1+1);
    diffh1.RemoveAll();  diffh1.SetSize(len1+1);

    v2->diffa.RemoveAll();  v2->diffa.SetSize(len2+1);
    diffh2.RemoveAll();	diffh2.SetSize(len2+1);

	// In case of a small file, reconnect early
	if(len1 < 25)
		maxscore = 1;
	else
		maxscore = 3;

	// Generate Hash Tables
    while(TRUE)
      	{
        if(idx1 >= len1-1)
            break;

        if(idx2 >= len2-1)
            break;

        if(!(idx1 % 100))
        	{
            CString num; num.Format("Diffing at line %d", idx1);
            message(num);
        	}
        if(YieldToWinEx())
        	{
    		message("Diff stopped");
     		break;
        	}
        str1 = doc1->strlist.GetLine(idx1);
        diffh1.SetAtGrow(idx1, HashString(str1));
        //PrintToNotepad("Hash1: %d  str %s\r\n", HashString(str1), str1);

        str2 = doc2->strlist.GetLine(idx2);
        diffh2.SetAtGrow(idx2, HashString(str2));
        //PrintToNotepad("Hash2: %d  str %s\r\n",  HashString(str2), str2);

        idx1++; idx2++;
     	}

     // Start again
     idx1 = 0; idx2 = 0;
     while(TRUE)
        {
        if(idx1 >= len1-1)
            break;
        if(idx2 >= len2-1)
            break;

		// Identical lines, no action
        if(diffh2.GetAt(idx2) == diffh1.GetAt(idx1))
            goto next;

        // Differ, find connection with 'maxscore' matching lines:
        idx11 = idx1;
        deviate = 0;
        while(TRUE)
            {
            // Safety speed net
            if(deviate++ > maxdeviate)
                break;
            //PrintToNotepad("Walk1 %d\r\n", idx11);

            if(idx11 >= len1-1)
                break;
            if(idx22 >= len2-1)
                break;

            idx22 = idx2;
            score = 0;
            deviate2 = 0;
            while(TRUE)
                {
	            // Safety speed net
                if(deviate2++ > maxdeviate)
                    break;

                //PrintToNotepad("****Walk2 %d\r\n", idx22);

                if(idx11 >= len1-1)
                    break;
                if(idx22 >= len2-1)
                    break;

                if(diffh2.GetAt(idx22) == diffh1.GetAt(idx11))
                    {
                    score++; idx11++;
                    }
                else
                    {
                    // step back
                    idx11 -= score;  score = 0;
                    }
                if(score > maxscore)
                    {
                    // show place of connect

                    //str1 = doc1->strlist.GetLine(idx11 - (maxscore+1));
                    //str2 = doc2->strlist.GetLine(idx22 - maxscore);
                    //PrintToNotepad("reconnect: %s -- %s\r\n",  str1, str2);

                    // Found connections, color them
                    for(int xx = idx1; xx < idx11 - (maxscore+1); xx++)
                    	{
                    	//str1 = doc1->strlist.GetLine(xx);
                    	//str2 = doc2->strlist.GetLine(idx2 + (xx-idx1));
                    	//if(strdiff(str1, str2) > 3)
                      	//	v1->diffa.SetAtGrow(xx, DIFF_ADD);
                      	//else
                      	//	v1->diffa.SetAtGrow(xx, DIFF_CHG);

                      	v1->diffa.SetAtGrow(xx, DIFF_ADD);
                      	}

                    for(int xxx = idx2; xxx < idx22 - maxscore; xxx++)
                    	{
                    	//str1 = doc2->strlist.GetLine(xxx);
                    	//str2 = doc1->strlist.GetLine(idx1 + (xxx-idx2));
                    	//if(strdiff(str1, str2) > 3)
    	             	//	v2->diffa.SetAtGrow(xxx, DIFF_DEL);
                      	//else
                      	//	v2->diffa.SetAtGrow(xxx, DIFF_CHG);

    	             	v2->diffa.SetAtGrow(xxx, DIFF_DEL);
    	             	}

                    idx1 = idx11 - (maxscore+1);
                    idx2 = idx22 - maxscore;
                    goto found;
                    }
                idx22++;
                }
            idx11++;
            idx22 = idx2;
            }
found:
next:
        idx1++; idx2++;
        }

	// Free resources
    diffh1.RemoveAll();
    diffh2.RemoveAll();

    v1->Busy(FALSE);
    v2->Busy(FALSE);
    message("Done diffing");
	in_diff = FALSE;

    return(0);
}

/////////////////////////////////////////////////////////////////////////////
// Return estimated number of patches needed between strings

int strdiff(const CString &str1, const CString &str2)
{
    char chh1, chh2;
    char chh11, chh22;
    char chh33, chh44;
    int idx1 = 0, idx2 = 0;
    int idx11 = 0, idx22 = 0;
    int idx33 = 0, idx44 = 0;
    int len1 = str1.GetLength();
    int len2 = str2.GetLength();
    int diff = 0;

    //PrintToNotepad("strdiff - 1 : %s\r\n", str1);
    //PrintToNotepad("strdiff - 2 : %s\r\n", str2);

	if(!len1)
		return(len2);

	if(!len2)
		return(len1);

    while(TRUE)
    	{
        if(idx1 >= len1)
            break;

        if(idx2 >= len2)
            break;

        chh1 = str1.GetAt(idx1);
        chh2 = str2.GetAt(idx2);

        if(chh1 != chh2)
        {
        int diff2 = 0;
        int diff3 = 0;
        int diff4 = 0;

        idx11 = idx1;
        idx22 = idx2;
        idx33 = idx1;
        idx44 = idx2;

        // try str1, walk str2
        while(TRUE)
            {
            if(idx22 >= len2)
                break;

            chh22 = str2.GetAt(idx22);
            if(chh1 == chh22)
                break;

            diff2++;
            idx22++;
            }
        // try str2, walk str1
        while(TRUE)
            {
            if(idx11 >= len1)
                break;

            chh11 = str1.GetAt(idx11);
            if(chh11 == chh2)
                break;

            diff3++;
            idx11++;
            }

        // Walk both
        while(TRUE)
            {
            if(idx33 >= len1)
                break;

            if(idx44 >= len2)
                break;

            chh33 = str1.GetAt(idx33);
            chh44 = str2.GetAt(idx44);
            if(chh33 == chh44)
                break;

            diff4++;
            idx33++;
            idx44++;
            }

        //PrintToNotepad("diff2 =  %d diff3 = %d diff4 = %d\r\n",
        //               	     diff2, diff3, diff4);

        // Assume closest match
        if(diff2 < diff3)
            {
            if(diff4 < diff2)
                {
                idx1 = idx33;
                idx2 = idx44;
                diff += diff4;
                }
            else
                {
                idx2 = idx22;
                diff += diff2;
                }
            }
        else
            {
            if(diff4 < diff3)
                {
                idx1 = idx33;
                idx2 = idx44;
                diff += diff4;
                }
            else
                {
                idx1 = idx11;
                diff += diff3;
                }
            }
        }
        idx1++;
        idx2++;
    }
    //PrintToNotepad("strdiff - ret : %d\r\n", diff);
    return(diff);
}
