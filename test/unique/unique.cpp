#include <pptest>
#include <colored_printer>
#include <ds/unique>
#include "../counter"
#include "../nomove"
#include "../nocopy"

template class ds::Unique<int>;
template class ds::Unique<Counter>;
template class ds::Unique<NoMove>;
template class ds::Unique<NoCopy>;

Test(unique_test)
{
	TestInit(unique_test);

	PreRun()
	{
		Counter::reset();
	}
	
	Testcase(test_allocator_support)
	{
		AssertTrue(ds::supports_allocator<ds::Unique<Counter>>::value);
	} TestcaseEnd(test_allocator_support);

	Testcase(test_noinit_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Unique<Counter>,ds::noinit_t>::value);
	} TestcaseEnd(test_noinit_constructible);
	
	Testcase(test_noinit)
	{
		{
			auto unique = ds::Unique<Counter>(ds::noinit);
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
		AssertTrue(ds::is_constructible<ds::Unique<Counter>>::value);
	} TestcaseEnd(test_default_constructible);
	
	Testcase(test_default_construct)
	{
		{
			auto unique = ds::Unique<Counter>();
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			AssertNotNull(unique);
			AssertEQ(*unique, 0);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_default_construct);

	Testcase(test_value_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Unique<Counter>,int>::value);
		AssertTrue(ds::is_constructible<ds::Unique<Counter>,Counter>::value);
	} TestcaseEnd(test_value_constructible);
	
	Testcase(test_value_construct)
	{
		{
			auto unique = ds::Unique<Counter>(5);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			AssertNotNull(unique);
			AssertEQ(*unique, 5);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_value_construct);

	Testcase(test_move_constructible)
	{
		AssertTrue(ds::is_move_constructible<ds::Unique<Counter>>::value);
	} TestcaseEnd(test_move_constructible);

	Testcase(test_move_construct)
	{
		{
			auto unique = ds::Unique<Counter>(5);
			AssertNotNull(unique);
			Counter * object_ptr_ = &*unique;
			auto moved_unique = ds::move(unique);
			AssertNotNull(moved_unique);
			AssertNull(unique);
			AssertEQ(&*moved_unique, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_move_construct);

	Testcase(test_move_assignable)
	{
		AssertTrue(ds::is_move_assignable<ds::Unique<Counter>>::value);
	} TestcaseEnd(test_move_assignable);

	Testcase(test_move_assign_null)
	{
		{
			auto unique = ds::Unique<Counter>(5);
			AssertNotNull(unique);
			Counter * object_ptr_ = &*unique;
			auto moved_unique = ds::Unique<Counter>(ds::noinit);
			moved_unique = ds::move(unique);
			AssertNotNull(moved_unique);
			AssertNull(unique);
			AssertEQ(&*moved_unique, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_move_assign_null);

	Testcase(test_move_assign_valid)
	{
		{
			auto unique = ds::Unique<Counter>(5);
			AssertNotNull(unique);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * object_ptr_ = &*unique;
			auto moved_unique = ds::Unique<Counter>(3);
			ExpectEQ(Counter::count(), 2);
			ExpectEQ(Counter::active(), 2);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			AssertNotNull(moved_unique);
			moved_unique = ds::move(unique);
			AssertNotNull(moved_unique);
			AssertNull(unique);
			AssertEQ(&*moved_unique, object_ptr_);
			ExpectEQ(Counter::count(), 2);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
		}
		ExpectEQ(Counter::count(), 2);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_move_assign_valid);

	Testcase(test_not_copy_constructible)
	{
		AssertTrue(!ds::is_copy_constructible<ds::Unique<Counter>>::value);
	} TestcaseEnd(test_not_copy_constructible);

	Testcase(test_not_copy_assignable)
	{
		AssertTrue(!ds::is_copy_assignable<ds::Unique<Counter>>::value);
	} TestcaseEnd(test_not_copy_assignable);
	
	Testcase(test_logical_not_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<int>>()).operator!()),bool>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<int> const>()).operator!()),bool>::value);
	} TestcaseEnd(test_logical_not_operator_defined);
	
	Testcase(test_logical_not_operator_on_null)
	{
		auto unique = ds::Unique<int>(ds::noinit);
		ExpectTrue(!unique);
		ExpectNull(unique);
	} TestcaseEnd(test_logical_not_operator_on_null);
	
	Testcase(test_logical_not_operator_on_valid)
	{
		auto unique = ds::Unique<int>(5);
		ExpectFalse(!unique);
		ExpectNotNull(unique);
	} TestcaseEnd(test_logical_not_operator_on_valid);
	
	Testcase(test_bool_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<int>>()).operator bool()),bool>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<int> const>()).operator bool()),bool>::value);
	} TestcaseEnd(test_bool_operator_defined);
	
	Testcase(test_bool_operator_on_null)
	{
		auto unique = ds::Unique<int>(ds::noinit);
		ExpectFalse(bool(unique));
	} TestcaseEnd(test_bool_operator_on_null);
	
	Testcase(test_bool_operator_on_valid)
	{
		auto unique = ds::Unique<int>(5);
		ExpectTrue(bool(unique));
	} TestcaseEnd(test_bool_operator_on_valid);
	
	Testcase(test_dereference_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<int>>()).operator*()),int &>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<int> const>()).operator*()),int const &>::value);
	} TestcaseEnd(test_dereference_operator_defined);
	
	Testcase(test_dereference_operator_on_valid)
	{
		auto unique = ds::Unique<int>(5);
		AssertNotNull(unique);
		AssertEQ(*unique, 5); 
	} TestcaseEnd(test_dereference_operator_on_valid);
	
	Testcase(test_arrow_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<Counter>>()).operator->()),Counter *>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<Counter> const>()).operator->()),Counter const *>::value);
	} TestcaseEnd(test_arrow_operator_defined);
	
	Testcase(test_arrow_operator_on_valid)
	{
		auto unique = ds::Unique<Counter>(5);
		AssertNotNull(unique);
		AssertEQ(unique->value(), 5); 
	} TestcaseEnd(test_arrow_operator_on_valid);

	Testcase(test_ptr_member_function_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<Counter>>()).ptr()),Counter *>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<Counter> const>()).ptr()),Counter const *>::value);
	} TestcaseEnd(test_ptr_member_function_defined);

	Testcase(test_ptr_member_function_on_valid)
	{
		auto unique = ds::Unique<Counter>(5);
		AssertNotNull(unique);
		ExpectEQ(unique.ptr(), &*unique); 
	} TestcaseEnd(test_ptr_member_function_on_valid);

	Testcase(test_ref_member_function_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<Counter>>()).ref()),Counter &>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Unique<Counter> const>()).ref()),Counter const &>::value);
	} TestcaseEnd(test_ref_member_function_defined);

	Testcase(test_ref_member_function_on_null)
	{
		auto unique = ds::Unique<Counter>(ds::noinit);
		AssertNull(unique);
		ExpectThrowAny(unique.ref()); 
		ExpectThrow(ds::Unique<Counter>::null_pointer const & , unique.ref()); 
	} TestcaseEnd(test_ref_member_function_on_null);

	Testcase(test_ref_member_function_on_valid)
	{
		auto unique = ds::Unique<Counter>(5);
		AssertNotNull(unique);
		ExpectEQ(&unique.ref(), &*unique); 
	} TestcaseEnd(test_ref_member_function_on_valid);

};

TestRegistry(unique_test)
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
	Register(test_move_assign_null)
	Register(test_move_assign_valid)
	Register(test_not_copy_constructible)
	Register(test_not_copy_assignable)
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
	return unique_test().run_all(reporter_t<unique_test>(pptest::normal));
}
