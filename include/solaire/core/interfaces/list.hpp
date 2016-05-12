#ifndef SOLAIRE_INTERFACES_LIST_HPP
#define SOLAIRE_INTERFACES_LIST_HPP

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

#include "solaire/core/interfaces/deque.hpp"

namespace solaire { namespace interfaces {
	template<class T>
	SOLAIRE_EXPORT_INTERFACE list : public deque<T> {
    public:
		virtual SOLAIRE_INERFACE_CALL ~list() throw(){}
		virtual bool SOLAIRE_INERFACE_CALL insert(const uint32_t, const T&) throw() = 0;
		virtual bool SOLAIRE_INERFACE_CALL erase(const uint32_t) throw() = 0;
	};
}}

#endif