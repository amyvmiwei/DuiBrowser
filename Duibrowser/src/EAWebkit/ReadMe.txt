2011年6月30日改动

1. EAWebKitSupportPackages\EAIOEAWebKit\local\include\EAIO\EAStream.h
WINCE移植，Line： 53
原：
#include <sys/types.h>
改动为：
#if defined(EA_PLATFORM_WINCE)
	#include <windef.h>
	#include <winnt.h>
#else
    #include <sys/types.h>
#endif

2. EAWebKitSupportPackages\EAIOEAWebKit\local\include\EAIO\EAFileBase.h
Line: 49
原：

#include <sys/types.h> // Definition of off_t.

改动为：
#if defined(EA_PLATFORM_WINCE)
	#include <windef.h>
	#include <winnt.h>

	typedef long off_t;
#else
    #include <sys/types.h>
#endif

3. EAWebKitSupportPackages\EAIOEAWebKit\local\source\EAFileUtil.cpp
Line:  66
添加以下代码：
#elif defined(EA_PLATFORM_WINCE)

    #include <windows.h>
    #include <shlobj.h>
    #include <objbase.h>

    #ifdef _MSC_VER
        #pragma comment(lib, "ole32.lib")	// Required for CoInitializeEx, etc.
    #endif

4. EAWebKitSupportPackages\EAIOEAWebKit\local\source\EAFileUtil.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

5. EAWebKitSupportPackages\EAIOEAWebKit\local\include\EAIO\EAFileStream.h
Line : 68

原：
#if !defined(EA_PLATFORM_XENON) && !defined(EA_PLATFORM_PS3) && !defined(EA_PLATFORM_WINDOWS)

改动为：
#if !defined(EA_PLATFORM_XENON) && !defined(EA_PLATFORM_PS3) && !defined(EA_PLATFORM_WINDOWS) && !defined(EA_PLATFORM_WINCE)

Line : 195
原：
#if defined(EA_PLATFORM_WINDOWS) || defined(EA_PLATFORM_XENON)
改动为：
#if defined(EA_PLATFORM_WINDOWS) || defined(EA_PLATFORM_XENON) || defined(EA_PLATFORM_WINCE)


6: EAWebKitSupportPackages\EAIOEAWebKit\local\source\EAFileStream.cpp
Line: 41
原：
#if defined(EA_PLATFORM_WINDOWS) || defined(EA_PLATFORM_XENON)
改动为：
#if defined(EA_PLATFORM_WINDOWS) || defined(EA_PLATFORM_XENON) || defined(EA_PLATFORM_WINCE)

7:EAWebKitSupportPackages\EAIOEAWebKit\local\source\Win32\EAFileStreamWin32.cpp
Line： 50
原：
#elif defined(EA_PLATFORM_WINDOWS)
改动为：
#elif defined(EA_PLATFORM_WINDOWS) || defined(EA_PLATFORM_WINCE)

8: EAWebKitSupportPackages\EAIOEAWebKit\local\source\Win32\EAFileStreamWin32.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

9: include\EAWebKit\EAWebKitConfig.h
Line: 255
添加以下代码：
#if defined(EA_DLL) && defined(EA_PLATFORM_WINCE)
	#undef EAWEBKIT_WINDOWS_DLL
	#define EAWEBKIT_WINDOWS_DLL 1
#else
	#define EAWEBKIT_WINDOWS_DLL 0
#endif

10: include\EAWebKit\EAWebKitPlatformSocketAPI.h
Line: 48
添加以下代码：
#elif defined(EA_PLATFORM_WINCE)
	typedef int socklen_t;
	typedef int platform_ssize_t;



11. EAWebkit工程中只要是涉及 EA_PLATFORM_WINDOWS都做了改动

12. source\EAWebKitFileSystem.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

13. source\EAWebKitMemory.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

14. Webkit-owb\BAL\OWBAL\Concretizations\Facilities\EA\BCFileSystemEA.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的


15. Webkit-owb\BAL\OWBAL\Concretizations\Facilities\EA\BCSystemTimeEA.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

