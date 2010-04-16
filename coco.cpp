/////////////////////////////////////////////////////////////////////////////
// Coco.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "mxpad.h"
#include "Coco.h"
#include "gotoline.h"
#include "io.h"
#include "ViewText.h"
#include "misc.h"

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Coco dialog

Coco::Coco(CWnd* pParent /*=NULL*/)
    : CDialog(Coco::IDD, pParent)
{
    //{{AFX_DATA_INIT(Coco)
       // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////

void Coco::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Coco)
    DDX_Control(pDX, IDC_TREE1, m_tree);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(Coco, CDialog)
    //{{AFX_MSG_MAP(Coco)
    ON_WM_SHOWWINDOW()
    ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
    ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
    ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
    ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
    ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
    ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
    ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
    ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
    ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_OPERATIONS_COPY, OnOperationsCopy)
    ON_COMMAND(ID_OPERATIONS_EDIT, OnOperationsEdit)
    ON_COMMAND(ID_OPERATIONS_PASTE, OnOperationsPaste)
    ON_COMMAND(ID_OPERATIONS_SHOW, OnOperationsShow)
    ON_COMMAND(ID_OPERATIONS_DELETE, OnOperationsDelete)
    ON_WM_CHAR()
    ON_WM_KEYDOWN()
    ON_COMMAND(ID_OPERATIONS_NEW, OnOperationsNew)
    ON_COMMAND(ID_OPERATIONS_NEWNODE, OnOperationsNewnode)
    ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
    ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnShowWindow(BOOL bShow, UINT nStatus)

void Coco::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    // Create file
    CFile cf; CString fname;
    int count = 0, ret = 0;
    long hFile;
    struct _finddata_t c_file;

    fname.Format("%sCoco\\*.txt", dataroot);
    hFile = _findfirst( fname, &c_file );
    while(TRUE)
        {
        if(hFile == -1 || ret)
            break;
        getitem(c_file.name);
        ret = _findnext( hFile, &c_file );
        }
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::getitem(char *name)

void Coco::getitem(char *name)

