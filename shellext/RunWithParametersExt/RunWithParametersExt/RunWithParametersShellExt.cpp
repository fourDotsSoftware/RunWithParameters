// RunWithParametersShellExt.cpp : Implementation of CRunWithParametersShellExt

#include "stdafx.h"
#include "RunWithParametersShellExt.h"
#include <atlconv.h>  // for ATL string conversion macros
#include "Resource.h"
#include <atlcom.h>
#include <atlstr.h>
#include <stdio.h>
#include <tchar.h>
#define BUFSIZE 65536
#include <cwchar> 

//#include "ShobjIdl.h"
//#include "Shellapi.h"

// CRunWithParametersShellExt
CRunWithParametersShellExt::CRunWithParametersShellExt()
{
	m_hUnlockBmp = LoadBitmap( _AtlBaseModule.GetModuleInstance()  ,
                           MAKEINTRESOURCE(IDB_BITMAP1) );
}


STDMETHODIMP CRunWithParametersShellExt::Initialize ( 
  LPCITEMIDLIST pidlFolder,
  LPDATAOBJECT pDataObj,
  HKEY hProgID )
{
FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
STGMEDIUM stg = { TYMED_HGLOBAL };
HDROP     hDrop;

    // Look for CF_HDROP data in the data object.
    if ( FAILED( pDataObj->GetData ( &fmt, &stg ) ))
        {
        // Nope! Return an "invalid argument" error back to Explorer.
        return E_INVALIDARG;
        }

    // Get a pointer to the actual data.
    hDrop = (HDROP) GlobalLock ( stg.hGlobal );

    // Make sure it worked.
    if ( NULL == hDrop )
        return E_INVALIDARG;

    // Sanity check - make sure there is at least one filename.
UINT uNumFiles = DragQueryFile ( hDrop, 0xFFFFFFFF, NULL, 0 );
HRESULT hr = S_OK;

    if ( 0 == uNumFiles )
        {
        GlobalUnlock ( stg.hGlobal );
        ReleaseStgMedium ( &stg );
        return E_INVALIDARG;
        }

	bool isok=false;

	std::vector<LPCWSTR>::iterator it;
	it = m_lsFiles2.begin();		

	for (int k=0;k<uNumFiles;k++)
	{
		LPWSTR m_szFile3=new WCHAR[MAX_PATH];

		if ( 0 != DragQueryFile ( hDrop, k, (LPWSTR) m_szFile3, MAX_PATH ) )
		{
			isok=true;
			it=m_lsFiles2.insert ( it , m_szFile3 );
			//m_lsFiles2.a.push_back(m_szFile);
			
		}
	}
    // Get the name of the first file and store it in our member variable m_szFile.
    //if ( 0 == DragQueryFile ( hDrop, 0, m_szFile, MAX_PATH ) )
    //hr = E_INVALIDARG;

	if (!isok)
	{
		hr = E_INVALIDARG;
	}

    GlobalUnlock ( stg.hGlobal );
    ReleaseStgMedium ( &stg );

    return hr;


}

HRESULT CRunWithParametersShellExt::QueryContextMenu (
  HMENU hmenu, UINT uMenuIndex, UINT uidFirstCmd,
  UINT uidLastCmd, UINT uFlags )
{
  // If the flags include CMF_DEFAULTONLY then we shouldn't do anything.

  if ( uFlags & CMF_DEFAULTONLY )
    return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 0 );

	UINT uID = uidFirstCmd;
	UINT upos=uMenuIndex;
	
// Insert the submenu into the ctx menu provided by Explorer.      
	
	TCHAR name[256];
	LONG res=ERROR_SUCCESS;
	CRegKey rkMenuItems;
	
	DWORD dwErr = ERROR_PATH_NOT_FOUND;
	DWORD dwErrMenuItems = ERROR_PATH_NOT_FOUND;
	TCHAR prch[sizeof(_T("Software\\4dots Software\\RunWithParameters\\MenuItems"))]
	=_T("Software\\4dots Software\\RunWithParameters\\MenuItems");

