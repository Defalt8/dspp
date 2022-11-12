#include <pptest>
#include <colored_printer>
#include <ds/allocator>

Test(default_allocator_nt_test)
{
	TestInit(default_allocator_nt_test);

	Testcase(test_allocate_requirements)
	{
		AssertTrue(ds::is_same<decltype(ds::DefaultAllocatorNT::allocate(size_t(0), ds::align_t(0))), void *>::value);
	} TestcaseEnd(test_allocate_requirements);

	Testcase(test_deallocate_requirements)
	{
		AssertTrue(ds::is_same<decltype(ds::DefaultAllocatorNT::deallocate((void *)nullptr)), void>::value);
	} TestcaseEnd(test_deallocate_requirements);

	Testcase(test_passing_allocation)
	{
		constexpr size_t size_ = 32;
		auto block_ = ds::DefaultAllocatorNT::allocate(size_);
		AssertNotNull(block_);
		ds::DefaultAllocatorNT::deallocate(block_);
	} TestcaseEnd(test_passing_allocation);

	Testcase(test_failing_allocation)
	{
		constexpr size_t size_ = -1;
		void * block_ = nullptr;
		AssertThrowNone(block_ = ds::DefaultAllocatorNT::allocate(size_));
		ExpectNull(block_);
		ds::DefaultAllocatorNT::deallocate(block_);
	} TestcaseEnd(test_failing_allocation);

	Testcase(test_zero_size_allocation)
	{
		constexpr size_t size_ = 0;
		auto block_ = ds::DefaultAllocatorNT::allocate(size_);
		AssertNotNull(block_);
		ds::DefaultAllocatorNT::deallocate(block_);
	} TestcaseEnd(test_zero_size_allocation);

};


TestRegistry(default_allocator_nt_test)
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
	return default_allocator_nt_test().run_all(reporter_t<default_allocator_nt_test>(pptest::normal));
}