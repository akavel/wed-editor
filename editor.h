

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Record keystrokes keypress flag

#define R_DOWN      1
#define R_CHAR      2
#define R_UP        3

#define R_SYSDOWN   4
#define R_SYSCHAR   5
#define R_SYSUP     6

// Diff coloring flags

#define DIFF_NONE   0
#define DIFF_DEL    1
#define DIFF_ADD    2
#define DIFF_CHG    3

void DeleteLine(CWedView *cv1, int drow);
void CopyToHold(CWedView *v1, int cut);
void InsertHold(CWedView *v1);
void addchar(CWedView *v1, char chh);
void YieldToWin();
void CopyToClip(CWedView *v1, int cut);
void PasteClip(CWedView *v1);
void PlayMacro(CWedView *v1);
CWedDoc*  GetDocFromPath(const char *str);

void TabbedPos(CString &str, int col, int *real, int *ontab);
void OnTabbed(CString &str, int ontab);
void UnTabbedPos(CString &str, int pos, int *real, int *ontab);
void ExpandTabs(CString &str);
int	scr2str(CString &str, int col);
int	str2scr(CString &str, int col);

void DeleteSelection(CWedView *v1);

void SubstStr(CString &str, CString src, CString sub);
int	 WalkStr(CString &str, CString sub);
void SelWord(CString &str, int col, int *begin, int *end, int scr = 0);

void PasteData(CWedView *v1, int source);
void PasteHold(CWedView *v1);
void PasteClip(CWedView *v1);

void CopyData(CWedView *v1, int cut, int target);
void CopyToClip(CWedView *v1, int cut);
void CopyToHold(CWedView *v1, int cut);

void Spell(CWedView *v1,  const char *dic,   const char *idx, 
		   const char *cus,   int flag);

int     CheckLine(CWedView *v1, int row, int flag);
int     CheckWord(CWedView *v1, CString &instr, CString &repl);


const char *GetRegStr();
int		PutRegStr(const char *str, const char *pass);

unsigned int    str_esc(const char *str, char *out, int lim);

unsigned long   hextol(char *str);
unsigned long   bintol(char *str);
unsigned long   otol(char *str);
unsigned int    hextoi(char *str, int lim);
unsigned int    dectoi(char *str, int lim);
unsigned int    hexlen(char *str);
unsigned int    declen(char *str);
void    long_to_bin_str(unsigned long num, char *str);

void    TabSelection(CWedView *v1, int shh);



// EOF