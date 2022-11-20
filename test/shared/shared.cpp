#include <pptest>
#include <colored_printer>
#include <ds/shared>
#include "../counter"

template class ds::Shared<int>;
template class ds::Shared<Counter>;

Test(shared_test)
{
	TestInit(shared_test);
	
	PreRun()
	{
		Counter::reset();
	}
	
	Testcase(test_allocator_support)
	{
		AssertTrue(ds::supports_allocator<ds::Shared<Counter>>::value);
	} TestcaseEnd(test_allocator_support);

	Testcase(test_noinit_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Shared<Counter>,ds::noinit_t>::value);
	} TestcaseEnd(test_noinit_constructible);
	
	Testcase(test_noinit)
	{
		{
			auto shared = ds::Shared<Counter>(ds::noinit);
			AssertNull(shared);
			ExpectFalse(shared.is_owner());
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
		AssertTrue(ds::is_constructible<ds::Shared<Counter>>::value);
	} TestcaseEnd(test_default_constructible);
	
	Testcase(test_default_construct)
	{
		{
			auto shared = ds::Shared<Counter>();
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			AssertEQ(*shared, 0);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_default_construct);

	Testcase(test_arg_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Shared<Counter>,int>::value);
		AssertTrue(ds::is_constructible<ds::Shared<Counter>,Counter>::value);
	} TestcaseEnd(test_arg_constructible);
	
	Testcase(test_arg_construct)
	{
		{
			auto shared = ds::Shared<Counter>(5);
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			AssertEQ(*shared, 5);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_arg_construct);

	struct Base
	{
		virtual Counter const & counter() const = 0;
	};

	struct Derived : Base
	{
		Counter _counter = 0;

		Counter const & counter() const override { return _counter; }

		~Derived() = default;
		Derived()  = default;
		Derived(int value_) 
			: _counter { value_ } 
		{}
	};

	struct VBase
	{
		virtual ~VBase() = default;
		virtual Counter const & counter() const = 0;
	};

	struct VDerived : VBase
	{
		Counter _counter = 0;

		Counter const & counter() const override { return _counter; }

		~VDerived() = default;
		VDerived()  = default;
		VDerived(int value_) 
			: _counter { value_ } 
		{}
	};

	Testcase(test_polymorphic_arg_inconstructible)
	{
		AssertFalse(ds::is_constructible<ds::Shared<Base>,ds::make<Derived>>::value);
		AssertFalse(ds::is_constructible<ds::Shared<Base>,ds::make<VDerived>>::value);
		AssertFalse(ds::is_constructible<ds::Shared<VBase>,ds::make<Derived>>::value);
	} TestcaseEnd(test_polymorphic_arg_inconstructible);
	
	Testcase(test_polymorphic_arg_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Shared<VBase>,ds::make<VDerived>>::value);
	} TestcaseEnd(test_polymorphic_arg_constructible);
	
	Testcase(test_polymorphic_arg_construct)
	{
		{
			auto unique = ds::Shared<VBase>(ds::make<VDerived>(), 5);
			AssertNotNull(unique);
			AssertEQ(unique->counter(), 5);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_polymorphic_arg_construct);

	Testcase(test_unique_constructible)
	{
		AssertTrue(ds::is_constructible<ds::Shared<Counter>,ds::Unique<Counter>>::value);
	} TestcaseEnd(test_unique_constructible);

	Testcase(test_unique_construct)
	{
		{
			auto unique = ds::Unique<Counter>(5);
			AssertNotNull(unique);
			Counter * object_ptr_ = &*unique;
			auto shared = ds::Shared<Counter>(ds::move(unique));
			AssertNotNull(shared);
			AssertNull(unique);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			AssertEQ(&*shared, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_unique_construct);

	Testcase(test_move_constructible)
	{
		AssertTrue(ds::is_move_constructible<ds::Shared<Counter>>::value);
	} TestcaseEnd(test_move_constructible);

	Testcase(test_move_construct)
	{
		{
			auto shared = ds::Shared<Counter>(5);
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			Counter * object_ptr_ = &*shared;
			auto moved_shared = ds::move(shared);
			AssertNotNull(moved_shared);
			ExpectTrue(moved_shared.is_owner());
			ExpectEQ(moved_shared.ref_count(), 1);
			AssertNull(shared);
			ExpectFalse(shared.is_owner());
			ExpectEQ(shared.ref_count(), 0);
			AssertEQ(&*moved_shared, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_move_construct);

	Testcase(test_move_assignable)
	{
		AssertTrue(ds::is_move_assignable<ds::Shared<Counter>>::value);
	} TestcaseEnd(test_move_assignable);

	Testcase(test_move_assign)
	{
		{
			auto shared = ds::Shared<Counter>(5);
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			Counter * object_ptr_ = &*shared;
			auto moved_shared = ds::Shared<Counter>(ds::noinit);
			moved_shared = ds::move(shared);
			AssertNotNull(moved_shared);
			ExpectTrue(moved_shared.is_owner());
			ExpectEQ(moved_shared.ref_count(), 1);
			AssertNull(shared);
			ExpectFalse(shared.is_owner());
			ExpectEQ(shared.ref_count(), 0);
			AssertEQ(&*moved_shared, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_move_assign);

	Testcase(test_copy_constructible)
	{
		AssertTrue(ds::is_copy_constructible<ds::Shared<Counter>>::value);
	} TestcaseEnd(test_copy_constructible);

	Testcase(test_copy_construct)
	{
		{
			auto shared = ds::Shared<Counter>(5);
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * object_ptr_ = &*shared;
			{
				auto copied_shared = shared;
				AssertNotNull(copied_shared);
				ExpectFalse(copied_shared.is_owner());
				ExpectEQ(copied_shared.ref_count(), 2);
				ExpectEQ(Counter::count(), 1);
				ExpectEQ(Counter::active(), 1);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
				AssertNotNull(shared);
				ExpectTrue(shared.is_owner());
				AssertEQ(shared.ref_count(), 2);
				ExpectEQ(&*copied_shared, object_ptr_);
				ExpectEQ(&*shared, object_ptr_);
			}
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			ExpectEQ(&*shared, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_copy_construct);

	Testcase(test_copy_assignable)
	{
		AssertTrue(ds::is_copy_assignable<ds::Shared<Counter>>::value);
	} TestcaseEnd(test_copy_assignable);
	
	Testcase(test_copy_assign_null)
	{
		{
			auto shared = ds::Shared<Counter>(5);
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * object_ptr_ = &*shared;
			{
				auto copied_shared = ds::Shared<Counter>(ds::noinit);
				copied_shared = shared;
				AssertNotNull(copied_shared);
				ExpectFalse(copied_shared.is_owner());
				ExpectEQ(copied_shared.ref_count(), 2);
				ExpectEQ(Counter::count(), 1);
				ExpectEQ(Counter::active(), 1);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
				AssertNotNull(shared);
				ExpectTrue(shared.is_owner());
				AssertEQ(shared.ref_count(), 2);
				ExpectEQ(&*copied_shared, object_ptr_);
				ExpectEQ(&*shared, object_ptr_);
			}
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			ExpectEQ(&*shared, object_ptr_);
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_copy_assign_null);

	Testcase(test_copy_assign_valid)
	{
		{
			auto shared = ds::Shared<Counter>(5);
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			Counter * object_ptr_ = &*shared;
			{
				auto copied_shared = ds::Shared<Counter>(3);
				copied_shared = shared;
				AssertNotNull(copied_shared);
				ExpectFalse(copied_shared.is_owner());
				ExpectEQ(copied_shared.ref_count(), 2);
				ExpectEQ(Counter::count(), 2);
				ExpectEQ(Counter::active(), 1);
				ExpectEQ(Counter::copies(), 0);
				ExpectEQ(Counter::moves(), 0);
				AssertNotNull(shared);
				ExpectTrue(shared.is_owner());
				AssertEQ(shared.ref_count(), 2);
				ExpectEQ(&*copied_shared, object_ptr_);
				ExpectEQ(&*shared, object_ptr_);
			}
			AssertNotNull(shared);
			ExpectTrue(shared.is_owner());
			ExpectEQ(shared.ref_count(), 1);
			ExpectEQ(&*shared, object_ptr_);
		}
		ExpectEQ(Counter::count(), 2);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_copy_assign_valid);

	Testcase(test_logical_not_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<int>>()).operator!()),bool>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<int> const>()).operator!()),bool>::value);
	} TestcaseEnd(test_logical_not_operator_defined);
	
	Testcase(test_logical_not_operator_on_null)
	{
		auto shared = ds::Shared<int>(ds::noinit);
		ExpectTrue(!shared);
		ExpectNull(shared);
	} TestcaseEnd(test_logical_not_operator_on_null);
	
	Testcase(test_logical_not_operator_on_valid)
	{
		auto shared = ds::Shared<int>(5);
		ExpectFalse(!shared);
		ExpectNotNull(shared);
	} TestcaseEnd(test_logical_not_operator_on_valid);
	
	Testcase(test_bool_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<int>>()).operator bool()),bool>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<int> const>()).operator bool()),bool>::value);
	} TestcaseEnd(test_bool_operator_defined);
	
	Testcase(test_bool_operator_on_null)
	{
		auto shared = ds::Shared<int>(ds::noinit);
		ExpectFalse(bool(shared));
	} TestcaseEnd(test_bool_operator_on_null);
	
	Testcase(test_bool_operator_on_valid)
	{
		auto shared = ds::Shared<int>(5);
		ExpectTrue(bool(shared));
	} TestcaseEnd(test_bool_operator_on_valid);
	
	Testcase(test_dereference_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<int>>()).operator*()),int &>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<int> const>()).operator*()),int const &>::value);
	} TestcaseEnd(test_dereference_operator_defined);
	
	Testcase(test_dereference_operator_on_valid)
	{
		auto shared = ds::Shared<int>(5);
		AssertNotNull(shared);
		AssertEQ(*shared, 5); 
	} TestcaseEnd(test_dereference_operator_on_valid);
	
	Testcase(test_arrow_operator_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<Counter>>()).operator->()),Counter *>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<Counter> const>()).operator->()),Counter const *>::value);
	} TestcaseEnd(test_arrow_operator_defined);
	
	Testcase(test_arrow_operator_on_valid)
	{
		auto shared = ds::Shared<Counter>(5);
		AssertNotNull(shared);
		AssertEQ(shared->value(), 5); 
	} TestcaseEnd(test_arrow_operator_on_valid);

	Testcase(test_destroy_member_function_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<Counter>>()).destroy()),void>::value);
	} TestcaseEnd(test_destroy_member_function_defined);

	Testcase(test_destroy_member_function_on_valid)
	{
		{
			auto shared = ds::Shared<Counter>(5);
			AssertNotNull(shared);
			AssertTrue(shared.is_owner());
			AssertTrue(shared.ref_count(), 1);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 1);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			AssertThrowNone(shared.destroy());
			AssertNull(shared);
			AssertFalse(shared.is_owner());
			AssertTrue(shared.ref_count(), 0);
			ExpectEQ(Counter::count(), 1);
			ExpectEQ(Counter::active(), 0);
			ExpectEQ(Counter::copies(), 0);
			ExpectEQ(Counter::moves(), 0);
			AssertThrowNone(shared.destroy());
		}
		ExpectEQ(Counter::count(), 1);
		ExpectEQ(Counter::active(), 0);
		ExpectEQ(Counter::copies(), 0);
		ExpectEQ(Counter::moves(), 0);
	} TestcaseEnd(test_destroy_member_function_on_valid);

	Testcase(test_ptr_member_function_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<Counter>>()).ptr()),Counter *>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<Counter> const>()).ptr()),Counter const *>::value);
	} TestcaseEnd(test_ptr_member_function_defined);

	Testcase(test_ptr_member_function_on_valid)
	{
		auto shared = ds::Shared<Counter>(5);
		AssertNotNull(shared);
		ExpectEQ(shared.ptr(), &*shared); 
	} TestcaseEnd(test_ptr_member_function_on_valid);

	Testcase(test_ref_member_function_defined)
	{
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<Counter>>()).ref()),Counter &>::value);
		AssertTrue(ds::is_same<decltype((ds::decl<ds::Shared<Counter> const>()).ref()),Counter const &>::value);
	} TestcaseEnd(test_ref_member_function_defined);

	Testcase(test_ref_member_function_on_null)
	{
		auto shared = ds::Shared<Counter>(ds::noinit);
		AssertNull(shared);
		ExpectThrowAny(shared.ref()); 
		ExpectThrow(ds::Shared<Counter>::null_pointer const & , shared.ref()); 
	} TestcaseEnd(test_ref_member_function_on_null);

	Testcase(test_ref_member_function_on_valid)
	{
		auto shared = ds::Shared<Counter>(5);
		AssertNotNull(shared);
		ExpectEQ(&shared.ref(), &*shared); 
	} TestcaseEnd(test_ref_member_function_on_valid);

};

TestRegistry(shared_test)
{
	Register(test_allocator_support)
	Register(test_noinit_constructible)
	Register(test_noinit)
	Register(test_default_constructible)
	Register(test_default_construct)
	Register(test_arg_constructible)
	Register(test_arg_construct)
	Register(test_polymorphic_arg_inconstructible)
	Register(test_polymorphic_arg_constructible)
	Register(test_polymorphic_arg_construct)
	Register(test_unique_constructible)
	Register(test_unique_construct)
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
	return shared_test().run_all(reporter_t<shared_test>(pptest::normal));
}
