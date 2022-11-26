#include <pptest>
#include <colored_printer>
#include <ds/fixed>
#include <ds/traits/iterable>
#include "../counter"
#include "../nocopy"
#include "../nomove"

template class ds::Fixed<5,int>;
template class ds::Fixed<5,int const>;
template class ds::Fixed<5,Counter>;
template class ds::Fixed<5,Counter const>;
template class ds::Fixed<5,NoCopy>;
template class ds::Fixed<5,NoCopy const>;
template class ds::Fixed<5,NoMove>;
template class ds::Fixed<5,NoMove const>;

Test(fixed_test)
{
	TestInit(fixed_test);

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

	PreRun()
	{
		Counter::reset();
	}

	Testcase(test_constexpr_default_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr auto fixed_ = ds::Fixed<size_,int>();
		AssertTrue(compare_eq(fixed_.array(), {0,0,0,0,0}));
	} TestcaseEnd(test_constexpr_default_constructor);

	Testcase(test_constexpr_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<size_,int> fixed_ = { 1,2,3,4,5 };
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
	} TestcaseEnd(test_constexpr_initializer_list_constructor);

	Testcase(test_constexpr_array_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<size_,int> fixed_({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
	} TestcaseEnd(test_constexpr_array_constructor);

	Testcase(test_constexpr_move_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<size_,int> fixed_({ 1,2,3,4,5 });
		constexpr auto fixed_moved_ = ds::cmove(fixed_);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		AssertTrue(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
	} TestcaseEnd(test_constexpr_move_constructor);

	Testcase(test_constexpr_copy_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<size_,int> fixed_({ 1,2,3,4,5 });
		constexpr auto fixed_copy_ = fixed_;
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		AssertTrue(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
	} TestcaseEnd(test_constexpr_copy_constructor);

	Testcase(test_constexpr_make_fixed)
	{
		constexpr auto fixed_ = ds::make_fixed<int>(1,2,3,4,5);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
	} TestcaseEnd(test_constexpr_make_fixed);

	Testcase(test_constexpr_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		constexpr auto fixed_ = ds::make_fixed<size_,int>(1,2,3,4);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,0}));
	} TestcaseEnd(test_constexpr_make_fixed_with_size);

	Testcase(test_default_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<size_,Counter>();
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {0,0,0,0,0}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_default_constructor);

	Testcase(test_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		{
			ds::Fixed<size_,Counter> fixed_ = { 1,2,3,4,5 };
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_initializer_list_constructor);

	Testcase(test_diverse_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		{
			ds::Fixed<size_,Counter> fixed_ = { true,2,uint8_t(3),uint8_t(4),int16_t(5) };
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_diverse_initializer_list_constructor);

	Testcase(test_array_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<size_,Counter>({ 1,2,3,4,5 });
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_array_constructor);

	Testcase(test_move_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<size_,Counter>{1,2,3,4,5};
			auto fixed_moved_ = ds::move(fixed_);
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 5);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 10);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 5);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_move_constructor);

	Testcase(test_copy_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<size_,Counter>{1,2,3,4,5};
			auto fixed_copy_ = fixed_;
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 5);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
			AssertTrue(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 10);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 5);
	} TestcaseEnd(test_copy_constructor);

	Testcase(test_move_assignment)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<size_,Counter>{1,2,3,4,5};
			auto fixed_moved_ = ds::Fixed<size_,Counter>();
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			fixed_moved_ = ds::move(fixed_);
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 5);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 10);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 5);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_move_assignment);

	Testcase(test_copy_assignment)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<size_,Counter>{1,2,3,4,5};
			auto fixed_copy_ = ds::Fixed<size_,Counter>();
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			fixed_copy_ = fixed_;
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 5);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
			AssertTrue(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 10);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 5);
	} TestcaseEnd(test_copy_assignment);

	Testcase(test_make_fixed)
	{
		{
			auto fixed_ = ds::make_fixed<Counter>(1,2,3,4,5);
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_make_fixed);

	Testcase(test_diverse_make_fixed)
	{
		{
			auto fixed_ = ds::make_fixed<Counter>(true,2,uint8_t(3),uint8_t(4),int16_t(5));
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_diverse_make_fixed);

	Testcase(test_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::make_fixed<size_,Counter>(1,2,3,4);
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,0}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_make_fixed_with_size);

	Testcase(test_diverse_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::make_fixed<size_,Counter>(true,2,uint8_t(3),uint16_t(4));
			AssertEQ(Counter::count(), 5);
			AssertEQ(Counter::active(), 5);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,0}));
		}
		AssertEQ(Counter::count(), 5);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(test_diverse_make_fixed_with_size);

	Testcase(test_indexing_operator)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<size_,int>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_[i], i+1);
		AssertThrowNone(auto value = fixed_[size_]);
	} TestcaseEnd(test_indexing_operator);

	Testcase(test_const_indexing_operator)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<size_,int>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_[i], i+1);
		AssertThrowNone(auto value = fixed_[size_]);
	} TestcaseEnd(test_const_indexing_operator);

	Testcase(test_at_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<size_,int>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_.at(i), i+1);
		AssertThrowAny(auto value = fixed_.at(size_));
		using index_out_of_bounds_t = ds::Fixed<size_,int>::index_out_of_bounds;
		AssertThrow(index_out_of_bounds_t const &, auto value = fixed_.at(size_););
	} TestcaseEnd(test_at_function);

	Testcase(test_const_at_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<size_,int>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_.at(i), i+1);
		AssertThrowAny(auto value = fixed_.at(size_));
		using index_out_of_bounds_t = ds::Fixed<size_,int>::index_out_of_bounds;
		AssertThrow(index_out_of_bounds_t const &, auto value = fixed_.at(size_););
	} TestcaseEnd(test_const_at_function);

	Testcase(test_array_function)
	{
		constexpr size_t size_ = 3;
		auto fixed_ = ds::Fixed<size_,int>({1,2,3});
		AssertTrue(ds::is_same<decltype(fixed_.array()), int (&)[size_]>::value);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3}));
	} TestcaseEnd(test_array_function);

	Testcase(test_const_array_function)
	{
		constexpr size_t size_ = 3;
		auto const fixed_ = ds::Fixed<size_,int>({1,2,3});
		AssertTrue(ds::is_same<decltype(fixed_.array()), int const(&)[size_]>::value);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3}));
	} TestcaseEnd(test_const_array_function);

	Testcase(test_size_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<size_,int>();
		AssertEQ(fixed_.size(), size_);
	} TestcaseEnd(test_size_function);

	Testcase(test_const_size_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<size_,int>();
		AssertEQ(fixed_.size(), size_);
	} TestcaseEnd(test_const_size_function);

	Testcase(test_begin_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<size_,int>({1,2,3,4,5});
		AssertTrue(ds::is_same<decltype(fixed_.begin()),int *>::value);
		AssertNotNull(fixed_.begin());
		AssertEQ(fixed_.begin(), &fixed_[0]);
	} TestcaseEnd(test_begin_function);

	Testcase(test_const_begin_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<size_,int>({1,2,3,4,5});
		AssertTrue(ds::is_same<decltype(fixed_.begin()),int const *>::value);
		AssertNotNull(fixed_.begin());
		AssertEQ(fixed_.begin(), &fixed_[0]);
	} TestcaseEnd(test_const_begin_function);

	Testcase(test_end_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<size_,int>({1,2,3,4,5});
		AssertTrue(ds::is_same<decltype(fixed_.end()),int *>::value);
		AssertNotNull(fixed_.end());
		AssertEQ(fixed_.end(), &fixed_[size_]);
	} TestcaseEnd(test_end_function);

	Testcase(test_const_end_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<size_,int>({1,2,3,4,5});
		AssertTrue(ds::is_same<decltype(fixed_.end()),int const *>::value);
		AssertNotNull(fixed_.end());
		AssertEQ(fixed_.end(), &fixed_[size_]);
	} TestcaseEnd(test_const_end_function);

	Testcase(test_has_iterable_trait_element_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t   = ds::Fixed<size_,int>;
		AssertTrue(ds::iterable_has_element<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::element_t,int>::value);
	} TestcaseEnd(test_has_iterable_trait_element_t);

	Testcase(test_const_has_iterable_trait_element_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t   = ds::Fixed<size_,int> const;
		AssertTrue(ds::iterable_has_element<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::element_t,int>::value);
	} TestcaseEnd(test_const_has_iterable_trait_element_t);

	Testcase(test_has_iterable_trait_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<size_,int>;
		AssertTrue(ds::iterable_has_indexable_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::indexable_iterator_t,int *>::value);
	} TestcaseEnd(test_has_iterable_trait_indexable_iterator_t);

	Testcase(test_const_has_iterable_trait_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<size_,int> const;
		AssertFalse(ds::iterable_has_indexable_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::indexable_iterator_t,void>::value);
	} TestcaseEnd(test_const_has_iterable_trait_indexable_iterator_t);

	Testcase(test_has_iterable_trait_const_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int>;
		AssertTrue(ds::iterable_has_const_indexable_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::const_indexable_iterator_t,int const *>::value);
	} TestcaseEnd(test_has_iterable_trait_const_indexable_iterator_t);

	Testcase(test_const_has_iterable_trait_const_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int> const;
		AssertTrue(ds::iterable_has_const_indexable_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::const_indexable_iterator_t,int const *>::value);
	} TestcaseEnd(test_const_has_iterable_trait_const_indexable_iterator_t);

	Testcase(test_has_iterable_trait_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<size_,int>;
		AssertTrue(ds::iterable_has_forward_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::forward_iterator_t,int *>::value);
	} TestcaseEnd(test_has_iterable_trait_forward_iterator_t);

	Testcase(test_const_has_iterable_trait_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<size_,int> const;
		AssertFalse(ds::iterable_has_forward_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::forward_iterator_t,void>::value);
	} TestcaseEnd(test_const_has_iterable_trait_forward_iterator_t);

	Testcase(test_has_iterable_trait_const_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int>;
		AssertTrue(ds::iterable_has_const_forward_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::const_forward_iterator_t,int const *>::value);
	} TestcaseEnd(test_has_iterable_trait_const_forward_iterator_t);

	Testcase(test_const_has_iterable_trait_const_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int> const;
		AssertTrue(ds::iterable_has_const_forward_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::const_forward_iterator_t,int const *>::value);
	} TestcaseEnd(test_const_has_iterable_trait_const_forward_iterator_t);

	Testcase(test_has_iterable_trait_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int>;
		AssertTrue(ds::iterable_has_reverse_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::reverse_iterator_t,int *>::value);
	} TestcaseEnd(test_has_iterable_trait_reverse_iterator_t);

	Testcase(test_const_has_not_iterable_trait_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int> const;
		AssertFalse(ds::iterable_has_reverse_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::reverse_iterator_t,void>::value);
	} TestcaseEnd(test_const_has_not_iterable_trait_reverse_iterator_t);

	Testcase(test_has_iterable_trait_const_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int>;
		AssertTrue(ds::iterable_has_const_reverse_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::const_reverse_iterator_t,int const *>::value);
	} TestcaseEnd(test_has_iterable_trait_const_reverse_iterator_t);

	Testcase(test_const_has_iterable_trait_const_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<size_,int> const;
		AssertTrue(ds::iterable_has_const_reverse_iterator<fixed_t>::value);
		AssertTrue(ds::is_same<ds::traits::iterable<fixed_t>::const_reverse_iterator_t,int const *>::value);
	} TestcaseEnd(test_const_has_iterable_trait_const_reverse_iterator_t);

	template <typename T
		, typename E   = ds::iterable_element_t<T>
		, typename CIt = ds::iterable_const_forward_iterator_t<T>>
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

	Testcase(test_iterable_traits_in_function_template_test)
	{
		constexpr size_t size_ = 5;
		ds::Fixed<size_,int> fixed_ = {1,2,3,4,5};
		auto total_ = accumulate(fixed_);
		AssertTrue(ds::is_same<decltype(total_),int>::value);
		AssertEQ(total_, 15);
	} TestcaseEnd(test_iterable_traits_in_function_template_test);

};

