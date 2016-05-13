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

#include <map>
#include <mutex>
#include <atomic>
#include "solaire/core/interfaces/allocator.hpp"

class default_allocator : public solaire::allocator {
private:
	std::map<const void*, uint32_t> mAllocations;
	std::atomic_uint32_t mBytes;
	mutable std::mutex mLock;
public:
	default_allocator() :
		mBytes(0) 
	{}

	virtual SOLAIRE_INTERFACE_CALL ~default_allocator() throw() {

	}

	// inherited from allocator
	void* SOLAIRE_INTERFACE_CALL allocate(const uint32_t aBytes) throw() override {
		void* const tmp = malloc(aBytes);
		if(tmp == nullptr) return nullptr;
		mLock.lock();
		mAllocations.emplace(tmp, aBytes);
		mLock.unlock();
		mBytes += aBytes;
		return tmp;
	}

	bool SOLAIRE_INTERFACE_CALL deallocate(const void* aObject) throw() override {
		mLock.lock();
		const auto it = mAllocations.find(aObject);
		if(it == mAllocations.end()) {
			mLock.unlock();
			return false;
		}else {
			const uint32_t bytes = it->second;
			mLock.unlock();
			mBytes -= bytes;
			free(const_cast<void*>(aObject));
			return true;
		}
	}

	uint32_t SOLAIRE_INTERFACE_CALL size_of_allocation(const void* aObject) const throw() override {
		mLock.lock();
		const auto it = mAllocations.find(aObject); if (it == mAllocations.end()) {
			mLock.unlock();
			return 0;
		}else {
			const uint32_t bytes = it->second;
			mLock.unlock();
			return bytes;
		}
	}

	uint32_t SOLAIRE_INTERFACE_CALL allocated_bytes() const throw() override {
		return mBytes;
	}
};

#if SOLAIRE_COMPILE_MODE != SOLAIRE_SHARED_IMPORT_COMPILE
	solaire::allocator* CURRENT_ALLOCATOR = nullptr;

	extern "C" SOLAIRE_EXPORT_API void SOLAIRE_EXPORT_CALL solaire_set_allocator(solaire::allocator* aAllocator) {
		CURRENT_ALLOCATOR = aAllocator;
	}

	extern "C" SOLAIRE_EXPORT_API solaire::allocator* SOLAIRE_EXPORT_CALL solaire_get_allocator() {
		if(CURRENT_ALLOCATOR == nullptr) CURRENT_ALLOCATOR = solaire_get_default_allocator();
		return CURRENT_ALLOCATOR;
	}

	extern "C" SOLAIRE_EXPORT_API solaire::allocator* SOLAIRE_EXPORT_CALL solaire_get_default_allocator() {
		static default_allocator DEFAULT_ALLOCATOR;
		return &DEFAULT_ALLOCATOR;
	}
#endif