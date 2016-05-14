#ifndef SOLAIRE_LOCAL_MEMORY_HPP
#define SOLAIRE_LOCAL_MEMORY_HPP

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
	template<const uint32_t BYTES> 
	class local_memory {
	private:
		union {
			uint8_t mBufferMemory[BYTES];
			void* mHeapMemory;
		};
		struct {
			uint8_t mBufferAlloc : 1;
			uint8_t mHeapAlloc : 1;
		};

		local_memory(local_memory&&);
		local_memory(const local_memory&);
		local_memory& operator=(local_memory&&);
		local_memory& operator=(const local_memory&);
	public:
		local_memory() :
			mHeapMemory(nullptr),
			mBufferAlloc(0),
			mHeapAlloc(0)
		{}

		inline bool is_allocated() const throw() {
			return mBufferAlloc || mHeapAlloc;
		}

		void* allocate(const uint32_t aBytes) {
			runtime_assert(! is_allocated(), "Memory has already been allocated");
			if(aBytes <= BYTES) {
				mBufferAlloc = 1;
				return mBufferMemory;
			}else {
				mHeapAlloc = 1;
				mHeapMemory = get_allocator().allocate(aBytes);
				runtime_assert(mHeapMemory, "Memory allocation failed");
				return mHeapMemory;
			}
		}

		void deallocate() {
			if(mBufferAlloc) {
				mBufferAlloc = 0;
			}else if(mHeapAlloc) {
				get_allocator().deallocate(mHeapMemory);
				mHeapMemory = nullptr;
				mHeapAlloc = 0;
			}else {
				throw std::runtime_error("Memory has not been allocated");
			}
		}

		inline void* get() throw() {
			return mBufferAlloc ? mBufferMemory : mHeapAlloc ? mHeapMemory : nullptr;
		}

		inline const void* get() const throw() {
			return mBufferAlloc ? mBufferMemory : mHeapAlloc ? mHeapMemory : nullptr;
		}
	};
}

#endif