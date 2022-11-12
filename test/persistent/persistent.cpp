#include <pptest>
#include <colored_printer>
#include <ds/persistent>
#include "../counter"

Test(persistent_test)
{
	TestInit(persistent_test);

	PreRun()
	{
		Counter::reset();
	}
	
	Testcase(test_allocator_support)
	{
		AssertTrue(ds::supports_allocator<ds::Persistent<Counter>>::value);
	} TestcaseEnd(test_allocator_support);

	Testcase(test_noinit_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Persistent<Counter>,ds::noinit_t>::value);
	} TestcaseEnd(test_noinit_constructible);
	
	Testcase(test_noinit)
	{
		{
			auto persistent = ds::Persistent<Counter>(ds::noinit);
			ExpectEQ(Counter::count(), 0);
			ExpectEQ(Counter::active(), 0);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
		}
		ExpectEQ(Counter::count(), 0);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_noinit);
	
	Testcase(test_default_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Persistent<Counter>>::value);
	} TestcaseEnd(test_default_constructible);
	
	Testcase(test_default_construct)
	{
		{
			auto persistent = ds::Persistent<Counter>();
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			AssertNotNull(persistent);
			AssertEQ(*persistent, 0);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_default_construct);

	Testcase(test_value_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Persistent<Counter>,int>::value);
		AssertTrue(ds::is_constructible<ds::Persistent<Counter>,Counter>::value);
	} TestcaseEnd(test_value_constructible);
	
	Testcase(test_value_construct)
	{
		{
			auto persistent = ds::Persistent<Counter>(5);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			AssertNotNull(persistent);
			AssertEQ(*persistent, 5);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_value_construct);

	Testcase(test_move_constructible)
	{
		AssertTrue(ds::is_move_constructible<ds::Persistent<Counter>>::value);
	} TestcaseEnd(test_move_constructible);

	Testcase(test_move_construct)
	{
		{
			auto persistent = ds::Persistent<Counter>(5);
			AssertNotNull(persistent);
			Counter * object_ptr_ = &*persistent;
			auto moved_persistent = ds::move(persistent);
			AssertNotNull(moved_persistent);
			AssertNull(persistent);
			AssertEQ(&*moved_persistent, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_move_construct);

	Testcase(test_move_assignable)
	{
		AssertTrue(ds::is_move_assignable<ds::Persistent<Counter>>::value);
	} TestcaseEnd(test_move_assignable);

	Testcase(test_move_assign)
	{
		{
			auto persistent = ds::Persistent<Counter>(5);
			AssertNotNull(persistent);
			Counter * object_ptr_ = &*persistent;
			auto moved_persistent = ds::Persistent<Counter>(ds::noinit);
			moved_persistent = ds::move(persistent);
			AssertNotNull(moved_persistent);
			AssertNull(persistent);
			AssertEQ(&*moved_persistent, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_move_assign);

	Testcase(test_copy_constructible)
	{
		AssertTrue(ds::is_copy_constructible<ds::Persistent<Counter>>::value);
	} TestcaseEnd(test_copy_constructible);

	Testcase(test_copy_construct)
	{
		{
			auto persistent = ds::Persistent<Counter>(5);
			AssertNotNull(persistent);
			ExpectEQ(persistent.ref_count(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * object_ptr_ = &*persistent;
			{
				auto copied_persistent = persistent;
				AssertNotNull(copied_persistent);
				ExpectEQ(copied_persistent.ref_count(), 2);
				ExpectEQ(Counter::count(), 1);
				ExpectEQ(Counter::active(), 1);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
				AssertNotNull(persistent);
				AssertEQ(persistent.ref_count(), 2);
				ExpectEQ(&*copied_persistent, object_ptr_);
				ExpectEQ(&*persistent, object_ptr_);
			}
			AssertNotNull(persistent);
			ExpectEQ(persistent.ref_count(), 1);
			ExpectEQ(&*persistent, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_copy_construct);

	Testcase(test_copy_assignable)
	{
		AssertTrue(ds::is_copy_assignable<ds::Persistent<Counter>>::value);
	} TestcaseEnd(test_copy_assignable);
	
	Testcase(test_copy_assign_null)
	{
		{
			auto persistent = ds::Persistent<Counter>(5);
			AssertNotNull(persistent);
			ExpectEQ(persistent.ref_count(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * object_ptr_ = &*persistent;
			{
				auto copied_persistent = ds::Persistent<Counter>(ds::noinit);
				copied_persistent = persistent;
				AssertNotNull(copied_persistent);
				ExpectEQ(copied_persistent.ref_count(), 2);
				ExpectEQ(Counter::count(), 1);
				ExpectEQ(Counter::active(), 1);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
				AssertNotNull(persistent);
				AssertEQ(persistent.ref_count(), 2);
				ExpectEQ(&*copied_persistent, object_ptr_);
				ExpectEQ(&*persistent, object_ptr_);
			}
			AssertNotNull(persistent);
			ExpectEQ(persistent.ref_count(), 1);
			ExpectEQ(&*persistent, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_copy_assign_null);
	
	Testcase(test_copy_assign_valid)
	{
		{
			auto persistent = ds::Persistent<Counter>(5);
			AssertNotNull(persistent);
			ExpectEQ(persistent.ref_count(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * object_ptr_ = &*persistent;
			{
				auto copied_persistent = ds::Persistent<Counter>(3);
				AssertNotNull(copied_persistent);
				ExpectEQ(Counter::count(), 2);
				ExpectEQ(Counter::active(), 2);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
				copied_persistent = persistent;
				AssertNotNull(copied_persistent);
				ExpectEQ(copied_persistent.ref_count(), 2);
				ExpectEQ(Counter::count(), 2);
				ExpectEQ(Counter::active(), 1);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
				AssertNotNull(persistent);
				AssertEQ(persistent.ref_count(), 2);
				ExpectEQ(&*copied_persistent, object_ptr_);
				ExpectEQ(&*persistent, object_ptr_);
			}
			AssertNotNull(persistent);
			ExpectEQ(persistent.ref_count(), 1);
			ExpectEQ(&*persistent, object_ptr_);
		}
		ExpectEQ(Counter::count(), 2);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_copy_assign_valid);

	Testcase(test_logical_not_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<int>>()).operator!()),bool>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<int> const>()).operator!()),bool>::value);
	} TestcaseEnd(test_logical_not_operator_defined);
	
	Testcase(test_logical_not_operator_on_null)
	{
		auto persistent = ds::Persistent<int>(ds::noinit);
		ExpectTrue(!persistent);
		ExpectNull(persistent);
	} TestcaseEnd(test_logical_not_operator_on_null);
	
	Testcase(test_logical_not_operator_on_valid)
	{
		auto persistent = ds::Persistent<int>(5);
		ExpectFalse(!persistent);
		ExpectNotNull(persistent);
	} TestcaseEnd(test_logical_not_operator_on_valid);
	
	Testcase(test_bool_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<int>>()).operator bool()),bool>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<int> const>()).operator bool()),bool>::value);
	} TestcaseEnd(test_bool_operator_defined);
	
	Testcase(test_bool_operator_on_null)
	{
		auto persistent = ds::Persistent<int>(ds::noinit);
		ExpectFalse(bool(persistent));
	} TestcaseEnd(test_bool_operator_on_null);
	
	Testcase(test_bool_operator_on_valid)
	{
		auto persistent = ds::Persistent<int>(5);
		ExpectTrue(bool(persistent));
	} TestcaseEnd(test_bool_operator_on_valid);
	
	Testcase(test_dereference_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<int>>()).operator*()),int &>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<int> const>()).operator*()),int const &>::value);
	} TestcaseEnd(test_dereference_operator_defined);
	
	Testcase(test_dereference_operator_on_valid)
	{
		auto persistent = ds::Persistent<int>(5);
		AssertNotNull(persistent);
		AssertEQ(*persistent, 5); 
	} TestcaseEnd(test_dereference_operator_on_valid);
	
	Testcase(test_arrow_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<Counter>>()).operator->()),Counter *>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<Counter> const>()).operator->()),Counter const *>::value);
	} TestcaseEnd(test_arrow_operator_defined);
	
	Testcase(test_arrow_operator_on_valid)
	{
		auto persistent = ds::Persistent<Counter>(5);
		AssertNotNull(persistent);
		AssertEQ(persistent->value(), 5); 
	} TestcaseEnd(test_arrow_operator_on_valid);

	Testcase(test_ptr_member_function_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<Counter>>()).ptr()),Counter *>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<Counter> const>()).ptr()),Counter const *>::value);
	} TestcaseEnd(test_ptr_member_function_defined);

	Testcase(test_ptr_member_function_on_valid)
	{
		auto persistent = ds::Persistent<Counter>(5);
		AssertNotNull(persistent);
		ExpectEQ(persistent.ptr(), &*persistent); 
	} TestcaseEnd(test_ptr_member_function_on_valid);

	Testcase(test_ref_member_function_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<Counter>>()).ref()),Counter &>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Persistent<Counter> const>()).ref()),Counter const &>::value);
	} TestcaseEnd(test_ref_member_function_defined);

	Testcase(test_ref_member_function_on_null)
	{
		auto persistent = ds::Persistent<Counter>(ds::noinit);
		AssertNull(persistent);
		ExpectThrowAny(persistent.ref()); 
		ExpectThrow(ds::Persistent<Counter>::null_pointer const & , persistent.ref()); 
	} TestcaseEnd(test_ref_member_function_on_null);

	Testcase(test_ref_member_function_on_valid)
	{
		auto persistent = ds::Persistent<Counter>(5);
		AssertNotNull(persistent);
		ExpectEQ(&persistent.ref(), &*persistent); 
	} TestcaseEnd(test_ref_member_function_on_valid);

};

