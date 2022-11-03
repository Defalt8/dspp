#include <type_traits>
#include <pptest>
#include <colored_printer>
#include <ds/fixed>
#include <ds/traits/iterator>
#include "../counter"

Begin_Test(fixed_test)

	template <typename T>
	struct Sequence 
	{
		T cur; 
		constexpr Sequence(T start_ = {}) : cur { start_ } {}
		constexpr operator T() { return cur++; }
	};

	template <typename E, size_t size1_, typename T, size_t size2_>
	static bool
	compare_eq(E const (& lhs)[size1_], T const (& rhs)[size2_])
	{
		if(size1_ != size2_)
			return false;
		for(size_t i = 0; i < size1_; ++i)
			if(lhs[i] != rhs[i])
				return false;
		return true;
	}

	Pre_Testcase_Run(fixed_test)
	{
		Counter::reset();
	}

	Begin_Testcase(fixed_test, test_constexpr_default_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr auto fixed_ = ds::Fixed<int,size_>();
		Assert_True(compare_eq(fixed_.array(), {0,0,0,0,0}));
	}
	End_Testcase(fixed_test, test_constexpr_default_constructor)

	Begin_Testcase(fixed_test, test_constexpr_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_ = { 1,2,3,4,5 };
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
	}
	End_Testcase(fixed_test, test_constexpr_initializer_list_constructor)

	Begin_Testcase(fixed_test, test_constexpr_diverse_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_ = { true,2.3,3.4f,4UL,5.L };
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
	}
	End_Testcase(fixed_test, test_constexpr_diverse_initializer_list_constructor)

	Begin_Testcase(fixed_test, test_constexpr_array_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_({ 1,2,3,4,5 });
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
	}
	End_Testcase(fixed_test, test_constexpr_array_constructor)

	Begin_Testcase(fixed_test, test_constexpr_move_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_({ 1,2,3,4,5 });
		constexpr auto fixed_moved_ = ds::cmove(fixed_);
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		Assert_True(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
	}
	End_Testcase(fixed_test, test_constexpr_move_constructor)

	Begin_Testcase(fixed_test, test_constexpr_copy_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_({ 1,2,3,4,5 });
		constexpr auto fixed_copy_ = fixed_;
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		Assert_True(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
	}
	End_Testcase(fixed_test, test_constexpr_copy_constructor)

	Begin_Testcase(fixed_test, test_constexpr_make_fixed)
	{
		constexpr auto fixed_ = ds::make_fixed<int>(1,2,3,4,5);
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
	}
	End_Testcase(fixed_test, test_constexpr_make_fixed)

	Begin_Testcase(fixed_test, test_constexpr_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		constexpr auto fixed_ = ds::make_fixed<int,size_>(1,2,3,4);
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,0}));
	}
	End_Testcase(fixed_test, test_constexpr_make_fixed_with_size)

	Begin_Testcase(fixed_test, test_default_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>();
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {0,0,0,0,0}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_default_constructor)

	Begin_Testcase(fixed_test, test_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		{
			ds::Fixed<Counter,size_> fixed_ = { 1,2,3,4,5 };
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_initializer_list_constructor)

	Begin_Testcase(fixed_test, test_diverse_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		{
			ds::Fixed<Counter,size_> fixed_ = { true,2.3,3.4f,4UL,5.L };
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_diverse_initializer_list_constructor)

	Begin_Testcase(fixed_test, test_array_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>({ 1,2,3,4,5 });
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_array_constructor)

	Begin_Testcase(fixed_test, test_move_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
			auto fixed_moved_ = ds::move(fixed_);
			Assert_EQ(Counter::count(), 10);
			Assert_EQ(Counter::active(), 10);
			Assert_EQ(Counter::moves(), 5);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 10);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 5);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_move_constructor)

	Begin_Testcase(fixed_test, test_copy_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
			auto fixed_copy_ = fixed_;
			Assert_EQ(Counter::count(), 10);
			Assert_EQ(Counter::active(), 10);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 5);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
			Assert_True(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 10);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 5);
	}
	End_Testcase(fixed_test, test_copy_constructor)

	Begin_Testcase(fixed_test, test_move_assignment)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
			auto fixed_moved_ = ds::Fixed<Counter,size_>();
			Assert_EQ(Counter::count(), 10);
			Assert_EQ(Counter::active(), 10);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			fixed_moved_ = ds::move(fixed_);
			Assert_EQ(Counter::count(), 15);
			Assert_EQ(Counter::active(), 10);
			Assert_EQ(Counter::moves(), 5);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 15);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 5);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_move_assignment)

	Begin_Testcase(fixed_test, test_copy_assignment)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
			auto fixed_copy_ = ds::Fixed<Counter,size_>();
			Assert_EQ(Counter::count(), 10);
			Assert_EQ(Counter::active(), 10);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			fixed_copy_ = fixed_;
			Assert_EQ(Counter::count(), 15);
			Assert_EQ(Counter::active(), 10);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 5);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
			Assert_True(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 15);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 5);
	}
	End_Testcase(fixed_test, test_copy_assignment)

	Begin_Testcase(fixed_test, test_make_fixed)
	{
		{
			auto fixed_ = ds::make_fixed<Counter>(1,2,3,4,5);
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_make_fixed)

	Begin_Testcase(fixed_test, test_diverse_make_fixed)
	{
		{
			auto fixed_ = ds::make_fixed<Counter>(true,2.3,3.f,4UL,5.L);
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_diverse_make_fixed)

	Begin_Testcase(fixed_test, test_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::make_fixed<Counter,size_>(1,2,3,4);
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,0}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_make_fixed_with_size)

	Begin_Testcase(fixed_test, test_diverse_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::make_fixed<Counter,size_>(true,2.3,3.f,4UL);
			Assert_EQ(Counter::count(), 5);
			Assert_EQ(Counter::active(), 5);
			Assert_EQ(Counter::moves(), 0);
			Assert_EQ(Counter::copies(), 0);
			Assert_True(compare_eq(fixed_.array(), {1,2,3,4,0}));
		}
		Assert_EQ(Counter::count(), 5);
		Assert_EQ(Counter::active(), 0);
		Assert_EQ(Counter::moves(), 0);
		Assert_EQ(Counter::copies(), 0);
	}
	End_Testcase(fixed_test, test_diverse_make_fixed_with_size)

	Begin_Testcase(fixed_test, test_indexing_operator)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			Assert_EQ(fixed_[i], i+1);
		Assert_ThrowNone(auto value = fixed_[size_]);
	}
	End_Testcase(fixed_test, test_indexing_operator)

	Begin_Testcase(fixed_test, test_const_indexing_operator)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			Assert_EQ(fixed_[i], i+1);
		Assert_ThrowNone(auto value = fixed_[size_]);
	}
	End_Testcase(fixed_test, test_const_indexing_operator)

	Begin_Testcase(fixed_test, test_at_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			Assert_EQ(fixed_.at(i), i+1);
		Assert_ThrowAny(auto value = fixed_.at(size_));
		using index_out_of_bounds_t = ds::Fixed<int,size_>::index_out_of_bounds;
		Assert_Throw(index_out_of_bounds_t const &, auto value = fixed_.at(size_););
	}
	End_Testcase(fixed_test, test_at_function)

	Begin_Testcase(fixed_test, test_const_at_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		Assert_True(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			Assert_EQ(fixed_.at(i), i+1);
		Assert_ThrowAny(auto value = fixed_.at(size_));
		using index_out_of_bounds_t = ds::Fixed<int,size_>::index_out_of_bounds;
		Assert_Throw(index_out_of_bounds_t const &, auto value = fixed_.at(size_););
	}
	End_Testcase(fixed_test, test_const_at_function)

	Begin_Testcase(fixed_test, test_array_function)
	{
		constexpr size_t size_ = 3;
		auto fixed_ = ds::Fixed<int,size_>({1,2,3});
		Assert_True(std::is_same<decltype(fixed_.array()), int (&)[size_]>::value);
		Assert_True(compare_eq(fixed_.array(), {1,2,3}));
	}
	End_Testcase(fixed_test, test_array_function)

	Begin_Testcase(fixed_test, test_const_array_function)
	{
		constexpr size_t size_ = 3;
		auto const fixed_ = ds::Fixed<int,size_>({1,2,3});
		Assert_True(std::is_same<decltype(fixed_.array()), int const(&)[size_]>::value);
		Assert_True(compare_eq(fixed_.array(), {1,2,3}));
	}
	End_Testcase(fixed_test, test_const_array_function)

	Begin_Testcase(fixed_test, test_size_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>();
		Assert_EQ(fixed_.size(), size_);
	}
	End_Testcase(fixed_test, test_size_function)

	Begin_Testcase(fixed_test, test_const_size_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>();
		Assert_EQ(fixed_.size(), size_);
	}
	End_Testcase(fixed_test, test_const_size_function)

	Begin_Testcase(fixed_test, test_begin_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		Assert_True(std::is_same<decltype(fixed_.begin()),int *>::value);
		Assert_NotNull(fixed_.begin());
		Assert_EQ(fixed_.begin(), &fixed_[0]);
	}
	End_Testcase(fixed_test, test_begin_function)

	Begin_Testcase(fixed_test, test_const_begin_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		Assert_True(std::is_same<decltype(fixed_.begin()),int const *>::value);
		Assert_NotNull(fixed_.begin());
		Assert_EQ(fixed_.begin(), &fixed_[0]);
	}
	End_Testcase(fixed_test, test_const_begin_function)

	Begin_Testcase(fixed_test, test_end_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		Assert_True(std::is_same<decltype(fixed_.end()),int *>::value);
		Assert_NotNull(fixed_.end());
		Assert_EQ(fixed_.end(), &fixed_[size_]);
	}
	End_Testcase(fixed_test, test_end_function)

	Begin_Testcase(fixed_test, test_const_end_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		Assert_True(std::is_same<decltype(fixed_.end()),int const *>::value);
		Assert_NotNull(fixed_.end());
		Assert_EQ(fixed_.end(), &fixed_[size_]);
	}
	End_Testcase(fixed_test, test_const_end_function)

	Begin_Testcase(fixed_test, test_has_iterator_trait_element_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t   = ds::Fixed<int,size_>;
		Assert_True(ds::traits::iterator_has_element<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::element_t,int>::value);
	}
	End_Testcase(fixed_test, test_has_iterator_trait_element_t)

	Begin_Testcase(fixed_test, test_const_has_iterator_trait_element_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t   = ds::Fixed<int,size_> const;
		Assert_True(ds::traits::iterator_has_element<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::element_t,int>::value);
	}
	End_Testcase(fixed_test, test_const_has_iterator_trait_element_t)

	Begin_Testcase(fixed_test, test_has_iterator_trait_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_>;
		Assert_True(ds::traits::iterator_has_indexable_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::indexable_iterator_t,int *>::value);
	}
	End_Testcase(fixed_test, test_has_iterator_trait_indexable_iterator_t)

	Begin_Testcase(fixed_test, test_const_has_iterator_trait_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_> const;
		Assert_False(ds::traits::iterator_has_indexable_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::indexable_iterator_t,void>::value);
	}
	End_Testcase(fixed_test, test_const_has_iterator_trait_indexable_iterator_t)

	Begin_Testcase(fixed_test, test_has_iterator_trait_const_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		Assert_True(ds::traits::iterator_has_const_indexable_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::const_indexable_iterator_t,int const *>::value);
	}
	End_Testcase(fixed_test, test_has_iterator_trait_const_indexable_iterator_t)

	Begin_Testcase(fixed_test, test_const_has_iterator_trait_const_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		Assert_True(ds::traits::iterator_has_const_indexable_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::const_indexable_iterator_t,int const *>::value);
	}
	End_Testcase(fixed_test, test_const_has_iterator_trait_const_indexable_iterator_t)

	Begin_Testcase(fixed_test, test_has_iterator_trait_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_>;
		Assert_True(ds::traits::iterator_has_forward_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::forward_iterator_t,int *>::value);
	}
	End_Testcase(fixed_test, test_has_iterator_trait_forward_iterator_t)

	Begin_Testcase(fixed_test, test_const_has_iterator_trait_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_> const;
		Assert_False(ds::traits::iterator_has_forward_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::forward_iterator_t,void>::value);
	}
	End_Testcase(fixed_test, test_const_has_iterator_trait_forward_iterator_t)

	Begin_Testcase(fixed_test, test_has_iterator_trait_const_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		Assert_True(ds::traits::iterator_has_const_forward_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::const_forward_iterator_t,int const *>::value);
	}
	End_Testcase(fixed_test, test_has_iterator_trait_const_forward_iterator_t)

	Begin_Testcase(fixed_test, test_const_has_iterator_trait_const_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		Assert_True(ds::traits::iterator_has_const_forward_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::const_forward_iterator_t,int const *>::value);
	}
	End_Testcase(fixed_test, test_const_has_iterator_trait_const_forward_iterator_t)

	Begin_Testcase(fixed_test, test_has_not_iterator_trait_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		Assert_False(ds::traits::iterator_has_reverse_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::reverse_iterator_t,void>::value);
	}
	End_Testcase(fixed_test, test_has_not_iterator_trait_reverse_iterator_t)

	Begin_Testcase(fixed_test, test_const_has_not_iterator_trait_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		Assert_False(ds::traits::iterator_has_reverse_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::reverse_iterator_t,void>::value);
	}
	End_Testcase(fixed_test, test_const_has_not_iterator_trait_reverse_iterator_t)

	Begin_Testcase(fixed_test, test_has_not_iterator_trait_const_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		Assert_False(ds::traits::iterator_has_const_reverse_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::const_reverse_iterator_t,void const>::value);
	}
	End_Testcase(fixed_test, test_has_not_iterator_trait_const_reverse_iterator_t)

	Begin_Testcase(fixed_test, test_const_has_not_iterator_trait_const_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		Assert_False(ds::traits::iterator_has_const_reverse_iterator<fixed_t>::value);
		Assert_True(std::is_same<ds::traits::iterator<fixed_t>::const_reverse_iterator_t,void const>::value);
	}
	End_Testcase(fixed_test, test_const_has_not_iterator_trait_const_reverse_iterator_t)

	template <typename T
		, typename E   = typename ds::traits::iterator<T>::element_t
		, typename CIt = typename ds::traits::iterator<T>::const_forward_iterator_t>
	static E
	accumulate(T const & const_forward_iterable)
	{
		E total_ = {};
		CIt begin_ = ds::begin(const_forward_iterable);
		CIt end_   = ds::end(const_forward_iterable);
		for(CIt it = begin_; it != end_; ++it)
			total_ += *it;
		return total_;
	}

	Begin_Testcase(fixed_test, test_iterator_traits_in_function_template_test)
	{
		constexpr size_t size_ = 5;
		ds::Fixed<int,size_> fixed_ = {1,2,3,4,5};
		auto total_ = accumulate(fixed_);
		Assert_True(std::is_same<decltype(total_),int>::value);
		Assert_EQ(total_, 15);
	}
	End_Testcase(fixed_test, test_iterator_traits_in_function_template_test)

	Begin_Testcase_Registration(fixed_test)
	{
		Register_Testcase(fixed_test, test_constexpr_default_constructor)
		Register_Testcase(fixed_test, test_constexpr_initializer_list_constructor)
		Register_Testcase(fixed_test, test_constexpr_diverse_initializer_list_constructor)
		Register_Testcase(fixed_test, test_constexpr_array_constructor)
		Register_Testcase(fixed_test, test_constexpr_move_constructor)
		Register_Testcase(fixed_test, test_constexpr_copy_constructor)
		Register_Testcase(fixed_test, test_constexpr_make_fixed)
		Register_Testcase(fixed_test, test_constexpr_make_fixed_with_size)
		Register_Testcase(fixed_test, test_default_constructor)
		Register_Testcase(fixed_test, test_initializer_list_constructor)
		Register_Testcase(fixed_test, test_diverse_initializer_list_constructor)
		Register_Testcase(fixed_test, test_array_constructor)
		Register_Testcase(fixed_test, test_move_constructor)
		Register_Testcase(fixed_test, test_copy_constructor)
		Register_Testcase(fixed_test, test_move_assignment)
		Register_Testcase(fixed_test, test_copy_assignment)
		Register_Testcase(fixed_test, test_make_fixed)
		Register_Testcase(fixed_test, test_diverse_make_fixed)
		Register_Testcase(fixed_test, test_make_fixed_with_size)
		Register_Testcase(fixed_test, test_diverse_make_fixed_with_size)
		Register_Testcase(fixed_test, test_indexing_operator)
		Register_Testcase(fixed_test, test_const_indexing_operator)
		Register_Testcase(fixed_test, test_at_function)
		Register_Testcase(fixed_test, test_const_at_function)
		Register_Testcase(fixed_test, test_array_function)
		Register_Testcase(fixed_test, test_const_array_function)
		Register_Testcase(fixed_test, test_size_function)
		Register_Testcase(fixed_test, test_const_size_function)
		Register_Testcase(fixed_test, test_begin_function)
		Register_Testcase(fixed_test, test_const_begin_function)
		Register_Testcase(fixed_test, test_end_function)
		Register_Testcase(fixed_test, test_const_end_function)
		Register_Testcase(fixed_test, test_has_iterator_trait_element_t)
		Register_Testcase(fixed_test, test_const_has_iterator_trait_element_t)
		Register_Testcase(fixed_test, test_has_iterator_trait_indexable_iterator_t)
		Register_Testcase(fixed_test, test_const_has_iterator_trait_indexable_iterator_t)
		Register_Testcase(fixed_test, test_has_iterator_trait_const_indexable_iterator_t)
		Register_Testcase(fixed_test, test_const_has_iterator_trait_const_indexable_iterator_t)
		Register_Testcase(fixed_test, test_has_iterator_trait_forward_iterator_t)
		Register_Testcase(fixed_test, test_const_has_iterator_trait_forward_iterator_t)
		Register_Testcase(fixed_test, test_has_iterator_trait_const_forward_iterator_t)
		Register_Testcase(fixed_test, test_const_has_iterator_trait_const_forward_iterator_t)
		Register_Testcase(fixed_test, test_has_not_iterator_trait_reverse_iterator_t)
		Register_Testcase(fixed_test, test_const_has_not_iterator_trait_reverse_iterator_t)
		Register_Testcase(fixed_test, test_has_not_iterator_trait_const_reverse_iterator_t)
		Register_Testcase(fixed_test, test_const_has_not_iterator_trait_const_reverse_iterator_t)
		Register_Testcase(fixed_test, test_iterator_traits_in_function_template_test)
	}
	End_Testcase_Registration(fixed_test)
End_Test(fixed_test)


template <class C> using reporter_t = pptest::colored_printer<C>; 

int main()
{
	return fixed_test().run_all(reporter_t<fixed_test>(pptest::normal));
}