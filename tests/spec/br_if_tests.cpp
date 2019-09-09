#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <catch2/catch.hpp>
#include <utils.hpp>
#include <wasm_config.hpp>
#include <eosio/vm/backend.hpp>

using namespace eosio;
using namespace eosio::vm;
extern wasm_allocator wa;

BACKEND_TEST_CASE( "Testing wasm <br_if_0_wasm>", "[br_if_0_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "br_if.0.wasm");
   backend_t bkend( code );
   bkend.set_wasm_allocator( &wa );
   bkend.initialize(nullptr);

   CHECK(!bkend.call_with_return(nullptr, "env", "type-i32"));
   CHECK(!bkend.call_with_return(nullptr, "env", "type-i64"));
   CHECK(!bkend.call_with_return(nullptr, "env", "type-f32"));
   CHECK(!bkend.call_with_return(nullptr, "env", "type-f64"));
   CHECK(bkend.call_with_return(nullptr, "env", "type-i32-value")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "type-i64-value")->to_ui64() == UINT32_C(2));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "type-f32-value")->to_f32()) == UINT32_C(1077936128));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "type-f64-value")->to_f64()) == UINT64_C(4616189618054758400));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-first", UINT32_C(0))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-first", UINT32_C(1))->to_ui32() == UINT32_C(3));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-mid", UINT32_C(0))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-mid", UINT32_C(1))->to_ui32() == UINT32_C(3));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-block-last", UINT32_C(0)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-block-last", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-first-value", UINT32_C(0))->to_ui32() == UINT32_C(11));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-first-value", UINT32_C(1))->to_ui32() == UINT32_C(10));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-mid-value", UINT32_C(0))->to_ui32() == UINT32_C(21));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-mid-value", UINT32_C(1))->to_ui32() == UINT32_C(20));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-last-value", UINT32_C(0))->to_ui32() == UINT32_C(11));
   CHECK(bkend.call_with_return(nullptr, "env", "as-block-last-value", UINT32_C(1))->to_ui32() == UINT32_C(11));
   CHECK(bkend.call_with_return(nullptr, "env", "as-loop-first", UINT32_C(0))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "as-loop-first", UINT32_C(1))->to_ui32() == UINT32_C(3));
   CHECK(bkend.call_with_return(nullptr, "env", "as-loop-mid", UINT32_C(0))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "as-loop-mid", UINT32_C(1))->to_ui32() == UINT32_C(4));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-loop-last", UINT32_C(0)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-loop-last", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "as-br-value")->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-br_if-cond"));
   CHECK(bkend.call_with_return(nullptr, "env", "as-br_if-value")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-br_if-value-cond", UINT32_C(0))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "as-br_if-value-cond", UINT32_C(1))->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-br_table-index"));
   CHECK(bkend.call_with_return(nullptr, "env", "as-br_table-value")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-br_table-value-index")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-return-value")->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-if-cond", UINT32_C(0))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "as-if-cond", UINT32_C(1))->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-then", UINT32_C(0), UINT32_C(0)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-then", UINT32_C(4), UINT32_C(0)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-then", UINT32_C(0), UINT32_C(1)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-then", UINT32_C(4), UINT32_C(1)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-else", UINT32_C(0), UINT32_C(0)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-else", UINT32_C(3), UINT32_C(0)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-else", UINT32_C(0), UINT32_C(1)));
   CHECK(!bkend.call_with_return(nullptr, "env", "as-if-else", UINT32_C(3), UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "as-select-first", UINT32_C(0))->to_ui32() == UINT32_C(3));
   CHECK(bkend.call_with_return(nullptr, "env", "as-select-first", UINT32_C(1))->to_ui32() == UINT32_C(3));
   CHECK(bkend.call_with_return(nullptr, "env", "as-select-second", UINT32_C(0))->to_ui32() == UINT32_C(3));
   CHECK(bkend.call_with_return(nullptr, "env", "as-select-second", UINT32_C(1))->to_ui32() == UINT32_C(3));
   CHECK(bkend.call_with_return(nullptr, "env", "as-select-cond")->to_ui32() == UINT32_C(3));
   CHECK(bkend.call_with_return(nullptr, "env", "as-call-first")->to_ui32() == UINT32_C(12));
   CHECK(bkend.call_with_return(nullptr, "env", "as-call-mid")->to_ui32() == UINT32_C(13));
   CHECK(bkend.call_with_return(nullptr, "env", "as-call-last")->to_ui32() == UINT32_C(14));
   CHECK(bkend.call_with_return(nullptr, "env", "as-call_indirect-func")->to_ui32() == UINT32_C(4));
   CHECK(bkend.call_with_return(nullptr, "env", "as-call_indirect-first")->to_ui32() == UINT32_C(4));
   CHECK(bkend.call_with_return(nullptr, "env", "as-call_indirect-mid")->to_ui32() == UINT32_C(4));
   CHECK(bkend.call_with_return(nullptr, "env", "as-call_indirect-last")->to_ui32() == UINT32_C(4));
   CHECK(bkend.call_with_return(nullptr, "env", "as-local.set-value", UINT32_C(0))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "as-local.set-value", UINT32_C(1))->to_ui32() == UINT32_C(17));
   CHECK(bkend.call_with_return(nullptr, "env", "as-local.tee-value", UINT32_C(0))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "as-local.tee-value", UINT32_C(1))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-global.set-value", UINT32_C(0))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "as-global.set-value", UINT32_C(1))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-load-address")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-loadN-address")->to_ui32() == UINT32_C(30));
   CHECK(bkend.call_with_return(nullptr, "env", "as-store-address")->to_ui32() == UINT32_C(30));
   CHECK(bkend.call_with_return(nullptr, "env", "as-store-value")->to_ui32() == UINT32_C(31));
   CHECK(bkend.call_with_return(nullptr, "env", "as-storeN-address")->to_ui32() == UINT32_C(32));
   CHECK(bkend.call_with_return(nullptr, "env", "as-storeN-value")->to_ui32() == UINT32_C(33));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "as-unary-operand")->to_f64()) == UINT64_C(4607182418800017408));
   CHECK(bkend.call_with_return(nullptr, "env", "as-binary-left")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-binary-right")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-test-operand")->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "as-compare-left")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-compare-right")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "as-memory.grow-size")->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-block-value", UINT32_C(0))->to_ui32() == UINT32_C(21));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-block-value", UINT32_C(1))->to_ui32() == UINT32_C(9));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br-value", UINT32_C(0))->to_ui32() == UINT32_C(5));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br-value", UINT32_C(1))->to_ui32() == UINT32_C(9));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_if-value", UINT32_C(0))->to_ui32() == UINT32_C(5));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_if-value", UINT32_C(1))->to_ui32() == UINT32_C(9));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_if-value-cond", UINT32_C(0))->to_ui32() == UINT32_C(5));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_if-value-cond", UINT32_C(1))->to_ui32() == UINT32_C(9));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_table-value", UINT32_C(0))->to_ui32() == UINT32_C(5));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_table-value", UINT32_C(1))->to_ui32() == UINT32_C(9));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_table-value-index", UINT32_C(0))->to_ui32() == UINT32_C(5));
   CHECK(bkend.call_with_return(nullptr, "env", "nested-br_table-value-index", UINT32_C(1))->to_ui32() == UINT32_C(9));
}