16. Webkit-owb\BAL\OWBAL\Concretizations\Internationalization\EA\BCUnicodeEA.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

17. Webkit-owb\BAL\WKAL\Concretizations\Network\EA\BCResourceHandleManagerEA.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

18. Webkit-owb\BAL\WKAL\Concretizations\Network\EA\BCTransportHandlerDirtySDK.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

19. Webkit-owb\BAL\WKAL\Concretizations\Widgets\EA\BCCursorEA.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

20. Webkit-owb\WebKit\OrigynWebBrowser\Api\WebView.cpp
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

21. Webkit-owb\WebKit\OrigynWebBrowser\WebCoreSupport\WebFrameLoaderClient.cpp 和WebFrameLoaderClient.h
	Webkit-owb\WebKit\OrigynWebBrowser\Api\WebFrame.cpp
为了消除ResourceRequest定义的二义性，改用WebCore::ResourceRequest

22. Webkit-owb\BAL\OWBAL\Concretizations\Types\EA\BCThreadingEA.h
文件中用宏EA_PLATFORM_WINCE括起来的都是新添加的

23. Webkit-owb\WebKit\OrigynWebBrowser\Api\DefaultPolicyDelegate.cpp
Line : 44
原来
#include <sys/types.h> 
#include <sys/stat.h> 
改动为：
#if defined(EA_PLATFORM_WINCE)
	#include <windows.h> 
#else
	#include <sys/types.h> 
	#include <sys/stat.h> 
#endif

Line: 145
原来：
        if (stat(url.utf8().data(), &st))
            isDirectory = S_ISDIR(st.st_mode);
改动为：
		#if defined(EA_PLATFORM_WINCE)
			WIN32_FIND_DATA findData = {0};
			HANDLE fileHandle = FindFirstFileW(url.charactersWithNullTermination(), &findData); 
			if (fileHandle != INVALID_HANDLE_VALUE)
			{
				if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					isDirectory = true;

				FindClose(fileHandle);
			}
		#else
			struct stat st;
			if (stat(url.utf8().data(), &st))
				isDirectory = S_ISDIR(st.st_mode);
		#endif


24. Webkit-owb\WebKit\OrigynWebBrowser\Api\WebDownload.cpp
Line: 44
原来：
#include <sys/stat.h>
#include <sys/types.h>
改动成：
#if defined(EA_PLATFORM_WINCE)
#else
	#include <sys/stat.h>
	#include <sys/types.h>
#endif

25. Webkit-owb\BAL\OWBAL\Concretizations\Memory\WK\BCFastMallocWK.h 和 BCFastMallocWK.cpp
添加了fastStrDup的实现，fastStrDup主要使用在Webkit-owb\WebCore\plugins\PluginStream.cpp Line: 137 和 139

26. Webkit-owb\WebCore\plugins\PluginStream.cpp
Line 41 添加引用： #include <wtf/FastMalloc.h>
Line 138 和 140, 把strdup替换成fastStrDup


27. Webkit-owb\BAL\OWBAL\Concretizations\Types\WK\BCStringExtrasWK.h
Line: 49 把strnicmp替换成_strnicmp
并添加以下代码：
#if PLATFORM(WINCE_OS)

inline int strnicmp(const char* string1, const char* string2, size_t count)
{
    return _strnicmp(string1, string2, count);
}

inline int stricmp(const char* string1, const char* string2)
{
    return _stricmp(string1, string2);
}

inline char* strdup(const char* strSource)
{
    return _strdup(strSource);
}

#endif

同时添加以下代码

inline double wtf_vsnprintf(char* buffer, size_t count, const char* format, va_list args)
{
    int result = _vsnprintf(buffer, count, format, args);

    // In the case where the string entirely filled the buffer, _vsnprintf will not
    // null-terminate it, but vsnprintf must.
    if (count > 0)
        buffer[count - 1] = '\0';

    return result;
}

// Work around a difference in Microsoft's implementation of vsnprintf, where 
// vsnprintf does not null terminate the buffer. WebKit can rely on the null termination.
#define vsnprintf(buffer, count, format, args) wtf_vsnprintf(buffer, count, format, args)



