/////////////////////////////////////////////////////////////////////////////
// misc.h : Services for the WED application
//
/////////////////////////////////////////////////////////////////////////////
// Misc app services for Wed


#pragma pack(1)

#ifdef      _MAX_PATH                      /* include only if we have FILE */

typedef struct                                          /* path components */
    {
    char    path[_MAX_PATH];
    char    drive[_MAX_DRIVE];
    char    dir[_MAX_DIR];
    char    fname[_MAX_FNAME];
    char    ext[_MAX_EXT];
    char    dummy[_MAX_FNAME];
    } PATH;
#endif

#pragma pack()


CMenu 	*GetTemplateMenu();
void	OpenSource(CString &dir);
void	SaveSourceAs(CString &dir);

void 	SaveAllDocs();
void 	message(const char * str);
void 	rowcol(const char * str);
void 	filesize(const char * str);
void 	hold(const char * str);
void 	mac(const char * str);
void 	mode(const char * str);
void	PathToFname(CString &docname);
void	PathToDir(CString &docname);
void	ShortenPath(CString &str, int len);
int		HashString(const char *name);
int		HashZString(const char *name);
void    YieldToWin();
int     YieldToWinEx();
int	 	FindNumOfChar(CString &str, CString &mus, int start);
int     create_full_dir(const char *fullname);
int     is_valid_path(char *str);
BOOL	GetSpecialFolder(UINT SpecialFolder, CString &SpecialFolderString);


// EOF



