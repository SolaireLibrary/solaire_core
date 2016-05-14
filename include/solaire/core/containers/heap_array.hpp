#ifndef SOLAIRE_HEAP_ARRAY_HPP
#define SOLAIRE_HEAP_ARRAY_HPP

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

#include "solaire/core/interfaces/allocator.hpp"
#include "solaire/core/containers/contiguous_list.hpp"
#include "solaire/core/list.hpp"

namespace solaire { 
	template<class T>
	SOLAIRE_EXPORT_CLASS heap_array : public contiguous_list<T> {
	protected:
		uint32_t mSize;

		inline static T* allocate(const uint32_t aSize) {
			void* const ptr = get_allocator().allocate(sizeof(T) * aSize);
			runtime_assert(ptr, "solaire::interfaces::heap_array::allocate : failed to allocate memory");
			return static_cast<T*>(ptr);
		}

		inline static void deallocate(const T* const aMemory) {
			runtime_assert(get_allocator().deallocate(aMemory), "solaire::interfaces::heap_array::deallocate : failed to deallocate memory");
		}

		// Inherited from ContiguousArray
		virtual bool SOLAIRE_INTERFACE_CALL _reserve(const uint32_t aSize) throw() override {
			return aSize <= mSize;
		}
	public:
		heap_array(const uint32_t aSize) :
			contiguous_list(allocate(aSize)),
			mSize(aSize)
		{
			mHeadPosition = mSize;
		}
		
		heap_array(heap_array<T>&& aOther) throw() :
			contiguous_list(std::move(aOther)),
			mSize(aOther.mSize)
		{
			aOther.mSize = 0;
		}

		heap_array(const heap_array<T>& aOther) throw() :
			contiguous_list(allocate(aOther.mSize)),
			mSize(aOther.mSize)
		{
			mHeadPosition = aOther.mHeadPosition;
			for(uint32_t i = 0; i < mHeadPosition; ++i) mBasePointer[i] = aOther.mBasePointer[i];
		}
	
		virtual SOLAIRE_INTERFACE_CALL ~heap_array() throw() {
			if(mBasePointer) {
				deallocate(mBasePointer);
				mBasePointer = nullptr;
			}
		}
		
		heap_array<T>& operator=(heap_array<T>&& aOther) throw() {
			std::swap(mBasePointer, aOther.mBasePointer);
			std::swap(mHeadPosition, aOther.mHeadPosition);
			std::swap(mSize, aOther.mSize);
			return *this;
		}

		heap_array<T>& operator=(const heap_array<T>& aOther) {
			if(mSize < aOther.mSize) {
				if(mBasePointer) {
					get_allocator().deallocate(mBasePointer);
					mBasePointer = nullptr;
				}
				mBasePointer = allocate(aOther.mSize);
				mSize = aOther.mSize;
			}
			mHeadPosition = aOther.mHeadPosition;
			for(uint32_t i = 0; i < mHeadPosition; ++i) mBasePointer[i] = aOther.mBasePointer[i];
			return *this;
		}
	};
}

#endif