#ifndef SOLAIRE_INTERFACES_DEQUE_HPP
#define SOLAIRE_INTERFACES_DEQUE_HPP

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

#include "solaire/core/interfaces/stack.hpp"

namespace solaire { namespace interfaces {
	template<class T>
	SOLAIRE_EXPORT_INTERFACE deque : public stack<T> {
    public:
		virtual SOLAIRE_INTERFACE_CALL ~deque() throw(){}
		virtual bool SOLAIRE_INTERFACE_CALL push_front(const T&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL pop_bront() throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL can_invalidate() const throw() = 0;
	};
}}

#endif