{
  description = "Popup";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
        overlays = [];
        config.allowUnfree = true;
      };

        gcc14Stdenv = pkgs.overrideCC pkgs.stdenv pkgs.gcc14;
      in {
        devShells.default = pkgs.mkShell {
          stdenv = gcc14Stdenv;

          nativeBuildInputs = with pkgs; [
            go-task
            mold
            sccache
            conan
            cmake
            conan
            ninja
            python3
            gdb
            qt6.qtbase
            qt6.qttools
            qt6.wrapQtAppsHook
          ];

          shellHook = ''
            export IN_NIX_SHELL=1
          '';
        };

        packages.popup = gcc14Stdenv.mkDerivation {
          pname = "popup";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = with pkgs; [
            mold
            sccache
            cmake
            ninja
            qt6.qtbase
            qt6.wrapQtAppsHook
            qt6.qttools
            spdlog
            cli11
          ];

        buildInputs = with pkgs; [
          qt6.qtbase
        ];

          buildPhase = ''
            cmake -S $src -B $TMPDIR/build/Release -DCMAKE_BUILD_TYPE=Release
            cmake --build $TMPDIR/build/Release
          '';

        installPhase = ''
          cmake --install $TMPDIR/build/Release --prefix $out
        '';

          installPhase = ''
            cmake --install $TMPDIR/build/Release --prefix $out
          '';
        };

        apps.${system}.popup = {
          type = "app";
          program = "${self.packages.${system}.popup}/popup";
        };

        defaultPackage = self.packages.${system}.popup;
      });
}
