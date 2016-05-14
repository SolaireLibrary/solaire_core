#ifndef SOLAIRE_ITERATOR_HPP
#define SOLAIRE_ITERATOR_HPP

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


#include "solaire/core/interfaces/iterator.hpp"
#include "solaire/core/local_memory.hpp"

namespace solaire {

	template<class T>
	class iterator {
	public:
		typedef T Type;
	private:
		local_memory<(SOLAIRE_WORD_SIZE / 2) - 1> mMemory;
	private:
		inline interfaces::iterator<T>& get_iterator() {
			interfaces::iterator<T>* const tmp = static_cast<interfaces::iterator<T>*>(mMemory.get());
			runtime_assert(tmp, "Iterator implementation is null");
			return *tmp;
	    }

		inline const interfaces::iterator<T>& get_iterator() const {
			const interfaces::iterator<T>* const tmp = static_cast<const interfaces::iterator<T>*>(mMemory.get());
			runtime_assert(tmp, "Iterator implementation is null");
			return *tmp;
	    }

		inline void _delete() {
			if(mMemory.is_allocated()) {
				get_iterator().~iterator();
				mMemory.deallocate();
			}
		}

		inline void _create(const interfaces::iterator<T>& aIterator) {
			interfaces::iterator<T>* const ptr = static_cast<interfaces::iterator<T>*>(mMemory.allocate(aIterator.size()));
			aIterator.copy(ptr);
		}

		inline void _create(const iterator<T>& aOther) {
			if(aOther.mMemory.is_allocated()) {
				_create(aOther.get_iterator());
			}
		}
	public:

		iterator() :
			mMemory()
		{}

		iterator(iterator<T>&& aOther) :
			mMemory()
		{
			_create(aOther);
		}

		iterator(const iterator<T>& aOther) :
			mMemory()
		{
			_create(aOther);
		}

		iterator(const interfaces::iterator<T>& aIterator) :
			mMemory()
        {
			_create(aIterator);
        }

		~iterator() {
			_delete();
		}

		inline iterator<T>& operator=(iterator<T>&& aOther) {
			_delete();
			_create(aOther);
			return *this;
		}

		inline iterator<T>& operator=(const iterator<T>& aOther) {
			_delete();
			_create(aOther);
			return *this;
		}

		inline operator iterator<const T>() const {
			iterator<T> tmp = *this;
			return *reinterpret_cast<iterator<const T>*>(&tmp);
		}

		// Comparison

		inline bool operator==(const iterator<T>& aOther) const {
			return get_iterator().get_offset() == aOther.get_iterator().get_offset();
		}

		inline bool operator!=(const iterator<T>& aOther) const {
			return get_iterator().get_offset() != aOther.get_iterator().get_offset();
		}

		inline bool operator<(const iterator<T>& aOther) const {
			return get_iterator().get_offset() < aOther.get_iterator().get_offset();
		}

		inline bool operator>(const iterator<T>& aOther) const {
			return get_iterator().get_offset() > aOther.get_iterator().get_offset();
		}

		inline bool operator<=(const iterator<T>& aOther) const {
			return get_iterator().get_offset() <= aOther.get_iterator().get_offset();
		}

		inline bool operator>=(const iterator<T>& aOther) const {
			return get_iterator().get_offset() >= aOther.get_iterator().get_offset();
		}

		// Dereference

		inline T& operator*() {
			return *const_cast<T*>(get_iterator().dereference());
		}

		inline const T& operator*() const {
			return *get_iterator().dereference();
		}

		inline T* operator->() {
			return const_cast<T*>(get_iterator().dereference());
		}

		inline const T* operator->() const {
			return get_iterator().dereference();
		}

		inline T& operator[](const uint32_t aIndex) {
			iterator<T> tmp(*this);
			tmp.increment(aIndex);
			return const_cast<T&>(tmp.get_iterator().dereference());
		}

		inline const T& operator[](const uint32_t aIndex) const {
			iterator<T> tmp(*this);
			tmp.increment(aIndex);
			return tmp.get_iterator().dereference();
		}

		// Increment

		inline iterator<T>& operator++() {
			get_iterator().increment(1);
			return *this;
		}

		inline iterator<T> operator++(int) {
			iterator<T> tmp(*this);
			get_iterator().increment(1);
			return tmp;
		}

		inline iterator<T>& operator+=(const uint32_t aOffset) {
			get_iterator().increment(aOffset);
			return *this;
		}

		inline iterator<T> operator+(const uint32_t aOffset) const {
			iterator<T> tmp(*this);
			tmp.get_iterator().increment(aOffset);
			return tmp;
		}

		// Decrement

		inline iterator<T>& operator--() {
			get_iterator().decrement(1);
			return *this;
		}

		inline iterator<T> operator--(int) {
			iterator<T> tmp(*this);
			get_iterator().decrement(1);
			return tmp;
		}

		inline iterator<T>& operator-=(const uint32_t aOffset) {
			get_iterator().decrement(aOffset);
			return *this;
		}

		inline iterator<T> operator-(const uint32_t aOffset) const {
			iterator<T> tmp(*this);
			tmp.get_iterator().decrement(aOffset);
			return tmp;
		}

		inline int32_t operator-(const iterator<T>& aOther) const {
			return get_iterator().get_offset() - aOther.get_iterator().get_offset();
		}
	};
}

#endif