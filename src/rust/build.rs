use std::env;
use std::fs;

fn extract_project_name(cmake_lists_content: &str) -> Option<String> {
    let mut in_project = false;

    for line in cmake_lists_content.lines() {
        let line = line.trim();

        if line.starts_with("project(") {
            in_project = true;
        }

        if in_project && !line.starts_with("project(") {
            let name = line.split_whitespace().next()?.trim();

            if name != "LANGUAGES" && name != "VERSION" && name != "DESCRIPTION" {
                return Some(name.to_string());
            }
        }
    }

    None
}

fn main() {
    let cmake_lists =
        fs::read_to_string("../../CMakeLists.txt").expect("Failed to read CMakeLists.txt");
    let project_name = extract_project_name(&cmake_lists).unwrap_or("cxxbridge".into());
    let cpp_std = env::var("CONAN_CXX_STD").unwrap_or("23".into());

    cxx_build::bridge("src/lib.rs")
        .flag_if_supported(&format!("-std={}", cpp_std))
        .compile(&project_name);

    println!("cargo:rerun-if-changed=src/lib.rs");
}