28. Webkit-owb\WebCore\bridge\npruntime.cpp
Line: 81 和142， 把strdup替换成fastStrDup

29: Webkit-owb\BAL\Base\wtf\Platform.h
Line: 62
增加：
/* OS(WINCE) - Windows CE; note that for this platform OS(WINDOWS) is also defined */
#if defined(_WIN32_WCE)
#define WTF_OS_WINCE 1
#endif

Line 314:
原来：
#define HAVE_FLOAT_H 1
#define HAVE_SYS_TIMEB_H 1
#define HAVE_VIRTUALALLOC 1     // To consider: Disable this because we don't want WebKit using this behind our backs.
改动为：
#if PLATFORM(WINCE_OS)
#define HAVE_ERRNO_H 0
#else
#define HAVE_FLOAT_H 1
#define HAVE_SYS_TIMEB_H 1
#define HAVE_VIRTUALALLOC 1     // To consider: Disable this because we don't want WebKit using this behind our backs.
#endif

30. Webkit-owb\JavaScriptCore\kjs\DateMath.cpp
Line: 685, 
原来：
    errno = 0;
    long day = strtol(dateString, &newPosStr, 10);
    if (errno)
        return NaN;

改动： 以及本文件中所有使用errno的地方
#if defined(EA_PLATFORM_WINCE)
    long result = strtol(string, &newPosStr, base);
    // Avoid the use of errno as it is not available on Windows CE
    if (string == newPosStr || *result == LONG_MIN || *result == LONG_MAX)
        return NaN;
#else
    errno = 0;
    long day = strtol(dateString, &newPosStr, 10);
    if (errno)
        return NaN;
#endif

LINE: 349
原来
    #elif PLATFORM(WIN_OS) || PLATFORM(XBOX) || PLATFORM(PS3) 
        #if COMPILER(MSVC7) || PLATFORM(PS3) 
            *localTM = *localtime(localTime);
        #else
            localtime_s(localTM, localTime);
        #endif
    #else
        localtime_r(localTime, localTM);
    #endif

改动为：
    #elif PLATFORM(WIN_OS) || PLATFORM(XBOX) || PLATFORM(PS3) || PLATFORM(WINCE_OS)
        #if COMPILER(MSVC7) || PLATFORM(PS3) || PLATFORM(WINCE_OS)
            *localTM = *localtime(localTime);
        #else
            localtime_s(localTM, localTime);
        #endif
    #else
        localtime_r(localTime, localTM);
    #endif

Line: 301， 并添加头文件： #include <windows.h>
原来：
    #if PLATFORM(WIN_OS) || PLATFORM(XBOX)
        // FIXME: the implementation for Windows is only millisecond resolution.
        #if COMPILER(BORLAND)
            struct timeb timebuffer;
            ftime(&timebuffer);
        #else
            struct _timeb timebuffer;
            _ftime(&timebuffer);
        #endif

        double utc = timebuffer.time * msPerSecond + timebuffer.millitm;

改动为：

    #if PLATFORM(WIN_OS) || PLATFORM(XBOX)
		#if defined(EA_PLATFORM_WINCE)
			FILETIME      ft;
			LARGE_INTEGER li;

			SYSTEMTIME systime = {0};
			GetSystemTime(&systime);
			SystemTimeToFileTime(&systime, &ft);

			li.LowPart  = ft.dwLowDateTime;
			li.HighPart = ft.dwHighDateTime;

			li.QuadPart -= INT64_C(116444736000000000);   // Offset to the 1970 Epoch time
			li.QuadPart /= 10;                            // Convert from 100 nanoseconds to microseconds

			double utc = (double)li.QuadPart;
		#else
			// FIXME: the implementation for Windows is only millisecond resolution.
			#if COMPILER(BORLAND)
				struct timeb timebuffer;
				ftime(&timebuffer);
			#else
				struct _timeb timebuffer;
				_ftime(&timebuffer);
			#endif

			double utc = timebuffer.time * msPerSecond + timebuffer.millitm;
		#endif

