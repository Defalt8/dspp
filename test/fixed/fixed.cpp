#include <type_traits>
#include <pptest>
#include <colored_printer>
#include <ds/fixed>
#include <ds/traits/iterator>
#include "../counter"

Test(fixed_test)
{
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

	PreRun(fixed_test)
	{
		Counter::reset();
	}

	Testcase(fixed_test, test_constexpr_default_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr auto fixed_ = ds::Fixed<int,size_>();
		AssertTrue(compare_eq(fixed_.array(), {0,0,0,0,0}));
	} TestcaseEnd(fixed_test, test_constexpr_default_constructor);

	Testcase(fixed_test, test_constexpr_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_ = { 1,2,3,4,5 };
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
	} TestcaseEnd(fixed_test, test_constexpr_initializer_list_constructor);

	Testcase(fixed_test, test_constexpr_diverse_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_ = { true,2.3,3.4f,4UL,5.L };
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
	} TestcaseEnd(fixed_test, test_constexpr_diverse_initializer_list_constructor);

	Testcase(fixed_test, test_constexpr_array_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
	} TestcaseEnd(fixed_test, test_constexpr_array_constructor);

	Testcase(fixed_test, test_constexpr_move_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_({ 1,2,3,4,5 });
		constexpr auto fixed_moved_ = ds::cmove(fixed_);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		AssertTrue(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
	} TestcaseEnd(fixed_test, test_constexpr_move_constructor);

	Testcase(fixed_test, test_constexpr_copy_constructor)
	{
		constexpr size_t size_ = 5;
		constexpr ds::Fixed<int,size_> fixed_({ 1,2,3,4,5 });
		constexpr auto fixed_copy_ = fixed_;
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		AssertTrue(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
	} TestcaseEnd(fixed_test, test_constexpr_copy_constructor);

	Testcase(fixed_test, test_constexpr_make_fixed)
	{
		constexpr auto fixed_ = ds::make_fixed<int>(1,2,3,4,5);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
	} TestcaseEnd(fixed_test, test_constexpr_make_fixed);

	Testcase(fixed_test, test_constexpr_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		constexpr auto fixed_ = ds::make_fixed<int,size_>(1,2,3,4);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,0}));
	} TestcaseEnd(fixed_test, test_constexpr_make_fixed_with_size);

	Testcase(fixed_test, test_default_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>();
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
	} TestcaseEnd(fixed_test, test_default_constructor);

	Testcase(fixed_test, test_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		{
			ds::Fixed<Counter,size_> fixed_ = { 1,2,3,4,5 };
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
	} TestcaseEnd(fixed_test, test_initializer_list_constructor);

	Testcase(fixed_test, test_diverse_initializer_list_constructor)
	{
		constexpr size_t size_ = 5;
		{
			ds::Fixed<Counter,size_> fixed_ = { true,2.3,3.4f,4UL,5.L };
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
	} TestcaseEnd(fixed_test, test_diverse_initializer_list_constructor);

	Testcase(fixed_test, test_array_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>({ 1,2,3,4,5 });
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
	} TestcaseEnd(fixed_test, test_array_constructor);

	Testcase(fixed_test, test_move_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
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
	} TestcaseEnd(fixed_test, test_move_constructor);

	Testcase(fixed_test, test_copy_constructor)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
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
	} TestcaseEnd(fixed_test, test_copy_constructor);

	Testcase(fixed_test, test_move_assignment)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
			auto fixed_moved_ = ds::Fixed<Counter,size_>();
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			fixed_moved_ = ds::move(fixed_);
			AssertEQ(Counter::count(), 15);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 5);
			AssertEQ(Counter::copies(), 0);
			AssertTrue(compare_eq(fixed_moved_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 15);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 5);
		AssertEQ(Counter::copies(), 0);
	} TestcaseEnd(fixed_test, test_move_assignment);

	Testcase(fixed_test, test_copy_assignment)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::Fixed<Counter,size_>{1,2,3,4,5};
			auto fixed_copy_ = ds::Fixed<Counter,size_>();
			AssertEQ(Counter::count(), 10);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 0);
			fixed_copy_ = fixed_;
			AssertEQ(Counter::count(), 15);
			AssertEQ(Counter::active(), 10);
			AssertEQ(Counter::moves(), 0);
			AssertEQ(Counter::copies(), 5);
			AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
			AssertTrue(compare_eq(fixed_copy_.array(), {1,2,3,4,5}));
		}
		AssertEQ(Counter::count(), 15);
		AssertEQ(Counter::active(), 0);
		AssertEQ(Counter::moves(), 0);
		AssertEQ(Counter::copies(), 5);
	} TestcaseEnd(fixed_test, test_copy_assignment);

	Testcase(fixed_test, test_make_fixed)
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
	} TestcaseEnd(fixed_test, test_make_fixed);

	Testcase(fixed_test, test_diverse_make_fixed)
	{
		{
			auto fixed_ = ds::make_fixed<Counter>(true,2.3,3.f,4UL,5.L);
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
	} TestcaseEnd(fixed_test, test_diverse_make_fixed);

	Testcase(fixed_test, test_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::make_fixed<Counter,size_>(1,2,3,4);
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
	} TestcaseEnd(fixed_test, test_make_fixed_with_size);

	Testcase(fixed_test, test_diverse_make_fixed_with_size)
	{
		constexpr size_t size_ = 5;
		{
			auto fixed_ = ds::make_fixed<Counter,size_>(true,2.3,3.f,4UL);
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
	} TestcaseEnd(fixed_test, test_diverse_make_fixed_with_size);

	Testcase(fixed_test, test_indexing_operator)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_[i], i+1);
		AssertThrowNone(auto value = fixed_[size_]);
	} TestcaseEnd(fixed_test, test_indexing_operator);

	Testcase(fixed_test, test_const_indexing_operator)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_[i], i+1);
		AssertThrowNone(auto value = fixed_[size_]);
	} TestcaseEnd(fixed_test, test_const_indexing_operator);

	Testcase(fixed_test, test_at_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_.at(i), i+1);
		AssertThrowAny(auto value = fixed_.at(size_));
		using index_out_of_bounds_t = ds::Fixed<int,size_>::index_out_of_bounds;
		AssertThrow(index_out_of_bounds_t const &, auto value = fixed_.at(size_););
	} TestcaseEnd(fixed_test, test_at_function);

	Testcase(fixed_test, test_const_at_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({ 1,2,3,4,5 });
		AssertTrue(compare_eq(fixed_.array(), {1,2,3,4,5}));
		for(int i = 0; i < size_; ++i)
			AssertEQ(fixed_.at(i), i+1);
		AssertThrowAny(auto value = fixed_.at(size_));
		using index_out_of_bounds_t = ds::Fixed<int,size_>::index_out_of_bounds;
		AssertThrow(index_out_of_bounds_t const &, auto value = fixed_.at(size_););
	} TestcaseEnd(fixed_test, test_const_at_function);

	Testcase(fixed_test, test_array_function)
	{
		constexpr size_t size_ = 3;
		auto fixed_ = ds::Fixed<int,size_>({1,2,3});
		AssertTrue(std::is_same<decltype(fixed_.array()), int (&)[size_]>::value);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3}));
	} TestcaseEnd(fixed_test, test_array_function);

	Testcase(fixed_test, test_const_array_function)
	{
		constexpr size_t size_ = 3;
		auto const fixed_ = ds::Fixed<int,size_>({1,2,3});
		AssertTrue(std::is_same<decltype(fixed_.array()), int const(&)[size_]>::value);
		AssertTrue(compare_eq(fixed_.array(), {1,2,3}));
	} TestcaseEnd(fixed_test, test_const_array_function);

	Testcase(fixed_test, test_size_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>();
		AssertEQ(fixed_.size(), size_);
	} TestcaseEnd(fixed_test, test_size_function);

	Testcase(fixed_test, test_const_size_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>();
		AssertEQ(fixed_.size(), size_);
	} TestcaseEnd(fixed_test, test_const_size_function);

	Testcase(fixed_test, test_begin_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		AssertTrue(std::is_same<decltype(fixed_.begin()),int *>::value);
		AssertNotNull(fixed_.begin());
		AssertEQ(fixed_.begin(), &fixed_[0]);
	} TestcaseEnd(fixed_test, test_begin_function);

	Testcase(fixed_test, test_const_begin_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		AssertTrue(std::is_same<decltype(fixed_.begin()),int const *>::value);
		AssertNotNull(fixed_.begin());
		AssertEQ(fixed_.begin(), &fixed_[0]);
	} TestcaseEnd(fixed_test, test_const_begin_function);

	Testcase(fixed_test, test_end_function)
	{
		constexpr size_t size_ = 5;
		auto fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		AssertTrue(std::is_same<decltype(fixed_.end()),int *>::value);
		AssertNotNull(fixed_.end());
		AssertEQ(fixed_.end(), &fixed_[size_]);
	} TestcaseEnd(fixed_test, test_end_function);

	Testcase(fixed_test, test_const_end_function)
	{
		constexpr size_t size_ = 5;
		auto const fixed_ = ds::Fixed<int,size_>({1,2,3,4,5});
		AssertTrue(std::is_same<decltype(fixed_.end()),int const *>::value);
		AssertNotNull(fixed_.end());
		AssertEQ(fixed_.end(), &fixed_[size_]);
	} TestcaseEnd(fixed_test, test_const_end_function);

	Testcase(fixed_test, test_has_iterator_trait_element_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t   = ds::Fixed<int,size_>;
		AssertTrue(ds::has_element<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::element_t,int>::value);
	} TestcaseEnd(fixed_test, test_has_iterator_trait_element_t);

	Testcase(fixed_test, test_const_has_iterator_trait_element_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t   = ds::Fixed<int,size_> const;
		AssertTrue(ds::has_element<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::element_t,int>::value);
	} TestcaseEnd(fixed_test, test_const_has_iterator_trait_element_t);

	Testcase(fixed_test, test_has_iterator_trait_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_>;
		AssertTrue(ds::has_indexable_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::indexable_iterator_t,int *>::value);
	} TestcaseEnd(fixed_test, test_has_iterator_trait_indexable_iterator_t);

	Testcase(fixed_test, test_const_has_iterator_trait_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_> const;
		AssertFalse(ds::has_indexable_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::indexable_iterator_t,void>::value);
	} TestcaseEnd(fixed_test, test_const_has_iterator_trait_indexable_iterator_t);

	Testcase(fixed_test, test_has_iterator_trait_const_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		AssertTrue(ds::has_const_indexable_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::const_indexable_iterator_t,int const *>::value);
	} TestcaseEnd(fixed_test, test_has_iterator_trait_const_indexable_iterator_t);

	Testcase(fixed_test, test_const_has_iterator_trait_const_indexable_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		AssertTrue(ds::has_const_indexable_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::const_indexable_iterator_t,int const *>::value);
	} TestcaseEnd(fixed_test, test_const_has_iterator_trait_const_indexable_iterator_t);

	Testcase(fixed_test, test_has_iterator_trait_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_>;
		AssertTrue(ds::has_forward_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::forward_iterator_t,int *>::value);
	} TestcaseEnd(fixed_test, test_has_iterator_trait_forward_iterator_t);

	Testcase(fixed_test, test_const_has_iterator_trait_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t    = ds::Fixed<int,size_> const;
		AssertFalse(ds::has_forward_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::forward_iterator_t,void>::value);
	} TestcaseEnd(fixed_test, test_const_has_iterator_trait_forward_iterator_t);

	Testcase(fixed_test, test_has_iterator_trait_const_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		AssertTrue(ds::has_const_forward_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::const_forward_iterator_t,int const *>::value);
	} TestcaseEnd(fixed_test, test_has_iterator_trait_const_forward_iterator_t);

	Testcase(fixed_test, test_const_has_iterator_trait_const_forward_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		AssertTrue(ds::has_const_forward_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::const_forward_iterator_t,int const *>::value);
	} TestcaseEnd(fixed_test, test_const_has_iterator_trait_const_forward_iterator_t);

	Testcase(fixed_test, test_has_not_iterator_trait_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		AssertFalse(ds::has_reverse_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::reverse_iterator_t,void>::value);
	} TestcaseEnd(fixed_test, test_has_not_iterator_trait_reverse_iterator_t);

	Testcase(fixed_test, test_const_has_not_iterator_trait_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		AssertFalse(ds::has_reverse_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::reverse_iterator_t,void>::value);
	} TestcaseEnd(fixed_test, test_const_has_not_iterator_trait_reverse_iterator_t);

	Testcase(fixed_test, test_has_not_iterator_trait_const_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_>;
		AssertFalse(ds::has_const_reverse_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::const_reverse_iterator_t,void const>::value);
	} TestcaseEnd(fixed_test, test_has_not_iterator_trait_const_reverse_iterator_t);

	Testcase(fixed_test, test_const_has_not_iterator_trait_const_reverse_iterator_t)
	{
		constexpr size_t size_ = 5;
		using fixed_t          = ds::Fixed<int,size_> const;
		AssertFalse(ds::has_const_reverse_iterator<fixed_t>::value);
		AssertTrue(std::is_same<ds::traits::iterator<fixed_t>::const_reverse_iterator_t,void const>::value);
	} TestcaseEnd(fixed_test, test_const_has_not_iterator_trait_const_reverse_iterator_t);

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

	Testcase(fixed_test, test_iterator_traits_in_function_template_test)
	{
		constexpr size_t size_ = 5;
		ds::Fixed<int,size_> fixed_ = {1,2,3,4,5};
		auto total_ = accumulate(fixed_);
		AssertTrue(std::is_same<decltype(total_),int>::value);
		AssertEQ(total_, 15);
	} TestcaseEnd(fixed_test, test_iterator_traits_in_function_template_test);

	Registry(fixed_test)
	{
		Register(fixed_test, test_constexpr_default_constructor)
		Register(fixed_test, test_constexpr_initializer_list_constructor)
		Register(fixed_test, test_constexpr_diverse_initializer_list_constructor)
		Register(fixed_test, test_constexpr_array_constructor)
		Register(fixed_test, test_constexpr_move_constructor)
		Register(fixed_test, test_constexpr_copy_constructor)
		Register(fixed_test, test_constexpr_make_fixed)
		Register(fixed_test, test_constexpr_make_fixed_with_size)
		Register(fixed_test, test_default_constructor)
		Register(fixed_test, test_initializer_list_constructor)
		Register(fixed_test, test_diverse_initializer_list_constructor)
		Register(fixed_test, test_array_constructor)
		Register(fixed_test, test_move_constructor)
		Register(fixed_test, test_copy_constructor)
		Register(fixed_test, test_move_assignment)
		Register(fixed_test, test_copy_assignment)
		Register(fixed_test, test_make_fixed)
		Register(fixed_test, test_diverse_make_fixed)
		Register(fixed_test, test_make_fixed_with_size)
		Register(fixed_test, test_diverse_make_fixed_with_size)
		Register(fixed_test, test_indexing_operator)
		Register(fixed_test, test_const_indexing_operator)
		Register(fixed_test, test_at_function)
		Register(fixed_test, test_const_at_function)
		Register(fixed_test, test_array_function)
		Register(fixed_test, test_const_array_function)
		Register(fixed_test, test_size_function)
		Register(fixed_test, test_const_size_function)
		Register(fixed_test, test_begin_function)
		Register(fixed_test, test_const_begin_function)
		Register(fixed_test, test_end_function)
		Register(fixed_test, test_const_end_function)
		Register(fixed_test, test_has_iterator_trait_element_t)
		Register(fixed_test, test_const_has_iterator_trait_element_t)
		Register(fixed_test, test_has_iterator_trait_indexable_iterator_t)
		Register(fixed_test, test_const_has_iterator_trait_indexable_iterator_t)
		Register(fixed_test, test_has_iterator_trait_const_indexable_iterator_t)
		Register(fixed_test, test_const_has_iterator_trait_const_indexable_iterator_t)
		Register(fixed_test, test_has_iterator_trait_forward_iterator_t)
		Register(fixed_test, test_const_has_iterator_trait_forward_iterator_t)
		Register(fixed_test, test_has_iterator_trait_const_forward_iterator_t)
		Register(fixed_test, test_const_has_iterator_trait_const_forward_iterator_t)
		Register(fixed_test, test_has_not_iterator_trait_reverse_iterator_t)
		Register(fixed_test, test_const_has_not_iterator_trait_reverse_iterator_t)
		Register(fixed_test, test_has_not_iterator_trait_const_reverse_iterator_t)
		Register(fixed_test, test_const_has_not_iterator_trait_const_reverse_iterator_t)
		Register(fixed_test, test_iterator_traits_in_function_template_test)
	};

} TestEnd(fixed_test);


template <class C> using reporter_t = pptest::colored_printer<C>; 

int main()
{
	return fixed_test().run_all(reporter_t<fixed_test>(pptest::normal));
}