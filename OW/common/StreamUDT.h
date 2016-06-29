// begin StreamUDT.h

/*
	Copyright (c) 2003 Mitch T. Besser, All rights reserved.	

	Permission to use, modify, copy, sell, and distribute this software 
	and its documentation for any purpose is hereby granted without fee, 
	provided that the above copyright notice appears in all copies and 
	that both that copyright notice and this permission notice appear 
	in relevant supporting documentation.  Mitch T. Besser makes no 
	representations about the suitability of this software for any purpose.  
	It is provided "as is" without express or implied warranty.  
*/

/*
	Last Updated:  06-MAY-2003

	File Description:  

	Templates for IOStream insertion and extraction of User Defined Types.  
	See:  
	Langer, Kreft. 
	Standard C++ IOStreams and Locales: 
	Advanced Programmer's Guide and Reference, 
	3.1.5 Generic Inserters and Extractors, 
	(Addison-Wesley, 2000) 
	ISBN 0-201-18395-1 
*/

#ifdef TRACE_INCLUDE
#	ifndef TRACE_INCLUDE_MSG
#		define TRACE_INCLUDE_MSG "#included "
#	endif
#	if _MSC_VER>=1200
#		define STRINGIZE_LINE_DELAY(L) #L
#		define STRINGIZE_LINE(L) STRINGIZE_LINE_DELAY(L)
#		pragma message(__FILE__ "(" STRINGIZE_LINE(__LINE__) ") : info: " TRACE_INCLUDE_MSG)
#		undef STRINGIZE_LINE
#		undef STRINGIZE_LINE_DELAY
#	else
#		error "insert your compiler's trace here.  "
#	endif
#endif

// Forward Declaration(s):  
// None.  

#ifndef _KEA_STREAMUDT_H_
#define _KEA_STREAMUDT_H_

#ifndef BEGIN_INCLUDES
#	define BEGIN_INCLUDES /* pre-include file hook */
#endif

#ifndef END_INCLUDES
#	define END_INCLUDES /* post-include file hook */
#endif

BEGIN_INCLUDES
#include <iostream>
END_INCLUDES

namespace KEA
{
	class _ClearWidth
	{
	private:
		std::ios_base& strm_;
		_ClearWidth(const _ClearWidth&);
		_ClearWidth& operator=(const _ClearWidth&);

	public:
		explicit _ClearWidth(std::ios_base& strm):
		strm_(strm)
		{
		}

		~_ClearWidth()
		{
			strm_.width(0);
		}
	};

	template<class charT, class Traits, typename UDT>
	std::basic_ostream<charT, Traits>& stream_inserter
	(
		std::basic_ostream<charT, Traits>& os, const UDT& value
	)
	{
		_ClearWidth clear_width(os);
		if (os.good())
		{
			std::ios_base::iostate error=std::ios_base::goodbit;
			try
			{
				typename std::basic_ostream<charT, Traits>::sentry prepost(os);
				if (prepost)
				{
					error=value.put_stream(os);
				}
			}
			catch (std::bad_alloc&)
			{
				error|=std::ios_base::badbit;
				try
				{
					os.setstate(error);
				}
				catch (std::ios_base::failure&)
				{
				}
				const std::ios_base::iostate exception_mask=os.exceptions();
				if ((error | os.rdstate()) & exception_mask)
				{
					throw;
				}
			}
			catch (...)
			{
				error|=std::ios_base::failbit;
				try
				{
					os.setstate(error);
				}
				catch (std::ios_base::failure&)
				{
				}
				const std::ios_base::iostate exception_mask=os.exceptions();
				if ((error | os.rdstate()) & exception_mask)
				{
					throw;
				}
			}
			os.setstate(error);
		}
		return os;
	}

	template<class charT, class Traits, typename UDT>
	std::basic_istream<charT, Traits>& stream_extractor
	(
		std::basic_istream<charT, Traits>& is, UDT& value
	)
	{
		_ClearWidth clear_width(is);
		if (is.good())
		{
			std::ios_base::iostate error=std::ios_base::goodbit;
			try
			{
				typename std::basic_istream<charT, Traits>::sentry prepost(is);
				if (prepost)
				{
					error=value.get_stream(is);
				}
			}
			catch (std::bad_alloc&)
			{
				error|=std::ios_base::badbit;
				try
				{
					is.setstate(error);
				}
				catch (std::ios_base::failure&)
				{
				}
				const std::ios_base::iostate exception_mask=is.exceptions();
				if ((error | is.rdstate()) & exception_mask)
				{
					throw;
				}
			}
			catch (...)
			{
				error|=std::ios_base::failbit;
				try
				{
					is.setstate(error);
				}
				catch (std::ios_base::failure&)
				{
				}
				const std::ios_base::iostate exception_mask=is.exceptions();
				if ((error | is.rdstate()) & exception_mask)
				{
					throw;
				}
			}
			is.setstate(error);
		}
		return is;
	}
}

#define DECLARE_STREAM_INSERTER(UDT)                        \
template<class charT, class Traits>                         \
std::basic_ostream<charT, Traits>& operator<<               \
(                                                           \
    std::basic_ostream<charT, Traits>& os, const UDT& value \
);

#define DEFINE_STREAM_INSERTER(UDT)                         \
template<class charT, class Traits>                         \
std::basic_ostream<charT, Traits>& operator<<               \
(                                                           \
    std::basic_ostream<charT, Traits>& os, const UDT& value \
)                                                           \
{                                                           \
    return KEA::stream_inserter(os, value);                 \
}

#define DECLARE_STREAM_EXTRACTOR(UDT)                 \
template<class charT, class Traits>                   \
std::basic_istream<charT, Traits>& operator>>         \
(                                                     \
    std::basic_istream<charT, Traits>& is, UDT& value \
);

#define DEFINE_STREAM_EXTRACTOR(UDT)                  \
template<class charT, class Traits>                   \
std::basic_istream<charT, Traits>& operator>>         \
(                                                     \
    std::basic_istream<charT, Traits>& is, UDT& value \
)                                                     \
{                                                     \
    return KEA::stream_extractor(is, value);          \
}
#endif // #ifndef _KEA_STREAMUDT_H_
// end StreamUDT.h