{
    CFile cf;
    CString fname, buff;
    fname.Format("%sCoco\\%s", dataroot, name);

    if(cf.Open(fname, CFile::modeRead))
       {
       CArchive ar( &cf, CArchive::load);
       ar.ReadString(buff);
       //P2N("Buffer %s\r\n", buff);

        HTREEITEM h1 = NULL;
        while(true)
            {
            CString buff2;

            int cc = buff.Find('\\');
            if(cc == -1)
                {
                //P2N("fcut at %s\r\n", buff);
                break;
                }
            //P2N("cut at %s\r\n", buff.Mid(0, cc));
            if(cc)
                {
                // See if that sub branch exists already:
                HTREEITEM h2 = m_tree.GetChildItem(h1);
          while(1)
          {
          if(!h2) break;
          if(m_tree.GetItemText(h2) == buff.Mid(0, cc))
              {
              // Change to that branch
              h1 = h2;
              break;
              }
          h2 = m_tree.GetNextItem(h2, TVGN_NEXT);
          }
          if(!h2)
                {
                //no, create it
                h1= m_tree.InsertItem(buff.Mid(0, cc), h1);
                }
         }
         buff = buff.Right(buff.GetLength() - (cc+1));
         }
       }
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnButton1()

void Coco::OnButton1()
{
    CreateBranch(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// Delete item
// void Coco::OnButton3()

void Coco::OnButton3()
{
    CString str;
    HTREEITEM h1 = m_tree.GetSelectedItem();

    // Anything selected ?
    if(!h1)
       {
       AfxMessageBox("Please select deletion point");
       return;
       }
    // Any Children ?
    HTREEITEM h2 = m_tree.GetNextItem(h1, TVGN_CHILD);
    if(h2)
       {
       AfxMessageBox("This node has children, cannot delete");
       return;
       }
    GetNodeFname(str);
    //P2N("Nodename %s\r\n", str);

    if(unlink(str))
        {
        AfxMessageBox("Cannot find file behind the item (possible orphan)");
        }
    // Go get it ....
    m_tree.DeleteItem(h1);
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnButton4()

void Coco::OnButton4()

{
    CreateBranch(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::CreateBranch(int doleaf)

void Coco::CreateBranch(int doleaf)

{
    CStringList list;
    CGotoLine   gt;
    HTREEITEM   h1;

    gt.m_prompt = "Create COCO item";

    h1 = m_tree.GetSelectedItem();

    if(doleaf && h1)
       h1 = m_tree.GetNextItem(h1, TVGN_PARENT);

    if(h1)
       gt.m_prompt =  "Current Branch: '" + m_tree.GetItemText(h1) + "'";
    else
       gt.m_prompt =  "";

    if (doleaf)
       gt.caption = "Create Coco Leaf";
    else
       gt.caption = "Create Coco Node";

    gt.DoModal();

    if(gt.m_esc)
       return;

    if(gt.m_str == "")
        {
       AfxMessageBox("Empty string");
       return;
        }
    if(gt.m_str.Find("\\") != -1)
        {
       AfxMessageBox("Item cannot contain BackSlash");
       return;
        }
    HTREEITEM h2 = m_tree.InsertItem(gt.m_str, h1);
    m_tree.Select(h2, TVGN_CARET );

    HTREEITEM h3 = h2;

    // Build Coco tree
    CString str; BuildTree(str);
    int hh = HashString(str);

    // Create file
    CFile cf; CString fname;
    fname.Format("%s%s%x.txt", dataroot, "Coco\\", hh);

    if(cf.Open(fname, CFile::modeCreate | CFile::modeWrite ))
        {
        CString lead;
        lead.Format("%s\r\n", str);
        cf.Write(lead, lead.GetLength());
        }
    else
        {
        AfxMessageBox("Cannot save tree");
        }
}

/////////////////////////////////////////////////////////////////////////////
// Copy from Coco to holding
// void Coco::OnButton5()

void Coco::OnButton5()

{
    int ucount = 0;
    HTREEITEM h1;

    if(!(h1 = m_tree.GetSelectedItem() ))
        {
        AfxMessageBox("Please select item first");
        return;
        }

    CString str; BuildTree(str);
    int hh = HashString(str);

    // Open file
    CFile cf;
    CString fname;
    fname.Format("%s%s%x.txt", dataroot, "Coco\\", hh);

    if(cf.Open(fname, CFile::modeRead))
       {
       CString str;
       CArchive ar( &cf, CArchive::load);

       // Read the directory line
       ar.ReadString(str);

       holding[currhold].RemoveAll();
       while(TRUE)
            {
            if(!ar.ReadString(str))
                break;

            ucount++;
            if(!(ucount%100))
                {
                CString num;
                num.Format( "Copy Coco line %d",
                        ucount);
                message(num);
                }
            holding[currhold].AddTail(str);
            }
       }
    CString num; num.Format("Copied %d lines", ucount);
    message(num);
}

/////////////////////////////////////////////////////////////////////////////
// Paste holding to tree
// void Coco::OnButton6()

void Coco::OnButton6()
{
    int ucount = 0;
    HTREEITEM h1;

    if(!(h1 = m_tree.GetSelectedItem() ))
        {
        AfxMessageBox("Please select item first");
        return;
        }

    CString str; BuildTree(str);
    int hh = HashString(str);

    // Open file
    CFile cf;
    char crlf[] = "\r\n";
    CString fname;
    fname.Format("%s%s%x.txt", dataroot, "Coco\\", hh);

    if(cf.Open(fname, CFile::modeReadWrite))
        {
        POSITION pos;
        CString lead;

        cf.Seek(0, CFile::end);

        pos = holding[currhold].GetHeadPosition();
        while(TRUE)
            {
            if (!pos)
                break;
            ucount++;

            if(!(ucount%100))
                {
                CString num;
                num.Format( "Paste to Coco line %d", ucount);
                message(num);
                }

            lead = holding[currhold].GetNext(pos);

            cf.Write(lead, lead.GetLength());
            cf.Write(crlf, 2);
            }
        }

    CString num; num.Format("Pasted %d lines", ucount);
    message(num);
}

/////////////////////////////////////////////////////////////////////////////
// Build tree
// void Coco::BuildTree(CString &str)

void Coco::BuildTree(CString &str)

{
    CStringList list;
    CGotoLine   gt;
    HTREEITEM   h1 = m_tree.GetSelectedItem();

    list.AddTail( m_tree.GetItemText(h1));
    while((h1 = m_tree.GetNextItem(h1, TVGN_PARENT)) )
       list.AddTail( m_tree.GetItemText(h1) );

    str = "";

    POSITION pos;
    pos = list.GetTailPosition();
    while(1)
       {
       str += "\\";
       if(!pos)
         break;
       str += list.GetPrev(pos);
       }

    //P2N("Item tree: %s\r\n", str);
}

/////////////////////////////////////////////////////////////////////////////
// Edit Coco item:
// void Coco::OnButton7()

void Coco::OnButton7()
{
    HTREEITEM h1;

    if(!(h1 = m_tree.GetSelectedItem() ))
        {
        AfxMessageBox("Please select item first");
        return;
        }
    CString str;   BuildTree(str);
    CString fname; GetNodeFname(fname);
    AfxGetApp()->OpenDocumentFile(fname);
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult)

void Coco::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
    ShowCode();
    *pResult = 0;
}


/////////////////////////////////////////////////////////////////////////////
// Get node file name
// void Coco::GetNodeFname(CString &str)

void Coco::GetNodeFname(CString &str1)

{
    // Build Coco tree
    CString str2; BuildTree(str2);
    int hh = HashString(str2);

    // Create file name
    str1.Format("%s%s%x.txt", dataroot, "Coco\\", hh);
}


/////////////////////////////////////////////////////////////////////////////
// void Coco::OnButton8()

void Coco::OnButton8()
{
    ShowCode();
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::ShowCode()

void Coco::ShowCode()

{
    ViewText vt;
    CString fname; GetNodeFname(fname);

    //P2N("Clicking tree at %s\r\n", fname);

    // Read Coco file
    CFile cf;
    if(cf.Open(fname, CFile::modeRead))
        {
        CString line;
        CArchive ar( &cf, CArchive::load);

        // Read initial line
        ar.ReadString(line);

        while(ar.ReadString(line))
            {
            vt.m_str += line + "\r\n";
            }
        }
    vt.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// Load menu
// void Coco::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult)

void Coco::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult)

{
    HTREEITEM h1;
    CMenu   mm;
    RECT    Rect;

    if(!(h1 = m_tree.GetSelectedItem() ))
        {
        return;
        }
    m_tree.GetItemRect(h1, &Rect, 1);
    POINT scr;
    scr.x = Rect.right;
    scr.y = Rect.bottom;
    ClientToScreen(&scr);
    mm.LoadMenu(IDR_MENU4);
    CMenu *pp = mm.GetSubMenu( 0 );
    pp->TrackPopupMenu( TPM_LEFTALIGN, scr.x, scr.y, this);
    *pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnMouseMove(UINT nFlags, CPoint point)

void Coco::OnMouseMove(UINT nFlags, CPoint point)
{
    CDialog::OnMouseMove(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnOperationsCopy()

void Coco::OnOperationsCopy()
{
    OnButton5();
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnOperationsEdit()

void Coco::OnOperationsEdit()
{
    OnButton7();
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnOperationsPaste()

void Coco::OnOperationsPaste()
{
    OnButton6();
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnOperationsShow()

void Coco::OnOperationsShow()
{
    OnButton8();
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnOperationsDelete()

void Coco::OnOperationsDelete()
{
    OnButton3();
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)

void Coco::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    //P2N("Onchar %c\r\n", nChar);
    CDialog::OnChar(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)

void Coco::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnOperationsNew()

void Coco::OnOperationsNew()
{
    OnButton4();
}

/////////////////////////////////////////////////////////////////////////////
// void Coco::OnOperationsNewnode()

void Coco::OnOperationsNewnode()
{
    OnButton1();
}


void Coco::OnButton11()

{
    CString strclip;

    int ucount = 0;
    HTREEITEM h1;

    if(!(h1 = m_tree.GetSelectedItem()))
        {
        AfxMessageBox("Please select item first");
        return;
        }

    CString str; BuildTree(str);
    int hh = HashString(str);

    // Open file
    CFile cf;
    CString fname;
    fname.Format("%s%s%x.txt", dataroot, "Coco\\", hh);

    if(cf.Open(fname, CFile::modeRead))
       {
       CString str;
       CArchive ar( &cf, CArchive::load);

       // Read the directory line
       ar.ReadString(str);

       while(TRUE)
            {
            if(!ar.ReadString(str))
                break;

            ucount++;
            if(!(ucount%100))
                {
                CString num;
                num.Format( "Copy Coco line %d", ucount);
                message(num);
                }
            strclip += str + "\r\n";
            }
       }

    //P2N("strclip=%s\r\n", strclip);

    HANDLE hMem;
    hMem = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE,
                strclip.GetLength()+1);
    if(!hMem)
        {
        AfxMessageBox("Cannot get mem for clipboard");
        return;
        }
    char *ptr = (char*)GlobalLock(hMem);
    if(!ptr)
        {
        AfxMessageBox("Cannot get ptr for clipboard");
        GlobalFree(hMem);
        return;
        }

    strcpy(ptr, (const char *)strclip);
    GlobalUnlock(hMem);

    // Traditional clipboard operation
    if(AfxGetMainWnd()->OpenClipboard())
        {
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();

        CString num; num.Format("Copied %d lines from COCO to clipboard", ucount);
        message(num);
        }
    else
        {
        AfxMessageBox("Cannot open clipboard");
        GlobalFree(hMem);
        }
}

void Coco::OnButton12()

{
    int ucount = 0;
    HTREEITEM h1;

    if(!(h1 = m_tree.GetSelectedItem() ))
        {
        AfxMessageBox("Please select item first");
        return;
        }


    if(!AfxGetMainWnd()->OpenClipboard())
        {
        AfxMessageBox("Cannot open clipboard");
        return;
        }

    HANDLE hMem = GetClipboardData(CF_TEXT);
    CloseClipboard();

    // Nothing there
    if(!hMem)
        {
        message ("Empty clipboard");
        return;
        }

    char *ptr = (char*)GlobalLock(hMem);
    if(!ptr)
        {
        message ("Empty clipboard");
        return;
        }

    int len = strlen(ptr);

    CString str; BuildTree(str);
    int hh = HashString(str);

    // Open file
    CFile cf;
    char crlf[] = "\r\n";
    CString fname;
    fname.Format("%s%s%x.txt", dataroot, "Coco\\", hh);

    if(cf.Open(fname, CFile::modeReadWrite))
        {
        cf.Seek(0, CFile::end);
        cf.Write(ptr, len);
        }
    CString num; num.Format("Pasted %d bytes", len);
    message(num);
}