31. Webkit-owb\JavaScriptCore\kjs\collector.cpp
Line: 942
原来：
    ASSERT((primaryHeap.operationInProgress == NoOperation) | (numberHeap.operationInProgress == NoOperation));
    if ((primaryHeap.operationInProgress != NoOperation) | (numberHeap.operationInProgress != NoOperation))
        abort();
改动为：
    ASSERT((primaryHeap.operationInProgress == NoOperation) | (numberHeap.operationInProgress == NoOperation));
    if ((primaryHeap.operationInProgress != NoOperation) | (numberHeap.operationInProgress != NoOperation))
#if defined(EA_PLATFORM_WINCE)
		ExitProcess(0);
#else
        abort();
#endif

32. Webkit-owb\BAL\WKAL\Concretizations\Network\EA\BCTransportHandlerDirtySDK.cpp
Line: 677
原：
swprintf(bufferLen,32, L"%u",pDirtySDKInfo->mPostData.length());
改动为：
_snwprintf(bufferLen,32, L"%u",pDirtySDKInfo->mPostData.length());

33. Webkit-owb\BAL\WKAL\Concretizations\Network\EA\BCCookieManagerEA.cpp
Line: 57
添加以下代码：
#if PLATFORM(WINCE_OS)
#include <wtf/StringExtras.h>
#endif

34. Webkit-owb\BAL\OWBAL\Concretizations\Types\WK\BCAssertionsWK.cpp
Line: 43
原来：
#include <crtdbg.h>
改动为：
	#if !PLATFORM(WINCE_OS)
		#include <crtdbg.h>
	#endif

Line: 84

35. Webkit-owb\BAL\OWBAL\Concretizations\Internationalization\WK\BCStringWK.cpp
Line: 314
原来：
String String::format(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    Vector<char, 256> buffer;

    // Do the format once to get the length.
#if COMPILER(MSVC)
    int result = _vscprintf(format, args);
#else
    char ch;
    int result = vsnprintf(&ch, 1, format, args);
    // We need to call va_end() and then va_start() again here, as the
    // contents of args is undefined after the call to vsnprintf
    // according to http://man.cx/snprintf(3)
    //
    // Not calling va_end/va_start here happens to work on lots of
    // systems, but fails e.g. on 64bit Linux.
    va_end(args);
    va_start(args, format);
#endif

    if (result == 0)
        return String("");
    if (result < 0)
        return String();
    unsigned len = result;
    buffer.grow(len + 1);
    
    // Now do the formatting again, guaranteed to fit.
    vsnprintf(buffer.data(), buffer.size(), format, args);

    va_end(args);
    
    return StringImpl::create(buffer.data(), len);
}
改动为：
String String::format(const char *format, ...)
{
#if PLATFORM(QT)
    // Use QString::vsprintf to avoid the locale dependent formatting of vsnprintf.
    // https://bugs.webkit.org/show_bug.cgi?id=18994
    va_list args;
    va_start(args, format);

    QString buffer;
    buffer.vsprintf(format, args);

    va_end(args);

    QByteArray ba = buffer.toUtf8();
    return StringImpl::create(ba.constData(), ba.length());

#elif PLATFORM(WINCE_OS)
    va_list args;
    va_start(args, format);

    Vector<char, 256> buffer;

    int bufferSize = 256;
    buffer.resize(bufferSize);
    for (;;) {
        int written = vsnprintf(buffer.data(), bufferSize, format, args);
        va_end(args);

        if (written == 0)
            return String("");
        if (written > 0)
            return StringImpl::create(buffer.data(), written);
        
        bufferSize <<= 1;
        buffer.resize(bufferSize);
        va_start(args, format);
    }

#else
    va_list args;
    va_start(args, format);

    Vector<char, 256> buffer;

    // Do the format once to get the length.
#if COMPILER(MSVC)
    int result = _vscprintf(format, args);
#else
    char ch;
    int result = vsnprintf(&ch, 1, format, args);
    // We need to call va_end() and then va_start() again here, as the
    // contents of args is undefined after the call to vsnprintf
    // according to http://man.cx/snprintf(3)
    //
    // Not calling va_end/va_start here happens to work on lots of
    // systems, but fails e.g. on 64bit Linux.
    va_end(args);
    va_start(args, format);
#endif

    if (result == 0)
        return String("");
    if (result < 0)
        return String();
    unsigned len = result;
    buffer.grow(len + 1);
    
    // Now do the formatting again, guaranteed to fit.
    vsnprintf(buffer.data(), buffer.size(), format, args);

    va_end(args);
    
    return StringImpl::create(buffer.data(), len);
#endif
}


