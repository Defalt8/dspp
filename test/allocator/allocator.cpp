#include <pptest>
#include <colored_printer>
#include <ds/allocator>

Test(default_allocator_test)
{
	TestInit(default_allocator_test);

	Testcase(test_allocate_requirements)
	{
		AssertTrue(ds::is_same<decltype(ds::default_allocator::allocate(size_t(0), ds::align_t(0))), void *>::value);
	} TestcaseEnd(test_allocate_requirements);

	Testcase(test_deallocate_requirements)
	{
		AssertTrue(ds::is_same<decltype(ds::default_allocator::deallocate((void *)nullptr)), void>::value);
	} TestcaseEnd(test_deallocate_requirements);

	Testcase(test_passing_allocation)
	{
		constexpr size_t size_ = 32;
		auto block_ = ds::default_allocator::allocate(size_);
		AssertNotNull(block_);
		ds::default_allocator::deallocate(block_);
	} TestcaseEnd(test_passing_allocation);

	Testcase(test_failing_allocation)
	{
		constexpr size_t size_ = -1;
		void * block_ = nullptr;
		ExpectThrow(ds::default_allocator::allocation_failure const &, block_ = ds::default_allocator::allocate(size_));
		ExpectNull(block_);
		ds::default_allocator::deallocate(block_);
		ExpectThrow(std::bad_alloc const &, block_ = ds::default_allocator::allocate(size_));
		ExpectNull(block_);
		ds::default_allocator::deallocate(block_);
	} TestcaseEnd(test_failing_allocation);

	Testcase(test_zero_size_allocation)
	{
		constexpr size_t size_ = 0;
		auto block_ = ds::default_allocator_nt::allocate(size_);
		AssertNotNull(block_);
		ds::default_allocator_nt::deallocate(block_);
	} TestcaseEnd(test_zero_size_allocation);

};

TestRegistry(default_allocator_test)
{
	Register(test_allocate_requirements)
	Register(test_deallocate_requirements)
	Register(test_passing_allocation)
	Register(test_failing_allocation)
	Register(test_zero_size_allocation)
};

template <class C> using reporter_t = pptest::colored_printer<C>;

int main()
{
	return default_allocator_test().run_all(reporter_t<default_allocator_test>(pptest::normal));
}
