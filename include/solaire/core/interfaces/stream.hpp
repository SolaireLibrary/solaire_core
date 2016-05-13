#ifndef SOLAIRE_INTERFACES_STREAM_HPP
#define SOLAIRE_INTERFACES_STREAM_HPP

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
	SOLAIRE_EXPORT_INTERFACE stream {
    public:
		virtual SOLAIRE_INTERFACE_CALL ~stream() throw(){}
		virtual bool SOLAIRE_INTERFACE_CALL is_offsetable() const throw() = 0;
		virtual uint32_t SOLAIRE_INTERFACE_CALL get_offset() const throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL set_offset(uint32_t) throw() = 0;
	};
}}

#endif