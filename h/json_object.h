#ifndef LIBJSON__JSON_OBJECT_H
#define LIBJSON__JSON_OBJECT_H

#include <string>
#include <map>

namespace json
{
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

		Object() : Value(TYPE_OBJECT) { }
		Object(const Object &o);
		virtual ~Object();

		void swap(Object &o);
		json::Object &operator = (const json::Object &o);

		iterator begin() { return iterator(m_members.begin()); }
		const_iterator begin() const { return const_iterator(m_members.begin()); }

		iterator end() { return iterator(m_members.end()); }
		const_iterator end() const { return const_iterator(m_members.end()); }

		Value *getValue(const std::string &key);
		const Value *getValue(const std::string &key) const;
		void setValue(const std::string &key, const Value &val);
		void setValue(const std::string &key, const Value *val);
		void takeValue(const std::string &key, Value *val);
		void removeValue(const std::string &key);

		Value *clone() const { return new Object(*this); }
	private:
		MapType m_members;
	};
}

#endif

