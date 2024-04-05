#pragma once
#include <string.h>
#include <cassert>
#include <stdexcept>
namespace Lib{
	namespace Container {
		template<size_t Size>
		class StaticString
		{
		public:
			using iterator = char*;
			using const_iterator = char const*;
			StaticString();
			StaticString(char const*);
			~StaticString();

			size_t Length()const;
			bool Copy(char const*);
			char const* CStr()const;
			size_t Capacity()const;
			iterator Begin()const;
			const_iterator CBegin()const;
			iterator End()const;
			const_iterator CEnd()const;
			char& operator[](size_t idx);
			char const& operator[](size_t idx)const;
		private:
			//null終端をカバー
			char m_chars[Size + 1];
			char* m_pNullTerm;
		};
		template<size_t Size>
		inline StaticString<Size>::StaticString()
		{
			m_pNullTerm = &(m_chars[0]);
			*m_pNullTerm = '\0';
		}
		template<size_t Size>
		inline StaticString<Size>::StaticString(char const* pSrc)
		{
			bool result = Copy(pSrc);
			assert(result && "文字列キャパシティが足りない");
			m_pNullTerm = &(m_chars[strlen(pSrc)]);
		}
		template<size_t Size>
		inline StaticString<Size>::~StaticString()
		{
		}
		template<size_t Size>
		inline size_t StaticString<Size>::Length() const
		{
			return m_pNullTerm - CStr();
		}
		template<size_t Size>
		inline bool StaticString<Size>::Copy(char const* pSrc)
		{
			if (Capacity() < strlen(pSrc)) return false;
			strcpy_s(m_chars, _countof(m_chars), pSrc);
			return true;
		}
		template<size_t Size>
		inline char const* StaticString<Size>::CStr() const
		{
			return &(m_chars[0]);
		}
		template<size_t Size>
		inline size_t StaticString<Size>::Capacity() const
		{
			return Size;
		}
		template<size_t Size>
		inline typename StaticString<Size>::iterator StaticString<Size>::Begin() const
		{
			return &(m_chars[0]);
		}
		template<size_t Size>
		inline typename StaticString<Size>::const_iterator StaticString<Size>::CBegin() const
		{
			return &(m_chars[0]);
		}

		template<size_t Size>
		inline typename StaticString<Size>::iterator StaticString<Size>::End() const
		{
			return m_pNullTerm;
		}
		template<size_t Size>
		inline typename StaticString<Size>::const_iterator StaticString<Size>::CEnd() const
		{
			return m_pNullTerm;
		}
		template<size_t Size>
		inline char& StaticString<Size>::operator[](size_t idx)
		{
			if (Length() <= idx) {
				throw std::out_of_range("idx error");
			}
			return m_chars[idx];
		}
		template<size_t Size>
		inline char const& StaticString<Size>::operator[](size_t idx)const
		{
			if (Length() <= idx) {
				throw std::out_of_range("idx error");
			}
			return m_chars[idx];
		}
	}
}

