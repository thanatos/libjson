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
#ifndef LIBJSON__JSON_OBJECT_H
#define LIBJSON__JSON_OBJECT_H

#include <string>
#include <map>

namespace json
{
	/**
	 * \brief A JSON object.
	 * JSON objects are key-value maps. Users of JSON object should not assume
	 * that keys will be in any particular order. Keys are unique.
	 */
	class Object : public Value
	{
	private:
		typedef std::map<std::string, Value *> MapType;

	public:
		// Note: We break our own casing rules just to keep with STL.

		class iterator
		{
		public:
			iterator() { };
			iterator(const iterator &i) : m_i(i.m_i) { }

			const std::string &key() const { return m_i->first; }
			Value *value() { return m_i->second; }

			Value *operator * () { return m_i->second; }

			// Pre-increment
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
			iterator operator ++ (int unused)
			{
				iterator temp(*this);
				return ++temp;
			}
			iterator operator -- (int unused)
			{
				iterator temp(*this);
				return --temp;
			}

			bool operator == (const iterator &i) const { return m_i == i.m_i; }
			bool operator != (const iterator &i) const { return m_i != i.m_i; }
		private:
			MapType::iterator m_i;

			iterator(const MapType::iterator &i) : m_i(i) { }

			friend class const_iterator;
			friend class json::Object;
		};

		class const_iterator
		{
		public:
			const_iterator() { };
			const_iterator(const const_iterator &i) : m_i(i.m_i) { }
			const_iterator(const iterator &i) : m_i(i.m_i) { }

			const std::string &key() const { return m_i->first; }
			const Value *value() { return m_i->second; }

			Value *operator * () { return m_i->second; }
			
			// Pre-increment
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
			const_iterator operator ++ (int unused)
			{
				const_iterator temp(*this);
				return ++temp;
			}
			const_iterator operator -- (int unused)
			{
				const_iterator temp(*this);
				return --temp;
			}
			
			bool operator == (const const_iterator &i) const { return m_i == i.m_i; }
			bool operator != (const const_iterator &i) const { return m_i != i.m_i; }
		private:
			MapType::const_iterator m_i;

			const_iterator(const MapType::const_iterator &i) : m_i(i) { }

			friend class json::Object;
		};

		/// Create an new, empty object.
		Object() : Value(TYPE_OBJECT) { }
		/// Create a copy of an object.
		Object(const Object &o);
		virtual ~Object();

		/// Swap this object with another object.
		void swap(Object &o);
		json::Object &operator = (const json::Object &o);

		iterator begin() { return iterator(m_members.begin()); }
		const_iterator begin() const { return const_iterator(m_members.begin()); }

		iterator end() { return iterator(m_members.end()); }
		const_iterator end() const { return const_iterator(m_members.end()); }

		/// Get a value from a key.
		Value *getValue(const std::string &key);
		/// Get a value from a key.
		const Value *getValue(const std::string &key) const;
		/**
		 * \brief Set a value inside the object.
		 * If the key is already present, it is replaced.
		 * This function creates a copy of val.
		 * \param key The key to associate the value with.
		 * \param val The value to add to the object.
		 */
		void setValue(const std::string &key, const Value &val);
		/**
		 * \brief Set a value inside the object.
		 * If the key is already present, it is replaced.
		 * This function creates a copy of val.
		 * \param key The key to associate the value with.
		 * \param val The value to add to the object.
		 */
		void setValue(const std::string &key, const Value *val);
		/**
		 * \brief Set a value inside the object.
		 * If the key is already present, it is replaced.
		 * \note This function does not create a copy of val. The object will
		 * take ownership of val, and will free it appropriately.
		 * \param key The key to associate the value with.
		 * \param val The value to add to the object.
		 */
		void takeValue(const std::string &key, Value *val);
		/**
		 * \brief Removes a key from the object.
		 * Removes a value from the object.
		 */
		void removeValue(const std::string &key);

		Value *clone() const { return new Object(*this); }
	private:
		MapType m_members;
	};
}

#endif