36: Webkit-owb\BAL\OWBAL\Concretizations\Internationalization\WK\BCRegularExpressionWK.cpp
Line: 37
原来：
#include <sys/types.h>
改动为：
#if !PLATFORM(WINCE_OS)
#include <sys/types.h>
#endif

37. source\EAWebKit.cpp
Line:117
WinCE上没有_aligned_malloc _aligned_free _aligned_realloc故都采用 malloc free realloc


38: EAWebKitSupportPackages\DirtySDKEAWebKit\local\core\source\dirtysock\pc\dirtylibwin.c
Line: 97

39: EAWebKitSupportPackages\libpngEAWebKit\local\include\libpng12\pngconf.h
Line: 1423
原：
#ifndef PNG_ABORT
#  define PNG_ABORT() abort()
#endif
修改为：
#ifndef PNG_ABORT
#  ifdef _WINDOWS_
#     define PNG_ABORT() ExitProcess(0)
#  else
#     define PNG_ABORT() //abort()
#  endif
#endif


40. Webkit-owb\BAL\WKAL\Concretizations\Network\EA\BCDateEA.h
因WinCE平台下<time.h>和<stdlib.h>对time_t定义不一致
time.h定义为：typedef long time_t;
stdlib.h定义为：typedef unsigned long  time_t;
所以在winCE平台下修改了一下include的头文件
BCDateEA.h中由#include <time.h>改成#include <stdlib.h>

41. EAWebKitSupportPackages\EABaseEAWebKit\local\include\Common\EABase\config\eaplatform.h
Line: 379
	#elif defined(mips) || defined(__mips__) || defined(MIPS) || defined(_MIPS_)
		// according to Fu, Chao-Ying<fu@mips.com>; email, MIPS should disable the JIT
        #define EA_PROCESSOR_MIPSS
        #define EA_PLATFORM_DESCRIPTION "Windows CE on MIPSS"

Line:

42: Webkit-owb\BAL\OWBAL\Concretizations\Internationalization\WK\BCAtomicStringWK.cpp
Line: 102
根据webkit.org官网上的相应代码做的修改
原：
#if PLATFORM(ARM)
    const UChar* stringCharacters = string->characters();
    for (unsigned i = 0; i != length; ++i) {
        if (*stringCharacters++ != *characters++)
            return false;
    }
    return true;
#else
改动为：
    // FIXME: perhaps we should have a more abstract macro that indicates when
    // going 4 bytes at a time is unsafe
#if PLATFORM(ARM) || PLATFORM(SH4) || PLATFORM(MIPS)
    const UChar* stringCharacters = string->characters();
    for (unsigned i = 0; i != length; ++i) {
        if (*stringCharacters++ != *characters++)
            return false;
    }
    return true;
#else

43: Webkit-owb\BAL\Base\wtf\Platform.h
Line:216
根据webkit.org官网上的相应代码做的修改
原：
/* PLATFORM(ARM) */
#if   defined(arm) \
   || defined(__arm__)
#define WTF_PLATFORM_ARM 1
#if defined(__ARMEB__)
#define WTF_PLATFORM_BIG_ENDIAN 1
#elif !defined(__ARM_EABI__) && !defined(__ARMEB__) && !defined(__VFP_FP__)
#define WTF_PLATFORM_MIDDLE_ENDIAN 1
#endif
#if !defined(__ARM_EABI__)
#define WTF_PLATFORM_FORCE_PACK 1
#endif
#endif

改动为：
/* PLATFORM(ARM) */
#if   defined(arm) \
	|| defined(__arm__)\
	|| defined(ARM) \
	|| defined(_ARM_)
