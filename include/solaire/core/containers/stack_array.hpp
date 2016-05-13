#ifndef SOLAIRE_STACK_ARRAY_HPP
#define SOLAIRE_STACK_ARRAY_HPP

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

#include "solaire/core/iterators/contiguous_iterator.hpp"
#include "solaire/core/list.hpp"

namespace solaire { 
	namespace interfaces {
		template<class T, const uint32_t S>
		SOLAIRE_EXPORT_CLASS stack_array : public contiguous_list<T> {
		private:
			T mArray[S];
		protected:
			// Inherited from contiguous_list
			bool SOLAIRE_INTERFACE_CALL assert_size(const uint32_t aSize) throw() override {
				return aSize <= S;
			}
		public:
			stack_array() throw() :
				contiguous_list(mArray)
			{
				mHeadPosition = S;
			}
		};
	}
}

#endif