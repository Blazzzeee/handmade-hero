{
  description = "Handmade Hero - Windows cross dev shell (clean)";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
    mingw = pkgs.pkgsCross.mingwW64;
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        # Windows cross compiler
        mingw.stdenv.cc

        # LSP
        pkgs.clang-tools   # clangd

        # Formatter
        pkgs.clang-tools   # clang-format

        # Build tools
        pkgs.cmake
        pkgs.gnumake

        # Optional testing
        pkgs.wineWow64Packages.stable
      ];

      shellHook = ''
        echo "Windows cross dev shell ready."
        echo "Compiler: $(which x86_64-w64-mingw32-g++)"
      '';
    };
  };
}