TestRegistry(fixed_test)
{
	Register(test_constexpr_default_constructor)
	Register(test_constexpr_initializer_list_constructor)
	Register(test_constexpr_array_constructor)
	Register(test_constexpr_move_constructor)
	Register(test_constexpr_copy_constructor)
	Register(test_constexpr_make_fixed)
	Register(test_constexpr_make_fixed_with_size)
	Register(test_default_constructor)
	Register(test_initializer_list_constructor)
	Register(test_diverse_initializer_list_constructor)
	Register(test_array_constructor)
	Register(test_move_constructor)
	Register(test_copy_constructor)
	Register(test_move_assignment)
	Register(test_copy_assignment)
	Register(test_make_fixed)
	Register(test_diverse_make_fixed)
	Register(test_make_fixed_with_size)
	Register(test_diverse_make_fixed_with_size)
	Register(test_indexing_operator)
	Register(test_const_indexing_operator)
	Register(test_at_function)
	Register(test_const_at_function)
	Register(test_array_function)
	Register(test_const_array_function)
	Register(test_size_function)
	Register(test_const_size_function)
	Register(test_begin_function)
	Register(test_const_begin_function)
	Register(test_end_function)
	Register(test_const_end_function)
	Register(test_has_iterable_trait_element_t)
	Register(test_const_has_iterable_trait_element_t)
	Register(test_has_iterable_trait_indexable_iterator_t)
	Register(test_const_has_iterable_trait_indexable_iterator_t)
	Register(test_has_iterable_trait_const_indexable_iterator_t)
	Register(test_const_has_iterable_trait_const_indexable_iterator_t)
	Register(test_has_iterable_trait_forward_iterator_t)
	Register(test_const_has_iterable_trait_forward_iterator_t)
	Register(test_has_iterable_trait_const_forward_iterator_t)
	Register(test_const_has_iterable_trait_const_forward_iterator_t)
	Register(test_has_iterable_trait_reverse_iterator_t)
	Register(test_const_has_not_iterable_trait_reverse_iterator_t)
	Register(test_has_iterable_trait_const_reverse_iterator_t)
	Register(test_const_has_iterable_trait_const_reverse_iterator_t)
	Register(test_iterable_traits_in_function_template_test)
};


template <class C> using reporter_t = pptest::colored_printer<C>; 

int main()
{
	return fixed_test().run_all(reporter_t<fixed_test>(pptest::normal));
}