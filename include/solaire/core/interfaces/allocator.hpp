#ifndef SOLAIRE_ALLOCATOR_HPP
#define SOLAIRE_ALLOCATOR_HPP

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

namespace solaire {
	SOLAIRE_EXPORT_INTERFACE allocator {
	public:
		virtual SOLAIRE_INTERFACE_CALL ~allocator() throw(){}
		virtual void* SOLAIRE_INTERFACE_CALL allocate(const uint32_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL deallocate(const void*) throw() = 0;
		virtual uint32_t SOLAIRE_INTERFACE_CALL size_of_allocation(const void*) const throw() = 0;
		virtual uint32_t SOLAIRE_INTERFACE_CALL allocated_bytes() const throw() = 0;
	};
}

extern "C" void SOLAIRE_EXPORT_CALL solaire_set_allocator(solaire::allocator*);
extern "C" solaire::allocator* SOLAIRE_EXPORT_CALL solaire_get_allocator();
extern "C" solaire::allocator* SOLAIRE_EXPORT_CALL solaire_get_default_allocator();

namespace solaire {

	inline void set_allocator(solaire::allocator& aAllocator) {
		solaire_set_allocator(&aAllocator);
	}

	inline solaire::allocator& get_allocator() {
		return *solaire_get_allocator();
	}

	inline solaire::allocator& get_default_allocator() {
		return *solaire_get_default_allocator();
	}
}

#endif