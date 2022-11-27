#include <pptest>
#include <colored_printer>
#include <ds/common>

auto _lambda = []() {};
using _lambda_t = decltype(_lambda);

Test(meta_functions_test)
{
	TestInit(meta_functions_test);

	struct A
	{};

	struct B
	{
		B(int) {}
		~B() = default;
	};

	struct C
	{
		C() = default;
		C(C &&) = default;
		C(C const &) = delete;
		virtual ~C() = default;
	};

	struct D : C
	{};

	struct E : B
	{};

	struct F : A
	{};

	struct _destructible
	{
		~_destructible() = default;
	};

	struct _indestructible
	{
		~_indestructible() = delete;
	};

	struct _trivially_default_constructible
	{
		_trivially_default_constructible() = default;
	};

	struct _default_constructible
	{
		_default_constructible() 
		{}
	};

	struct _default_inconstructible
	{
		_default_inconstructible() = delete;
	};

	struct _trivially_move_constructible
	{
		_trivially_move_constructible(_trivially_move_constructible &&) = default;
	};

	struct _move_constructible
	{
		_move_constructible(_move_constructible &&) 
		{}
	};

	struct _move_inconstructible
	{
		_move_inconstructible(_move_inconstructible &&) = delete;
	};

	struct _trivially_copy_constructible
	{
		_trivially_copy_constructible(_trivially_copy_constructible const &) = default;
	};

	struct _copy_constructible
	{
		_copy_constructible(_copy_constructible const &)
		{}
	};

	struct _copy_inconstructible
	{
		_copy_inconstructible(_copy_inconstructible const &) = delete;
	};


	struct _assignable
	{
		_assignable & 
		operator=(int) 
		{
			return *this;
		}
	};

	struct _unassignable
	{
		_unassignable & operator=(int) = delete;
	};

	struct _trivially_move_assignable
	{
		_trivially_move_assignable & operator=(_trivially_move_assignable &&) = default;
	};

	struct _move_assignable
	{
		_move_assignable & 
		operator=(_move_assignable &&) 
		{
			return *this;
		}
	};

	struct _move_unassignable
	{
		_move_unassignable & operator=(_move_unassignable &&) = delete;
	};

	struct _trivially_copy_assignable
	{
		_trivially_copy_assignable & operator=(_trivially_copy_assignable const &) = default;
	};

	struct _copy_assignable
	{
		_copy_assignable & 
		operator=(_copy_assignable const &) 
		{
			return *this;
		}
	};

	struct _copy_unassignable
	{
		_copy_unassignable & operator=(_copy_unassignable const &) = delete;
	};

	union      _union  {};
	struct     _struct { int bar; void foo(){}; };
	class      _class  {};
	enum       _enum       { _a, _b };
	enum class _enum_class { _a, _b };

	using _func_t     = void();
	using _func_ptr_t = void (*)();
	using _func_ref_t = void (&)();
	
	Testcase(test_integral_constant)
	{
		ExpectEQ(0, ds::integral_constant<int,0>::value);
		ExpectEQ(5, ds::integral_constant<int,5>::value);

	} TestcaseEnd(test_integral_constant);

	Testcase(test_bool_constant)
	{
		ExpectTrue(ds::bool_constant<true>::value);
		ExpectFalse(ds::bool_constant<false>::value);
		ExpectTrue(ds::true_type::value);
		ExpectFalse(ds::false_type::value);

	} TestcaseEnd(test_bool_constant);

	Testcase(test_add_pointer_t)
	{
		ExpectTrue(ds::is_same<ds::add_pointer_t<int>,int *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int const>,int const *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int volatile>,int volatile *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int const volatile>,int const volatile *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int &>,int *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int const &>,int const *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int volatile &>,int volatile *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int const volatile &>,int const volatile *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int &&>,int *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int const &&>,int const *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int volatile &&>,int volatile *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int const volatile &&>,int const volatile *>::value);
		ExpectTrue(ds::is_same<ds::add_pointer_t<int *>,int **>::value);

	} TestcaseEnd(test_add_pointer_t);

	Testcase(test_add_lvalue_reference_t)
	{
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int>,int &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int const>,int const &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int volatile>,int volatile &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int const volatile>,int const volatile &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int &>,int &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int const &>,int const &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int volatile &>,int volatile &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int const volatile &>,int const volatile &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int &&>,int &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int const &&>,int const &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int volatile &&>,int volatile &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int const volatile &&>,int const volatile &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int *>,int * &>::value);
		ExpectTrue(ds::is_same<ds::add_lvalue_reference_t<int * const>,int * const &>::value);

	} TestcaseEnd(test_add_lvalue_reference_t);

	Testcase(test_add_rvalue_reference_t)
	{
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int>,int &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int const>,int const &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int volatile>,int volatile &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int const volatile>,int const volatile &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int &>,int &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int const &>,int const &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int volatile &>,int volatile &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int const volatile &>,int const volatile &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int &&>,int &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int const &&>,int const &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int volatile &&>,int volatile &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int const volatile &&>,int const volatile &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int *>,int * &&>::value);
		ExpectTrue(ds::is_same<ds::add_rvalue_reference_t<int * const>,int * const &&>::value);

	} TestcaseEnd(test_add_rvalue_reference_t);

	Testcase(test_remove_cv_t)
	{
		ExpectTrue(ds::is_same<ds::remove_cv_t<int >,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cv_t<int const>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cv_t<int volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cv_t<int const volatile>,int>::value);

	} TestcaseEnd(test_remove_cv_t);

	Testcase(test_remove_reference_t)
	{
		ExpectTrue(ds::is_same<ds::remove_reference_t<int>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int &>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int const &>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int volatile &>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int const volatile &>,int const volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int &&>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int const &&>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int volatile &&>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_reference_t<int const volatile &&>,int const volatile>::value);

	} TestcaseEnd(test_remove_reference_t);

	Testcase(test_remove_cvref_t)
	{
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int &>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int const &>,int >::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int volatile &>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int const volatile &>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int &&>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int const &&>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int volatile &&>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_cvref_t<int const volatile &&>,int>::value);

	} TestcaseEnd(test_remove_cvref_t);

	Testcase(test_remove_pointer_t)
	{
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int *>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const *>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile *>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile *>,int const volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int *>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const *>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile *>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile *>,int const volatile>::value);

		ExpectTrue(ds::is_same<ds::remove_pointer_t<int * const>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const * const>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile * const>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile * const>,int const volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int * const>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const * const>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile * const>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile * const>,int const volatile>::value);

		ExpectTrue(ds::is_same<ds::remove_pointer_t<int * volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const * volatile>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile * volatile>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile * volatile>,int const volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int * volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const * volatile>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile * volatile>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile * volatile>,int const volatile>::value);

		ExpectTrue(ds::is_same<ds::remove_pointer_t<int * const volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const * const volatile>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile * const volatile>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile * const volatile>,int const volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int * const volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const * const volatile>,int const>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int volatile * const volatile>,int volatile>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_t<int const volatile * const volatile>,int const volatile>::value);

	} TestcaseEnd(test_remove_pointer_t);

	Testcase(test_remove_pointer_cv_t)
	{
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int>,int *>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int *>,int *>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int const *>,int *>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int volatile *>,int *>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int const volatile *>,int *>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int * const >,int *>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int * volatile >,int *>::value);
		ExpectTrue(ds::is_same<ds::remove_pointer_cv_t<int * const volatile >,int *>::value);
	
	} TestcaseEnd(test_remove_pointer_cv_t);

	Testcase(test_base_type_t)
	{
		ExpectTrue(ds::is_same<ds::base_type_t<int>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int &>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const &>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int volatile &>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const volatile &>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int &&>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const &&>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int volatile &&>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const volatile &&>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int *>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const *>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int volatile *>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const volatile *>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int * const>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int * volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int * const volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const * const>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const * volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const * const volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int volatile * const>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int volatile * volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int volatile * const volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const volatile * const>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const volatile * volatile>,int>::value);
		ExpectTrue(ds::is_same<ds::base_type_t<int const volatile * const volatile>,int>::value);
	
	} TestcaseEnd(test_base_type_t);

	Testcase(test_copy_cv_t)
	{
		ExpectTrue(ds::is_same<ds::copy_cv_t<int,float>,float>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const,float>,float const>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const,float const>,float const>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile,float>,float volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile,float volatile>,float volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile,float>,float const volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile,float const volatile>,float const volatile>::value);
	
		ExpectTrue(ds::is_same<ds::copy_cv_t<int &,float>,float>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const &,float>,float const>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const &,float const>,float const>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile &,float>,float volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile &,float volatile>,float volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile &,float>,float const volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile &,float const volatile>,float const volatile>::value);
	
		ExpectTrue(ds::is_same<ds::copy_cv_t<int &,float &>,float &>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const &,float &>,float const &>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const &,float const &>,float const &>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile &,float &>,float volatile &>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile &,float volatile &>,float volatile &>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile &,float &>,float const volatile &>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile &,float const volatile &>,float const volatile &>::value);
	
		ExpectTrue(ds::is_same<ds::copy_cv_t<int &&,float>,float>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const &&,float>,float const>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const &&,float const>,float const>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile &&,float>,float volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int volatile &&,float volatile>,float volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile &&,float>,float const volatile>::value);
		ExpectTrue(ds::is_same<ds::copy_cv_t<int const volatile &&,float const volatile>,float const volatile>::value);
	
	} TestcaseEnd(test_copy_cv_t);

	template <bool condition_, ds::enable_if_t<condition_,int> = 0>  static constexpr int  _enable_if_foo();
	template <bool condition_, ds::enable_if_t<!condition_,int> = 0> static constexpr void _enable_if_foo();

	Testcase(test_enable_if_t)
	{
		ExpectTrue(ds::is_same<decltype(_enable_if_foo<true>()),int>::value);
		ExpectTrue(ds::is_same<decltype(_enable_if_foo<false>()),void>::value);

	} TestcaseEnd(test_enable_if_t);

	Testcase(test_conditional_t)
	{
		ExpectTrue(ds::is_same<ds::conditional_t<true,int,void>,int>::value);
		ExpectTrue(ds::is_same<ds::conditional_t<false,int,void>,void>::value);

	} TestcaseEnd(test_conditional_t);

	Testcase(test_are_all_true)
	{
		ExpectTrue(ds::are_all_true<ds::true_type>::value);
		ExpectTrue(ds::are_all_true<ds::true_type,ds::true_type>::value);
		ExpectFalse(ds::are_all_true<ds::true_type,ds::false_type>::value);
		ExpectFalse(ds::are_all_true<ds::false_type,ds::true_type>::value);
		ExpectTrue(ds::are_all_true<ds::true_type,ds::true_type,ds::true_type>::value);
		ExpectFalse(ds::are_all_true<ds::false_type,ds::true_type,ds::true_type>::value);
		ExpectFalse(ds::are_all_true<ds::true_type,ds::false_type,ds::true_type>::value);
		ExpectFalse(ds::are_all_true<ds::true_type,ds::true_type,ds::false_type>::value);

	} TestcaseEnd(test_are_all_true);

	Testcase(test_are_all_false)
	{
		ExpectTrue(ds::are_all_false<ds::false_type>::value);
		ExpectTrue(ds::are_all_false<ds::false_type,ds::false_type>::value);
		ExpectFalse(ds::are_all_false<ds::false_type,ds::true_type>::value);
		ExpectFalse(ds::are_all_false<ds::true_type,ds::false_type>::value);
		ExpectTrue(ds::are_all_false<ds::false_type,ds::false_type,ds::false_type>::value);
		ExpectFalse(ds::are_all_false<ds::true_type,ds::false_type,ds::false_type>::value);
		ExpectFalse(ds::are_all_false<ds::false_type,ds::true_type,ds::false_type>::value);
		ExpectFalse(ds::are_all_false<ds::false_type,ds::false_type,ds::true_type>::value);

	} TestcaseEnd(test_are_all_false);

	Testcase(test_is_same)
	{
		ExpectTrue(ds::is_same<int,int>::value);
		ExpectFalse(ds::is_same<int const,int>::value);
		ExpectFalse(ds::is_same<int volatile,int>::value);
		ExpectFalse(ds::is_same<int const volatile,int>::value);
		ExpectFalse(ds::is_same<int,void>::value);
		ExpectFalse(ds::is_same<int *,int>::value);
		ExpectFalse(ds::is_same<int &,int>::value);
		ExpectFalse(ds::is_same<int &&,int>::value);
	
	} TestcaseEnd(test_is_same);

	Testcase(test_is_type_in_pack)
	{
		ExpectTrue(ds::is_type_in_pack<int,int>::value);
		ExpectTrue(ds::is_type_in_pack<int,void,int>::value);
		ExpectTrue(ds::is_type_in_pack<int,int,void>::value);
		ExpectTrue(ds::is_type_in_pack<int,void,float,int>::value);
		ExpectTrue(ds::is_type_in_pack<int,void,int,float>::value);
		ExpectTrue(ds::is_type_in_pack<int,int,void,float>::value);
		ExpectFalse(ds::is_type_in_pack<int>::value);
		ExpectFalse(ds::is_type_in_pack<int,void>::value);
		ExpectFalse(ds::is_type_in_pack<int,void,float>::value);
	
	} TestcaseEnd(test_is_type_in_pack);

	Testcase(test_is_const)
	{
		ExpectTrue(ds::is_const<int const>::value);
		ExpectTrue(ds::is_const<int const volatile>::value);
		ExpectTrue(ds::is_const<int const &>::value);
		ExpectTrue(ds::is_const<int const volatile &>::value);
		ExpectTrue(ds::is_const<int const &&>::value);
		ExpectTrue(ds::is_const<int const volatile &&>::value);
		ExpectTrue(ds::is_const<int * const>::value);
		ExpectTrue(ds::is_const<int const * const>::value);
		ExpectTrue(ds::is_const<int volatile * const>::value);
		ExpectTrue(ds::is_const<int const volatile * const>::value);
		ExpectFalse(ds::is_const<int &>::value);
		ExpectFalse(ds::is_const<int &&>::value);
		ExpectFalse(ds::is_const<int volatile &>::value);
		ExpectFalse(ds::is_const<int volatile &&>::value);
		ExpectFalse(ds::is_const<int>::value);
		ExpectFalse(ds::is_const<int volatile>::value);
		ExpectFalse(ds::is_const<int *>::value);
		ExpectFalse(ds::is_const<int const *>::value);
		ExpectFalse(ds::is_const<int volatile *>::value);
		ExpectFalse(ds::is_const<int const volatile *>::value);

	} TestcaseEnd(test_is_const);

	Testcase(test_is_reference)
	{
		ExpectTrue(ds::is_reference<int &>::value);
		ExpectTrue(ds::is_reference<int &&>::value);
		ExpectTrue(ds::is_reference<int const &>::value);
		ExpectTrue(ds::is_reference<int const &&>::value);
		ExpectTrue(ds::is_reference<int volatile &>::value);
		ExpectTrue(ds::is_reference<int volatile &&>::value);
		ExpectTrue(ds::is_reference<int const volatile &>::value);
		ExpectTrue(ds::is_reference<int const volatile &&>::value);
		ExpectTrue(ds::is_reference<int (&)[]>::value);
		ExpectTrue(ds::is_reference<int (&)[3]>::value);
		ExpectTrue(ds::is_reference<int (&&)[]>::value);
		ExpectTrue(ds::is_reference<int (&&)[3]>::value);
		ExpectTrue(ds::is_reference<int const (&)[]>::value);
		ExpectTrue(ds::is_reference<int const (&)[3]>::value);
		ExpectTrue(ds::is_reference<int const (&&)[]>::value);
		ExpectTrue(ds::is_reference<int const (&&)[3]>::value);
		ExpectTrue(ds::is_reference<_func_ref_t>::value);
		
		ExpectFalse(ds::is_reference<int>::value);
		ExpectFalse(ds::is_reference<int *>::value);
		ExpectFalse(ds::is_reference<_func_t>::value);
		ExpectFalse(ds::is_reference<_func_ptr_t>::value);

	} TestcaseEnd(test_is_reference);

	Testcase(test_is_pointer)
	{
		ExpectTrue(ds::is_pointer<int *>::value);
		ExpectTrue(ds::is_pointer<int const *>::value);
		ExpectTrue(ds::is_pointer<int volatile *>::value);
		ExpectTrue(ds::is_pointer<int const volatile *>::value);
		ExpectTrue(ds::is_pointer<int const * const>::value);
		ExpectTrue(ds::is_pointer<int volatile * const>::value);
		ExpectTrue(ds::is_pointer<int const volatile * const>::value);
		ExpectTrue(ds::is_pointer<int const * volatile>::value);
		ExpectTrue(ds::is_pointer<int volatile * volatile>::value);
		ExpectTrue(ds::is_pointer<int const volatile * volatile>::value);
		ExpectTrue(ds::is_pointer<int const * const volatile>::value);
		ExpectTrue(ds::is_pointer<int volatile * const volatile>::value);
		ExpectTrue(ds::is_pointer<int const volatile * const volatile>::value);
		ExpectTrue(ds::is_pointer<_func_ptr_t>::value);
		
		ExpectFalse(ds::is_pointer<int>::value);
		ExpectFalse(ds::is_pointer<int &>::value);
		ExpectFalse(ds::is_pointer<int &&>::value);
		ExpectFalse(ds::is_pointer<_func_t>::value);
		ExpectFalse(ds::is_pointer<_func_ref_t>::value);

	} TestcaseEnd(test_is_pointer);

	Testcase(test_is_array)
	{
		ExpectTrue(ds::is_array<int[]>::value);
		ExpectTrue(ds::is_array<int[3]>::value);
		ExpectFalse(ds::is_array<int (&)[]>::value);
		ExpectFalse(ds::is_array<int (&)[3]>::value);
		ExpectFalse(ds::is_array<int (&&)[]>::value);
		ExpectFalse(ds::is_array<int (&&)[3]>::value);
		ExpectFalse(ds::is_array<int const (&)[]>::value);
		ExpectFalse(ds::is_array<int const (&)[3]>::value);
		ExpectFalse(ds::is_array<int const (&&)[]>::value);
		ExpectFalse(ds::is_array<int const (&&)[3]>::value);
		ExpectFalse(ds::is_array<int>::value);
		ExpectFalse(ds::is_array<int *>::value);
		ExpectFalse(ds::is_array<int &>::value);
		ExpectFalse(ds::is_array<int &&>::value);
	
	} TestcaseEnd(test_is_array);

	Testcase(test_is_signed)
	{
		ExpectTrue(ds::is_signed<char>::value);
		ExpectTrue(ds::is_signed<signed char>::value);
		ExpectTrue(ds::is_signed<signed short>::value);
		ExpectTrue(ds::is_signed<signed int>::value);
		ExpectTrue(ds::is_signed<signed long>::value);
		ExpectTrue(ds::is_signed<signed long long>::value);
		ExpectTrue(ds::is_signed<float>::value);
		ExpectTrue(ds::is_signed<double>::value);
		ExpectTrue(ds::is_signed<long double>::value);

		ExpectFalse(ds::is_signed<bool>::value);
		ExpectFalse(ds::is_signed<ds::char8_t>::value);
		ExpectFalse(ds::is_signed<char16_t>::value);
		ExpectFalse(ds::is_signed<char32_t>::value);
		ExpectFalse(ds::is_signed<unsigned char>::value);
		ExpectFalse(ds::is_signed<unsigned short>::value);
		ExpectFalse(ds::is_signed<unsigned int>::value);
		ExpectFalse(ds::is_signed<unsigned long>::value);
		ExpectFalse(ds::is_signed<unsigned long long>::value);

	} TestcaseEnd(test_is_signed);

	Testcase(test_is_unsigned)
	{
		ExpectTrue(ds::is_unsigned<bool>::value);
		ExpectTrue(ds::is_unsigned<ds::char8_t>::value);
		ExpectTrue(ds::is_unsigned<char16_t>::value);
		ExpectTrue(ds::is_unsigned<char32_t>::value);
		ExpectTrue(ds::is_unsigned<unsigned char>::value);
		ExpectTrue(ds::is_unsigned<unsigned short>::value);
		ExpectTrue(ds::is_unsigned<unsigned int>::value);
		ExpectTrue(ds::is_unsigned<unsigned long>::value);
		ExpectTrue(ds::is_unsigned<unsigned long long>::value);

		ExpectFalse(ds::is_unsigned<char>::value);
		ExpectFalse(ds::is_unsigned<signed char>::value);
		ExpectFalse(ds::is_unsigned<signed short>::value);
		ExpectFalse(ds::is_unsigned<signed int>::value);
		ExpectFalse(ds::is_unsigned<signed long>::value);
		ExpectFalse(ds::is_unsigned<signed long long>::value);
		ExpectFalse(ds::is_unsigned<float>::value);
		ExpectFalse(ds::is_unsigned<double>::value);
		ExpectFalse(ds::is_unsigned<long double>::value);

	} TestcaseEnd(test_is_unsigned);

	Testcase(test_is_integral)
	{
		ExpectTrue(ds::is_integral<bool>::value);
		ExpectTrue(ds::is_integral<char>::value);
		ExpectTrue(ds::is_integral<ds::char8_t>::value);
		ExpectTrue(ds::is_integral<char16_t>::value);
		ExpectTrue(ds::is_integral<char32_t>::value);
		ExpectTrue(ds::is_integral<wchar_t>::value);
		ExpectTrue(ds::is_integral<signed char>::value);
		ExpectTrue(ds::is_integral<unsigned char>::value);
		ExpectTrue(ds::is_integral<signed short>::value);
		ExpectTrue(ds::is_integral<unsigned short>::value);
		ExpectTrue(ds::is_integral<signed int>::value);
		ExpectTrue(ds::is_integral<unsigned int>::value);
		ExpectTrue(ds::is_integral<signed long>::value);
		ExpectTrue(ds::is_integral<unsigned long>::value);
		ExpectTrue(ds::is_integral<signed long long>::value);
		ExpectTrue(ds::is_integral<unsigned long long>::value);

		ExpectTrue(ds::is_integral<bool const>::value);
		ExpectTrue(ds::is_integral<char const>::value);
		ExpectTrue(ds::is_integral<ds::char8_t const>::value);
		ExpectTrue(ds::is_integral<char16_t const>::value);
		ExpectTrue(ds::is_integral<char32_t const>::value);
		ExpectTrue(ds::is_integral<wchar_t const>::value);
		ExpectTrue(ds::is_integral<signed char const>::value);
		ExpectTrue(ds::is_integral<unsigned char const>::value);
		ExpectTrue(ds::is_integral<signed short const>::value);
		ExpectTrue(ds::is_integral<unsigned short const>::value);
		ExpectTrue(ds::is_integral<signed int const>::value);
		ExpectTrue(ds::is_integral<unsigned int const>::value);
		ExpectTrue(ds::is_integral<signed long const>::value);
		ExpectTrue(ds::is_integral<unsigned long const>::value);
		ExpectTrue(ds::is_integral<signed long long const>::value);
		ExpectTrue(ds::is_integral<unsigned long long const>::value);

		ExpectTrue(ds::is_integral<bool volatile>::value);
		ExpectTrue(ds::is_integral<char volatile>::value);
		ExpectTrue(ds::is_integral<ds::char8_t volatile>::value);
		ExpectTrue(ds::is_integral<char16_t volatile>::value);
		ExpectTrue(ds::is_integral<char32_t volatile>::value);
		ExpectTrue(ds::is_integral<wchar_t volatile>::value);
		ExpectTrue(ds::is_integral<signed char volatile>::value);
		ExpectTrue(ds::is_integral<unsigned char volatile>::value);
		ExpectTrue(ds::is_integral<signed short volatile>::value);
		ExpectTrue(ds::is_integral<unsigned short volatile>::value);
		ExpectTrue(ds::is_integral<signed int volatile>::value);
		ExpectTrue(ds::is_integral<unsigned int volatile>::value);
		ExpectTrue(ds::is_integral<signed long volatile>::value);
		ExpectTrue(ds::is_integral<unsigned long volatile>::value);
		ExpectTrue(ds::is_integral<signed long long volatile>::value);
		ExpectTrue(ds::is_integral<unsigned long long volatile>::value);

		ExpectTrue(ds::is_integral<bool const volatile>::value);
		ExpectTrue(ds::is_integral<char const volatile>::value);
		ExpectTrue(ds::is_integral<ds::char8_t const volatile>::value);
		ExpectTrue(ds::is_integral<char16_t const volatile>::value);
		ExpectTrue(ds::is_integral<char32_t const volatile>::value);
		ExpectTrue(ds::is_integral<wchar_t const volatile>::value);
		ExpectTrue(ds::is_integral<signed char const volatile>::value);
		ExpectTrue(ds::is_integral<unsigned char const volatile>::value);
		ExpectTrue(ds::is_integral<signed short const volatile>::value);
		ExpectTrue(ds::is_integral<unsigned short const volatile>::value);
		ExpectTrue(ds::is_integral<signed int const volatile>::value);
		ExpectTrue(ds::is_integral<unsigned int const volatile>::value);
		ExpectTrue(ds::is_integral<signed long const volatile>::value);
		ExpectTrue(ds::is_integral<unsigned long const volatile>::value);
		ExpectTrue(ds::is_integral<signed long long const volatile>::value);
		ExpectTrue(ds::is_integral<unsigned long long const volatile>::value);

		ExpectFalse(ds::is_integral<bool &>::value);
		ExpectFalse(ds::is_integral<char &>::value);
		ExpectFalse(ds::is_integral<ds::char8_t &>::value);
		ExpectFalse(ds::is_integral<char16_t &>::value);
		ExpectFalse(ds::is_integral<char32_t &>::value);
		ExpectFalse(ds::is_integral<wchar_t &>::value);
		ExpectFalse(ds::is_integral<signed char &>::value);
		ExpectFalse(ds::is_integral<unsigned char &>::value);
		ExpectFalse(ds::is_integral<signed short &>::value);
		ExpectFalse(ds::is_integral<unsigned short &>::value);
		ExpectFalse(ds::is_integral<signed int &>::value);
		ExpectFalse(ds::is_integral<unsigned int &>::value);
		ExpectFalse(ds::is_integral<signed long &>::value);
		ExpectFalse(ds::is_integral<unsigned long &>::value);
		ExpectFalse(ds::is_integral<signed long long &>::value);
		ExpectFalse(ds::is_integral<unsigned long long &>::value);

		ExpectFalse(ds::is_integral<bool &&>::value);
		ExpectFalse(ds::is_integral<char &&>::value);
		ExpectFalse(ds::is_integral<ds::char8_t &&>::value);
		ExpectFalse(ds::is_integral<char16_t &&>::value);
		ExpectFalse(ds::is_integral<char32_t &&>::value);
		ExpectFalse(ds::is_integral<wchar_t &&>::value);
		ExpectFalse(ds::is_integral<signed char &&>::value);
		ExpectFalse(ds::is_integral<unsigned char &&>::value);
		ExpectFalse(ds::is_integral<signed short &&>::value);
		ExpectFalse(ds::is_integral<unsigned short &&>::value);
		ExpectFalse(ds::is_integral<signed int &&>::value);
		ExpectFalse(ds::is_integral<unsigned int &&>::value);
		ExpectFalse(ds::is_integral<signed long &&>::value);
		ExpectFalse(ds::is_integral<unsigned long &&>::value);
		ExpectFalse(ds::is_integral<signed long long &&>::value);
		ExpectFalse(ds::is_integral<unsigned long long &&>::value);

		ExpectFalse(ds::is_integral<void>::value);
		ExpectFalse(ds::is_integral<float>::value);
		ExpectFalse(ds::is_integral<double>::value);
		ExpectFalse(ds::is_integral<long double>::value);

	} TestcaseEnd(test_is_integral);

	Testcase(test_is_floating_point)
	{
		ExpectTrue(ds::is_floating_point<float>::value);
		ExpectTrue(ds::is_floating_point<double>::value);
		ExpectTrue(ds::is_floating_point<long double>::value);
		
		ExpectTrue(ds::is_floating_point<float const>::value);
		ExpectTrue(ds::is_floating_point<double const>::value);
		ExpectTrue(ds::is_floating_point<long double const>::value);
		
		ExpectTrue(ds::is_floating_point<float volatile>::value);
		ExpectTrue(ds::is_floating_point<double volatile>::value);
		ExpectTrue(ds::is_floating_point<long double volatile>::value);
		
		ExpectTrue(ds::is_floating_point<float const volatile>::value);
		ExpectTrue(ds::is_floating_point<double const volatile>::value);
		ExpectTrue(ds::is_floating_point<long double const volatile>::value);
		
		ExpectFalse(ds::is_floating_point<void>::value);
		ExpectFalse(ds::is_floating_point<bool>::value);
		ExpectFalse(ds::is_floating_point<char>::value);
		ExpectFalse(ds::is_floating_point<ds::char8_t>::value);
		ExpectFalse(ds::is_floating_point<char16_t>::value);
		ExpectFalse(ds::is_floating_point<char32_t>::value);
		ExpectFalse(ds::is_floating_point<wchar_t>::value);
		ExpectFalse(ds::is_floating_point<signed char>::value);
		ExpectFalse(ds::is_floating_point<unsigned char>::value);
		ExpectFalse(ds::is_floating_point<signed short>::value);
		ExpectFalse(ds::is_floating_point<unsigned short>::value);
		ExpectFalse(ds::is_floating_point<signed int>::value);
		ExpectFalse(ds::is_floating_point<unsigned int>::value);
		ExpectFalse(ds::is_floating_point<signed long>::value);
		ExpectFalse(ds::is_floating_point<unsigned long>::value);
		ExpectFalse(ds::is_floating_point<signed long long>::value);
		ExpectFalse(ds::is_floating_point<unsigned long long>::value);

	
	} TestcaseEnd(test_is_floating_point);

	Testcase(test_is_arithmetic)
	{
		ExpectTrue(ds::is_arithmetic<bool>::value);
		ExpectTrue(ds::is_arithmetic<char>::value);
		ExpectTrue(ds::is_arithmetic<ds::char8_t>::value);
		ExpectTrue(ds::is_arithmetic<char16_t>::value);
		ExpectTrue(ds::is_arithmetic<char32_t>::value);
		ExpectTrue(ds::is_arithmetic<wchar_t>::value);
		ExpectTrue(ds::is_arithmetic<signed char>::value);
		ExpectTrue(ds::is_arithmetic<unsigned char>::value);
		ExpectTrue(ds::is_arithmetic<signed short>::value);
		ExpectTrue(ds::is_arithmetic<unsigned short>::value);
		ExpectTrue(ds::is_arithmetic<signed int>::value);
		ExpectTrue(ds::is_arithmetic<unsigned int>::value);
		ExpectTrue(ds::is_arithmetic<signed long>::value);
		ExpectTrue(ds::is_arithmetic<unsigned long>::value);
		ExpectTrue(ds::is_arithmetic<signed long long>::value);
		ExpectTrue(ds::is_arithmetic<unsigned long long>::value);
		ExpectTrue(ds::is_arithmetic<float>::value);
		ExpectTrue(ds::is_arithmetic<double>::value);
		ExpectTrue(ds::is_arithmetic<long double>::value);
		
		ExpectFalse(ds::is_arithmetic<void>::value);
	
	} TestcaseEnd(test_is_arithmetic);

	Testcase(test_is_scalar)
	{
		ExpectTrue(ds::is_scalar<bool>::value);
		ExpectTrue(ds::is_scalar<char>::value);
		ExpectTrue(ds::is_scalar<ds::char8_t>::value);
		ExpectTrue(ds::is_scalar<char16_t>::value);
		ExpectTrue(ds::is_scalar<char32_t>::value);
		ExpectTrue(ds::is_scalar<wchar_t>::value);
		ExpectTrue(ds::is_scalar<signed char>::value);
		ExpectTrue(ds::is_scalar<unsigned char>::value);
		ExpectTrue(ds::is_scalar<signed short>::value);
		ExpectTrue(ds::is_scalar<unsigned short>::value);
		ExpectTrue(ds::is_scalar<signed int>::value);
		ExpectTrue(ds::is_scalar<unsigned int>::value);
		ExpectTrue(ds::is_scalar<signed long>::value);
		ExpectTrue(ds::is_scalar<unsigned long>::value);
		ExpectTrue(ds::is_scalar<signed long long>::value);
		ExpectTrue(ds::is_scalar<unsigned long long>::value);
		ExpectTrue(ds::is_scalar<float>::value);
		ExpectTrue(ds::is_scalar<double>::value);
		ExpectTrue(ds::is_scalar<long double>::value);
		ExpectTrue(ds::is_scalar<_enum>::value);
		ExpectTrue(ds::is_scalar<_enum_class>::value);
		ExpectTrue(ds::is_scalar<int *>::value);
		ExpectTrue(ds::is_scalar<ds::nullptr_t>::value);
		
		ExpectFalse(ds::is_scalar<void>::value);
	
	} TestcaseEnd(test_is_scalar);

	Testcase(test_is_string)
	{
		ExpectTrue(ds::is_string<char[]>::value);
		ExpectTrue(ds::is_string<char[3]>::value);
		ExpectTrue(ds::is_string<char(*)[]>::value);
		ExpectTrue(ds::is_string<char(*)[3]>::value);
		ExpectTrue(ds::is_string<char(&)[]>::value);
		ExpectTrue(ds::is_string<char(&)[3]>::value);
		ExpectTrue(ds::is_string<char const (*)[]>::value);
		ExpectTrue(ds::is_string<char const (*)[3]>::value);
		ExpectTrue(ds::is_string<char const (&)[]>::value);
		ExpectTrue(ds::is_string<char const (&)[3]>::value);
		ExpectTrue(ds::is_string<char volatile (*)[]>::value);
		ExpectTrue(ds::is_string<char volatile (*)[3]>::value);
		ExpectTrue(ds::is_string<char volatile (&)[]>::value);
		ExpectTrue(ds::is_string<char volatile (&)[3]>::value);
		ExpectTrue(ds::is_string<char const volatile (*)[]>::value);
		ExpectTrue(ds::is_string<char const volatile (*)[3]>::value);
		ExpectTrue(ds::is_string<char const volatile (&)[]>::value);
		ExpectTrue(ds::is_string<char const volatile (&)[3]>::value);
		ExpectTrue(ds::is_string<char *>::value);
		ExpectTrue(ds::is_string<char const *>::value);
		ExpectTrue(ds::is_string<char volatile *>::value);
		ExpectTrue(ds::is_string<char const volatile *>::value);

		ExpectFalse(ds::is_string<void>::value);
		ExpectFalse(ds::is_string<char>::value);
		ExpectFalse(ds::is_string<int>::value);
	
	} TestcaseEnd(test_is_string);

	Testcase(test_is_enum)
	{
		ExpectTrue(ds::is_enum<_enum>::value);
		ExpectTrue(ds::is_enum<_enum_class>::value);

		ExpectFalse(ds::is_enum<_struct>::value);
		ExpectFalse(ds::is_enum<_class>::value);
		ExpectFalse(ds::is_enum<_union>::value);
		ExpectFalse(ds::is_enum<_lambda_t>::value);
		ExpectFalse(ds::is_enum<_func_t>::value);
		ExpectFalse(ds::is_enum<_func_ptr_t>::value);
		ExpectFalse(ds::is_enum<_func_ref_t>::value);
		ExpectFalse(ds::is_enum<bool>::value);
		ExpectFalse(ds::is_enum<char>::value);
		ExpectFalse(ds::is_enum<ds::char8_t>::value);
		ExpectFalse(ds::is_enum<char16_t>::value);
		ExpectFalse(ds::is_enum<char32_t>::value);
		ExpectFalse(ds::is_enum<wchar_t>::value);
		ExpectFalse(ds::is_enum<signed char>::value);
		ExpectFalse(ds::is_enum<unsigned char>::value);
		ExpectFalse(ds::is_enum<signed short>::value);
		ExpectFalse(ds::is_enum<unsigned short>::value);
		ExpectFalse(ds::is_enum<signed int>::value);
		ExpectFalse(ds::is_enum<unsigned int>::value);
		ExpectFalse(ds::is_enum<signed long>::value);
		ExpectFalse(ds::is_enum<unsigned long>::value);
		ExpectFalse(ds::is_enum<signed long long>::value);
		ExpectFalse(ds::is_enum<unsigned long long>::value);
		ExpectFalse(ds::is_enum<float>::value);
		ExpectFalse(ds::is_enum<double>::value);
		ExpectFalse(ds::is_enum<long double>::value);
		ExpectFalse(ds::is_enum<void>::value);
	
	} TestcaseEnd(test_is_enum);

	Testcase(test_is_class)
	{
		ExpectTrue(ds::is_class<_struct>::value);
		ExpectTrue(ds::is_class<_class>::value);
		ExpectTrue(ds::is_class<_lambda_t>::value);

		ExpectFalse(ds::is_class<_enum>::value);
		ExpectFalse(ds::is_class<_enum_class>::value);
		ExpectFalse(ds::is_class<_union>::value);
		ExpectFalse(ds::is_class<_func_t>::value);
		ExpectFalse(ds::is_class<_func_ptr_t>::value);
		ExpectFalse(ds::is_class<_func_ref_t>::value);
		ExpectFalse(ds::is_class<bool>::value);
		ExpectFalse(ds::is_class<char>::value);
		ExpectFalse(ds::is_class<ds::char8_t>::value);
		ExpectFalse(ds::is_class<char16_t>::value);
		ExpectFalse(ds::is_class<char32_t>::value);
		ExpectFalse(ds::is_class<wchar_t>::value);
		ExpectFalse(ds::is_class<signed char>::value);
		ExpectFalse(ds::is_class<unsigned char>::value);
		ExpectFalse(ds::is_class<signed short>::value);
		ExpectFalse(ds::is_class<unsigned short>::value);
		ExpectFalse(ds::is_class<signed int>::value);
		ExpectFalse(ds::is_class<unsigned int>::value);
		ExpectFalse(ds::is_class<signed long>::value);
		ExpectFalse(ds::is_class<unsigned long>::value);
		ExpectFalse(ds::is_class<signed long long>::value);
		ExpectFalse(ds::is_class<unsigned long long>::value);
		ExpectFalse(ds::is_class<float>::value);
		ExpectFalse(ds::is_class<double>::value);
		ExpectFalse(ds::is_class<long double>::value);
		ExpectFalse(ds::is_class<void>::value);
	
	} TestcaseEnd(test_is_class);

	Testcase(test_is_function)
	{
		ExpectTrue(ds::is_function<_func_t>::value);
		ExpectTrue(ds::is_function<ds::remove_pointer_t<_func_ptr_t>>::value);
		ExpectTrue(ds::is_function<ds::remove_reference_t<_func_ref_t>>::value);
		
		ExpectFalse(ds::is_function<_enum>::value);
		ExpectFalse(ds::is_function<_enum_class>::value);
		ExpectFalse(ds::is_function<_struct>::value);
		ExpectFalse(ds::is_function<_class>::value);
		ExpectFalse(ds::is_function<_union>::value);
		ExpectFalse(ds::is_function<_lambda_t>::value);
		ExpectFalse(ds::is_function<_func_ptr_t>::value);
		ExpectFalse(ds::is_function<_func_ref_t>::value);
		ExpectFalse(ds::is_function<bool>::value);
		ExpectFalse(ds::is_function<char>::value);
		ExpectFalse(ds::is_function<ds::char8_t>::value);
		ExpectFalse(ds::is_function<char16_t>::value);
		ExpectFalse(ds::is_function<char32_t>::value);
		ExpectFalse(ds::is_function<wchar_t>::value);
		ExpectFalse(ds::is_function<signed char>::value);
		ExpectFalse(ds::is_function<unsigned char>::value);
		ExpectFalse(ds::is_function<signed short>::value);
		ExpectFalse(ds::is_function<unsigned short>::value);
		ExpectFalse(ds::is_function<signed int>::value);
		ExpectFalse(ds::is_function<unsigned int>::value);
		ExpectFalse(ds::is_function<signed long>::value);
		ExpectFalse(ds::is_function<unsigned long>::value);
		ExpectFalse(ds::is_function<signed long long>::value);
		ExpectFalse(ds::is_function<unsigned long long>::value);
		ExpectFalse(ds::is_function<float>::value);
		ExpectFalse(ds::is_function<double>::value);
		ExpectFalse(ds::is_function<long double>::value);
		ExpectFalse(ds::is_function<void>::value);
	
	} TestcaseEnd(test_is_function);

	Testcase(test_is_member_object_pointer)
	{
		ExpectTrue(ds::is_member_object_pointer<decltype(&_struct::bar)>::value);

		ExpectFalse(ds::is_member_object_pointer<decltype(&_struct::foo)>::value);
		ExpectFalse(ds::is_member_object_pointer<_func_t>::value);
		ExpectFalse(ds::is_member_object_pointer<ds::remove_pointer_t<_func_ptr_t>>::value);
		ExpectFalse(ds::is_member_object_pointer<ds::remove_reference_t<_func_ref_t>>::value);
		ExpectFalse(ds::is_member_object_pointer<_enum>::value);
		ExpectFalse(ds::is_member_object_pointer<_enum_class>::value);
		ExpectFalse(ds::is_member_object_pointer<_struct>::value);
		ExpectFalse(ds::is_member_object_pointer<_class>::value);
		ExpectFalse(ds::is_member_object_pointer<_union>::value);
		ExpectFalse(ds::is_member_object_pointer<_lambda_t>::value);
		ExpectFalse(ds::is_member_object_pointer<_func_ptr_t>::value);
		ExpectFalse(ds::is_member_object_pointer<_func_ref_t>::value);
		ExpectFalse(ds::is_member_object_pointer<bool>::value);
		ExpectFalse(ds::is_member_object_pointer<char>::value);
		ExpectFalse(ds::is_member_object_pointer<ds::char8_t>::value);
		ExpectFalse(ds::is_member_object_pointer<char16_t>::value);
		ExpectFalse(ds::is_member_object_pointer<char32_t>::value);
		ExpectFalse(ds::is_member_object_pointer<wchar_t>::value);
		ExpectFalse(ds::is_member_object_pointer<signed char>::value);
		ExpectFalse(ds::is_member_object_pointer<unsigned char>::value);
		ExpectFalse(ds::is_member_object_pointer<signed short>::value);
		ExpectFalse(ds::is_member_object_pointer<unsigned short>::value);
		ExpectFalse(ds::is_member_object_pointer<signed int>::value);
		ExpectFalse(ds::is_member_object_pointer<unsigned int>::value);
		ExpectFalse(ds::is_member_object_pointer<signed long>::value);
		ExpectFalse(ds::is_member_object_pointer<unsigned long>::value);
		ExpectFalse(ds::is_member_object_pointer<signed long long>::value);
		ExpectFalse(ds::is_member_object_pointer<unsigned long long>::value);
		ExpectFalse(ds::is_member_object_pointer<float>::value);
		ExpectFalse(ds::is_member_object_pointer<double>::value);
		ExpectFalse(ds::is_member_object_pointer<long double>::value);
		ExpectFalse(ds::is_member_object_pointer<void>::value);
	
	} TestcaseEnd(test_is_member_object_pointer);

	Testcase(test_is_member_function_pointer)
	{
		ExpectTrue(ds::is_member_function_pointer<decltype(&_struct::foo)>::value);

		ExpectFalse(ds::is_member_function_pointer<decltype(&_struct::bar)>::value);
		ExpectFalse(ds::is_member_function_pointer<_func_t>::value);
		ExpectFalse(ds::is_member_function_pointer<ds::remove_pointer_t<_func_ptr_t>>::value);
		ExpectFalse(ds::is_member_function_pointer<ds::remove_reference_t<_func_ref_t>>::value);
		ExpectFalse(ds::is_member_function_pointer<_enum>::value);
		ExpectFalse(ds::is_member_function_pointer<_enum_class>::value);
		ExpectFalse(ds::is_member_function_pointer<_struct>::value);
		ExpectFalse(ds::is_member_function_pointer<_class>::value);
		ExpectFalse(ds::is_member_function_pointer<_union>::value);
		ExpectFalse(ds::is_member_function_pointer<_lambda_t>::value);
		ExpectFalse(ds::is_member_function_pointer<_func_ptr_t>::value);
		ExpectFalse(ds::is_member_function_pointer<_func_ref_t>::value);
		ExpectFalse(ds::is_member_function_pointer<bool>::value);
		ExpectFalse(ds::is_member_function_pointer<char>::value);
		ExpectFalse(ds::is_member_function_pointer<ds::char8_t>::value);
		ExpectFalse(ds::is_member_function_pointer<char16_t>::value);
		ExpectFalse(ds::is_member_function_pointer<char32_t>::value);
		ExpectFalse(ds::is_member_function_pointer<wchar_t>::value);
		ExpectFalse(ds::is_member_function_pointer<signed char>::value);
		ExpectFalse(ds::is_member_function_pointer<unsigned char>::value);
		ExpectFalse(ds::is_member_function_pointer<signed short>::value);
		ExpectFalse(ds::is_member_function_pointer<unsigned short>::value);
		ExpectFalse(ds::is_member_function_pointer<signed int>::value);
		ExpectFalse(ds::is_member_function_pointer<unsigned int>::value);
		ExpectFalse(ds::is_member_function_pointer<signed long>::value);
		ExpectFalse(ds::is_member_function_pointer<unsigned long>::value);
		ExpectFalse(ds::is_member_function_pointer<signed long long>::value);
		ExpectFalse(ds::is_member_function_pointer<unsigned long long>::value);
		ExpectFalse(ds::is_member_function_pointer<float>::value);
		ExpectFalse(ds::is_member_function_pointer<double>::value);
		ExpectFalse(ds::is_member_function_pointer<long double>::value);
		ExpectFalse(ds::is_member_function_pointer<void>::value);
	
	} TestcaseEnd(test_is_member_function_pointer);

	Testcase(test_is_destructible)
	{
		ExpectTrue(ds::is_destructible<A>::value);
		ExpectTrue(ds::is_destructible<B>::value);
		ExpectTrue(ds::is_destructible<C>::value);
		ExpectTrue(ds::is_destructible<D>::value);
		ExpectTrue(ds::is_destructible<E>::value);
		ExpectTrue(ds::is_destructible<F>::value);
		ExpectFalse(ds::is_destructible<_indestructible>::value);
	
	} TestcaseEnd(test_is_destructible);

	Testcase(test_is_trivially_destructible)
	{ 
		ExpectTrue(ds::is_trivially_destructible<int>::value);
		ExpectTrue(ds::is_trivially_destructible<A>::value); 
		ExpectTrue(ds::is_trivially_destructible<B>::value); 
		ExpectTrue(ds::is_trivially_destructible<E>::value); 
		ExpectTrue(ds::is_trivially_destructible<F>::value); 

		ExpectFalse(ds::is_trivially_destructible<void>::value);
		ExpectFalse(ds::is_trivially_destructible<C>::value);
		ExpectFalse(ds::is_trivially_destructible<D>::value);

	} TestcaseEnd(test_is_trivially_destructible);

	Testcase(test_is_virtually_destructible)
	{
		ExpectTrue(ds::is_virtually_destructible<C>::value);
		ExpectTrue(ds::is_virtually_destructible<D>::value);

		ExpectFalse(ds::is_virtually_destructible<int>::value);
		ExpectFalse(ds::is_virtually_destructible<A>::value);
		ExpectFalse(ds::is_virtually_destructible<B>::value);
		ExpectFalse(ds::is_virtually_destructible<E>::value);

	} TestcaseEnd(test_is_virtually_destructible);

	Testcase(test_is_aggregate_initializable)
	{
		struct _S { int i; float f; };
		ExpectTrue(ds::is_aggregate_initializable<int,int>::value);
		ExpectTrue(ds::is_aggregate_initializable<int[2],int,int>::value);
		ExpectTrue(ds::is_aggregate_initializable<_S,int,float>::value);
		ExpectFalse(ds::is_aggregate_initializable<_S,int,int>::value);
		ExpectTrue(ds::is_aggregate_initializable<A>::value);
		ExpectTrue(ds::is_aggregate_initializable<A,A &&>::value);
		ExpectTrue(ds::is_aggregate_initializable<A,A const &>::value);
		ExpectTrue(ds::is_aggregate_initializable<B,int>::value);
		ExpectTrue(ds::is_aggregate_initializable<B,B &&>::value);
		ExpectTrue(ds::is_aggregate_initializable<B,B const &>::value);
		ExpectTrue(ds::is_aggregate_initializable<C>::value);
		ExpectTrue(ds::is_aggregate_initializable<C,C &&>::value);
		ExpectTrue(ds::is_aggregate_initializable<D,D &&>::value);
		ExpectTrue(ds::is_aggregate_initializable<E,E &&>::value);
		ExpectTrue(ds::is_aggregate_initializable<E,E const &>::value);
		ExpectTrue(ds::is_aggregate_initializable<F>::value);
		ExpectTrue(ds::is_aggregate_initializable<F,F &&>::value);
		ExpectTrue(ds::is_aggregate_initializable<F,F const &>::value);

		ExpectFalse(ds::is_aggregate_initializable<int,void>::value);
		ExpectFalse(ds::is_aggregate_initializable<A,int>::value);
		ExpectFalse(ds::is_aggregate_initializable<B>::value);
		ExpectFalse(ds::is_aggregate_initializable<B,A &&>::value);
		ExpectFalse(ds::is_aggregate_initializable<B,A const &>::value);
		ExpectFalse(ds::is_aggregate_initializable<C,C const &>::value);
		ExpectFalse(ds::is_aggregate_initializable<D, D const &>::value);

	} TestcaseEnd(test_is_aggregate_initializable);

	Testcase(test_is_constructible)
	{
		ExpectTrue(ds::is_constructible<_default_constructible>::value);
		ExpectTrue(ds::is_constructible<int,int>::value);
		ExpectTrue(ds::is_constructible<A>::value);
		ExpectTrue(ds::is_constructible<A,A &&>::value);
		ExpectTrue(ds::is_constructible<A,A const &>::value);
		ExpectTrue(ds::is_constructible<B,int>::value);
		ExpectTrue(ds::is_constructible<B,B &&>::value);
		ExpectTrue(ds::is_constructible<B,B const &>::value);
		ExpectTrue(ds::is_constructible<C>::value);
		ExpectTrue(ds::is_constructible<C,C &&>::value);
		ExpectTrue(ds::is_constructible<D,D &&>::value);
		ExpectTrue(ds::is_constructible<E,E &&>::value);
		ExpectTrue(ds::is_constructible<E,E const &>::value);
		ExpectTrue(ds::is_constructible<F>::value);
		ExpectTrue(ds::is_constructible<F,F &&>::value);
		ExpectTrue(ds::is_constructible<F,F const &>::value);

		ExpectFalse(ds::is_constructible<_default_inconstructible>::value);
		ExpectFalse(ds::is_constructible<int,void>::value);
		ExpectFalse(ds::is_constructible<A,int>::value);
		ExpectFalse(ds::is_constructible<B>::value);
		ExpectFalse(ds::is_constructible<B,A &&>::value);
		ExpectFalse(ds::is_constructible<B,A const &>::value);
		ExpectFalse(ds::is_constructible<C,C const &>::value);
		ExpectFalse(ds::is_constructible<D, D const &>::value);

	} TestcaseEnd(test_is_constructible);

	Testcase(test_is_move_constructible)
	{
		ExpectTrue(ds::is_move_constructible<int>::value);
		ExpectTrue(ds::is_move_constructible<_move_constructible>::value);
		ExpectTrue(ds::is_move_constructible<_trivially_move_constructible>::value);

		ExpectFalse(ds::is_move_constructible<_move_inconstructible>::value);
	
	} TestcaseEnd(test_is_move_constructible);

	Testcase(test_is_copy_constructible)
	{
		ExpectTrue(ds::is_copy_constructible<int>::value);
		ExpectTrue(ds::is_copy_constructible<_copy_constructible>::value);
		ExpectTrue(ds::is_copy_constructible<_trivially_copy_constructible>::value);

		ExpectFalse(ds::is_copy_constructible<_copy_inconstructible>::value);
	
	} TestcaseEnd(test_is_copy_constructible);

	Testcase(test_is_trivially_constructible)
	{
		ExpectTrue(ds::is_trivially_constructible<int>::value);
		ExpectTrue(ds::is_trivially_constructible<_trivially_default_constructible>::value);
		ExpectTrue(ds::is_trivially_constructible<_trivially_move_constructible,_trivially_move_constructible &&>::value);
		ExpectTrue(ds::is_trivially_constructible<_trivially_copy_constructible,_trivially_copy_constructible const &>::value);

		ExpectFalse(ds::is_trivially_constructible<_default_constructible>::value);
	
	} TestcaseEnd(test_is_trivially_constructible);

	Testcase(test_is_trivially_move_constructible)
	{
		ExpectTrue(ds::is_trivially_move_constructible<int>::value);
		ExpectTrue(ds::is_trivially_move_constructible<_trivially_move_constructible>::value);

		ExpectFalse(ds::is_trivially_move_constructible<_move_constructible>::value);
		ExpectFalse(ds::is_trivially_move_constructible<_move_inconstructible>::value);
	
	} TestcaseEnd(test_is_trivially_move_constructible);

	Testcase(test_is_trivially_copy_constructible)
	{
		ExpectTrue(ds::is_trivially_copy_constructible<int>::value);
		ExpectTrue(ds::is_trivially_copy_constructible<_trivially_copy_constructible>::value);

		ExpectFalse(ds::is_trivially_copy_constructible<_copy_constructible>::value);
		ExpectFalse(ds::is_trivially_copy_constructible<_copy_inconstructible>::value);
	
	} TestcaseEnd(test_is_trivially_copy_constructible);

	Testcase(test_is_assignable)
	{
		ExpectTrue(ds::is_assignable<_assignable,int>::value);

		ExpectFalse(ds::is_assignable<_unassignable,int>::value);
	
	} TestcaseEnd(test_is_assignable);

	Testcase(test_is_move_assignable)
	{
		ExpectTrue(ds::is_move_assignable<int>::value);
		ExpectTrue(ds::is_move_assignable<_move_assignable>::value);
		ExpectTrue(ds::is_move_assignable<_trivially_move_assignable>::value);

		ExpectFalse(ds::is_move_assignable<_move_unassignable>::value);
	
	} TestcaseEnd(test_is_move_assignable);

	Testcase(test_is_copy_assignable)
	{
		ExpectTrue(ds::is_copy_assignable<int>::value);
		ExpectTrue(ds::is_copy_assignable<_copy_assignable>::value);
		ExpectTrue(ds::is_copy_assignable<_trivially_copy_assignable>::value);

		ExpectFalse(ds::is_copy_assignable<_copy_unassignable>::value);
	
	} TestcaseEnd(test_is_copy_assignable);

	Testcase(test_is_trivially_assignable)
	{
		ExpectTrue(ds::is_trivially_assignable<_trivially_move_assignable,_trivially_move_assignable &&>::value);
		ExpectTrue(ds::is_trivially_assignable<_trivially_copy_assignable,_trivially_copy_assignable const &>::value);

		ExpectFalse(ds::is_trivially_assignable<_move_unassignable,_move_unassignable &&>::value);
		ExpectFalse(ds::is_trivially_assignable<_copy_unassignable,_copy_unassignable const &>::value);
	
	} TestcaseEnd(test_is_trivially_assignable);

	Testcase(test_is_trivially_move_assignable)
	{
		ExpectTrue(ds::is_trivially_move_assignable<_trivially_move_assignable>::value);

		ExpectFalse(ds::is_trivially_move_assignable<_move_assignable>::value);
		ExpectFalse(ds::is_trivially_move_assignable<_move_unassignable>::value);
	
	} TestcaseEnd(test_is_trivially_move_assignable);

	Testcase(test_is_trivially_copy_assignable)
	{
		ExpectTrue(ds::is_trivially_copy_assignable<_trivially_copy_assignable>::value);

		ExpectFalse(ds::is_trivially_copy_assignable<_copy_assignable>::value);
		ExpectFalse(ds::is_trivially_copy_assignable<_copy_unassignable>::value);
	
	} TestcaseEnd(test_is_trivially_copy_assignable);

	Testcase(test_is_static_castable)
	{
		ExpectTrue(ds::is_static_castable<int,int>::value);
		ExpectTrue(ds::is_static_castable<int,float>::value);
		ExpectTrue(ds::is_static_castable<float,int>::value);
		ExpectTrue(ds::is_static_castable<D,C>::value);
		ExpectTrue(ds::is_static_castable<E,B>::value);
		ExpectTrue(ds::is_static_castable<F,A>::value);
		ExpectTrue(ds::is_static_castable<D &,C &>::value);
		ExpectTrue(ds::is_static_castable<E &,B &>::value);
		ExpectTrue(ds::is_static_castable<F &,A &>::value);
	
		ExpectFalse(ds::is_static_castable<D,B>::value);
		ExpectFalse(ds::is_static_castable<D,A>::value);
		ExpectFalse(ds::is_static_castable<E,C>::value);
		ExpectFalse(ds::is_static_castable<E,A>::value);
		ExpectFalse(ds::is_static_castable<F,C>::value);
		ExpectFalse(ds::is_static_castable<F,B>::value);
		ExpectFalse(ds::is_static_castable<D &,B &>::value);
		ExpectFalse(ds::is_static_castable<D &,A &>::value);
		ExpectFalse(ds::is_static_castable<E &,C &>::value);
		ExpectFalse(ds::is_static_castable<E &,A &>::value);
		ExpectFalse(ds::is_static_castable<F &,C &>::value);
		ExpectFalse(ds::is_static_castable<F &,B &>::value);
	
	
	} TestcaseEnd(test_is_static_castable);

	Testcase(test_is_dynamic_castable)
	{
		ExpectTrue(ds::is_dynamic_castable<D &,C &>::value);
		ExpectTrue(ds::is_dynamic_castable<E &,B &>::value);
		ExpectTrue(ds::is_dynamic_castable<F &,A &>::value);
		ExpectTrue(ds::is_dynamic_castable<D &,B &>::value);
		ExpectTrue(ds::is_dynamic_castable<D &,A &>::value);
	
		ExpectFalse(ds::is_dynamic_castable<int,int>::value);
		ExpectFalse(ds::is_dynamic_castable<int,float>::value);
		ExpectFalse(ds::is_dynamic_castable<float,int>::value);
		ExpectFalse(ds::is_dynamic_castable<D,B>::value);
		ExpectFalse(ds::is_dynamic_castable<D,A>::value);
		ExpectFalse(ds::is_dynamic_castable<E,C>::value);
		ExpectFalse(ds::is_dynamic_castable<E,A>::value);
		ExpectFalse(ds::is_dynamic_castable<F,C>::value);
		ExpectFalse(ds::is_dynamic_castable<F,B>::value);
		ExpectFalse(ds::is_dynamic_castable<E &,C &>::value);
		ExpectFalse(ds::is_dynamic_castable<E &,A &>::value);
		ExpectFalse(ds::is_dynamic_castable<F &,C &>::value);
		ExpectFalse(ds::is_dynamic_castable<F &,B &>::value);
	
	} TestcaseEnd(test_is_dynamic_castable);

};


