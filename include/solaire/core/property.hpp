#ifndef SOLAIRE_PROPERTY_HPP
#define SOLAIRE_PROPERTY_HPP

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
	template<class CLASS, class TYPE, TYPE(CLASS::*GETTER)() const, void(CLASS::*SETTER)(TYPE)>
	struct value_property{
	private:
		CLASS& mParent;
	public:
		SOLAIRE_CONSTEXPR_11 value_property(CLASS& aParent) :
			mParent(aParent)
		{}

        SOLAIRE_FORCE_INLINE void operator=(TYPE aValue) {
			(mParent.*SETTER)(aValue);
		}

        SOLAIRE_FORCE_INLINE operator TYPE() const throw() {
			return (mParent.*GETTER)();
		}
	};

	template<class CLASS, class TYPE, TYPE&(CLASS::*GETTER)()>
	struct reference_property{
	private:
		CLASS& mParent;
	public:
		SOLAIRE_CONSTEXPR_11 reference_property(CLASS& aParent) :
			mParent(aParent)
		{}

        SOLAIRE_FORCE_INLINE TYPE& operator=(const TYPE& aValue) {
			TYPE& value = (mParent.*GETTER)();
			value = aValue;
			return value;
		}

        SOLAIRE_FORCE_INLINE TYPE& operator=(TYPE&& aValue) {
			TYPE& value = (mParent.*GETTER)();
			value = std::move(aValue);
			return value;
		}

        SOLAIRE_FORCE_INLINE operator TYPE&() throw() {
			return (mParent.*GETTER)();
		}

        SOLAIRE_FORCE_INLINE operator const TYPE&() const throw() {
            CLASS& parent = const_cast<CLASS&>(mParent);
			return (parent.*GETTER)();
		}
	};

	template<class CLASS, class TYPE, TYPE(CLASS::*GETTER)() const>
	struct read_only_value_property{
	private:
		CLASS& mParent;
	public:
		SOLAIRE_CONSTEXPR_11 read_only_value_property(CLASS& aParent) :
			mParent(aParent)
		{}

        SOLAIRE_FORCE_INLINE operator TYPE() const throw() {
			return (mParent.*GETTER)();
		}
	};

	template<class CLASS, class TYPE, const TYPE&(CLASS::*GETTER)() const>
	struct read_only_reference_property{
	private:
		CLASS& mParent;
	public:
		SOLAIRE_CONSTEXPR_11 read_only_reference_property(CLASS& aParent) :
			mParent(aParent)
		{}

        SOLAIRE_FORCE_INLINE operator const TYPE&() const throw() {
			return (mParent.*GETTER)();
		}
	};
}

#endif
