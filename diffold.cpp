

// Return line relation in file

int CWedView::linediff(CWedView *v1, CWedView *v2)
{
    ASSERT_VALID(v1); ASSERT_VALID(v2);

    CWedDoc *doc1 = v1->GetDocument();
    CWedDoc *doc2 = v2->GetDocument();

    ASSERT_VALID(doc1); ASSERT_VALID(doc2);

    message("Diffing files ...");
    diffchange = FALSE;

    CString str1, str2;
    CString str11, str22;
    CString str111, str222;

    int idx1   = 0, idx2 = 0;
    int idx11  = 0, idx22 = 0;
    int idx111 = 0, idx222 = 0;

    int len1 = doc1->strlist.GetCount();
    int len2 = doc2->strlist.GetCount();
    int diff = 0;

    //PrintToNotepad("linediff: %d  %d\r\n",  (int)doc1, (int)doc2);

    // Prepare diff arrays:
    v1->diffa.RemoveAll();
    v1->diffa.SetSize(len1);

    v2->diffa.RemoveAll();
    v2->diffa.SetSize(len2);

    while(TRUE)
        {
        if(was_esc)
        {
         message("Diff stopped");
         break;
        }

        if(idx1 >= len1)
            break;

        if(idx2 >= len2)
            break;

        // This is a test for ondraw coloring
        //v1->diffa.SetAt(idx1, DIFF_DEL);
        //v2->diffa.SetAt(idx2, DIFF_ADD);

        str1 = doc1->strlist.GetLine(idx1);
        str2 = doc2->strlist.GetLine(idx2);

        int clen = 0;
        int diff2 = 0;
        int diff3 = 0;

        // Equal, no need to do anything
        if(str1 == str2)
            goto next1;

        //PrintToNotepad("str1: %s\r\n",    (const char *)str1);
        //PrintToNotepad("str2: %s\r\n",    (const char *)str2);

        // Not interested in empty lines
        //while(str1 == "" && idx1 < len1 )
        //    str1 = doc1->strlist.GetLine(++idx1);
        //
        //while(str2 == "" && idx2 < len2 )
        //    str2 = doc2->strlist.GetLine(++idx2);

        //clen = min(str1.GetLength(), str2.GetLength());
        // Are they similar?
        //if(strdiff(str1, str2) < clen/5)
        //   {
        //    v1->diffa.SetAt(idx1, DIFF_CHG);
        //    v2->diffa.SetAt(idx2, DIFF_CHG);
        //    goto next1;
        //    }
        idx11 = idx1+1;
        idx22 = idx2+1;

        // Start walking
        while(TRUE)
            {
            if(idx11 >= len1)
                break;

            if(idx22 >= len2)
                break;

            str11 = doc1->strlist.GetLine(idx11);
            str22 = doc2->strlist.GetLine(idx22);

            //while(str11 == "" && idx11 < len1)
            //    str11 = doc1->strlist.GetLine(++idx11);

            //while(str22 == "" && idx22 < len2)
            //    str22 = doc2->strlist.GetLine(++idx22);

            if(str11 == str22)
            {
                idx1 = idx11;
                idx2 = idx22;
                break;
            }

            //PrintToNotepad("seek str11: %s\r\n",
             //           (const char *)str11);

            //PrintToNotepad("seek str22: %s\r\n",
            //            (const char *)str2);

            idx111 = idx11;
            idx222 = idx22;

            while(TRUE)
                {
                if(idx222 >= len2)
                    break;
                if(idx111 >= len1)
                    break;

                // Try doc2, walk doc1
                str111 = doc1->strlist.GetLine(idx111);
                //while(str111 == "" && idx111 < len1)
                //    str111 = doc1->strlist.GetLine(++idx111);

                //PrintToNotepad("seek str111: %s\r\n",
                //        (const char *)str111);

                if(str111 == str22)
                {
                for(int xxx = idx11-1; xxx < idx111-1; xxx++)
                    v1->diffa.SetAt(xxx, DIFF_DEL);
                    idx11= idx111;
                    break;
                }

                // Try doc2, walk doc1
                str222 = doc2->strlist.GetLine(idx222);
                //while(str222 == "" && idx222 < len2)
                //    str222 = doc2->strlist.GetLine(++idx222);

                //PrintToNotepad("seek str222: %s\r\n",
                //        (const char *)str222);

                if(str222 == str11)
                {
                for(int xxx = idx22-1; xxx < idx222-1; xxx++)
                    v2->diffa.SetAt(xxx, DIFF_DEL);
                    idx22= idx222;
                    break;
                }
                idx111++;
                idx222++;
                }
            idx11++;
            idx22++;
            }
next1:  idx1++;
        idx2++;
        }
    return(diff);
}

// EOF