//	lstrcat(prch,name);	
	dwErrMenuItems = rkMenuItems.Open(HKEY_CURRENT_USER, prch, KEY_QUERY_VALUE);						
	
	// if (m_lsFiles2.size()<=0)
  //{
	//MessageBox ( NULL , _T("Size 0"), _T("SimpleShlExt"),MB_ICONINFORMATION );
  //}
  //else if (m_lsFiles2.size()==1)
  //{
	//MessageBox ( NULL , _T("Size 1"), _T("SimpleShlExt"),MB_ICONINFORMATION );
  //}
  //else if (m_lsFiles2.size()>1)
  //{
	//MessageBox ( NULL , _T("Size >1"), _T("SimpleShlExt"),MB_ICONINFORMATION );
  //}
     	
		TCHAR prcaption[256]={0};
		ULONG prsize=sizeof(prcaption);

		dwErr = ERROR_PATH_NOT_FOUND;
		if (dwErrMenuItems == ERROR_SUCCESS)
		{
			//MessageBox ( NULL , _T("MenuItems Suc"), _T("SimpleShlExt"),MB_ICONINFORMATION );

			dwErr = rkMenuItems.QueryStringValue(_T("Copy File Contents"), prcaption, &prsize);							
			
			if (dwErr==ERROR_SUCCESS)
			{
			//MessageBox ( NULL , _T("Copy File Contents Suc"), _T("SimpleShlExt"),MB_ICONINFORMATION );
			}
		}
		
		if ((dwErr == ERROR_SUCCESS && (lstrcmp(prcaption,_T("True"))==0) )
			|| dwErr!=ERROR_SUCCESS)
		{					
			InsertMenu ( hmenu, iRunWithParameters=upos++, MF_BYPOSITION, uID++, _T("Copy Text Contents"));				

			if ( NULL != m_hUnlockBmp) 
			SetMenuItemBitmaps ( hmenu, upos-1, MF_BYPOSITION, m_hUnlockBmp, m_hUnlockBmp );
		}
			
		dwErr = ERROR_PATH_NOT_FOUND;

		TCHAR prcaption2[256]={0};
		ULONG prsize2=sizeof(prcaption);
		
		if (dwErrMenuItems == ERROR_SUCCESS)
		{			
			dwErr = rkMenuItems.QueryStringValue(_T("Copy File Contents with Encoding"), prcaption2, &prsize2);

			if (dwErr==ERROR_SUCCESS)
			{
				//MessageBox ( NULL , _T("Copy File Contents Enc Suc"), _T("SimpleShlExt"),MB_ICONINFORMATION );
			}
		}	

		if ((dwErr == ERROR_SUCCESS && (lstrcmp(prcaption2,_T("True"))==0))
			|| dwErr!=ERROR_SUCCESS) 
		{
			InsertMenu ( hmenu,iRunWithParametersEncoding= upos++, MF_BYPOSITION, uID++, _T("Copy Text Contents with Encoding"));
			SetMenuItemBitmaps ( hmenu, upos-1, MF_BYPOSITION, m_hUnlockBmp, m_hUnlockBmp );
		}

    return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, uID - uidFirstCmd );
	
	//return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 1 );
}


HRESULT CRunWithParametersShellExt::GetCommandString (
  UINT_PTR idCmd, UINT uFlags, UINT* pwReserved,
//  UINT idCmd, UINT uFlags, UINT* pwReserved,
  LPSTR pszName, UINT cchMax )

