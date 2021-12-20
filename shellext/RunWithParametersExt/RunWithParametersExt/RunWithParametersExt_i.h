

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Apr 20 13:09:53 2012
 */
/* Compiler settings for .\RunWithParametersExt.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RunWithParametersExt_i_h__
#define __RunWithParametersExt_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRunWithParametersShellExt_FWD_DEFINED__
#define __IRunWithParametersShellExt_FWD_DEFINED__
typedef interface IRunWithParametersShellExt IRunWithParametersShellExt;
#endif 	/* __IRunWithParametersShellExt_FWD_DEFINED__ */


#ifndef __RunWithParametersShellExt_FWD_DEFINED__
#define __RunWithParametersShellExt_FWD_DEFINED__

#ifdef __cplusplus
typedef class RunWithParametersShellExt RunWithParametersShellExt;
#else
typedef struct RunWithParametersShellExt RunWithParametersShellExt;
#endif /* __cplusplus */

#endif 	/* __RunWithParametersShellExt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IRunWithParametersShellExt_INTERFACE_DEFINED__
#define __IRunWithParametersShellExt_INTERFACE_DEFINED__

/* interface IRunWithParametersShellExt */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRunWithParametersShellExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6464AA1-28BB-42a9-B67B-59A8E5AE27C0")
    IRunWithParametersShellExt : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IRunWithParametersShellExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRunWithParametersShellExt * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRunWithParametersShellExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRunWithParametersShellExt * This);
        
        END_INTERFACE
    } IRunWithParametersShellExtVtbl;

    interface IRunWithParametersShellExt
    {
        CONST_VTBL struct IRunWithParametersShellExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRunWithParametersShellExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRunWithParametersShellExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRunWithParametersShellExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRunWithParametersShellExt_INTERFACE_DEFINED__ */



#ifndef __RunWithParametersExtLib_LIBRARY_DEFINED__
#define __RunWithParametersExtLib_LIBRARY_DEFINED__

/* library RunWithParametersExtLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RunWithParametersExtLib;

EXTERN_C const CLSID CLSID_RunWithParametersShellExt;

#ifdef __cplusplus

class DECLSPEC_UUID("AA6347ED-CD79-40f0-88EB-BA54125B9E81")
RunWithParametersShellExt;
#endif
#endif /* __RunWithParametersExtLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


