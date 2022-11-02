#include <type_traits>
#include <pptest>
#include <colored_printer>
#include <ds/allocator>

Begin_Test(allocator_test)

	Begin_Testcase(allocator_test, test_allocate_requirements)
	{
		Assert_True(std::is_same<decltype(ds::Allocator::allocate(size_t(0), size_t(0))), void *>::value);
	}
	End_Testcase(allocator_test, test_allocate_requirements)

	Begin_Testcase(allocator_test, test_deallocate_requirements)
	{
		Assert_True(std::is_same<decltype(ds::Allocator::deallocate((void *)nullptr)), void>::value);
	}
	End_Testcase(allocator_test, test_deallocate_requirements)

	Begin_Testcase(allocator_test, test_passing_allocation)
	{
		constexpr size_t size_ = 32;
		auto block_ = ds::Allocator::allocate(size_);
		Assert_NotNull(block_);
		ds::Allocator::deallocate(block_);
	}
	End_Testcase(allocator_test, test_passing_allocation)

	Begin_Testcase(allocator_test, test_failing_allocation)
	{
		constexpr size_t size_ = -1;
		void * block_ = nullptr;
		Assert_Throw(ds::Allocator::allocation_failure const &, block_ = ds::Allocator::allocate(size_));
		Check_Null(block_);
		ds::Allocator::deallocate(block_);
	}
	End_Testcase(allocator_test, test_failing_allocation)

	Begin_Testcase(allocator_test, test_zero_size_allocation)
	{
		constexpr size_t size_ = 0;
		auto block_ = ds::AllocatorNT::allocate(size_);
		Assert_NotNull(block_);
		ds::AllocatorNT::deallocate(block_);
	}
	End_Testcase(allocator_test, test_zero_size_allocation)

	Begin_Testcase_Registration(allocator_test)
	{
		Register_Testcase(allocator_test, test_allocate_requirements)
		Register_Testcase(allocator_test, test_deallocate_requirements)
		Register_Testcase(allocator_test, test_passing_allocation)
		Register_Testcase(allocator_test, test_failing_allocation)
		Register_Testcase(allocator_test, test_zero_size_allocation)
	}
	End_Testcase_Registration(allocator_test)
End_Test(allocator_test);

template <class C> using reporter_t = pptest::colored_printer<C>;

int main()
{
	return allocator_test().run_all(reporter_t<allocator_test>(pptest::normal));
}