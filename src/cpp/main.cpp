#include <fstream>
#include <random>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "helpers.hpp"
#include "oxidize.hpp"
#include "types.hpp"
#include "version.hpp"

#include "lib.rs.h"

namespace {

auto get() -> Result< i32 >
{
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> distr( 1, 100 );
    i32 num{ distr( gen ) };

    if( num % 2 == 0 ) {
        return Err( "No number available!", Error::ErrorType::OverflowError );
    }

    return Ok( num );
}

}

auto main( int argc, char** argv ) -> int
{
    CLI::App app{ "My awesome CLI app" };

    bool debug{ false };
    app.add_flag( "-d,--debug", debug, "Enable debug mode" );

    std::string config{ "config.txt" };
    app.add_option( "-c,--config", config, "Path to the config file" );

    CLI11_PARSE( app, argc, argv );

    spdlog::level::level_enum log_level{ spdlog::level::info };

    if( debug ) {
        log_level = spdlog::level::debug;
    }

    std::ifstream file{ config };
    nlohmann::json json_config{};
    std::string app_name{};

    try {
        file >> json_config;
        app_name = json_config["app"]["name"].get< std::string >();
    }
    catch( nlohmann::json::exception const& err ) {
        SPDLOG_ERROR( "Error parsing config: {}", err.what() );
        return 1;
    }

    spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] [%s:%#] %v" );
    spdlog::set_level( log_level );
    SPDLOG_INFO( "Starting {} v{} ..", app_name, version::getVersionInfo() );

    if( auto val = get() ) {
        auto result = DBG( add_numbers( 2_kHz, 3 ) ) + DBG( val.value() );
    }
    else {
        SPDLOG_ERROR( val.error().to_string() );
    }

    SPDLOG_INFO( "Done." );
}
