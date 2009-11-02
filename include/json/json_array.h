/*
 * Copyright (c) 2009 Roy Wellington IV
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef LIBJSON__JSON_ARRAY_H
#define LIBJSON__JSON_ARRAY_H

#include <vector>

#include "json.h"
#include "json_unused.h"

namespace json
{
	class Array : public Value
	{
	public:
		class iterator;
		class const_iterator;

		Array() : Value(TYPE_ARRAY) { }
		Array(const Array &a);
		virtual ~Array();

		void swap(json::Array &a);
		json::Array &operator = (const json::Array &a);

		Value &operator [] (int index) { return *(m_values[index]); }

		void pushBack(const Value *v);
		void pushBack(const Value &v) { pushBack(&v); }
		void pushBackTake(Value *v) { m_values.push_back(v); }

		iterator begin() { return iterator(m_values.begin()); }
		const_iterator begin() const { return const_iterator(m_values.begin()); }
		iterator end() { return iterator(m_values.end()); }
		const_iterator end() const { return const_iterator(m_values.end()); }

		size_t size() const { return m_values.size(); }
		bool empty() const { return m_values.empty(); }

		Value *clone() const { return new Array(*this); }

		// Note: We break our own casing rules just to keep with STL.

		class iterator
		{
		public:
			iterator() { }
			iterator(const iterator &i) : m_i(i.m_i) { }

			Value &operator * () { return **m_i; }
			Value *operator -> () { return *m_i; }

			// Pre increment
			iterator &operator ++ ()
			{
				++m_i;
				return *this;
			}
			iterator &operator -- ()
			{
				--m_i;
				return *this;
			}

			// Post increment
			iterator operator ++ (int JSON_UNUSED(unused))
			{
				iterator temp(*this);
				return ++temp;
			}
			iterator operator -- (int JSON_UNUSED(unused))
			{
				iterator temp(*this);
				return --temp;
			}

			bool operator == (const iterator &i) const { return m_i == i.m_i; }
			bool operator != (const iterator &i) const { return m_i != i.m_i; }

		private:
			friend class const_iterator;
			friend class Array;

			iterator(const std::vector<Value *>::iterator &i) : m_i(i) { }

			std::vector<Value *>::iterator m_i;
		};

		class const_iterator
		{
		public:
			const_iterator() { }
			const_iterator(const iterator &i) : m_i(i.m_i) { }

			Value &operator * () { return **m_i; }
			Value *operator -> () { return *m_i; }

			// Pre increment
			const_iterator &operator ++ ()
			{
				++m_i;
				return *this;
			}
			const_iterator &operator -- ()
			{
				--m_i;
				return *this;
			}

			// Post increment
			const_iterator operator ++ (int JSON_UNUSED(unused))
			{
				const_iterator temp(*this);
				return ++temp;
			}
			const_iterator operator -- (int JSON_UNUSED(unused))
			{
				const_iterator temp(*this);
				return --temp;
			}

			bool operator == (const const_iterator &i) const { return m_i == i.m_i; }
			bool operator != (const const_iterator &i) const { return m_i != i.m_i; }

		private:
			friend class Array;

			const_iterator(const std::vector<Value *>::const_iterator &i) : m_i(i) { }

			std::vector<Value *>::const_iterator m_i;
		};

	private:
		std::vector<Value *> m_values;
	};
}

#endif
