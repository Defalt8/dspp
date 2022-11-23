#include <pptest>
#include <colored_printer>
#include <ds/sys>

Test(sys_test)
{
	TestInit(sys_test);

	static constexpr char const * existing_dir_path  = WORKING_DIR"_test_dir";
	static constexpr char const * existing_file_path = WORKING_DIR"_test_file.txt";
  #ifdef _WIN32
	static constexpr char const * invalid_path       = WORKING_DIR"?<|>";
  #else
	static constexpr char const * invalid_path       = "";
  #endif

	Testcase(test_exists)
	{
		ExpectFalse(ds::sys::exists(nullptr));
		ExpectFalse(ds::sys::exists(WORKING_DIR"_non_existent"));
		ExpectTrue(ds::sys::exists("."));
		constexpr char const * dir_path  = WORKING_DIR"_test_dir";
		constexpr char const * file_path = WORKING_DIR"_test_file.txt";
		ExpectTrue(ds::sys::exists(dir_path));
		ExpectTrue(ds::sys::exists(file_path));

	} TestcaseEnd(test_exists);

	Testcase(test_get_type)
	{
		ExpectEQ(ds::sys::get_type("."), ds::sys::type::dir);
		ExpectEQ(ds::sys::get_type(nullptr), ds::sys::type::does_not_exist);
		ExpectEQ(ds::sys::get_type(WORKING_DIR"_non_existent"), ds::sys::type::does_not_exist);
		constexpr char const * dir_path  = WORKING_DIR"_test_dir";
		constexpr char const * file_path = WORKING_DIR"_test_file.txt";
		AssertTrue(ds::sys::exists(dir_path));
		AssertTrue(ds::sys::exists(file_path));
		ExpectEQ(ds::sys::get_type(dir_path), ds::sys::type::dir);
		ExpectEQ(ds::sys::get_type(file_path), ds::sys::type::regular_file);
		
	} TestcaseEnd(test_get_type);

	Testcase(test_is_dir)
	{
		ExpectTrue(ds::sys::is_dir("."));
		ExpectTrue(ds::sys::is_dir("/"));
		ExpectFalse(ds::sys::is_dir(nullptr));
		ExpectFalse(ds::sys::is_dir(WORKING_DIR"_non_existent"));
		AssertTrue(ds::sys::exists(existing_dir_path));
		AssertTrue(ds::sys::exists(existing_file_path));
		ExpectTrue(ds::sys::is_dir(existing_dir_path));
		ExpectFalse(ds::sys::is_dir(existing_file_path));

	} TestcaseEnd(test_is_dir);

	Testcase(test_is_file)
	{
		ExpectFalse(ds::sys::is_file("."));
		ExpectFalse(ds::sys::is_file("/"));
		ExpectFalse(ds::sys::is_file(nullptr));
		ExpectFalse(ds::sys::is_file(WORKING_DIR"_non_existent"));
		constexpr char const * dir_path  = WORKING_DIR"_test_dir";
		constexpr char const * file_path = WORKING_DIR"_test_file.txt";
		AssertTrue(ds::sys::exists(dir_path));
		AssertTrue(ds::sys::exists(file_path));
		ExpectTrue(ds::sys::is_file(file_path));
		ExpectFalse(ds::sys::is_file(dir_path));

	} TestcaseEnd(test_is_file);

	Testcase(test_is_regular_file)
	{
		ExpectFalse(ds::sys::is_regular_file("."));
		ExpectFalse(ds::sys::is_regular_file("/"));
		ExpectFalse(ds::sys::is_regular_file(nullptr));
		ExpectFalse(ds::sys::is_regular_file(WORKING_DIR"_non_existent"));
		constexpr char const * dir_path  = WORKING_DIR"_test_dir";
		constexpr char const * file_path = WORKING_DIR"_test_file.txt";
		AssertTrue(ds::sys::exists(dir_path));
		AssertTrue(ds::sys::exists(file_path));
		ExpectTrue(ds::sys::is_regular_file(file_path));
		ExpectFalse(ds::sys::is_regular_file(dir_path));

	} TestcaseEnd(test_is_regular_file);

	Testcase(test_mkdir_non_existing)
	{
		constexpr char const * dir_path = WORKING_DIR"_test_mkdir";
		if(ds::sys::exists(dir_path))
		{
			if(ds::sys::get_type(dir_path) == ds::sys::type::dir)
				ds::sys::rmdir(dir_path);
			else
				remove(dir_path);
		}
		AssertFalse(ds::sys::exists(dir_path));
		ExpectEQ(ds::sys::mkdir(dir_path), ds::sys::smkdir::ok);
		AssertEQ(ds::sys::get_type(dir_path), ds::sys::type::dir);

	} TestcaseEnd(test_mkdir_non_existing);

	Testcase(test_mkdir_existing)
	{
		ExpectEQ(ds::sys::mkdir(existing_dir_path), ds::sys::smkdir::ok);
		ExpectEQ(ds::sys::mkdir(existing_file_path), ds::sys::smkdir::file_exists);

	} TestcaseEnd(test_mkdir_existing);

	Testcase(test_mkdir_invalid_path)
	{
		char _max_path[ds::sys::max_path+2] = {};
		for(auto & e : _max_path)
			e = 'e';
		_max_path[ds::sys::max_path+1] = '\0';
		ExpectEQ(ds::sys::mkdir(nullptr), ds::sys::smkdir::invalid_path);
		ExpectEQ(ds::sys::mkdir(invalid_path), ds::sys::smkdir::invalid_path);
		ExpectEQ(ds::sys::mkdir(""), ds::sys::smkdir::invalid_path);
		ExpectEQ(ds::sys::mkdir(_max_path), ds::sys::smkdir::name_too_long);

	} TestcaseEnd(test_mkdir_invalid_path);

	Testcase(test_mkdirs_non_existing)
	{
		constexpr char const * dir_path = WORKING_DIR"_test_mkdirs/subdir1/subdir2";
		if(ds::sys::exists(dir_path))
		{
			if(ds::sys::get_type(dir_path) == ds::sys::type::dir)
			{
				ds::sys::rmdir(dir_path);
				ds::sys::rmdir(WORKING_DIR"_test_mkdirs/subdir1");
				ds::sys::rmdir(WORKING_DIR"_test_mkdirs");
			}
			else
				remove(dir_path);
		}
		AssertFalse(ds::sys::exists(dir_path));
		ExpectEQ(ds::sys::mkdirs(dir_path), ds::sys::smkdir::ok);
		AssertEQ(ds::sys::get_type(dir_path), ds::sys::type::dir);

	} TestcaseEnd(test_mkdirs_non_existing);

	Testcase(test_mkdirs_existing)
	{
		ExpectEQ(ds::sys::mkdirs(existing_dir_path), ds::sys::smkdir::ok);
		ExpectEQ(ds::sys::mkdirs(existing_file_path), ds::sys::smkdir::file_exists);

	} TestcaseEnd(test_mkdirs_existing);

	Testcase(test_mkdirs_invalid_path)
	{
		char _max_path[ds::sys::max_path+2] = {};
		for(auto & e : _max_path)
			e = 'e';
		_max_path[ds::sys::max_path+1] = '\0';
		ExpectEQ(ds::sys::mkdirs(nullptr), ds::sys::smkdir::invalid_path);
		ExpectEQ(ds::sys::mkdirs(invalid_path), ds::sys::smkdir::invalid_path);
		ExpectEQ(ds::sys::mkdirs(""), ds::sys::smkdir::invalid_path);
		ExpectEQ(ds::sys::mkdirs(_max_path), ds::sys::smkdir::name_too_long);

	} TestcaseEnd(test_mkdirs_invalid_path);

	Testcase(test_rmdir_not_empty)
	{
		constexpr char const * dir_path = WORKING_DIR"_test_rmdir_not_empty";
		constexpr char const * subdir_path = WORKING_DIR"_test_rmdir_not_empty/subdir";
		if(ds::sys::exists(subdir_path))
		{
			if(ds::sys::get_type(subdir_path) != ds::sys::type::dir)
				remove(subdir_path);
		}
		else
			ds::sys::mkdirs(subdir_path);
		AssertTrue(ds::sys::exists(subdir_path));
		AssertEQ(ds::sys::get_type(subdir_path), ds::sys::type::dir);
		ExpectEQ(ds::sys::rmdir(dir_path), ds::sys::srmdir::not_empty);
		ExpectTrue(ds::sys::exists(subdir_path));

	} TestcaseEnd(test_rmdir_not_empty);

	Testcase(test_rmdir_invalid_path)
	{
		char _max_path[ds::sys::max_path+2] = {};
		for(auto & e : _max_path)
			e = 'e';
		_max_path[ds::sys::max_path+1] = '\0';
		ExpectEQ(ds::sys::rmdir(nullptr), ds::sys::srmdir::invalid_path);
		ExpectEQ(ds::sys::rmdir(invalid_path), ds::sys::srmdir::invalid_path);
		ExpectEQ(ds::sys::rmdir(""), ds::sys::srmdir::invalid_path);
		ExpectEQ(ds::sys::rmdir(_max_path), ds::sys::srmdir::name_too_long);

	} TestcaseEnd(test_rmdir_invalid_path);

	Testcase(test_rmdir)
	{
		constexpr char const * dir_path = WORKING_DIR"_test_rmdir";
		if(ds::sys::exists(dir_path))
		{
			if(ds::sys::get_type(dir_path) != ds::sys::type::dir)
				remove(dir_path);
		}
		else
			ds::sys::mkdir(dir_path);
		AssertTrue(ds::sys::exists(dir_path));
		AssertEQ(ds::sys::get_type(dir_path), ds::sys::type::dir);
		ExpectEQ(ds::sys::rmdir(dir_path), ds::sys::srmdir::ok);
		ExpectFalse(ds::sys::exists(dir_path));

	} TestcaseEnd(test_rmdir);

	Testcase(test_mkfile_non_existing)
	{
		constexpr char const * file_path = WORKING_DIR"_test_mkfile.txt";
		if(ds::sys::exists(file_path))
		{
			if(ds::sys::get_type(file_path) == ds::sys::type::dir)
				ds::sys::rmdir(file_path);
			else
				remove(file_path);
		}
		AssertFalse(ds::sys::exists(file_path));
		ExpectEQ(ds::sys::mkfile(file_path), ds::sys::smkfile::ok);
		AssertEQ(ds::sys::get_type(file_path), ds::sys::type::regular_file);

	} TestcaseEnd(test_mkfile_non_existing);

	Testcase(test_mkfile_existing)
	{
		ExpectEQ(ds::sys::mkfile(existing_dir_path), ds::sys::smkfile::dir_exists);
		ExpectEQ(ds::sys::mkfile(existing_file_path), ds::sys::smkfile::regular_file_exists);

	} TestcaseEnd(test_mkfile_existing);

	Testcase(test_mkfile_invalid_path)
	{
		char _max_path[ds::sys::max_path+2] = {};
		for(auto & e : _max_path)
			e = 'e';
		_max_path[ds::sys::max_path+1] = '\0';
		ExpectEQ(ds::sys::mkfile(nullptr), ds::sys::smkfile::invalid_path);
		ExpectEQ(ds::sys::mkfile(invalid_path), ds::sys::smkfile::invalid_path);
		ExpectEQ(ds::sys::mkfile(""), ds::sys::smkfile::invalid_path);
		ExpectEQ(ds::sys::mkfile(_max_path), ds::sys::smkfile::name_too_long);

	} TestcaseEnd(test_mkfile_invalid_path);

	Testcase(test_rmfile_existing)
	{
		constexpr char const * file_path = WORKING_DIR"_test_rmfile.txt";
		if(ds::sys::exists(file_path))
		{
			if(ds::sys::get_type(file_path) == ds::sys::type::dir)
			{
				ds::sys::rmdir(file_path);
				ds::sys::mkfile(file_path);
			}
		}
		else
			ds::sys::mkfile(file_path);
		AssertTrue(ds::sys::exists(file_path));
		AssertEQ(ds::sys::get_type(file_path), ds::sys::type::regular_file);
		ExpectEQ(ds::sys::rmfile(file_path), ds::sys::srmfile::ok);
		AssertFalse(ds::sys::exists(file_path));

	} TestcaseEnd(test_rmfile_existing);

	Testcase(test_rmfile_non_existing)
	{
		ExpectEQ(ds::sys::rmfile(WORKING_DIR"_inexistent_file.txt"), ds::sys::srmfile::file_not_found);

	} TestcaseEnd(test_rmfile_non_existing);

	Testcase(test_rmfile_invalid_path)
	{
		char _max_path[ds::sys::max_path+2] = {};
		for(auto & e : _max_path)
			e = 'e';
		_max_path[ds::sys::max_path+1] = '\0';
		ExpectEQ(ds::sys::rmfile(nullptr), ds::sys::srmfile::invalid_path);
		ExpectEQ(ds::sys::rmfile(invalid_path), ds::sys::srmfile::invalid_path);
		ExpectEQ(ds::sys::rmfile(""), ds::sys::srmfile::invalid_path);
		ExpectEQ(ds::sys::rmfile(_max_path), ds::sys::srmfile::name_too_long);

	} TestcaseEnd(test_rmfile_invalid_path);


};

TestRegistry(sys_test)
{
	Register(test_exists)
	Register(test_get_type)
	Register(test_is_dir)
	Register(test_is_file)
	Register(test_is_regular_file)
	Register(test_mkdir_non_existing)
	Register(test_mkdir_existing)
	Register(test_mkdir_invalid_path)
	Register(test_mkdirs_non_existing)
	Register(test_mkdirs_existing)
	Register(test_mkdirs_invalid_path)
	Register(test_rmdir_not_empty)
	Register(test_rmdir_invalid_path)
	Register(test_rmdir)
	Register(test_mkfile_non_existing)
	Register(test_mkfile_existing)
	Register(test_mkfile_invalid_path)
	Register(test_rmfile_existing)
	Register(test_rmfile_non_existing)
	Register(test_rmfile_invalid_path)
};

template <class C>
using reporter_t = pptest::colored_printer<C>;

int main()
{
	return sys_test().run_all(reporter_t<sys_test>(pptest::normal));
}