{
USES_CONVERSION;		

return E_INVALIDARG;
  // Check idCmd, it must be 0 since we have only one menu item.

 // if ( 0 != idCmd )
  //  return E_INVALIDARG;
//	return E_FAIL;
 
  // If Explorer is asking for a help string, copy our string into the

  // supplied buffer.
  
  if (uFlags==GCS_VALIDATE)
  {
	return NOERROR;
  }
  else if ( uFlags == GCS_HELPTEXT || uFlags==GCS_HELPTEXTW)
    {
    LPCTSTR szText = _T("Copy File Contents");	

	//HINSTANCE hInst = AfxGetInstanceHandle();
    if ( uFlags & GCS_UNICODE )
      {
      // We need to cast pszName to a Unicode string, and then use the

      // Unicode string copy API.

      lstrcpynW ( (LPWSTR) pszName, T2CW(szText), cchMax );
      }
    else
      {
      // Use the ANSI string copy API to return the help string.

      lstrcpynA ( pszName, T2CA(szText), cchMax );
      }
 
    return S_OK;
	//return NOERROR;
    }
	else if ( uFlags == GCS_VERB || uFlags==GCS_VERBW)
    {
	//	MessageBox ( NULL , _T("gcs_verb"), _T("SimpleShlExt"),MB_ICONINFORMATION );
    LPCTSTR szText = _T("RunWithParameters");
 
    if ( uFlags & GCS_UNICODE )
      {
      // We need to cast pszName to a Unicode string, and then use the

      // Unicode string copy API.

      lstrcpynW ( (LPWSTR) pszName, T2CW(szText), cchMax );
      }
    else
      {
      // Use the ANSI string copy API to return the help string.

      lstrcpynA ( pszName, T2CA(szText), cchMax );
      }
 
    return S_OK;
	//return NOERROR;
    }
 
   
  //return E_INVALIDARG;
  return S_OK;
}

