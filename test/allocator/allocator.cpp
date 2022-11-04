#include <type_traits>
#include <pptest>
#include <colored_printer>
#include <ds/allocator>

Test(allocator_test)
{
	Testcase(allocator_test, test_allocate_requirements)
	{
		AssertTrue(std::is_same<decltype(ds::Allocator::allocate(size_t(0), size_t(0))), void *>::value);
	} TestcaseEnd(allocator_test, test_allocate_requirements)

	Testcase(allocator_test, test_deallocate_requirements)
	{
		AssertTrue(std::is_same<decltype(ds::Allocator::deallocate((void *)nullptr)), void>::value);
	} TestcaseEnd(allocator_test, test_deallocate_requirements)

	Testcase(allocator_test, test_passing_allocation)
	{
		constexpr size_t size_ = 32;
		auto block_ = ds::Allocator::allocate(size_);
		AssertNotNull(block_);
		ds::Allocator::deallocate(block_);
	} TestcaseEnd(allocator_test, test_passing_allocation)

	Testcase(allocator_test, test_failing_allocation)
	{
		constexpr size_t size_ = -1;
		void * block_ = nullptr;
		ExpectThrow(ds::Allocator::allocation_failure const &, block_ = ds::Allocator::allocate(size_));
		ExpectNull(block_);
		ds::Allocator::deallocate(block_);
		ExpectThrow(std::bad_alloc const &, block_ = ds::Allocator::allocate(size_));
		ExpectNull(block_);
		ds::Allocator::deallocate(block_);
	} TestcaseEnd(allocator_test, test_failing_allocation)

	Testcase(allocator_test, test_zero_size_allocation)
	{
		constexpr size_t size_ = 0;
		auto block_ = ds::AllocatorNT::allocate(size_);
		AssertNotNull(block_);
		ds::AllocatorNT::deallocate(block_);
	} TestcaseEnd(allocator_test, test_zero_size_allocation)

	Registry(allocator_test)
	{
		Register(allocator_test, test_allocate_requirements)
		Register(allocator_test, test_deallocate_requirements)
		Register(allocator_test, test_passing_allocation)
		Register(allocator_test, test_failing_allocation)
		Register(allocator_test, test_zero_size_allocation)
	};

} TestEnd(allocator_test);

template <class C> using reporter_t = pptest::colored_printer<C>;

int main()
{
	return allocator_test().run_all(reporter_t<allocator_test>(pptest::normal));
}
