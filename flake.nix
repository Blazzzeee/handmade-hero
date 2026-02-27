{
  description = "Handmade Hero - Windows cross dev shell (clang clean)";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };

    cross = pkgs.pkgsCross.mingwW64;
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        # Clang from host
        pkgs.llvmPackages_latest.clang
        pkgs.llvmPackages_latest.lld
        cross.buildPackages.gdb

        # Proper mingw cross compiler (provides headers + crt + libs)
        cross.stdenv.cc

        # LSP / formatter
        pkgs.clang-tools
        pkgs.gdb

        # Optional
        pkgs.cmake
        pkgs.gnumake
        pkgs.wineWow64Packages.stable
      ];

      shellHook = ''
        echo "Windows cross dev shell ready."
        echo "GNU cross compiler: $(which x86_64-w64-mingw32-g++)"
        echo "Clang version: $(clang --version | head -n1)"
      '';
    };
  };
}
