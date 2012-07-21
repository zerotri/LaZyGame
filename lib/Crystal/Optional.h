#ifndef CRYSTAL_OPTIONAL_H
#define CRYSTAL_OPTIONAL_H
namespace Crystal
{
	/*template <class T>
	class OptionalBase
	{
	public:
		OptionalBase() : validity(false) {};
		OptionalBase<T> & operator =  (OptionalBase<T> const & t);
		OptionalBase(OptionalBase<T> const & other)
			: validity(other.validity) {};
		bool const isValid() const {return validity;};
		bool const isInvalid() const {return !validity;};
	protected:
		bool validity;
		T data; //storage space for T
	};

	template <class T>
	class Optional : public OptionalBase<T>
	{
	public:
		Optional()
			: OptionalBase<T>() {};
		Optional(T const & t)
		{
			validity = true;
			construct(t);
		};
		Optional(Optional<T> const& other) {};

		~Optional()
		{
			if(validity) destroy();
		};

		Optional<T> & operator = (T const & t)
		{
			data = t;
		}
		Optional<T> & operator = (Optional<T> const & other)
		{
			if(other != Crystal::Null)
			{
				data = other.data;
				validity = true;
			}
			else
			{
				validity = false;
			}
		}
		bool const operator == (Optional<T> const & other)
		{
			return (isValid() && other.isValid() && (data == other.data))
		}
		bool const operator < (Optional<T> const & other)
		{
			return (isValid() && other.isValid() && (data < other.data))
		}

		T const & operator * () const
		{
			return GetT();
		}

		T & operator * ()
		{
			return GetT();
		}

		T const * operator -> () const
		{
			return GetT();
		}

		T * operator -> ()
		{
			return GetT();
		}
		void clear();
	private:
		T const * const GetT() const
		{
			return reinterpret_cast<T const * const>(data);
		};
		T * const GetT()
		{
			return reinterpret_cast<T * const>(data);
		}
		void construct(T const & t)
		{
			new (GetT()) T(t);
		}
		void destroy()
		{
			GetT()->~T();
		}
	};
	static Optional<bool> data = t;*/
}
#endif