HRESULT CRunWithParametersShellExt::InvokeCommand(
  LPCMINVOKECOMMANDINFO pCmdInfo)
{
  // If lpVerb really points to a string, ignore this function call and bail out.
/*
	BOOL fEx = FALSE;
    BOOL fUnicode = FALSE;

    if(pCmdInfo->cbSize == sizeof(CMINVOKECOMMANDINFOEX))
    {
        fEx = TRUE;
        if((lpcmi->fMask & CMIC_MASK_UNICODE))
        {
            fUnicode = TRUE;
        }
    }

    if( !fUnicode && HIWORD(pCmdInfo->lpVerb))
    {
		  if ( 0 != HIWORD( pCmdInfo->lpVerb) )
			return E_INVALIDARG;
		/*
        if(StrCmpIA(lpcmi->lpVerb, m_pszVerb))
        {
            return E_FAIL;
        }*/
   // }
/*
    else if( fUnicode && HIWORD(((CMINVOKECOMMANDINFOEX *) pCmdInfo)->lpVerbW))
    {
        if(StrCmpIW(((CMINVOKECOMMANDINFOEX *)lpcmi)->lpVerbW, m_pwszVerb))
        {
            return E_FAIL;
        }
    }

    else if(LOWORD(lpcmi->lpVerb) != IDM_DISPLAY)
    {
        return E_FAIL;
    }
*/
	//MessageBox ( NULL ,_T("Invokecmd0"), _T("SimpleShlExt"),MB_ICONINFORMATION );

  if ( 0 != HIWORD( pCmdInfo->lpVerb) )
    return E_INVALIDARG;
 
  //MessageBox ( NULL ,_T("Invokecmd"), _T("SimpleShlExt"),MB_ICONINFORMATION );

	HANDLE hFile;
	HANDLE hTempFile;
	DWORD dwRetVal;
	DWORD dwBytesRead;
	DWORD dwBytesWritten;
	DWORD dwBufSize = BUFSIZE;
	UINT uRetVal;
	WCHAR szTempName[MAX_PATH] = TEXT("just_dummy");
	//LPWSTR buffer = malloc(sizeof(BUFSIZE));
	WCHAR lpPathBuffer[MAX_PATH] = TEXT("just_dummy");
	BOOL fSuccess;

  // Get the command index - the only valid one is 0.  		

	
// Get the temp path.
dwRetVal = GetTempPath(dwBufSize, // length of the buffer
lpPathBuffer); // buffer for path
if (dwRetVal > dwBufSize)
{
return E_INVALIDARG;
}
else
{

lstrcatW(lpPathBuffer,_T("RunWithParameterstmp.txt"));


//MessageBox ( NULL , lpPathBuffer, _T("SimpleShlExt"),
 //                  MB_ICONINFORMATION );


}

/*
// Create a temporary file.
uRetVal = GetTempFileName(lpPathBuffer, // directory for tmp files
L"NEW", // temp file name prefix
0, // create unique name
szTempName); // buffer for the name

MessageBox ( NULL , szTempName, _T("SimpleShlExt"),
                   MB_ICONINFORMATION );


if (uRetVal == 0)
{
return E_INVALIDARG;
}

MessageBox ( NULL , _T("TEMPFILEGET"), _T("SimpleShlExt"),
                   MB_ICONINFORMATION );
*/
// Create the new file to write the upper-case version to.
hTempFile = CreateFile((LPTSTR) lpPathBuffer, // file name
GENERIC_READ | GENERIC_WRITE, // open r-w
0, // do not share
NULL, // default security
CREATE_ALWAYS, // overwrite existing
FILE_ATTRIBUTE_NORMAL,// normal file
NULL); // no template
 

//MessageBox ( NULL , _T("TEMPFILECREATED"), _T("SimpleShlExt"),MB_ICONINFORMATION );

if (hTempFile == INVALID_HANDLE_VALUE)
{
	return E_INVALIDARG;
}


  int iVerb=LOWORD(pCmdInfo->lpVerb);

   WCHAR sParam[40000];
   lstrcpyW(sParam,_T(" "));
/*
   lstrcpyW(sParam,_T("-Imgs:"));
   lstrcpyW(sParam,_T("\""));
   lstrcatW(sParam,m_szFile);
   lstrcatW(sParam,_T("\""));
*/

  for (int k=0;k<m_lsFiles2.size();k++)
  {
	//MessageBox ( NULL , (LPCWSTR)m_lsFiles2[k], _T("SimpleShlExt"),
	//				MB_ICONINFORMATION );

   lstrcatW(sParam,_T("\""));
   lstrcatW(sParam,(WCHAR*)m_lsFiles2[k]);
   lstrcatW(sParam,_T("\" "));
  }

  bool only_one_file=true;

  if (m_lsFiles2.size()>1)
  {
	only_one_file=false;
  }

 

 // lstrcatW(sParam,_T(" -Cmd:"));

  //  switch ( LOWORD( pCmdInfo->lpVerb ) )

  WCHAR cmd[100];


  //MessageBox ( NULL ,cstr , _T("SimpleShlExt"),MB_ICONINFORMATION );	    

if (iVerb==iRunWithParameters)
{
lstrcatW(sParam,_T(" -RunWithParameters"));
}
else if (iVerb==iRunWithParametersEncoding)
{
	lstrcatW(sParam,_T(" -RunWithParametersEncoding"));
}

//lstrcatW(sParam,cmd);

      
	//MessageBox ( NULL , sParam, _T("SimpleShlExt"),MB_ICONINFORMATION );	    

		WCHAR szMsg[MAX_PATH + 32];
	    CRegKey reg;
        LONG    lRet;

        lRet = reg.Open ( HKEY_LOCAL_MACHINE,
                          _T("Software\\4dots Software\\RunWithParameters"),KEY_QUERY_VALUE);

		//MessageBox ( NULL , _T("test"), _T("SimpleShlExt"),
        //         MB_ICONINFORMATION );	    

		if (lRet!=ERROR_SUCCESS)
		{
			return E_UNEXPECTED;
		}

		TCHAR szFp[MAX_PATH];		
		DWORD dwSizeFp = sizeof(szFp) / sizeof(TCHAR); // # of characters in the buffer 
		
		lRet=reg.QueryStringValue(_T("InstallationDirectory"),szFp,&dwSizeFp);
 
		if (lRet!=ERROR_SUCCESS)
		{
			return E_UNEXPECTED;
		}

		//MessageBox ( NULL , _T("test2"), _T("SimpleShlExt"),
         //        MB_ICONINFORMATION );	    

		
		//MessageBox ( pCmdInfo->hwnd, m_szFile, _T("SimpleShlExt"),
          //         MB_ICONINFORMATION );


		//ShellExecute(NULL, _T("open"), _T("test.txt"), NULL, _T("."),SW_SHOWNORMAL);
		TCHAR szFp2[MAX_PATH];
		//szFp=lstrcat(szFp,_T("ImgTransformer.exe"));

		
		wcscat_s(szFp,_T("\\RunWithParameters.exe") );

		//MessageBox ( pCmdInfo->hwnd, szFp, _T("SimpleShlExt"),
          //         MB_ICONINFORMATION );
		
		
		//28.9.11 lstrcpyW(szMsg,_T("-showunlockfile "));

		
		lstrcpyW(szFp2,_T("\""));
		lstrcatW(szFp2,szFp);
		lstrcatW(szFp2,_T("\""));
		

		WCHAR szTempParam[MAX_PATH];
		lstrcpyW(szTempParam,_T("-TempFile:\""));
		lstrcatW(szTempParam,lpPathBuffer);
		lstrcatW(szTempParam,_T("\""));

		//wcscat_s(szMsg,_T("-showunlockfile "));
		//wcscat_s(szMsg,m_szFile);

		//wsprintf ( szMsg, _T("-showunlockfile "), m_szFile );
		//szMsg=lstrcat(_T("-showunlockfile "),m_szFile);
				
		//MessageBox ( pCmdInfo->hwnd, szMsg, _T("SimpleShlExt"),
          //         MB_ICONINFORMATION );

		//1ShellExecute(NULL, _T("open"), szFp, szMsg, _T("."), SW_SHOWNORMAL);


		//MessageBox ( NULL , sParam, _T("SimpleShlExt"),
       //          MB_ICONINFORMATION );	    

		//MessageBox ( NULL , szFp2, _T("SimpleShlExt"),
        //         MB_ICONINFORMATION );	    

	//	ShellExecute(NULL, _T("open"), szFp2, sParam, _T("."), SW_SHOWNORMAL);

		
	//MessageBox ( pCmdInfo->hwnd, szTempName, _T("SimpleShlExt"),
	//                   MB_ICONINFORMATION );
		
		//MessageBox ( NULL, _T("OK1"), _T("SimpleShlExt"),MB_ICONINFORMATION );

		fSuccess = WriteFile(hTempFile,
		sParam,
		std::wcslen (sParam)*sizeof(wchar_t),
		&dwBytesWritten,
		NULL);

		//MessageBox ( NULL, _T("OK2"), _T("SimpleShlExt"),MB_ICONINFORMATION );

		CloseHandle (hTempFile);

		//MessageBox ( NULL, _T("OK3"), _T("SimpleShlExt"),MB_ICONINFORMATION );
		if (!fSuccess)
		{
		return E_INVALIDARG;
		}
		//removeShellExecute(NULL, _T("open"), szFp2, sParam, _T("."), SW_SHOWNORMAL);
        ShellExecute(NULL, _T("open"), szFp2, szTempParam, _T("."), SW_SHOWNORMAL);

		//wsprintf ( szMsg, _T("The selected file was:\n\n%s"), m_szFile );
 
		//MessageBox ( NULL, _T("OK"), _T("SimpleShlExt"),MB_ICONINFORMATION );
 
      return S_OK;
   }


  