#define WTF_PLATFORM_ARM 1
#if defined(__ARMEB__)
#define WTF_PLATFORM_BIG_ENDIAN 1
#elif !defined(__ARM_EABI__) && !defined(__ARMEB__) && !defined(__VFP_FP__)
#define WTF_PLATFORM_MIDDLE_ENDIAN 1
#endif
#if !defined(__ARM_EABI__)
#define WTF_PLATFORM_FORCE_PACK 1
#endif
#endif

Line : 168行添加以下代码：
#if defined(mips) || defined(__mips__) || defined(MIPS) || defined(_MIPS_)
// according to Fu, Chao-Ying<fu@mips.com>; email, MIPS should disable the JIT

#define WTF_PLATFORM_MIPS 1
/* #define WTF_PLATFORM_BIG_ENDIAN 1 // If your CPU is big endian */
#define ENABLE_JIT 0

#else
/* CPU(MIPS) - MIPS 32-bit */
/* Note: Only O32 ABI is tested, so we enable it for O32 ABI for now.  */
#if (defined(mips) || defined(__mips__) || defined(MIPS) || defined(_MIPS_)) \
    && defined(_ABIO32)
#define WTF_PLATFORM_MIPS 1
#if defined(__MIPSEB__)
#define WTF_PLATFORM_BIG_ENDIAN 1
#endif
#define WTF_MIPS_PIC (defined __PIC__)
#define WTF_MIPS_ARCH __mips
#define WTF_MIPS_ISA(v) (defined WTF_MIPS_ARCH && WTF_MIPS_ARCH == v)
#define WTF_MIPS_ISA_AT_LEAST(v) (defined WTF_MIPS_ARCH && WTF_MIPS_ARCH >= v)
#define WTF_MIPS_ARCH_REV __mips_isa_rev
#define WTF_MIPS_ISA_REV(v) (defined WTF_MIPS_ARCH_REV && WTF_MIPS_ARCH_REV == v)
#define WTF_MIPS_DOUBLE_FLOAT (defined __mips_hard_float && !defined __mips_single_float)
#define WTF_MIPS_FP64 (defined __mips_fpr && __mips_fpr == 64)
/* MIPS requires allocators to use aligned memory */
#define WTF_USE_ARENA_ALLOC_ALIGNMENT_INTEGER 1
#endif /* MIPS */
#endif

44. EAWebKitSupportPackages\EAIOEAWebKit\local\source\EAFileDirectory.cpp
文件中用defined(EA_PLATFORM_WINCE)括起来的代码全部为先添加


45. EAWebKitSupportPackages\PPMallocEAWebKit\local\include\PPMalloc\internal\config.h
文件中用defined(EA_PLATFORM_WINCE)括起来的代码全部为先添加

46. EAWebKitSupportPackages\EATextEAWebKit\local\include\EAText\EATextConfig.h
文件中用defined(EA_PLATFORM_WINCE)括起来的代码全部为先添加

47. EAWebKitSupportPackages\EATextEAWebKit\local\source\EATextFontServer.cpp
文件中用defined(EA_PLATFORM_WINCE)括起来的代码全部为先添加

48. EAWebKitSupportPackages\EAIOEAWebKit\local\include\EAIO\internal\Config.h
文件中用defined(EA_PLATFORM_WINCE)括起来的代码全部为先添加

49. EAWebKitSupportPackages\EAIOEAWebKit\local\include\EAIO\EAFileBase.h
文件中用defined(EA_PLATFORM_WINCE)括起来的代码全部为先添加

50. EAWebKitSupportPackages\EASTLEAWebKit\local\source\assert.cpp
文件中用defined(EA_PLATFORM_WINCE)括起来的代码全部为先添加