TestRegistry(persistent_test)
{
	Register(test_allocator_support)
	Register(test_noinit_constructible)
	Register(test_noinit)
	Register(test_default_constructible)
	Register(test_default_construct)
	Register(test_value_constructible)
	Register(test_value_construct)
	Register(test_move_constructible)
	Register(test_move_construct)
	Register(test_move_assignable)
	Register(test_move_assign)
	Register(test_copy_constructible)
	Register(test_copy_construct)
	Register(test_copy_assignable)
	Register(test_copy_assign_null)
	Register(test_copy_assign_valid)
	Register(test_logical_not_operator_defined)
	Register(test_logical_not_operator_on_null)
	Register(test_logical_not_operator_on_valid)
	Register(test_bool_operator_defined)
	Register(test_bool_operator_on_null)
	Register(test_bool_operator_on_valid)
	Register(test_dereference_operator_defined)
	Register(test_dereference_operator_on_valid)
	Register(test_arrow_operator_defined)
	Register(test_arrow_operator_on_valid)
	Register(test_ptr_member_function_defined)
	Register(test_ptr_member_function_on_valid)
	Register(test_ref_member_function_defined)
	Register(test_ref_member_function_on_null)
	Register(test_ref_member_function_on_valid)
};

template <class C>
using reporter_t = pptest::ColoredPrinter<C>;

int main()
{
	return persistent_test().run_all(reporter_t<persistent_test>(pptest::normal));
}