TestRegistry(meta_functions_test)
{
	Register(test_integral_constant)
	Register(test_bool_constant)
	Register(test_add_pointer_t)
	Register(test_add_lvalue_reference_t)
	Register(test_add_rvalue_reference_t)
	Register(test_remove_cv_t)
	Register(test_remove_reference_t)
	Register(test_remove_cvref_t)
	Register(test_remove_pointer_t)
	Register(test_remove_pointer_cv_t)
	Register(test_base_type_t)
	Register(test_copy_cv_t)
	Register(test_enable_if_t)
	Register(test_conditional_t)
	Register(test_are_all_true)
	Register(test_are_all_false)
	Register(test_is_same)
	Register(test_is_type_in_pack)
	Register(test_is_const)
	Register(test_is_reference)
	Register(test_is_pointer)
	Register(test_is_array)
	Register(test_is_signed)
	Register(test_is_unsigned)
	Register(test_is_integral)
	Register(test_is_floating_point)
	Register(test_is_arithmetic)
	Register(test_is_scalar)
	Register(test_is_string)
	Register(test_is_enum)
	Register(test_is_class)
	Register(test_is_function)
	Register(test_is_member_object_pointer)
	Register(test_is_member_function_pointer)
	Register(test_is_destructible)
	Register(test_is_trivially_destructible)
	Register(test_is_virtually_destructible)
	Register(test_is_aggregate_initializable)
	Register(test_is_constructible)
	Register(test_is_move_constructible)
	Register(test_is_copy_constructible)
	Register(test_is_trivially_constructible)
	Register(test_is_trivially_move_constructible)
	Register(test_is_trivially_copy_constructible)
	Register(test_is_assignable)
	Register(test_is_move_assignable)
	Register(test_is_copy_assignable)
	Register(test_is_trivially_assignable)
	Register(test_is_trivially_move_assignable)
	Register(test_is_trivially_copy_assignable)
	Register(test_is_static_castable)
	Register(test_is_dynamic_castable)
};

template <class C>
using reporter_t = pptest::colored_printer<C>;

int main()
{
	return meta_functions_test().run_all(reporter_t<meta_functions_test>(pptest::normal));
}