2011年6月23日改动
***********************************************************************
************1. E:\Webkit\Codes\DuiBrowser\src\EAWebkit\Webkit-owb\WebKit\OrigynWebBrowser\WebCoreSupport\WebFrameLoaderClient.cpp
***********************************************************************
Line 421：
修正ViewNotification接收不到网页标题的bug
增加以下代码：
    EA::WebKit::View* pView = EA::WebKit::GetView(m_webFrame->webView());

    if(pView)
    {
        EA::WebKit::LoadInfo& loadInfo = pView->GetLoadInfo();
        loadInfo.mpView = pView;
        loadInfo.mLET   = EA::WebKit::kLETTitleReceived;

		WebCore::KURL kurl(title);
		if(kurl.string().length() != 0)
		{			
			GetFixedString(loadInfo.mPageTitle)->assign(kurl.string().characters(), kurl.string().length());
		}

        EA::WebKit::ViewNotification* const pViewNotification = EA::WebKit::GetViewNotification();
        if(pViewNotification)
            pViewNotification->LoadUpdate(loadInfo);
    }

2011年6月22日 改动

***********************************************************************
************1. Source\EAWebKitFileSystem.cpp
***********************************************************************
Line 39: 
#include "PlatformString.h"
using namespace OWBAL;

Line 156:
由：
pFileInfo->mpFile = fopen(path, openFlags & kWrite ? "wb" : "rb");
修改为：
文件的路径是utf8编码的，并且经过url encode的，所以这里需要把ut8转成ansi
	String fileName = String::fromUTF8(path);

	ULONG cchWideChar = static_cast<ULONG>(fileName.length());
	ULONG cbMultiByte = WideCharToMultiByte(CP_ACP, 0, fileName.charactersWithNullTermination(), cchWideChar, NULL, 0, NULL, NULL);

	char* ansiFileName = new char[cbMultiByte+1];
	EAW_ASSERT(!ansiFileName);
	
	ULONG cchSize = WideCharToMultiByte(CP_ACP, 0, fileName.charactersWithNullTermination(), cchWideChar, ansiFileName, cbMultiByte, NULL, NULL);
	ansiFileName[cbMultiByte] = '\0';

	pFileInfo->mpFile = fopen(ansiFileName, openFlags & kWrite ? "wb" : "rb");

	delete[] ansiFileName;
	ansiFileName = NULL;

***********************************************************************
************2. EAWebKitSupportPackages\EATextEAWebKit\local\source\EATextOutlineFont.cpp
***********************************************************************
Line 1368:
添加了下面代码：
// 主要解决了在设置FontFamilyStandard、FontFamilySerif、FontFamilySansSerif、FontFamilyMonospace、FontFamilyCursive、FamilyFantasy等字体设置成Simsun时个别中文字体显示不正确的，而当设置成带有"True Type Outlines"的标志的字体（如：宋体-方正超大字符集，微软雅黑）等字体时显示正确的问题, 这里主要是根据通过freetype中FT_Render_Glyph函数获取的FT_GlyphSlot::bitmap.pixel_mode类型来设置位图的格式，原来程序是这样设置的：mGlyphBitmap.mBitmapFormat  = (mFontDescription.mSmooth == kSmoothEnabled) ? kBFGrayscale : kBFMonochrome;

switch (static_cast<FT_Pixel_Mode>(pGlyphSlot->bitmap.pixel_mode))
{
case FT_PIXEL_MODE_MONO:
	mGlyphBitmap.mBitmapFormat = kBFMonochrome;
	break;
case FT_PIXEL_MODE_GRAY:
	mGlyphBitmap.mBitmapFormat = kBFGrayscale;
	break;
case FT_PIXEL_MODE_LCD:
case FT_PIXEL_MODE_LCD_V:
	mGlyphBitmap.mBitmapFormat = kBFGrayscale;
	break;
}

***********************************************************************
************************** EAWebkit 1.21.00 ***************************
***********************************************************************
2011年6月17日：

■EAWebkit
	更新到EAWebKit-1.21.00.darkspore版本
	
■主要更新了下面目录：
	1. EAWebKitSupportPackages
	2. include
	3. source
	4. Webkit-owb
	而projects目录下的工程文件(*.vcproj)没有更新
	
■本身自我修改的有以下文件
	1. "include/EAWebKit/EAWebKitConfig.h"
第98行
#ifndef EAWEBKIT_DEBUG
    #if defined(EA_DEBUG) || defined(_DEBUG)
        #define EAWEBKIT_DEBUG 0
    #else
        #define EAWEBKIT_DEBUG 0
    #endif
