#include <pptest>
#include <colored_printer>
#include <ds/common>
#include <ds/fixed_stack>
#include "../counter"

template class ds::FixedStack<5,int>;

Test(fixed_stack_test)
{
	TestInit(fixed_stack_test);

	PreRun()
	{
		Counter::reset();
	}

	Testcase(default_construct_throws_none)
	{
		ExpectThrowNone(ds::FixedStack<5,int>());
	} TestcaseEnd(default_construct_throws_none);

	Testcase(default_construct)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>();
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
		}
		ExpectEQ(Counter::count(), 0);
		ExpectEQ(Counter::active(), 0);
	} TestcaseEnd(default_construct);

	Testcase(move_construct_throws_none)
	{
		auto fstack = ds::FixedStack<5,int>();
		ExpectThrowNone(auto moved_ = ds::move(fstack));
	} TestcaseEnd(move_construct_throws_none);

	Testcase(move_construct_empty)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>();
			AssertEQ(fstack.size(), 0);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
			auto moved_ = ds::move(fstack);
			AssertEQ(moved_.size(), 0);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
		}
		ExpectEQ(Counter::count(), 0);
		ExpectEQ(Counter::active(), 0);
	} TestcaseEnd(move_construct_empty);

	Testcase(move_construct_none_empty)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>();
			for(int i = 1; i <= 3; ++i)
				AssertNotNull(fstack.push(i));
			AssertEQ(fstack.size(), 3);
			ExpectEQ(Counter::count(), 3);
			ExpectEQ(Counter::active(), 3);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 0);
			auto moved_ = ds::move(fstack);
			AssertEQ(moved_.size(), 3);
			ExpectEQ(Counter::count(), 6);
			ExpectEQ(Counter::active(), 3);
			ExpectEQ(Counter::moves(), 3);
			ExpectEQ(Counter::copies(), 0);
			for(size_t i = 0; i < fstack.size(); ++i)
				AssertEQ(fstack[i], moved_[i]);
		}
		ExpectEQ(Counter::count(), 6);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 3);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(move_construct_none_empty);

	Testcase(move_construct_full)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>();
			for(int i = 1; i <= 5; ++i)
				AssertNotNull(fstack.push(i));
			AssertEQ(fstack.size(), 5);
			ExpectEQ(Counter::count(), 5);
			ExpectEQ(Counter::active(), 5);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 0);
			auto moved_ = ds::move(fstack);
			AssertEQ(moved_.size(), 5);
			ExpectEQ(Counter::count(), 10);
			ExpectEQ(Counter::active(), 5);
			ExpectEQ(Counter::moves(), 5);
			ExpectEQ(Counter::copies(), 0);
			for(size_t i = 0; i < fstack.size(); ++i)
				AssertEQ(fstack[i], moved_[i]);
		}
		ExpectEQ(Counter::count(), 10);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 5);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(move_construct_full);

	Testcase(copy_construct_throws_none)
	{
		auto fstack = ds::FixedStack<5,int>();
		ExpectThrowNone(auto copied_ = fstack);
	} TestcaseEnd(copy_construct_throws_none);

	Testcase(copy_construct_empty)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>();
			AssertEQ(fstack.size(), 0);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
			auto copied_ = fstack;
			AssertEQ(copied_.size(), 0);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
		}
		ExpectEQ(Counter::count(), 0);
		ExpectEQ(Counter::active(), 0);
	} TestcaseEnd(copy_construct_empty);

	Testcase(copy_construct_none_empty)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>();
			for(int i = 1; i <= 3; ++i)
				AssertNotNull(fstack.push(i));
			AssertEQ(fstack.size(), 3);
			ExpectEQ(Counter::count(), 3);
			ExpectEQ(Counter::active(), 3);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 0);
			auto copied_ = fstack;
			AssertEQ(copied_.size(), 3);
			ExpectEQ(Counter::count(), 6);
			ExpectEQ(Counter::active(), 6);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 3);
			for(size_t i = 0; i < fstack.size(); ++i)
				AssertEQ(fstack[i], copied_[i]);
		}
		ExpectEQ(Counter::count(), 6);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 3);
	} TestcaseEnd(copy_construct_none_empty);

	Testcase(copy_construct_full)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>();
			for(int i = 1; i <= 5; ++i)
				AssertNotNull(fstack.push(i));
			AssertEQ(fstack.size(), 5);
			ExpectEQ(Counter::count(), 5);
			ExpectEQ(Counter::active(), 5);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 0);
			auto copied_ = fstack;
			AssertEQ(copied_.size(), 5);
			ExpectEQ(Counter::count(), 10);
			ExpectEQ(Counter::active(), 10);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 5);
			for(size_t i = 0; i < fstack.size(); ++i)
				AssertEQ(fstack[i], copied_[i]);
		}
		ExpectEQ(Counter::count(), 10);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 5);
	} TestcaseEnd(copy_construct_full);

	Testcase(array_construct_throws_none)
	{
		ExpectThrowNone(ds::FixedStack<5,int>({1,2,3,4,5}));
	} TestcaseEnd(array_construct_throws_none);

	Testcase(array_construct_empty)
	{
		auto fstack = ds::FixedStack<5,Counter>({});
		ExpectEQ(Counter::count(), 0);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(array_construct_empty);

	Testcase(array_construct_none_empty)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>({1,2,3});
			ExpectEQ(Counter::count(), 3);
			ExpectEQ(Counter::active(), 3);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 0);
		}
		ExpectEQ(Counter::count(), 3);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(array_construct_none_empty);

	Testcase(array_construct_full)
	{
		{
			auto fstack = ds::FixedStack<5,Counter>({1,2,3,4,5});
			ExpectEQ(Counter::count(), 5);
			ExpectEQ(Counter::active(), 5);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 0);
		}
		ExpectEQ(Counter::count(), 5);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(array_construct_full);

	Testcase(push_on_empty_is_valid)
	{
		{
			constexpr size_t capacity_ = 5; 
			auto fstack = ds::FixedStack<capacity_,Counter>();
			ExpectEQ(fstack.capacity(), capacity_);
			ExpectEQ(fstack.size(), 0);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * it = nullptr;
			AssertNotNull(it = fstack.push(1));
			ExpectEQ(*it, 1);
			ExpectEQ(fstack.size(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(push_on_empty_is_valid);

	Testcase(push_until_full_is_valid)
	{
		constexpr size_t capacity_ = 5; 
		{
			auto fstack = ds::FixedStack<capacity_,Counter>();
			ExpectEQ(fstack.capacity(), capacity_);
			ExpectEQ(fstack.size(), 0);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			for(int i = 1; size_t(i) <= capacity_; ++i)
			{
				Counter * it = nullptr;
				AssertNotNull(it = fstack.push(i));
				ExpectEQ(*it, i);
				ExpectEQ(fstack.size(), size_t(i));
				ExpectEQ(Counter::count(), i);
				ExpectEQ(Counter::active(), i);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
			}
			ExpectEQ(fstack.size(), fstack.capacity());
		}
		ExpectEQ(Counter::count(), capacity_);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(push_until_full_is_valid);

	Testcase(push_on_full_returns_nullptr)
	{
		constexpr size_t capacity_ = 5; 
		{
			auto fstack = ds::FixedStack<capacity_,Counter>();
			ExpectEQ(fstack.capacity(), capacity_);
			ExpectEQ(fstack.size(), 0);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			for(int i = 1; size_t(i) <= capacity_; ++i)
				AssertNotNull(fstack.push(i));
			AssertNull(fstack.push(int(capacity_ + 1)));
			ExpectEQ(fstack.size(), fstack.capacity());
		}
		ExpectEQ(Counter::count(), capacity_);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(push_on_full_returns_nullptr);

	Testcase(pop_on_empty_returns_false)
	{
		constexpr size_t capacity_ = 5; 
		auto fstack = ds::FixedStack<capacity_,Counter>();
		ExpectFalse(fstack.pop());
		ExpectEQ(Counter::count(), 0);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(pop_on_empty_returns_false);

	Testcase(pop_move_to_on_empty_returns_false)
	{
		constexpr size_t capacity_ = 5; 
		Counter n = 0;
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 1);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 0);
		auto fstack = ds::FixedStack<capacity_,Counter>();
		ExpectFalse(fstack.pop(n));
		ExpectEQ(n, 0);
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 1);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(pop_move_to_on_empty_returns_false);

	Testcase(pop_until_empty_returns_true)
	{
		constexpr size_t capacity_ = 5; 
		{
			auto fstack = ds::FixedStack<capacity_,Counter>();
			for(int i = 1; i <= 5; ++i)
				AssertNotNull(fstack.push(i));
			for(int i = 5; i > 0; --i)
			{
				AssertEQ(Counter::active(), i);
				AssertTrue(fstack.pop());
				AssertEQ(Counter::active(), i-1);
				AssertEQ(Counter::moves(), 0);
				AssertEQ(Counter::copies(), 0);
			}
		}
		ExpectEQ(Counter::count(), capacity_);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), 0);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(pop_until_empty_returns_true);

	Testcase(pop_move_to_until_empty_returns_true)
	{
		constexpr size_t capacity_ = 5; 
		{
			Counter n = 0;
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::moves(), 0);
			ExpectEQ(Counter::copies(), 0);
			auto fstack = ds::FixedStack<capacity_,Counter>();
			for(int i = 1; i <= 5; ++i)
				AssertNotNull(fstack.push(i));
			for(int i = 5, m = 0; i > 0; --i)
			{
				AssertEQ(Counter::active(), i + 1);
				AssertTrue(fstack.pop(n));
				AssertEQ(n, i);
				AssertEQ(Counter::count(), capacity_ + 1);
				AssertEQ(Counter::active(), i);
				AssertEQ(Counter::moves(), ++m);
				AssertEQ(Counter::copies(), 0);
			}
		}
		ExpectEQ(Counter::count(), capacity_ + 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::moves(), capacity_);
		ExpectEQ(Counter::copies(), 0);
	} TestcaseEnd(pop_move_to_until_empty_returns_true);

	Testcase(size_max_size_member_functions)
	{
		auto fstack = ds::FixedStack<3,int>();
		ExpectEQ(fstack.capacity(), 3);
		ExpectEQ(fstack.size(), 0);
		ExpectLT(fstack.size(), fstack.capacity());
		AssertNotNull(fstack.push(1));
		ExpectEQ(fstack.size(), 1);
		ExpectLT(fstack.size(), fstack.capacity());
		AssertNotNull(fstack.push(2));
		ExpectEQ(fstack.size(), 2);
		ExpectLT(fstack.size(), fstack.capacity());
		AssertNotNull(fstack.push(2));
		ExpectEQ(fstack.size(), 3);
		ExpectEQ(fstack.size(), fstack.capacity());
	} TestcaseEnd(size_max_size_member_functions);

	Testcase(begin_end_member_functions)
	{
		auto fstack = ds::FixedStack<5,int>();
		ExpectNull(fstack.begin());
		ExpectNull(fstack.end());
		AssertNotNull(fstack.push(1));
		AssertNotNull(fstack.begin());
		ExpectEQ(*fstack.begin(), 1);
		ExpectEQ(fstack.begin()+1, fstack.end());
		AssertNotNull(fstack.push(2));
		AssertNotNull(fstack.begin());
		ExpectEQ(*fstack.begin(), 1);
		ExpectEQ(*(fstack.begin()+1), 2);
		ExpectEQ(fstack.begin()+2, fstack.end());
	} TestcaseEnd(begin_end_member_functions);

	Testcase(rbegin_rend_member_functions)
	{
		auto fstack = ds::FixedStack<5,int>();
		ExpectNull(fstack.rbegin());
		ExpectNull(fstack.rend());
		AssertNotNull(fstack.push(1));
		AssertNotNull(fstack.rbegin());
		ExpectEQ(*fstack.rbegin(), 1);
		ExpectEQ(fstack.rbegin()-1, fstack.rend());
		AssertNotNull(fstack.push(2));
		AssertNotNull(fstack.rbegin());
		ExpectEQ(*fstack.rbegin(), 2);
		ExpectEQ(*(fstack.rbegin()-1), 1);
		ExpectEQ(fstack.rbegin()-2, fstack.rend());
	} TestcaseEnd(rbegin_rend_member_functions);

	Testcase(foreach_iteration)
	{
		auto fstack = ds::FixedStack<5,int>();
		int i = 0;
		for(auto & e : fstack)
			AssertEQ(e, ++i);
	} TestcaseEnd(foreach_iteration);

	Testcase(iterable_traits)
	{
		using E = int;
		using fixed_stack_t = ds::FixedStack<5,E>;
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::size_t,size_t>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::element_t,E>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::indexable_iterator_t,E *>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::const_indexable_iterator_t,E const *>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::forward_iterator_t,E *>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::const_forward_iterator_t,E const *>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::reverse_iterator_t,E *>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<fixed_stack_t>::const_reverse_iterator_t,E const *>::value);
	} TestcaseEnd(iterable_traits);

	Testcase(const_iterable_traits)
	{
		using E = int;
		using const_fixed_stack_t = ds::FixedStack<5,E> const;
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::size_t,size_t>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::element_t,E>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::indexable_iterator_t,void>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::const_indexable_iterator_t,E const *>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::forward_iterator_t,void>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::const_forward_iterator_t,E const *>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::reverse_iterator_t,void>::value);
		ExpectTrue(ds::is_same<ds::traits::iterable<const_fixed_stack_t>::const_reverse_iterator_t,E const *>::value);
	} TestcaseEnd(const_iterable_traits);

};

TestRegistry(fixed_stack_test)
{
	Register(default_construct_throws_none)
	Register(default_construct)
	Register(move_construct_throws_none)
	Register(move_construct_empty)
	Register(move_construct_none_empty)
	Register(move_construct_full)
	Register(copy_construct_throws_none)
	Register(copy_construct_empty)
	Register(copy_construct_none_empty)
	Register(copy_construct_full)
	Register(array_construct_throws_none)
	Register(array_construct_empty)
	Register(array_construct_none_empty)
	Register(array_construct_full)
	Register(push_on_empty_is_valid)
	Register(push_until_full_is_valid)
	Register(push_on_full_returns_nullptr)
	Register(pop_on_empty_returns_false)
	Register(pop_move_to_on_empty_returns_false)
	Register(pop_until_empty_returns_true)
	Register(pop_move_to_until_empty_returns_true)
	Register(size_max_size_member_functions)
	Register(begin_end_member_functions)
	Register(rbegin_rend_member_functions)
	Register(foreach_iteration)
	Register(iterable_traits)
	Register(const_iterable_traits)
};

template <class C> using reporter_t = pptest::colored_printer<C>;

int main()
{
	return fixed_stack_test().run_all(reporter_t<fixed_stack_test>(pptest::normal));
}
