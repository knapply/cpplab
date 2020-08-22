#include <knapply.hpp>


#include <benchmark/benchmark.h>


using namespace std::literals::string_view_literals;

std::string_view csv1 =
    R"(name,it,,erations,real_time,cpu_time,time_unit,bytes_per_second,items_perfffffffffffffffffffffffffffffffff_second,label,error_occurred,error_messageaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaname,it,,erations,real_time,cpu_time,time_unit,bytes_per_second)";

static void BM_split(benchmark::State& state) {
  for (auto _ : state)
    knapply::txt::split(csv1, ",,"sv);
}
BENCHMARK(BM_split);


static void BM_split_fixed1(benchmark::State& state) {
  for (auto _ : state)
    knapply::txt::split_fixed<19>(csv1, ",,"sv);
}
BENCHMARK(BM_split_fixed1);


BENCHMARK_MAIN();
