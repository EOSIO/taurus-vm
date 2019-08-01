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
using backend_t = backend<std::nullptr_t>;

TEST_CASE( "Testing wasm <memory_size_0_wasm>", "[memory_size_0_wasm_tests]" ) {
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "memory_size.0.wasm");
   backend_t bkend( code );
   bkend.set_wasm_allocator( &wa );
   bkend.initialize(nullptr);

   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(0));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(4)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(5));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(0)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(5));
}

TEST_CASE( "Testing wasm <memory_size_1_wasm>", "[memory_size_1_wasm_tests]" ) {
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "memory_size.1.wasm");
   backend_t bkend( code );
   bkend.set_wasm_allocator( &wa );
   bkend.initialize(nullptr);

   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(2));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(4)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(6));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(0)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(6));
}

TEST_CASE( "Testing wasm <memory_size_2_wasm>", "[memory_size_2_wasm_tests]" ) {
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "memory_size.2.wasm");
   backend_t bkend( code );
   bkend.set_wasm_allocator( &wa );
   bkend.initialize(nullptr);

   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(0));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(3)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(0));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(0)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(4)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(1));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(2));
}

TEST_CASE( "Testing wasm <memory_size_3_wasm>", "[memory_size_3_wasm_tests]" ) {
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "memory_size.3.wasm");
   backend_t bkend( code );
   bkend.set_wasm_allocator( &wa );
   bkend.initialize(nullptr);

   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(3));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(4));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(3)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(7));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(0)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(7));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(2)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(7));
   CHECK(!bkend.call_with_return(nullptr, "env", "grow", UINT32_C(1)));
   CHECK(bkend.call_with_return(nullptr, "env", "size")->to_ui32() == UINT32_C(8));
}

