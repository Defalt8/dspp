#include <ds/all>

ds::string_stream<> sst(1024);

int main()
{
	auto choices = ds::make_fixed<ds::string_view>("eat", "sleep", "do something else", "work a little", "read something");
	auto i = ds::random<int>(int(time(0))).next_range(0, choices.size());
	sst << choices[i] << ds::endl;
}