#endif	

	2. "Webkit-owb/WebCore/page/FrameTree.cpp"
第171行
	// FIXME: this following coding is disabled by achellies to implement to disable the new window created
#if 1
	if (name == "_blank")
		return parent() ? parent() : m_thisFrame;
#else
    // Since "_blank" should never be any frame's name, the following just amounts to an optimization.
    if (name == "_blank")
        return 0;
#endif

	3. "Webkit-owb/BAL/Base/wtf/Platform.h"
第257行
#if !USE(CASQT_UNICODE)
#define WTF_USE_ICU_UNICODE 1
#endif

	4. "Webkit-owb/BAL/OWBAL/Concretizations/Internationalization/WK/BCTextEncodingWK.cpp"
第114行
#elif USE(CASQT_UNICODE)
	// added by achellies
    //OwnPtr<TextCodec> textCodec = newTextCodec(*this);
    return newTextCodec(*this)->encode(characters, length, handling);
#endif

	5. "Webkit-owb/BAL/OWBAL/Concretizations/Internationalization/WK/BCTextEncodingRegistryWK.cpp" 
第182行
    TextCodecUTF8::registerEncodingNames(addToTextEncodingNameMap);
    TextCodecUTF8::registerCodecs(addToTextCodecMap);

第191行
#if USE(CASQT_UNICODE)
	// added by achellies
    TextCodecCasQt::registerEncodingNames(addToTextEncodingNameMap);
    TextCodecCasQt::registerCodecs(addToTextCodecMap);
#endif
	


***********************************************************************
************************** EAWebkit 1.41.01 ***************************
***********************************************************************
2011年6月16日：

■EAWebkit
	更新到eawebkit_monopolystreets_1_14_01版本

■主要更新了下面目录：
	1. doc
	2. EAWebKitSupportPackages
	3. include
	4. licenses
	5. source
	6. Webkit-owb
	而projects目录下的工程文件(*.vcproj)没有更新

■本身自我修改的有以下文件
	1. "Webkit-owb/WebCore/page/FrameTree.cpp"
第171行
	// FIXME: this following coding is disabled by achellies to implement to disable the new window created
#if 1
	if (name == "_blank")
		return parent() ? parent() : m_thisFrame;
#else
    // Since "_blank" should never be any frame's name, the following just amounts to an optimization.
    if (name == "_blank")
        return 0;
#endif

	2. "include/EAWebKit/EAWebKitConfig.h"
第98行
#ifndef EAWEBKIT_DEBUG
    #if defined(EA_DEBUG) || defined(_DEBUG)
        #define EAWEBKIT_DEBUG 0
    #else
        #define EAWEBKIT_DEBUG 0
    #endif
#endif

	3. "source/EAWebKitFileSystem.cpp"
第152行
#ifdef _MSC_VER
	pFileInfo->mpFile = fopen(path, openFlags & kWrite ? "wb" : "rb");
#else
	pFileInfo->mpFile = fopen(path, openFlags & kWrite ? "w" : "r");
#endif

	4. "Webkit-owb/BAL/Base/wtf/Platform.h"
第257行
#if !USE(CASQT_UNICODE)
#define WTF_USE_ICU_UNICODE 1
#endif

	5. "Webkit-owb/BAL/OWBAL/Concretizations/Internationalization/WK/BCTextEncodingWK.cpp"
第114行
#elif USE(CASQT_UNICODE)
	// added by achellies
    //OwnPtr<TextCodec> textCodec = newTextCodec(*this);
    return newTextCodec(*this)->encode(characters, length, handling);
#endif

	6. "Webkit-owb/BAL/OWBAL/Concretizations/Internationalization/WK/BCTextEncodingRegistryWK.cpp" 
第182行
    TextCodecUTF8::registerEncodingNames(addToTextEncodingNameMap);
    TextCodecUTF8::registerCodecs(addToTextCodecMap);

第191行
#if USE(CASQT_UNICODE)
	// added by achellies
    TextCodecCasQt::registerEncodingNames(addToTextEncodingNameMap);
    TextCodecCasQt::registerCodecs(addToTextCodecMap);
#endif

