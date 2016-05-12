#ifndef P12218319_INTERFACES_ITERATOR_HPP
#define P12218319_INTERFACES_ITERATOR_HPP

//Copyright 2016 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include "solaire/core/core.hpp"

namespace solaire { namespace interfaces {
	template<class T>
	SOLAIRE_EXPORT_INTERFACE raw_iterator {
	public:
		typedef T Type;
		virtual SOLAIRE_INTERFACE_CALL ~raw_iterator() throw(){}

		virtual const T* SOLAIRE_INTERFACE_CALL dereference() const throw() = 0;
		virtual void SOLAIRE_INTERFACE_CALL increment(const uint32_t) throw() = 0;
		virtual void SOLAIRE_INTERFACE_CALL decrement(const uint32_t) throw() = 0;
		virtual void SOLAIRE_INTERFACE_CALL copy(raw_iterator<T>* const) const throw() = 0;
		virtual int32_t SOLAIRE_INTERFACE_CALL get_offset() const throw() = 0;
	};

	enum {
		MAX_INTERFACES_ITERATOR_SIZE = (SOLAIRE_WORD_SIZE / 2) - 1
	};
}}

#endif