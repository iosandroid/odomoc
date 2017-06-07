

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Jun 07 07:47:32 2017
 */
/* Compiler settings for ScannerApp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

#ifndef __ScannerApp_i_h__
#define __ScannerApp_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IScanner_FWD_DEFINED__
#define __IScanner_FWD_DEFINED__
typedef interface IScanner IScanner;

#endif 	/* __IScanner_FWD_DEFINED__ */


#ifndef __Scanner_FWD_DEFINED__
#define __Scanner_FWD_DEFINED__

#ifdef __cplusplus
typedef class Scanner Scanner;
#else
typedef struct Scanner Scanner;
#endif /* __cplusplus */

#endif 	/* __Scanner_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IScanner_INTERFACE_DEFINED__
#define __IScanner_INTERFACE_DEFINED__

/* interface IScanner */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IScanner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D1382FE6-5650-4DBD-A036-5A8B1443A193")
    IScanner : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Scan( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IScannerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScanner * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScanner * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScanner * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScanner * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScanner * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScanner * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScanner * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Scan )( 
            IScanner * This);
        
        END_INTERFACE
    } IScannerVtbl;

    interface IScanner
    {
        CONST_VTBL struct IScannerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScanner_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScanner_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScanner_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScanner_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IScanner_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IScanner_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IScanner_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IScanner_Scan(This)	\
    ( (This)->lpVtbl -> Scan(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IScanner_INTERFACE_DEFINED__ */



#ifndef __ScannerAppLib_LIBRARY_DEFINED__
#define __ScannerAppLib_LIBRARY_DEFINED__

/* library ScannerAppLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ScannerAppLib;

EXTERN_C const CLSID CLSID_Scanner;

#ifdef __cplusplus

class DECLSPEC_UUID("1696978A-B108-47E6-A905-677A66BDBB9B")
Scanner;
#endif
#endif /* __ScannerAppLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


